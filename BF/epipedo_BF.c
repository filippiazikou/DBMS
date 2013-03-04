#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF_Lib.h"

int BF_errno;
int time;

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

/*It finds the number of the place in the array b where the block is going to be stored and it returns this number. It writes in the disc if it has to*/
int find_place(void)
{
	/*Declarations*/
	int bn = -1, i;
	FILE* fp_temp;
	/*Implementation*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].pinned == 0) {
			bn = i;
			break;
		}
	}
	/*if there is no place to pin a block return error*/
	if (bn == -1) {
		BF_errno = BFE_NOBUF;
		return BFE_NOBUF;
	}
	for (i = bn + 1 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].pinned == 0 && b[i].timestamp < b[bn].timestamp) bn = i;
	}
	/*Check if it's needed to write in the disc, and write if it is*/
	if (b[bn].dirty == 1 && b[bn].valid == 1) {
		fp_temp = fopen (b[bn].filename, "rb+");
		fseek(fp_temp, b[bn].BlN * BF_BLOCK_SIZE, SEEK_SET);
		fwrite(b[bn].data, sizeof(char), BF_BLOCK_SIZE, fp_temp);
		fflush(fp_temp);
		fclose(fp_temp);
	}
	if (b[bn].valid == 1) free(b[bn].filename);
	b[bn].valid = 0;
	b[bn].dirty = 0;
	return bn;
}

/*~*~*~FUNCTIONS~*~*~*/
/*Implementation of BF_Init function*/
void BF_Init (void)
{
	/*Declarations*/
	int i, j;
	/*Implementation*/
	/*array f of open files*/
	for (i = 0 ; i < MAXOPENFILES ; i++) {
		f[i].valid = 0;
		for (j = 0 ; j < BF_BUFFER_SIZE ; j++)
			f[i].pinned_blocks[j] = 0;
	}
	/*array b of blocks*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		b[i].pinned = 0;
		b[i].timestamp = 0;
		b[i].dirty = 0;
		b[i].valid = 0;
		b[i].BlN = 0;
	}
	time = 0;
}

/*Implementation of BF_CreateFile function*/
int BF_CreateFile (char *fileName)
{
	/*Definitions*/
	FILE *x;
	int i;
	char h[BF_BLOCK_SIZE];
	/*Implementation*/
	if (fopen(fileName, "rb") == NULL) {	//if file doesn't already exist
		x = fopen (fileName, "wb");	//create the file
		for (i = 0 ; i < BF_BLOCK_SIZE ; i++) {
			h[i] = 0;	//fill the header with zeros
		}
		fwrite (h, sizeof(char), BF_BLOCK_SIZE, x);
		fclose(x);	//close the file
		return BFE_OK;
	}
	/*if we cannot create the file return an error*/
	else {
		BF_errno = BFE_CANNOTCREATE;
		return BFE_CANNOTCREATE;
	}	
}

/*Implementation of BF_DestroyFile function*/
int BF_DestroyFile (char *fileName)
{
	/*Definitions*/
	int i;
	FILE *x;
	/*Implementation*/
	for (i = 0 ; i < MAXOPENFILES ; i++) {
		/*If the file is open return an error*/
		if (f[i].valid == 1 && strcmp (fileName, f[i].filename) == 0) {
			BF_errno = BFE_FILEOPEN;
			return BFE_FILEOPEN;
		}
	}
	x = fopen(fileName, "rb");
	/*If the filename given is wrong return error*/
	if (x == NULL) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	else {
		fclose (x);
		fopen (fileName, "wb");	//destroy all the contents of the file
		fclose (x);
		remove (fileName);	//delete the file
		return BFE_OK;
	}
}

/*Implementation of BF_OpenFile function*/
int BF_OpenFile(char *fileName)
{
	/*Definitions*/
	int filedesc = -1 ;
	int i, exists, flag = -1;
	/*Implementation*/
	/*Check if there is an available place in memory for files*/
	for (i = 0 ; i < MAXOPENFILES ; i++) {
		if (f[i].valid == 0) {
			filedesc = i;
			break;
		}
	}
	/*if there's not available place, return error*/
	if (filedesc == -1) {
		BF_errno = BFE_FTABFULL;
		return BFE_FTABFULL;
	}
	/*if the file is already open*/
	for (i = 0 ; i < MAXOPENFILES ; i++) {
		if (f[i].valid == 1 && strcmp(fileName, f[i].filename) == 0) {
			flag = i;	//the specific place where the file is already open
			i = MAXOPENFILES;
			BF_errno = BFE_FILEOPEN;
		}
	}
	f[filedesc].filename = malloc(strlen(fileName) * sizeof(char));
	strcpy(f[filedesc].filename , fileName);
	f[filedesc].fp = fopen(f[filedesc].filename, "rb+");
	/*if the file doesn't exist*/
	if (f[filedesc].fp == NULL) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	/*if the file isn't already open*/
	if (flag == -1) {
		f[filedesc].header = malloc(BF_BLOCK_SIZE * sizeof(char)) ;
		fread(f[filedesc].header, sizeof(char), BF_BLOCK_SIZE, f[filedesc].fp);
	}
	/*else if it's not open, we do not allocate memory for the header*/
	else {
		f[filedesc].header = f[flag].header ;
	}
	f[filedesc].valid = 1;
	return filedesc;
}

/*Implementation of BF_CloseFile function*/
int BF_CloseFile (int fileDesc)
{
	/* Declarations */
	int i, flag = 0;
	FILE  *fp_temp;
	/* Implementation */
	/* Check if the number of the file is correct and return error */
	if (fileDesc < 0 || fileDesc >= MAXOPENFILES || f[fileDesc].valid == 0) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	/* Check for pinned blocks */
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (f[fileDesc].pinned_blocks[i] != 0) {
			BF_errno = BFE_OS;
			return BFE_OS;
		}
	}
	/* Write in the disc */
	/* Write the header */
	fp_temp = fopen (f[fileDesc].filename, "rb+");
	if (fp_temp == NULL) {
		BF_errno = BFE_OS;
		return BFE_OS;
	}
	fseek(fp_temp, 0L, SEEK_SET);
	fwrite(f[fileDesc].header, sizeof(char), BF_BLOCK_SIZE, fp_temp);
	fflush(fp_temp);
	fclose(fp_temp);
	/*Write the blocks*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].dirty == 1 && b[i].valid == 1 && b[i].pinned == 0 && strcmp(b[i].filename , f[fileDesc].filename) == 0) {
			fp_temp = fopen (b[i].filename, "rb+");
			fseek(fp_temp, b[i].BlN * BF_BLOCK_SIZE, SEEK_SET);
			fwrite(b[i].data, sizeof(char), BF_BLOCK_SIZE, fp_temp);
			fflush(fp_temp);
			fclose(fp_temp);
			/* Clean struct */
			b[i].valid = 0;
			b[i].dirty = 0;
			free(b[i].filename);
		}
	}
	/* Close the file */
	if (fclose(f[fileDesc].fp) == 0) {
		for (i = 0 ;  i < MAXOPENFILES ; i++) {
			if (f[i].valid == 1 && strcmp(f[i].filename , f[fileDesc].filename) == 0)
				flag = 1;
		}
		if (flag == 0)  free(f[fileDesc].header);
		free(f[fileDesc].filename);
		f[fileDesc].valid = 0;
		return BFE_OK;
	}
	/*Cannot close the file*/
	else {
		BF_errno = BFE_OS;
		return BFE_OS;
	}
}

/*Implementation of BF_GetFirstBlock function*/
int BF_GetFirstBlock (int fileDesc, int *blockNum, char **blockBuf)
{
	/*Declarations*/
	int bn = -1;
	int i, j, counter = 0;
	int flag = 0, flag2 = 0;
	int bn_file;	//the first valid block in the file
	/*Implementation*/
	/*Check if the number of the file is correct and return error*/
	if (fileDesc < 0 || fileDesc >= MAXOPENFILES || f[fileDesc].valid == 0) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	/*Find in the header the first valid block (counter)*/
	for (i = 0 ; i < BF_BLOCK_SIZE ; i++) {
		for (j = 0 ; j < 8 ; j++) {
			if (is_bit_set(f[fileDesc].header[i], j) == 0)
				counter += 1;
			else {
				flag2 = 1;
				j = 8;
				i = BF_BLOCK_SIZE;
			}
		}
	}
	if (flag2 == 0) {
		BF_errno = BFE_INVALIDBLOCK;
		return BFE_INVALIDBLOCK;
	}
	/*Check if the block is already in the buffer*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].valid == 1 && strcmp(f[fileDesc].filename , b[i].filename) == 0 && b[i].BlN == counter + 1) {
			bn = i;
			flag = 1;
			BF_errno = BFE_BLOCKFIXED;
			break;
		}
	}
	/*if the block isn't already in the buffer*/
	if (bn == -1) {
		bn = find_place();	//call find place function
		/*if buffer is unavailable return error*/
		if (bn == BFE_NOBUF) {
			BF_errno = BFE_NOBUF;
			return BFE_NOBUF;
		}
		/*if buffer is available*/
		fseek(f[fileDesc].fp, (counter+1)*BF_BLOCK_SIZE, SEEK_SET);
		fread(b[bn].data, sizeof(char), BF_BLOCK_SIZE, f[fileDesc].fp);
		b[bn].BlN = counter + 1;
		b[bn].filename = malloc(strlen(f[fileDesc].filename) * sizeof(char));
		strcpy(b[bn].filename , f[fileDesc].filename);
	}
	if (f[fileDesc].pinned_blocks[bn] == 0) {
		b[bn].pinned += 1;
		f[fileDesc].pinned_blocks[bn] = b[bn].BlN;
	}
	b[bn].timestamp = time;
	time += 1;
	b[bn].valid = 1;
	*blockBuf = b[bn].data;
	*blockNum = b[bn].BlN - 1;
	return BFE_OK;
}

/*Implementation of BF_GetNextBlock function*/
int BF_GetNextBlock (int fileDesc, int *blockNum, char **blockBuf)
{
	int bn = -1;
	int i, j, k, counter = *blockNum + 1;
	int flag = 0, flag2 = 0;
	int bn_file;	//the first valid block in the file
	/*Implementation*/
	/*Check if the number of the file is correct and return error*/
	if (fileDesc < 0 || fileDesc >= MAXOPENFILES || f[fileDesc].valid == 0) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	/*Find in the header the first valid block (counter) after blockNum*/
	for (i = *blockNum/8 ; i < BF_BLOCK_SIZE ; i++) {
		if (i==*blockNum/8) k = ((*blockNum % 8) + 1);
		else k = 0;
		for (j = k ; j < 8 ; j++) {
			if (is_bit_set(f[fileDesc].header[i], j) == 0) 
				counter += 1;
			else {
				flag2 = 1;
				j = 8;
				i = BF_BLOCK_SIZE;
			}
		}
	}
	if (flag2 == 0) {
		BF_errno = BFE_INVALIDBLOCK;
		return BFE_INVALIDBLOCK;
	}
	/*Check if the block is already in the buffer*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].valid == 1 && strcmp(f[fileDesc].filename , b[i].filename) == 0 && b[i].BlN == counter + 1) {
			bn = i;
			flag = 1;
			BF_errno = BFE_BLOCKFIXED;
			break;
		}
	}
	/*if the block isn't already in the buffer*/
	if (bn == -1) {
		bn = find_place();	//call find place function
		/*if buffer is unavailable return error*/
		if (bn == BFE_NOBUF) {
			BF_errno = BFE_NOBUF;
			return BFE_NOBUF;
		}
		/*if buffer is available*/
		fseek(f[fileDesc].fp, (counter+1)*BF_BLOCK_SIZE, SEEK_SET);
		fread(b[bn].data, sizeof(char), BF_BLOCK_SIZE, f[fileDesc].fp);
		b[bn].BlN = counter + 1;
		b[bn].filename = malloc(strlen(f[fileDesc].filename) * sizeof(char));
		strcpy(b[bn].filename , f[fileDesc].filename);
	}
	if (f[fileDesc].pinned_blocks[bn] == 0) {
		b[bn].pinned += 1;
		f[fileDesc].pinned_blocks[bn] = b[bn].BlN;
	}
	b[bn].timestamp = time;
	time += 1;
	b[bn].valid = 1;
	*blockBuf = b[bn].data;
	*blockNum = b[bn].BlN - 1;
	return BFE_OK;
}

/*Implementation of BF_GetThisBlock function*/
int BF_GetThisBlock (int fileDesc, int blockNum, char **blockBuf)
{
	/*Declarations*/
	int bn = -1;
	int i, j, counter = 1;
	int flag = 0;
	int bn_file;	//the first valid block in the file
	/*Implementation*/
	/*Check if the number of the file is correct and return error*/
	if (fileDesc < 0 || fileDesc >= MAXOPENFILES || f[fileDesc].valid == 0) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	/*check if the current block is valid*/
	if (is_bit_set(f[fileDesc].header[blockNum/8], (blockNum % 8)) == 0) {
		BF_errno = BFE_INVALIDBLOCK;
		return BFE_INVALIDBLOCK;
	}
	/*Check if the block is already in the buffer*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].valid == 1 && strcmp(f[fileDesc].filename , b[i].filename) == 0 && b[i].BlN == blockNum + 1) {
			bn = i;
			flag = 1;
			BF_errno = BFE_BLOCKFIXED;
			break;
		}
	}
	/*if the block isn't already in a buffer*/
	if (bn == -1) {
		bn = find_place();	//call find place function
		/*if buffer is unavailable return error*/
		if (bn == BFE_NOBUF) {
			BF_errno = BFE_NOBUF;
			return BFE_NOBUF;
		}
		/*if buffer is available*/
		fseek(f[fileDesc].fp, (blockNum+1)*BF_BLOCK_SIZE, SEEK_SET);
		fread(b[bn].data, sizeof(char), BF_BLOCK_SIZE, f[fileDesc].fp);
		b[bn].BlN = blockNum + 1;
		b[bn].filename = malloc(strlen(f[fileDesc].filename) * sizeof(char));
		strcpy(b[bn].filename , f[fileDesc].filename);
	}
	if (f[fileDesc].pinned_blocks[bn] == 0) {
		b[bn].pinned += 1;
		f[fileDesc].pinned_blocks[bn] = b[bn].BlN;
	}
	b[bn].timestamp = time;
	time += 1;
	b[bn].valid = 1;
	*blockBuf = b[bn].data;
	return BFE_OK;
}

/*Implementation of BF_AllocBlock function*/
int BF_AllocBlock (int fileDesc, int *blockNum, char **blockBuf)
{
	/*Declarations*/
	unsigned int i;
	unsigned int counter = 0;
	int j, bn = -1;
	/*Implementation*/
	/*Check if the number of the file is correct and return error*/
	if (fileDesc < 0 || fileDesc >= MAXOPENFILES || f[fileDesc].valid == 0) {
		BF_errno = BFE_INVALIDBLOCK;
		return BFE_INVALIDBLOCK;
	}
	bn = find_place();
	if (bn == BFE_NOBUF) {
		BF_errno = BFE_NOBUF;
		return BFE_NOBUF;
	}
	/*change the header*/
	for (i = 0 ; i < BF_BLOCK_SIZE ; i++) {
		for (j = 0 ; j < 8 ; j++) {
			if (is_bit_set(f[fileDesc].header[i], j) == 0) {
				f[fileDesc].header[i] = set_bit(f[fileDesc].header[i], j);
				j = 8;
				i = BF_BLOCK_SIZE;
			}
			counter += 1;
		}
	}
	/*The file can have  only 8 * 1024 blocks, because we use only one block as a header. So it returns an error in an other case*/
	if (counter == (8 * BF_BLOCK_SIZE)) {
		BF_errno = BFE_TOOBIGFILE;
		return BFE_TOOBIGFILE;
	}
	b[bn].BlN = counter;
	for (i = 0 ; i < BF_BLOCK_SIZE ; i++) {
		b[bn].data[i] = 0;
	}
	b[bn].pinned = 1;
	b[bn].timestamp = time;
	time += 1;
	b[bn].dirty = TRUE;
	b[bn].valid = 1;
	b[bn].filename = malloc(strlen(f[fileDesc].filename) * sizeof(char));
	strcpy(b[bn].filename, f[fileDesc].filename);
	*blockNum = b[bn].BlN - 1;
	*blockBuf = b[bn].data;
	f[fileDesc].pinned_blocks[bn] = b[bn].BlN;
	return BFE_OK;
}

/*Implementation of BF_DisposeBlock function*/
int BF_DisposeBlock (int fileDesc, int *blockNum)
{
	/*Declarations*/
	int i, bn = -1;
	/*Implementation*/
	/*Check if the number of the file is correct and return error*/
	if (fileDesc < 0 || fileDesc >= MAXOPENFILES || f[fileDesc].valid == 0) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	/*find the block*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].valid == 1 && strcmp(b[i].filename, f[fileDesc].filename) == 0 && b[i].BlN == *blockNum + 1) {
			bn = i;
			break;
		}
	}
	/*check if the block is valid*/
	if (bn != -1 && b[bn].pinned != 0) {
		BF_errno = BFE_INVALIDBLOCK;
		return BFE_INVALIDBLOCK;
	}
	/*the block is unpinned but exists in the buffer*/
	if (bn != -1) {
		b[bn].valid = 0;
		b[bn].dirty = FALSE;
		free(b[bn].filename);
	}
	/*Set header's current value to zero*/
	f[fileDesc].header[*blockNum/8] = clear_bit(f[fileDesc].header[*blockNum/8], (*blockNum) % 8);
	return BFE_OK;
}

/*Implementation of BF_UnpinBlock function*/
int BF_UnpinBlock (int fileDesc, int blockNum, int dirty)
{
	/*Declarations*/
	int bn = -1, i;
	/*Implementation*/
	/*Check if the number of the file is correct and return error*/
	if (fileDesc < 0 || fileDesc >= MAXOPENFILES || f[fileDesc].valid == 0) {
		BF_errno = BFE_FD;
		return BFE_FD;
	}
	/*find the block*/
	for (i = 0 ; i < BF_BUFFER_SIZE ; i++) {
		if (b[i].valid==1 && strcmp(b[i].filename, f[fileDesc].filename) == 0 && b[i].BlN == blockNum + 1) {
			bn = i;
			break;
		}
	}
	/*check if the block is valid*/
	if (bn == -1) {
		BF_errno = BFE_INVALIDBLOCK;
		return BFE_INVALIDBLOCK;
	}
	if (b[bn].pinned == 0) {
			BF_errno = BFE_BLOCKUNFIXED;
			return BFE_BLOCKUNFIXED;
	}
	if (dirty == TRUE) b[bn].dirty = TRUE ;
	b[bn].pinned -= 1;
	f[fileDesc].pinned_blocks[bn] = 0;
}

/*Implementation of BF_PrintError function*/
void BF_PrintError (char *errString)
{
	/*print an error string*/
	fprintf(stderr, "%s\n", errString);
	/*print an error message for the last error that happened*/
	switch (BF_errno) {
		case BFE_NOMEM:
			fprintf(stderr, "No memory!\n");
			break;
		case BFE_NOBUF:
			fprintf(stderr, "No buffer!\n");
			break;
		case BFE_BLOCKFIXED:
			fprintf(stderr, "This block is already pinned in the memory!\n");
			break;
		case BFE_BLOCKNOTINBUF:
			fprintf(stderr, "The block you try to unpin is not pinned!\n");
			break;
		case BFE_BLOCKINBUF:
			fprintf(stderr, "The block is already in memory!\n");
			break;
		case BFE_OS:
			fprintf(stderr, "There is an error of the Operating System!\n");
			break;
		case BFE_INCOMPLETEREAD:
			fprintf(stderr, "The reading of the block was incomplete!\n");
			break;
		case BFE_INCOMPLETEWRITE:
			fprintf(stderr, "The writing in the block was incomplete!\n");
			break;
		case BFE_INCOMPLETEHDRREAD:
			fprintf(stderr, "The reading of the header was incomplete!\n");
			break;
		case BFE_INCOMPLETEHDRWRITE:
			fprintf(stderr, "The wiritng in the header was incomplete!\n");
			break;
		case BFE_INVALIDBLOCK:
			fprintf(stderr, "The number of the block is invalid!\n");
			break;
		case BFE_FILEOPEN:
			fprintf(stderr, "The file is already open!\n");
			break;
		case BFE_FTABFULL:
			fprintf(stderr, "The list of the open files is full!\n");
			break;
		case BFE_FD:
			fprintf(stderr, "The number of the file is invalid!\n");
			break;
		case BFE_EOF:
			fprintf(stderr, "You reached the end of the file!\n");
			break;
		case BFE_BLOCKFREE:
			fprintf(stderr, "The block is already free!\n");
			break;
		case BFE_BLOCKUNFIXED:
			fprintf(stderr, "The block is already unpinned!\n");
			break;
		case BFE_CANNOTCREATE:
			fprintf(stderr, "It's impossible to create a new file!\n");
			break;
		case BFE_TOOBIGFILE:
			fprintf(stderr, "The file can only have 1024 * 8 blocks!\n");
			break;
		default:
			fprintf(stderr, "No error!\n");
			break;
	}
}

