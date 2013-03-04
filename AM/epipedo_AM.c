#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "BF_Lib.h"
#include "AM_Lib.h"

int AM_errno;

/*~*~*~*~*~ JS Hash function ~*~*~*~*~*~*/
unsigned char JSHash(char* str, unsigned int len)
{
	unsigned int hash = 1315423911;
	unsigned int i = 0;

	for(i = 0; i < len; str++, i++) {
		hash ^= ((hash << 5) + (*str) + (hash >> 2));
	}

	return (unsigned char) hash;
}

/*~*~*~HELPING FUNCTIONS~*~*~*/
/*Check a specific bit of a char*/
char is_bit_set(char data,int n)
{
	return data&(1<<n);
}

/*Make 0 a specific bit of a char*/
char clear_bit(char data,int n)
{
	return data&(~(1<<n));
}

/*Make 1 a specific bit of a char*/
char set_bit(char data,int n)
{
	return data|(1<<n);
}


/* Imlementation of AM_Init function */
void AM_Init(void)
{
	int i;
	for (i = 0 ; i < MAXSCANS ; i++) {
		s[i].fileDesc = -1;	//-1 free place to enter scan
	}
	BF_Init();
}

/* Implementation of AM_CreateIndex function */
int AM_CreateIndex(char *fileName, int indexNo, char attrType, int attrLength)
{
	/*Declarations*/
	char *fileNameIndexNo;
	char *blockBuf;
	int i = strlen(fileName), open, fileDesc, blockNum;	//open = BF's fileDesc
	/*Implementation*/
	fileNameIndexNo = malloc ((strlen(fileName) + 3)*sizeof(char));	//allocate space to create the filename
	strcpy(fileNameIndexNo, fileName);	//copy the fileName
	fileNameIndexNo[i] = '.';	//put the dot
	sprintf(&fileNameIndexNo[i+1], "%d", indexNo);	//put the number after the dot
	/* return error */
	if (BF_CreateFile(fileNameIndexNo) != 0) {
		AM_errno = AME_BFERROR;
		return AME_BFERROR;
	}
	fileDesc = BF_OpenFile(fileNameIndexNo);
	/* return error */
	if (fileDesc < 0) {
		AM_errno = AME_OS;
		return AME_OS;
	}
	BF_AllocBlock (fileDesc, &blockNum, &blockBuf);
	for (i = 0 ; i < 1024 ; i++) blockBuf[i] = 0;	
	BF_UnpinBlock (fileDesc, blockNum, 1);
	BF_CloseFile (fileDesc);
	return AME_OK;
}

/* Implementation of AM_DestroyIndex function */
int AM_DestroyIndex(char *fileName, int indexNo)
{
	/* Declarations */
	char *fileNameIndexNo;
	int i = strlen(fileName);
	/* Implementation */
	fileNameIndexNo = malloc ((strlen(fileName) + 3)*sizeof(char));	//allocate space to create the filename
	strcpy(fileNameIndexNo, fileName);	//copy the fileName
	fileNameIndexNo[i] = '.';	//put the dot
	sprintf(&fileNameIndexNo[i+1], "%d", indexNo);	//put the number after the dot
	if (BF_DestroyFile(fileNameIndexNo) == 0)  return AME_OK;
	/* return error */
	else {
		AM_errno = AME_BFERROR;
		return AME_BFERROR;
	}
}

/* Implementation of AM_OpenIndex function */
int AM_OpenIndex(char *fileName, int indexNo)
{
	/*Declarations*/
	char *fileNameIndexNo;
	int i = strlen(fileName), open;	//open = BF's fileDesc
	/*Implementation*/
	fileNameIndexNo = malloc ((strlen(fileName) + 3)*sizeof(char));	//allocate space to create the filename
	strcpy(fileNameIndexNo, fileName);	//copy the fileName
	fileNameIndexNo[i] = '.';	//put the dot
	sprintf(&fileNameIndexNo[i+1], "%d", indexNo);	//put the number after the dot
	open = BF_OpenFile(fileNameIndexNo);
	if (open >= 0)  return open;
	/*return error*/
	else {
		AM_errno = AME_NOTOPEN;
		return AME_NOTOPEN;
	}
}

/* Implementation of AM_CloseIndex function */
int AM_CloseIndex(int fileDesc)
{
	/*Implementation*/
	if (BF_CloseFile(fileDesc) == 0) return AME_OK;
	/*return error*/
	else {
		AM_errno = AME_OS;
		return AME_OS;
	}
}

/* Implementation of AM_InsertEntry function */
int AM_InsertEntry(int fileDesc, char attrType, int attrLength, char *value, int recId)
{
	/*Declarations*/
	unsigned char hash;	//value of the hash function
	char *header;	//store the AM_header
	char *blockBuf;
	char *blockBuf2;
	char *value2;
	int recId2;
	short local_depth = 0;
	int headerNum, blockNum, blockNum2, i, j, k;
	unsigned int total_depth;
	int place = -1;	//the empty space for the record
	int first_place;	//the first place that points to the bucket
	int recNum = -1;
	int pointersNum;
	double totalrecNum;	//the number of records that can fit in a bucket
	double bitmapLength;	//the size of bitmap
	/*Implementation*/
	/* Separate different cases by attrType */
	/* Case of an integer */
	if (attrType == 'i') {
		hash = JSHash(value, sizeof(int));
	}
	/* Case of a float */
	else if (attrType == 'f') {
		hash = JSHash(value, sizeof(float));
	}
	/* Case of characters */
	else if (attrType == 'c') {
		hash = JSHash(value, attrLength);
	}
	/* wrong given attrType --> Return error */
	else {
		AM_errno = AME_TYPEERROR;
		return AM_errno;
	}
	/* return BF error */
	if (BF_GetFirstBlock(fileDesc, &headerNum, &header) != 0) {
		AM_errno = AME_BFERROR;
		return AME_BFERROR;
	}
	memcpy (&total_depth, header, sizeof(int));
	hash = hash >> (8-total_depth);	//find the important bits
	totalrecNum = floor(((1024-sizeof(short))*8)/((sizeof(int)+attrLength)*8+1) );	//number of records that can fit in the bucket
	bitmapLength = ceil(totalrecNum/8);	//find the size of bitmap
	/* case of zero buckets */
	if (header[sizeof(int)+0] == 0) {
		BF_AllocBlock (fileDesc, &blockNum, &blockBuf);	//allocate memory for a bucket
		header[sizeof(int)+0] = blockNum;
		blockBuf[1023] = set_bit(blockBuf[1023], 0);	//make 1 the 1st place of the reverse bitmap
		memcpy(&blockBuf[0], &local_depth, sizeof(short));	//write the local depth
		memcpy(&blockBuf[sizeof(short)+0], value, attrLength);	//write the value
		memcpy(&blockBuf[sizeof(short)+attrLength], &recId, sizeof(int));	//write the recId
		BF_UnpinBlock (fileDesc, blockNum, TRUE);	//unpin the bucket
		BF_UnpinBlock (fileDesc, headerNum, TRUE);	//unpin the AM_header
	}
	else {
		blockNum = header[sizeof(int)+hash];	//the result of hash + 4 bytes of the total_depth
		BF_GetThisBlock (fileDesc, blockNum, &blockBuf);
		memcpy(&local_depth, &blockBuf[0], sizeof(short));
		for (i = 0 ; i < totalrecNum ; i++) {
			if (is_bit_set(blockBuf[1023 - i/8], i%8) == 0) {
				blockBuf[1023 - i/8] = set_bit(blockBuf[1023 - i/8], i%8);
				place = i;
				break;
			}
		}
		/* there is some space in the bucket for the new record */
		if (place != -1) {
			memcpy(&blockBuf[place*(attrLength+sizeof(int))+sizeof(short)], value, attrLength);	//write the value
			memcpy(&blockBuf[place*(attrLength+sizeof(int))+sizeof(short)+attrLength], &recId, sizeof(int));	//write the recId
			BF_UnpinBlock (fileDesc, blockNum, TRUE);	//unpin the bucket
			BF_UnpinBlock (fileDesc, headerNum, FALSE);	//unpin the AM_header
		}
		/* the bucket is full, but we don't need to dublicate the array of cells */
		else if (local_depth < total_depth) {
			pointersNum = pow(2, total_depth - local_depth);	//find the number of cells that point to the bucket we need
			BF_AllocBlock (fileDesc, &blockNum2, &blockBuf2);
			local_depth += 1;	//raise the local depth
			memcpy(&blockBuf2[0], &local_depth, sizeof(short));	//write the local depth to the new bucket
			memcpy(&blockBuf[0], &local_depth, sizeof(short));	//write the new local depth to the bucket
			//eyresi tis prwtis thesis pou deixnei ston idio kado
			first_place = sizeof(int) + hash;
			while (header[first_place] == blockNum) first_place -= 1;
			for (i = first_place + pointersNum/2 + 1 ; i <= first_place + pointersNum ; i++)
				header[i] = blockNum2;
			/* seperate the records */
			for (i = 1023 ; i > 1023-bitmapLength ; i--) blockBuf[i] = 0; //set bitmap to zero
			/* Recursion to put one by one the records */
			for (i = sizeof(short) ; i < (1023 - bitmapLength) ; i += (attrLength + sizeof(int)) ) {
				value2 = malloc(attrLength*sizeof(char));
				memcpy(value2 , &blockBuf[i], attrLength);
			//	memset(value2, 0, attrLength);
				memcpy(&recId2, &blockBuf[i+attrLength], sizeof(int));
				AM_InsertEntry(fileDesc, attrType, attrLength, value2, recId2);
				free(value2);
			}
			AM_InsertEntry(fileDesc, attrType, attrLength, value, recId);
			/* Remove the records that were copied to the other bucket */
			for (i = 0 ; i < totalrecNum ; i++) {
				if (is_bit_set(blockBuf[1023 - i/8], i%8) == 0) {
					place = i;
					for (k = place + sizeof(int) ; k < (place + sizeof(int) + attrLength) ; k++)
							blockBuf[k] = 0;	//set all the bytes to zero
					break;
				}
			}
			BF_UnpinBlock (fileDesc, blockNum, TRUE);
			BF_UnpinBlock (fileDesc, blockNum2, TRUE);
			BF_UnpinBlock (fileDesc, headerNum, TRUE);	//unpin the AM_header
		}
		/* the bucket is full and we do need to dublicate the array of cells */
		else if (local_depth == total_depth) {
			/* move the records to new bucket */
			for (i = sizeof(int)+pow(2, total_depth+1)-1 ; i > sizeof(int) ; i--)
				header[i] = header[(i-sizeof(int))/2+sizeof(int)];
			total_depth += 1;	//augment the total depth value
			memcpy (header, &total_depth, sizeof(int));	//write the new total depth in AM header
			BF_UnpinBlock (fileDesc, blockNum, TRUE);
			BF_UnpinBlock (fileDesc, headerNum, TRUE);	//unpin the AM_header
			AM_InsertEntry(fileDesc, attrType, attrLength, value, recId);
		}
	}
	return AME_OK;
}

/* Implementation of AM_DeleteEntry function */
int AM_DeleteEntry (int fileDesc, char attrType, int attrLength, char *value, int recId)
{
	/*Declarations*/
	char *blockBuf;
	char *header;
	char clear_chars = 0;
	char flag = 0;
	unsigned char hash;
	int blockNum, headerNum;
	int i, place, counter = 0;
	unsigned int total_depth;
	int clear_ints = 0;
	float clear_floats = 0;
	double totalrecNum;	//the number of records that can fit in a bucket
	double bitmapLength;	//the size of bitmap
	/*Implementation*/
	if (BF_GetFirstBlock(fileDesc, &headerNum, &header) != 0) {
		AM_errno = AME_BFERROR;
		return AME_BFERROR;
	}
	if (attrType == 'i') {
		hash = JSHash(value, sizeof(int));
	}
	/* Case of a float */
	else if (attrType == 'f') {
		hash = JSHash(value, sizeof(float));
	}
	/* Case of characters */
	else if (attrType == 'c') {
		hash = JSHash(value, attrLength);
	}
	/* wrong given attrType --> Return error */
	else {
		AM_errno = AME_TYPEERROR;
		return AM_errno;
	}
	memcpy (&total_depth, header, sizeof(int));
	hash = hash >> (8-total_depth);	//find the important bits
	if (header[hash + sizeof(int)] == 0) {
		AM_errno = AME_OS;
		return AM_errno;
	}
	blockNum = header[hash + sizeof(int)];
	if (BF_GetThisBlock (fileDesc, blockNum, &blockBuf) != 0) {
		AM_errno = AME_BFERROR;
		return AME_BFERROR;
	}
	/* Wrong recId given --> return error */
	if (recId < 1) {
		AM_errno = AME_RECID;
		return AM_errno;
	}
	totalrecNum = floor( ((1024-sizeof(short))*8)/((sizeof(int)+attrLength)*8+1) );
	bitmapLength = ceil(totalrecNum/8);	//find the size of bitmap
	for (i = sizeof(short)+attrLength ; i < 1023-bitmapLength ; i += attrLength+sizeof(int)) {
		counter += 1;		
		if (memcmp(value, &blockBuf[i], sizeof(int)) == 0) {
			place = i;
			flag = 1;
			i = 1023-bitmapLength;
		}
	}
	if (flag == 0) {
		AM_errno = AME_RECID;
		return AM_errno;
	}
	/* Separate different cases by attrType */
	/* Case of an integer */
	if (attrType == 'i') {
		memcpy (&blockBuf[place], &clear_ints, sizeof(int));
		blockBuf[1023-((counter-1)/8)] = clear_bit(blockBuf[1023-((counter-1)/8)], (counter-1)%8);
	}
	/* Case of a float */
	else if (attrType == 'f') {
		memcpy (&blockBuf[place], &clear_floats, sizeof(float));
		blockBuf[1023-((counter-1)/8)] = clear_bit(blockBuf[1023-((counter-1)/8)], (counter-1)%8);
	}
	/* Case of characters */
	else if (attrType == 'c') {
		memcpy (&blockBuf[place], &clear_chars, attrLength);
		blockBuf[1023-((counter-1)/8)] = clear_bit(blockBuf[1023-((counter-1)/8)], (counter-1)%8);
	}
	/* wrong given attrType --> Return error */
	else {
		AM_errno = AME_TYPEERROR;
		return AM_errno;
	}
	return AME_OK;
}

/* Implementation of AM_OpenIndexScan function */
int AM_OpenIndexScan (int fileDesc, char attrType, int attrLength, int op, char *value)
{
	/* Declarations */
	int i, scanDesc = -1;
	/* Implementation */
	for (i = 0 ; i < MAXSCANS ; i++) {
		if (s[i].fileDesc == -1) {
			scanDesc = i;
			i = MAXSCANS;
		}
	}
	if (scanDesc == -1) {
		AM_errno = AME_SCANERROR;
		return AM_errno;
	}
	s[scanDesc].fileDesc = fileDesc;
	s[scanDesc].op = op;
	s[scanDesc].record = 0;
	s[scanDesc].hashNum = sizeof(int);
	s[scanDesc].attrType = attrType;
	s[scanDesc].attrLength = attrLength;
	s[scanDesc].max_recs = floor( ((1024-sizeof(short))*8)/((sizeof(int)+attrLength)*8+1) );
	/* Copy the value */
	/* Separate different cases by attrType */
	/* Case of an integer */
	if (value !=NULL) {
		if (attrType == 'i') {
			s[scanDesc].value = malloc (sizeof(int));
			memcpy(s[scanDesc].value, value, sizeof(int));
		}
		/* Case of a float */
		else if (attrType == 'f') {
			s[scanDesc].value = malloc (sizeof(float));
			memcpy(s[scanDesc].value, value, sizeof(float));
		}
		/* Case of characters */
		else if (attrType == 'c') {
			s[scanDesc].value = malloc ((strlen(value)+1)*sizeof(char));
			memcpy(s[scanDesc].value, value, strlen(value)+1);
		}
		/* wrong given attrType --> Return error */
		else {
			AM_errno = AME_TYPEERROR;
			return AM_errno;
		}
	}
	else s[scanDesc].value = NULL;
	return scanDesc;
}

/* Implementation of AM_FindNextEntry function */
int AM_FindNextEntry (int scanDesc)
{
	/* Declarations */
	char *header;
	char *blockBuf;
	char hash;
	int headerNum, blockNum, total_depth;
	int flag = 0;
	int recId;
	int i = s[scanDesc].hashNum;
	/* Implementation */
	if (BF_GetFirstBlock(s[scanDesc].fileDesc, &headerNum, &header) != 0) {
		AM_errno = AME_BFERROR;
		return AME_BFERROR;
	}
	/* check if there are more than one cell pointing in the same bucket */
	while ((i < 1024) && header[i] == header[i+1]) {
		 i += 1;
		flag = 1;
	}
	//na svistoun oi katw grammes
	//an mpike sti while to i na deixnei stin teleytaia thesi tou pinaka pou theloume to block
	//if (flag == 1) i -= 1;
	//flag = 0;
	s[scanDesc].hashNum = i;
	/* there are no more buckets to search */
	if (i == 1024 || header[i] == 0) {
		AM_errno = AME_EOF;
		return AM_errno;
	}
	
	/* case of all the records */
	if (s[scanDesc].value == NULL) {
		//pairnoume sti mnimi to block pou prepei na psaksoume
		blockNum = header[i];
		if (BF_GetThisBlock (s[scanDesc].fileDesc, blockNum, &blockBuf) != 0) {
			//kai unpin?
			AM_errno = AME_BFERROR;
			return AM_errno;
		}
		while (flag == 0) {
			s[scanDesc].record += 1;
			//elegxos an ksepernaei to orio eggrafwn / kado
			if (s[scanDesc].record > s[scanDesc].max_recs) {
				s[scanDesc].hashNum += 1;
				s[scanDesc].record = 0;
				BF_UnpinBlock (s[scanDesc].fileDesc, blockNum, 0);
				BF_UnpinBlock (s[scanDesc].fileDesc, headerNum, 0);
				return AM_FindNextEntry(scanDesc);
			}
			/* check if the records is valid */
			if (is_bit_set(blockBuf[1023 - (s[scanDesc].record - 1)/8] , (s[scanDesc].record - 1)%8 ) == 1) flag = 1;
		}
		memcpy(&recId, &blockBuf[sizeof(int) + s[scanDesc].record-1 + s[scanDesc].attrLength], sizeof(int));
		BF_UnpinBlock (s[scanDesc].fileDesc, blockNum, 0);
		BF_UnpinBlock (s[scanDesc].fileDesc, headerNum, 0);
		return recId;
	}
	/* case of EQUAL */
	else if (s[scanDesc].op == 1) {
		/* Case of an int */
		if (s[scanDesc].attrType == 'i') {
			hash = JSHash(s[scanDesc].value, sizeof(int));
		}
		/* Case of a float */
		else if (s[scanDesc].attrType == 'f') {
			hash = JSHash(s[scanDesc].value, sizeof(float));
		}
		/* Case of characters */
		else if (s[scanDesc].attrType == 'c') {
			hash = JSHash(s[scanDesc].value, s[scanDesc].attrLength);
		}
		/* wrong given attrType --> Return error */
		else {
			AM_errno = AME_TYPEERROR;
			return AM_errno;
		}
		memcpy (&total_depth, header, sizeof(int));
		hash = hash >> (8-total_depth);	//find the important bits
		blockNum = header[sizeof(int)+hash];
		if (blockNum == 0) {
			AM_errno = AME_EOF;
			return AME_EOF;
			/*error kai unpin ?*/
		}
		if (BF_GetThisBlock (s[scanDesc].fileDesc, blockNum, &blockBuf) != 0) {
			//kai unpin?
			AM_errno = AME_BFERROR;
			return AM_errno;
		}
		while (flag == 0) {
			s[scanDesc].record += 1;
			//elegxos an ksepernaei to orio eggrafwn / kado
			if (s[scanDesc].record >= s[scanDesc].max_recs) {
				s[scanDesc].record = 0;
				BF_UnpinBlock (s[scanDesc].fileDesc, blockNum, 0);
				BF_UnpinBlock (s[scanDesc].fileDesc, headerNum, 0);
				return AME_EOF;
			}
			/* Check if the records is valid */
			if (is_bit_set(blockBuf[1023 - (s[scanDesc].record - 1)/8] ,(s[scanDesc].record - 1)%8 ) == 1) { 
				if (s[scanDesc].attrType == 'i' && memcmp(s[scanDesc].value, &blockBuf[sizeof(int) + s[scanDesc].record-1], sizeof(int)) == 0)
					flag = 1;
				else if (s[scanDesc].attrType == 'f' && memcmp(s[scanDesc].value, &blockBuf[sizeof(int) + s[scanDesc].record-1], sizeof(float)) == 0)
					flag = 1;
				else if (s[scanDesc].attrType == 'c' && memcmp(s[scanDesc].value, &blockBuf[sizeof(int) + s[scanDesc].record-1], strlen(s[scanDesc].value)) == 0)
					flag = 1;
			}
		}
		memcpy(&recId, &blockBuf[sizeof(int) + s[scanDesc].record-1 + s[scanDesc].attrLength], sizeof(int));
		BF_UnpinBlock (s[scanDesc].fileDesc, blockNum, 0);
		BF_UnpinBlock (s[scanDesc].fileDesc, headerNum, 0);
		return recId;
	}
	/* Case of NOT EQUAL */
	//elegxw ola ta buckets me memcmp ena xreazetai mono sto bucket pou dinei i hash function
	else if (s[scanDesc].op == 6) {
		blockNum = header[i];
		if (BF_GetThisBlock (s[scanDesc].fileDesc, blockNum, &blockBuf) != 0) {
			//kai unpin?
			AM_errno = AME_BFERROR;
			return AM_errno;
		}
		while (flag == 0) {
			s[scanDesc].record += 1;
			//elegxos an ksepernaei to orio eggrafwn / kado
			if (s[scanDesc].record > s[scanDesc].max_recs) {
				s[scanDesc].hashNum += 1;
				s[scanDesc].record = 0;
				BF_UnpinBlock (s[scanDesc].fileDesc, blockNum, 0);
				BF_UnpinBlock (s[scanDesc].fileDesc, headerNum, 0);
				return AM_FindNextEntry(scanDesc);
			}
			/* check if the record is valid */
			if (is_bit_set(blockBuf[1023 - (s[scanDesc].record - 1)/8] ,(s[scanDesc].record - 1)%8 ) == 1) {
				 if (s[scanDesc].attrType == 'i' && memcmp(s[scanDesc].value, &blockBuf[sizeof(int) + s[scanDesc].record-1], sizeof(int)) != 0)
					flag = 1;
				else if (s[scanDesc].attrType == 'f' && memcmp(s[scanDesc].value, &blockBuf[sizeof(int) + s[scanDesc].record-1], sizeof(float)) != 0)
					flag = 1;
				else if (s[scanDesc].attrType == 'c' && memcmp(s[scanDesc].value, &blockBuf[sizeof(int) + s[scanDesc].record-1], strlen(s[scanDesc].value)) != 0)
					flag = 1;
			}
		}
		memcpy(&recId, &blockBuf[sizeof(int) + s[scanDesc].record-1 + s[scanDesc].attrLength], sizeof(int));
		BF_UnpinBlock (s[scanDesc].fileDesc, blockNum, 0);
		BF_UnpinBlock (s[scanDesc].fileDesc, headerNum, 0);
		return recId;
	}
}

/* Implementation of AM_CloseIndexScan function */
int AM_CloseIndexScan (int scanDesc)
{
	/*Implementation*/
	if (scanDesc < 0 || scanDesc >= MAXSCANS || s[scanDesc].fileDesc == -1) {
		AM_errno = AME_SCANERROR;
		return AM_errno;
	}
	s[scanDesc].fileDesc = -1;
	free(s[scanDesc].value);
	return AME_OK;
}

/* Implementation of AM_PrintError function */
void AM_PrintError (char *errString)
{
	/* print the error string */
	fprintf(stderr, "%s\n", errString);
	/* print an error message for the last error that happened */
	switch (AM_errno) {
		case AME_BFERROR:
			BF_PrintError("The message of BF level error follows:\n");
		case AME_TYPEERROR:
			fprintf(stderr, "You can choose only between int ('i'), float ('f') and char ('c').\n");
		case AME_NOTOPEN:
			fprintf(stderr, "Cannot open the file.\n");
		case AME_OS:
			fprintf(stderr, "AM general error of the Operating System.\n");
		case AME_RECID:
			fprintf(stderr, "Wrong recId given.\n");
		case AME_SCANERROR: 
			fprintf(stderr, "Wrong scanDesc.\n");
		default:
			fprintf(stderr, "There are no errors! :)\n");
	}
}


/*~*~*~*~*~ MAIN ~*~*~*~*~*~*/
/*int main (void)
{
	int fileDesc;
	AM_CreateIndex("mpla", 1, 'c', 1);
	fileDesc = AM_OpenIndex("mpla", 1);
	AM_InsertEntry(fileDesc, 'c', 4, "sad", 1);
	AM_InsertEntry(fileDesc, 'c', 4, "hap", 2);
//	BF_PrintError("Edw einai i PrintError tou BF epipedou");
// 	AM_DestroyIndex("mpla", 1);
	AM_CloseIndex(fileDesc);
	return 0;
}*/

