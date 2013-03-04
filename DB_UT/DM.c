#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DB_Lib.h"
#include "DM_Lib.h"
#include "UT_Lib.h"
#include "HF_Lib.h"
#include "AM_Lib.h"
#include "BF_Lib.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HELPING FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* helping function for relCat - takes a pointer to struct and the name of the file, and it returns recId*/
int relCatFunction(relDesc *r, char *name)
{
	/* Declarations */
	int recId, scanDesc;
	char *record;

	/* Implementation */

	/* open a scanning or return error if necessary */
	scanDesc = HF_OpenFileScan(relCatFileDesc, sizeof(relDesc), 'c',MAXNAME, 0, 1, name);
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on relCatFunction.");
		return DME_HFERROR;
	}

	/* allocate memory for relCat */
	record = malloc(sizeof(relDesc));

	/* find next record */
	recId = HF_FindNextRec(scanDesc, record);
	memcpy(r, record, sizeof(relDesc));

	/* free allocated memory for relCat */
	free(record);

	/* Close the open scanning or return error if necessary */
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on relCatFunction.");
		return DME_HFERROR;
	}

	/* return record's id */
	return recId;
}


/* helping function for attrCat - takes a pointer to struct, to name of file, to name of field, and it returns recId*/
int attrCatFunction(attrDesc *a, char *nameFile, char *nameField)
{
	/* Declarations */
	int recId, scanDesc;
	char flag = 0;
	char *record;

	/* Implementation */

	/* Open a scanning for attrCat or return error if necessary */
	scanDesc = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c', strlen(nameFile), 0, 1, nameFile);
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on relCatFunction.");
		return DME_HFERROR;
	}

	/* allocate memory for attrCat */
	record = malloc(sizeof(attrDesc));
	while (flag == 0) {
		/* find next record or return error if necessary */
		recId = HF_FindNextRec(scanDesc, record);
		if (recId < 0) {
			fprintf(stderr, "Field not found! Filippia rocks!\n");
			return DME_ERROR;
		}
		memcpy(a, record, sizeof(attrDesc));
		/* compare the fields and change the flag if they are the same */
		if (strcmp(a->attrName, nameField) == 0) flag = 1;
	}

	/* free allocated memory for attrCat */
	free(record);

	/* Close the open scanning or return error if necessary */
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on relCatFunction.");
		return DME_HFERROR;
	}

	/* return record's id */
	return recId;
}


/* helping function check_add_substract called in functions DM_substract and DM_add */
int check_add_subtract(char *relName1, char *relName2)
{
	/* Declarations */
	relDesc r1, r2;	//r1 -> for data file, r2 -> for results file
	attrDesc a1, a2;
	int recId1, recId2, flag = 0, scanDesc1, scanDesc2;
	char *record1;
	char *record2;

	/* Implementation */
	/* check if fileNames are the same or return error if necessary */
	if (strcmp (relName1, relName2) == 0) {
		fprintf(stderr, "Error, the files cannot be the same!\n");
		return DME_ERROR;
	}

	/* Check if fields of files using structs r1 and r2 exist in relCat or return error if necessary */
	recId1 = relCatFunction(&r1, relName1);
	if (recId1 < 0) {
		fprintf(stderr, "Wrong file name 1 given in check_add_subtract!\n");
		return DME_ERROR;
	}
	recId2 = relCatFunction(&r2, relName2);
	if (recId2 < 0) {
		fprintf(stderr, "Wrong file name 2 given in check_add_subtract!\n");
		return DME_ERROR;
	}
	
	/* check if the fields of file are in the same row and have the same type and length, or return error if necessary */

	if (r1.attrCnt != r2.attrCnt) {
		fprintf(stderr, "The files don't have the same number of fields");
		return DME_ERROR;
	}

	/* open scanning for both files or return error if necessary */
	scanDesc1 = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c',strlen(r1.relName), 0, 1, r1.relName);
	scanDesc2 = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c',strlen(r2.relName), 0, 1, r2.relName);
	if (scanDesc1 < 0 || scanDesc2 < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on check_add_subtract.");
		return DME_HFERROR;
	}

	/* allocate memory for 2 buffers */
	record1 = malloc(sizeof(attrDesc));
	record2 = malloc(sizeof(attrDesc));
	while (flag == 0) {
		/* find next records for both files */
		recId1 = HF_FindNextRec(scanDesc1, record1);
		recId2 = HF_FindNextRec(scanDesc2, record2);
		if (recId1 < 0 || recId2 < 0) {
			flag = 1;
			break;
		}
		memcpy(&a1, record1, sizeof(attrDesc));
		memcpy(&a2, record2, sizeof(attrDesc));
		/* check the fields and return error if necessary */
		if (a1.offset != a2.offset || a1.attrLength != a2.attrLength || a1.attrType != a2.attrType) {
			HF_PrintError("Different fields of files in check_add_subtract.\n");
			return DME_HFERROR;
		}
	}

	/* free both allocated memory buffers */
	free(record1);
	free(record2);

	/* close both open scannings or return error if necessary */
	if (HF_CloseFileScan(scanDesc1) < 0 || HF_CloseFileScan(scanDesc2) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on check_add_subtract.\n");
		return DME_HFERROR;
	}

	return DME_OK;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DM FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Implementation of DM_select function */
int DM_select(int argc, char* argv[])
{
	/* Declarations */
	int N;
	char print, indexed = 0; //0 if we print in stdout, else 1 - 0 if there is an index for the field, else 1
	int condition;	//0 if "Where <condition>" exists, else the place in argv array where there is onoma-sxesis-epilogis 
	char *fileNameData;
	int fileDescResult, fileDescData, recId, AMfileDesc;
	int i;
	int rec = 0;
	int k, e;	//k is the place in argv array which is the 1st "onoma-provallomenou-pediou" kai e the last field
	int sumLength = 0;
	char *bufferData;
	char *bufferResult;
	char *buffer;
	int scanDesc;
	int eos = 0; //End Of Scan
	int pointer = 0;
	int printi, numberi;
	int op;
	float printfl, numberf;
	char *prints;
	char *value;
	relDesc rData, rResult; //rData -> file of Data, rR -> file of Results
	attrDesc a;

	/* Implementation */
	/* the argc is even */
	if (argc%2 == 0) {
		N = atoi (argv[1]);	//plithos-gnwrismatwn-ta-opoia-provalontai
		print = 0;	//print flag set to zero
		k = 3;

		/* allocate memory for Results */
		strcpy(rResult.relName, "temp");

		/* allocate memory for Data */
		fileNameData = malloc (strlen (argv[2]) + 1);
		strcpy (fileNameData, argv[2]);
		if (argc == 2 + 2*N) {
			condition = 0;
			e = argc -1;
		}
		else {
			condition = argc - 4;
			e = argc - 5;
		}
	}

	/* the argc is odd, so the field "onoma-sxesis-apotelesmatos" exists */
	else {
		N = atoi(argv[2]);	//plithos-gnwrismatwn-ta-opoia-provalontai
		print = 1;	//print flag set to one
		k = 4;
		strcpy(rResult.relName, argv[1]);
		fileNameData = malloc (strlen (argv[3]) + 1);
		strcpy (fileNameData, argv[3]);
		if (argc == 3 + 2*N) {
			condition = 0;
			e = argc -1;
		}
		else {
			condition = argc - 4;
			e = argc - 5;
		}
	}

	/* Find operator if it exists */
	if (condition != 0) {
		if (strcmp("=", argv[argc - 2]) == 0) op = EQUAL;
		else if (strcmp("<", argv[argc - 2]) == 0) op = LESS_THAN;
		else if (strcmp(">", argv[argc - 2]) == 0) op = GREATER_THAN;
		else if (strcmp("<=", argv[argc - 2]) == 0) op = LESS_THAN_OR_EQUAL;
		else if (strcmp(">=", argv[argc - 2]) == 0) op = GREATER_THAN_OR_EQUAL;
		else if (strcmp("!=", argv[argc - 2]) == 0) op = NOT_EQUAL;
		/* return error for wrong operator */
		else {
			fprintf(stderr, "Wrong op given!\n");
			return DME_ERROR;
		}
	}

	/* initialize struct r according to fileNameData */

	recId = relCatFunction(&rData, fileNameData);
	/*return error if necessary */
	if (recId < 0) {
		if (recId == HFE_EOF) {	// <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 8a meinei auto??
			fprintf(stderr, "Wrong file name given in DM_insert!\n");
			return DME_ERROR;
		}
		else
			fprintf(stderr, "Error in DM_insert!\n");
			return DME_ERROR;
	}

	/* open the file or return error if necessary */
	fileDescData = HF_OpenFile(rData.relName);
	if (fileDescData < 0) {
		HF_PrintError("Error in HF_OpenFile called on DM_select.");
		return DME_HFERROR;
	}	

	//me for apo k ews oso einai pairnoume ena ena ta pedia - apo attrcat vlepoume megethos kai an einai egira- kai prosthetoume se ena metriti kai meta malloc to bufferResult kata metriti

	rResult.indexCnt = 0 ; 
	rResult.relWidth = 0;
	rResult.attrCnt = 0;
	for (i = k ; i <= e ; i += 2) {
		if (attrCatFunction(&a, fileNameData, argv[i]) < 0) {
			fprintf(stderr, "Wrong field given!\n");
			return DME_ERROR;
		}
		else {
			rResult.attrCnt += 1;
			rResult.relWidth += a.attrLength;
		}
	}

	/* create and open file for inserting results or return error if necessary */
	if (HF_CreateFile(rResult.relName) < 0) {
		HF_PrintError("Error in HF_CreateFile called on DM_select.");
		return DME_HFERROR;
	}
	fileDescResult = HF_OpenFile(rResult.relName);
	if (fileDescResult < 0) {
		HF_PrintError("Error in HF_OpenFile called on DM_select.");
		return DME_HFERROR;
	}	

	/* allocate memory for 2 buffers */
	bufferData = malloc (rData.relWidth);
	bufferResult = malloc(rResult.relWidth);

	/* take the record of condition from attrCat , if it exists */
	if (condition != 0) {
		if (attrCatFunction(&a, argv[argc - 4], argv[argc - 3]) >= 0) {
			if (a.indexed == TRUE)
				indexed = 1;
			else
				indexed = 0;
			if (a.attrType == 'i') {
				value = malloc(sizeof(int));
				numberi = atoi(argv[argc - 1]);
				memcpy(value, &numberi, sizeof(int));
			}
			else if (a.attrType == 'f') {
				value = malloc(sizeof(float));
				numberf = atof(argv[argc - 1]);
				memcpy(value, (char *)&numberf, sizeof(float));
			}
			else {
				value = malloc(strlen(argv[argc - 1]) + 1);
				strcpy(value, argv[argc - 1]);
			}
		}
		else {
			fprintf(stderr, "Error in DM_select function!\n");
			return DME_ERROR;
		}
	}

	/* open scanning depending on cases of having an index or not and save first record */

	/* case of having both condition and index */
	if (condition != 0 && indexed == 1) {
		AMfileDesc = AM_OpenIndex(a.relName, a.indexNo);
		scanDesc = AM_OpenIndexScan(AMfileDesc, a.attrType, a.attrLength, op, value);
		recId = AM_FindNextEntry(scanDesc);
		if (recId < 0) eos = 1;
		if (eos != 1 && HF_GetThisRec(fileDescData, recId, bufferData, rData.relWidth) != HFE_OK) {
			HF_PrintError("Error in HF_GetThisRec used in DM_select!\n");
			return DME_HFERROR;
		}
	}
	/* case of not having condition */
	else if (condition == 0) {
		scanDesc = HF_OpenFileScan(fileDescData,rData.relWidth, 'c', 0, 0, 0, NULL);
		recId = HF_FindNextRec(scanDesc, bufferData);
		if (recId < 0) eos = 1;
	}
	/* case of not having index */
	else {
		scanDesc = HF_OpenFileScan(fileDescData, rData.relWidth, a.attrType, a.attrLength, a.offset, op, value);
		recId = HF_FindNextRec(scanDesc, bufferData);
		if (recId < 0) eos = 1;
	}

	/* take suitable fields in bufferresult and write in data file */
	while (eos == 0) {
		pointer = 0;
		for (i = k ; i <= e ; i += 2) {
			recId = attrCatFunction(&a, fileNameData, argv[i]);
			memcpy(&bufferResult[pointer], &bufferData[a.offset], a.attrLength);
			pointer += a.attrLength;
		}
		HF_InsertRec(fileDescResult, bufferResult, rResult.relWidth);
		if (condition != 0 && indexed == 1) {
			recId = AM_FindNextEntry(scanDesc);
			if (recId < 0) eos = 1;
			if (eos != 1 && HF_GetThisRec(fileDescData, recId, bufferData, rData.relWidth) != HFE_OK) {
				HF_PrintError("Error in HF_GetThisRec used in DM_select!\n");
				return DME_HFERROR;
			}
		}
		else {
			recId = HF_FindNextRec(scanDesc, bufferData);
			if (recId < 0) eos = 1;
		}
	}

	/* close indexes or scannings */
	if (condition != 0 && indexed == 1) AM_CloseIndexScan(scanDesc);
	else HF_CloseFileScan(scanDesc);

	/* cases of having result file */
	if (print == 0) {
		buffer = malloc(rResult.relWidth);
		scanDesc = HF_OpenFileScan(fileDescResult, rResult.relWidth, 'c', 0, 0, 0, NULL);
		recId = HF_FindNextRec(scanDesc, buffer);
		while (recId >= 0) {
			pointer = 0;
			for (i = k ; i <= e ; i += 2) {
				recId = attrCatFunction(&a, fileNameData, argv[i]);
				if (a.attrType == 'i') {
					memcpy(&printi, &buffer[pointer], sizeof(int));
					printf("%d\t", printi);
				}
				else if (a.attrType == 'f') {
					memcpy(&printfl, &buffer[pointer], sizeof(float));
					printf("%f\t", printfl);
				}
				else {
					prints = malloc(a.attrLength);
					memcpy(prints, &buffer[pointer], a.attrLength);
					if (strlen(prints) <= 7) {
						printf("%s\t\t\t", prints);
					}
					else if (strlen(prints) <= 15) {
						printf("%s\t\t", prints);
					}
					else {
						printf("%s\t", prints);
					}
					free(prints);
				}
				pointer += a.attrLength;
			}
			printf("\n");
			recId = HF_FindNextRec(scanDesc, buffer);
		}
		HF_CloseFileScan(scanDesc);
		free(buffer);
		HF_CloseFile(fileDescResult);
		HF_DestroyFile(rResult.relName);
	}
	else {
		/* update relCat */
		buffer = malloc (sizeof(relDesc));
		memcpy(buffer, &rResult, sizeof(relDesc));
		HF_InsertRec(relCatFileDesc, buffer, sizeof(relDesc));
		free(buffer);

		/* update attrCat */
		buffer = malloc (sizeof(attrDesc));
		pointer = 0;
		for (i = k ; i <= e ; i += 2) {
			recId = attrCatFunction(&a, fileNameData, argv[i]);
			strcpy(a.relName, rResult.relName);
			a.indexed = 0;
			a.indexNo = 0;
			a.offset = pointer;
			memcpy(buffer, &a, sizeof(attrDesc));
			HF_InsertRec(attrCatFileDesc, buffer, sizeof(attrDesc));
			pointer += a.attrLength;
		}
		/* free allocated buffer */
		free(buffer);

		/* close file of results */
		HF_CloseFile(fileDescResult);
	}

	/* close the file and free allocated memory */
	HF_CloseFile(fileDescData);
	free(fileNameData);
	if (condition !=0) free(value);
}


/* Implementation of DM_join function */
int DM_join(int argc, char* argv[])
{
	/* Declarations */
	int N;
	char print, indexed = 0; //0 if we print in stdout, else 1 - 0 if there is an index for the field, 1 if there is for the 1st and 2 for the 2nd
	int fileDescResult, fileDescData1, fileDescData2, AMfileDesc, recId, recId1, recId2;
	int i;
	int rec = 0;
	int k;	//place in argv where onoma-provalomenis-sxesis-1 exists
	int sumLength = 0;
	char *bufferData1;
	char *bufferData2;
	char *bufferResult;
	char *buffer;
	int offset;
	int scanDesc1, scanDesc2;
	int eosEx = 0, eosEs = 0;	//End Of Scan
	int pointer = 0;
	int printi;
	int op;
	float printfl;
	char *prints;
	relDesc rData1, rData2, rResult; //rData -> data files, rResult -> result file
	attrDesc aJoin1, aJoin2, a;	//aEx -> field for external node

	/* Implementation */
	/* the argc is even */
	if (argc%2 != 0) {
		N = atoi (argv[1]);	//plithos-gnwrismatwn-ta-opoia-provalontai
		print = 0;	//print flag set to zero
		k = 2;
		/* initialize file names in struct relDesc */
		strcpy(rResult.relName, "temp");
		
	}
	/* the argc is odd, so the field "onoma-sxesis-apotelesmatos" exists */
	else {
		N = atoi(argv[2]);	//plithos-gnwrismatwn-ta-opoia-provalontai
		print = 1;	//print flag set to one
		k = 3;
		strcpy(rResult.relName, argv[2 + 2*N]);
	}

	/* Initialize data files in struct relDesc */
	strcpy (rData1.relName, argv[argc-5]);
	strcpy (rData2.relName, argv[argc-2]);

	/* use helping function for relCat for both Data files or return error if necessary */
	recId = relCatFunction(&rData1, rData1.relName);
	if (recId < 0) {
		fprintf(stderr, "Wrong file name given in DM_join!\n");
		return DME_ERROR;
	}
	recId = relCatFunction(&rData2, rData2.relName);
	if (recId < 0) {
		fprintf(stderr, "Wrong file name given in DM_join!\n");
		return DME_ERROR;
	}

	/* Initialize struct attrDesc for fields of condition */
	
	recId = attrCatFunction(&aJoin1, rData1.relName, argv[argc-4]);
	if (recId < 0) {
		fprintf(stderr, "Wrong file name given in DM_join!\n");
		return DME_ERROR;
	}
	recId = attrCatFunction(&aJoin2, rData2.relName, argv[argc-1]);
	if (recId < 0) {
		fprintf(stderr, "Wrong file name given in DM_join!\n");
		return DME_ERROR;
	}

	/* check if the fields are of the same type and return error if necessary */

	if (aJoin1.attrType != aJoin2.attrType || aJoin1.attrLength != aJoin2.attrLength) {
		fprintf(stderr, "Error --> different type of fields!\n");
		return DME_ERROR;
	}

	/* Check if fields are correctly given and count fields for file */

	rResult.indexCnt = 0; 
	rResult.relWidth = 0;
	rResult.attrCnt = 0;
	for (i = k ; i <= (argc - 7) ; i += 2) {
		if (strcmp(argv[i], rData1.relName) != 0 && strcmp(argv[i], rData2.relName) != 0) {
			fprintf(stderr, "Wrong file Name.\n");
			return DME_ERROR;
		}
		if (attrCatFunction(&a, argv[i], argv[i+1]) < 0) {
			fprintf(stderr, "Wrong field given!\n");
			return DME_ERROR;
		}
		else {
			rResult.attrCnt += 1;
			rResult.relWidth += a.attrLength;
		}
	}

	/* Open all files, both Data files and result file */
		
	/* create and open result file for inserting the results or return errors if necessary */
	if (HF_CreateFile(rResult.relName) < 0) {
		HF_PrintError("Error in HF_CreateFile called on DM_select.");
		return DME_HFERROR;
	}
	fileDescResult = HF_OpenFile(rResult.relName);
	if (fileDescResult < 0) {
		HF_PrintError("Error in HF_OpenFile called on DM_select.");
		return DME_HFERROR;
	}

	/* open data files or return error if necessary */
	fileDescData1 = HF_OpenFile(rData1.relName);
	fileDescData2 = HF_OpenFile(rData2.relName);
	if (fileDescData1 < 0 || fileDescData2 < 0) {
		HF_PrintError("Error in HF_OpenFile called on DM_select.");
		return DME_HFERROR;
	}

	/* allocated memory buffers for all files */
	bufferData1 = malloc (rData1.relWidth);
	bufferData2 = malloc (rData2.relWidth);
	bufferResult = malloc(rResult.relWidth);

	/* Open external scanning */
	if (aJoin1.indexed == TRUE) {
		AMfileDesc = AM_OpenIndex (rData1.relName, aJoin1.indexNo);
		indexed = 1;
		scanDesc2 = HF_OpenFileScan(fileDescData2, rData2.relWidth, 'c', 0, 0, 0, NULL);
		if (scanDesc2 < 0) {
			HF_PrintError("Error in HF_OpenFileScan called on DM_join.");
			return DME_HFERROR;
		}
		recId2 = HF_FindNextRec(scanDesc2, bufferData2);
		if (recId2 < 0) eosEx = 1;
		/* Find operator */
		if (strcmp("=", argv[argc - 3]) == 0) op = EQUAL;
		else if (strcmp("<", argv[argc - 3]) == 0) op = LESS_THAN;
		else if (strcmp(">", argv[argc - 3]) == 0) op = GREATER_THAN;
		else if (strcmp("<=", argv[argc - 3]) == 0) op = LESS_THAN_OR_EQUAL;
		else if (strcmp(">=", argv[argc - 3]) == 0) op = GREATER_THAN_OR_EQUAL;
		else if (strcmp("!=", argv[argc - 3]) == 0) op = NOT_EQUAL;
		/* return error for wrong operator */
		else {
			fprintf(stderr, "Wrong op given!\n");
			return DME_ERROR;
		}
		
	}
	else if (aJoin2.indexed == TRUE) {
		AMfileDesc = AM_OpenIndex (rData2.relName, aJoin2.indexNo);
		indexed = 2;
		scanDesc1 = HF_OpenFileScan(fileDescData1, rData1.relWidth, 'c', 0, 0, 0, NULL);
		if (scanDesc1 < 0) {
			HF_PrintError("Error in HF_OpenFileScan called on DM_join.");
			return DME_HFERROR;
		}
		recId1 = HF_FindNextRec(scanDesc1, bufferData1);
		if (recId1 < 0) eosEx = 1;

		/* Find operator */
		if (strcmp("=", argv[argc - 3]) == 0) op = EQUAL;
		else if (strcmp("<", argv[argc - 3]) == 0) op = GREATER_THAN_OR_EQUAL;
		else if (strcmp(">", argv[argc - 3]) == 0) op = LESS_THAN_OR_EQUAL;
		else if (strcmp("<=", argv[argc - 3]) == 0) op = GREATER_THAN;
		else if (strcmp(">=", argv[argc - 3]) == 0) op = LESS_THAN;
		else if (strcmp("!=", argv[argc - 3]) == 0) op = NOT_EQUAL;
		/* return error for wrong operator */
		else {
			fprintf(stderr, "Wrong op given!\n");
			return DME_ERROR;
		}
	}
	else {
		scanDesc2 = HF_OpenFileScan(fileDescData2, rData2.relWidth, 'c', 0, 0, 0, NULL);
		if (scanDesc2 < 0) {
			HF_PrintError("Error in HF_OpenFileScan called on DM_join.");
			return DME_HFERROR;
		}
		recId2 = HF_FindNextRec(scanDesc2, bufferData2);
		if (recId2 < 0) eosEx = 1;
		/* Find operator */
		if (strcmp("=", argv[argc - 3]) == 0) op = EQUAL;
		else if (strcmp("<", argv[argc - 3]) == 0) op = LESS_THAN;
		else if (strcmp(">", argv[argc - 3]) == 0) op = GREATER_THAN;
		else if (strcmp("<=", argv[argc - 3]) == 0) op = LESS_THAN_OR_EQUAL;
		else if (strcmp(">=", argv[argc - 3]) == 0) op = GREATER_THAN_OR_EQUAL;
		else if (strcmp("!=", argv[argc - 3]) == 0) op = NOT_EQUAL;
		/* return error for wrong operator */
		else {
			fprintf(stderr, "Wrong op given!\n");
			return DME_ERROR;
		}
	}
	
	while (eosEx == 0) {
		/* open internal scanning */
		if (indexed == 0) {
			scanDesc1 = HF_OpenFileScan(fileDescData1, rData1.relWidth, aJoin1.attrType, aJoin1.attrLength, aJoin1.offset, op, &bufferData2[aJoin2.offset]);
			recId1 = HF_FindNextRec(scanDesc1, bufferData1);
			if (recId1 < 0) eosEs = 1;
		}
		else if (indexed == 1) {
			scanDesc1 = AM_OpenIndexScan(AMfileDesc, aJoin1.attrType, aJoin1.attrLength, op, &bufferData2[aJoin2.offset]);
			recId1 = AM_FindNextEntry(scanDesc1);
			if (recId1 < 0) eosEs = 1;
			else if (HF_GetThisRec(fileDescData1, recId1, bufferData1, rData1.relWidth) < 0) {
				HF_PrintError("Error in HF_GetThisRec called on DM_join.");
				return DME_HFERROR;
			}
		}
		else {
			scanDesc2 = AM_OpenIndexScan(AMfileDesc, aJoin2.attrType, aJoin2.attrLength, op, &bufferData1[aJoin1.offset]);
			recId2 = AM_FindNextEntry(scanDesc2);
			if (recId2 < 0) eosEs = 1;
			else if (HF_GetThisRec(fileDescData2, recId2, bufferData2, rData2.relWidth) < 0) {
				HF_PrintError("Error in HF_GetThisRec called on DM_join.");
				return DME_HFERROR;
			}
		}
		while (eosEs == 0) {
			/* take one by one all the fileds, put the in results buffer and put them in file */
			pointer = 0;
			for (i = k ; i <= (argc - 7) ; i += 2) {
				recId = attrCatFunction(&a, argv[i], argv[i+1]);
				if (strcmp(rData1.relName, argv[i]) == 0) 
					memcpy(&bufferResult[pointer], &bufferData1[a.offset], a.attrLength);
				else
					memcpy(&bufferResult[pointer], &bufferData2[a.offset], a.attrLength);
				pointer += a.attrLength;
			}
			HF_InsertRec(fileDescResult, bufferResult, rResult.relWidth);
			if (indexed == 0) {
				recId1 = HF_FindNextRec(scanDesc1, bufferData1);
				if (recId1 < 0) eosEs = 1;
			}
			else if (indexed == 1) {
				recId1 = AM_FindNextEntry(scanDesc1);
				if (recId1 < 0) eosEs = 1;
				else if (HF_GetThisRec(fileDescData1, recId1, bufferData1, rData1.relWidth) < 0) {
					HF_PrintError("Error in HF_GetThisRec called on DM_join.");
					return DME_HFERROR;
				}
			}
			else {
				recId2 = AM_FindNextEntry(scanDesc2);
				if (recId2 < 0) eosEs = 1;
				else if (HF_GetThisRec(fileDescData2, recId2, bufferData2, rData2.relWidth) < 0) {
					HF_PrintError("Error in HF_GetThisRec called on DM_join.");
					return DME_HFERROR;
				}
			}
		}
		/* close internal scanning and find next record by external scanning */
		if (indexed == 0) {
			HF_CloseFileScan(scanDesc1);
			recId2 = HF_FindNextRec(scanDesc2, bufferData2);
			if (recId2 < 0) eosEx = 1;
		}
		else if (indexed == 1) {
			AM_CloseIndexScan(scanDesc1);
			recId2 = HF_FindNextRec(scanDesc2, bufferData2);
			if (recId2 < 0) eosEx = 1;
		}
		else {
			AM_CloseIndexScan(scanDesc2);
			recId1 = HF_FindNextRec(scanDesc1, bufferData1);
			if (recId1 < 0) eosEx = 1;
		}
	}
	/* close external scanning */
	if (indexed == 2) HF_CloseFileScan(scanDesc1);
	else HF_CloseFileScan(scanDesc2);

	/* cases of having results file */
	if (print == 0) {
		buffer = malloc(rResult.relWidth);
		scanDesc1 = HF_OpenFileScan(fileDescResult, rResult.relWidth, 'c', 0, 0, 0, NULL);
		recId = HF_FindNextRec(scanDesc1, buffer);
		while (recId >= 0) {
			offset = 0;
			for (i = k ; i <= (argc - 7) ; i += 2) {
				recId = attrCatFunction(&a, argv[i], argv[i+1]);
				if (a.attrType == 'i') {
					memcpy(&printi, &buffer[offset], sizeof(int));
					printf("%d\t", printi);
				}
				else if (a.attrType == 'f') {
					memcpy(&printfl, &buffer[offset], sizeof(float));
					printf("%f\t", printfl);
				}
				else {
					prints = malloc(a.attrLength);
					memcpy(prints, &buffer[offset], a.attrLength);
					if (strlen(prints) <= 7) {
						printf("%s\t\t\t", prints);
					}
					else if (strlen(prints) <= 15) {
						printf("%s\t\t", prints);
					}
					else {
						printf("%s\t", prints);
					}
					free(prints);
				}
				offset += a.attrLength;
			}
			printf("\n");
			recId = HF_FindNextRec(scanDesc1, buffer);
		}
		HF_CloseFileScan(scanDesc1);
		free(buffer);
		HF_CloseFile(fileDescResult);
		HF_DestroyFile(rResult.relName);
	}
	else {
		/* update relCat */
		buffer = malloc (sizeof(relDesc));
		memcpy(buffer, &rResult, sizeof(relDesc));
		HF_InsertRec(relCatFileDesc, buffer, sizeof(relDesc));
		free(buffer);

		/* update attrCat */
		buffer = malloc (sizeof(attrDesc));
		a.offset = 0;
		for (i = k ; i <= argc - 7 ; i += 2) {
			recId = attrCatFunction(&a, argv[i], argv[i+1]);
			strcpy(a.relName, rResult.relName);
			a.indexed = 0;
			a.indexNo = 0;
			memcpy(buffer, &a, sizeof(attrDesc));
			HF_InsertRec(attrCatFileDesc, buffer, sizeof(attrDesc));
			a.offset += a.attrLength;
		}

		/* free allocated buffer */
		free(buffer);

		/* close file of results */
		HF_CloseFile(fileDescResult);
	}

	/* close both data files */
	HF_CloseFile(fileDescData1);
	HF_CloseFile(fileDescData2);
}


/* Implementation of DM_delete function */
int DM_delete(int argc, char* argv[])
{
	/* Declarations */
	relDesc r;
	attrDesc a; //a -> gia to pedio pou thelw ti sinthiki
	attrDesc tempa;	//tempa -> to see if a field has index
	char *record;
	char *value;
	char *temp_record;	//record gia to attrCat
	int recId, attrRecId, fileDesc, scanDesc, attrScanDesc, AMfileDesc, tempFileDesc;
	int condition;
	int op;
	int eos = 0, i;	//end of scan
	int numberi;
	float numberf;

	/* Implementation */

	/* Find in relCat the record we need and save it in struct */
	recId = relCatFunction(&r, argv[1]);
	if (recId < 0) {
		fprintf(stderr, "Wrong file name!\n");
		return DME_ERROR;
	}

	record = malloc(r.relWidth);

	/* check if the operands and the condition are correct */
	if (argc == 5) {
		condition = 1; 
	}
	else if (argc == 2) {
		condition = 0;
	}
	
	/* return error if necessary */
	else {
		fprintf(stderr, "Wrong operands!\n");
		return DME_ERROR;
	}

	fileDesc = HF_OpenFile(argv[1]);

	/* if condition exists take in a struct the info for the field for attrcat and find if there is an index or not */
	if (condition == 1) {
		/* Find the operator */
		if (strcmp("=", argv[3]) == 0) op = EQUAL;
		else if (strcmp("<", argv[3]) == 0) op = LESS_THAN;
		else if (strcmp(">", argv[3]) == 0) op = GREATER_THAN;
		else if (strcmp("<=", argv[3]) == 0) op = LESS_THAN_OR_EQUAL;
		else if (strcmp(">=", argv[3]) == 0) op = GREATER_THAN_OR_EQUAL;
		else if (strcmp("!=", argv[3]) == 0) op = NOT_EQUAL;
		/* or return error if necessary */
		else {
			fprintf(stderr, "Wrong op given!\n");
			return DME_ERROR;
		}
		attrRecId = attrCatFunction(&a, argv[1], argv[2]);
		if (a.attrType == 'i') {
			value = malloc(sizeof(int));
			numberi = atoi(argv[argc - 1]);
			memcpy(value, &numberi, sizeof(int));
		}
		else if (a.attrType == 'f') {
			value = malloc(sizeof(float));
			numberf = atof(argv[argc - 1]);
			memcpy(value, (char *)&numberf, sizeof(float));
		}
		else {
			value = malloc(strlen(argv[argc - 1]) + 1);
			strcpy(value, argv[argc - 1]);
		}
		if (a.indexed == TRUE) {
			AMfileDesc = AM_OpenIndex (argv[1], a.indexNo);
			scanDesc = AM_OpenIndexScan(AMfileDesc, a.attrType, a.attrLength, op, value);
			recId = AM_FindNextEntry(scanDesc);
			if (recId < 0) eos = 1;
			if (eos != 1 && HF_GetThisRec(fileDesc, recId, record, r.relWidth) != HFE_OK) {
				HF_PrintError("Error in HF_GetThisRec used in DM_delete!\n");
				return DME_HFERROR;
			}
		}
		else {
			scanDesc = HF_OpenFileScan(fileDesc, r.relWidth, a.attrType,a.attrLength, a.offset, op, value);
			recId = HF_FindNextRec(scanDesc, record);
			if (recId < 0) eos = 1;
		}
		free(value);
	}

	/* If there is no condition, open an HF Scan with value NULL */
	else {
		scanDesc = HF_OpenFileScan(fileDesc, r.relWidth, 'c', 0, 0, 0, NULL);
		recId = HF_FindNextRec(scanDesc, record);
		if (recId < 0) eos = 1;
		
	}

	temp_record = malloc(sizeof(attrDesc));

	/* find records to delete until EOF - delete also in indexes */
	while (eos == 0) {

		/* Delete from HF */
		if (HF_DeleteRec(fileDesc, recId, r.relWidth) < 0) {
			HF_PrintError("Error in HF_DeleteRec used in DM_delete!\n");
			return DME_HFERROR;
		}

		/* Delete from indexes */
		attrScanDesc = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c', strlen(r.relName), 0, 1, r.relName);
		attrRecId = HF_FindNextRec(attrScanDesc, temp_record);
		while (attrRecId >= 0) {
			memcpy(&tempa, temp_record, sizeof(attrDesc));
			if (tempa.indexed == TRUE) {
				value = malloc(tempa.attrLength);
				memcpy(value, &record[tempa.offset], tempa.attrLength);
				tempFileDesc = AM_OpenIndex (tempa.relName, tempa.indexNo);
				AM_DeleteEntry(tempFileDesc, tempa.attrType, tempa.attrLength, value, recId);
				AM_CloseIndex (tempFileDesc);
				free(value);
			}
			attrRecId = HF_FindNextRec(attrScanDesc, temp_record);
		}
		HF_CloseFileScan(attrScanDesc);

		/* find next record */
		if (condition != 0 && a.indexed == TRUE) {
			recId = AM_FindNextEntry(scanDesc);
			if (recId < 0) eos = 1;
			if (eos != 1 && HF_GetThisRec(fileDesc, recId, record, r.relWidth) != HFE_OK) {
				HF_PrintError("Error in HF_GetThisRec used in DM_delete!\n");
				return DME_HFERROR;

			}
		}
		else {
			recId = HF_FindNextRec(scanDesc, record);
			if (recId < 0) eos = 1;
		}
	}

	/* free allocated buffer for records */
	free(temp_record);

	/* Close the scanning */
	if (condition != 0 && a.indexed == TRUE) {
		AM_CloseIndexScan(scanDesc);
	}
	else {
		HF_CloseFileScan(scanDesc);
	}

	/* close file and free allocated memory */
	HF_CloseFile(fileDesc);
	free(record);
}


/* Implementation of DM_subtract function */
int DM_subtract(int argc,char* argv[])
{
	/* Declarations */
	int check;
	int flag = 0, i;
	int fileDesc, scanDesc, scanDescResults, recIdData,recIdResults, attrscanDesc, fileDescResults, AMfileDesc, attrRecId;
	int numberi;
	float numberf;
	char *fileNameData;
	char *fileNameResults;
	char *record;
	char *recordResults;
	char *attrecord;
	relDesc r;
	attrDesc a;

	/* Implementation */
	fileNameResults = malloc (strlen(argv[1])+1);
	fileNameData = malloc (strlen(argv[2])+1);
	strcpy (fileNameResults, argv[1]);
	strcpy (fileNameData, argv[2]);

	/* check for correct data */
	check = check_add_subtract(fileNameResults, fileNameData) ;
	if (check < 0) return check;

	/* save in struct r the data of the file */ 
	relCatFunction(&r, fileNameResults);
	/* allocate memory */
	record = malloc(r.relWidth);
	recordResults = malloc(r.relWidth);
	attrecord = malloc(sizeof(attrDesc));
	
	/* Open Results file or return error if necessary */
	fileDescResults = HF_OpenFile(fileNameResults);
	if (fileDescResults < 0) {
		HF_PrintError("Error in HF_OpenFile called on DM_subtract.");
		return DME_HFERROR;
	}

	/* open file and scanning for file relName2 or return error if necessary */
	fileDesc = HF_OpenFile(fileNameData);
	if (fileDesc < 0) {
		HF_PrintError("Error in HF_OpenFile called on DM_subtract.");
		return DME_HFERROR;
	}

	/* open a scanning or return error if necessary */
	scanDesc = HF_OpenFileScan(fileDesc, r.relWidth, 'c', 0, 0, 0, NULL);
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on DM_subtract.");
		return DME_HFERROR;
	}

	/* Take the records one by one from data file */
	recIdData = HF_FindNextRec(scanDesc,record);
	
	while (recIdData >= 0) {
		scanDescResults = HF_OpenFileScan(fileDescResults, r.relWidth, 'c', 0, 0, 0, NULL);
		if (scanDescResults < 0) {
			HF_PrintError("Error in HF_OpenFileScan called on DM_subtract.");
			return DME_HFERROR;
		}
		recIdResults = HF_FindNextRec(scanDescResults,recordResults);
		while (recIdResults >= 0) {
			if (memcmp(record, recordResults, r.relWidth) == 0) {
				HF_DeleteRec(fileDescResults, recIdResults, r.relWidth);
				/*Diagrafi apo eyretiria*/
				attrscanDesc = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c',strlen(fileNameResults), 0, EQUAL, fileNameResults);
				attrRecId = HF_FindNextRec(attrscanDesc,attrecord);
				while (attrRecId >= 0) {
					memcpy(&a, attrecord, sizeof(attrDesc));
					if (a.indexed == TRUE) {
						AMfileDesc = AM_OpenIndex (fileNameResults, a.indexNo);
						AM_DeleteEntry(AMfileDesc, a.attrType, a.attrLength, &record[a.offset], recIdResults);
						AM_CloseIndex (AMfileDesc);
					}
					attrRecId = HF_FindNextRec(attrscanDesc,attrecord);
				}
				HF_CloseFileScan(attrscanDesc);
			}
			recIdResults = HF_FindNextRec(scanDescResults,recordResults);
		}
		/* close the scanning for the results */
		HF_CloseFileScan(scanDescResults);
		recIdData = HF_FindNextRec(scanDesc,record);
	}

	/* Close the files and free the allocated memory space */
	HF_CloseFileScan(scanDesc);
	HF_CloseFile(fileDesc);
	HF_CloseFile(fileDescResults);
	free(record);
	free(recordResults);
	free(attrecord);
}


/* Implementation of DM_insert function */
int DM_insert(int argc,char* argv[])
{
	/* Declarations */
	int fileDescResults;
	int recId;
	int i, counter = 0;
	int AM_fileDesc;
	int HF_fileDesc;
	char indexflag;
	char *buffer;
	char *value;
	char *fileNameData;
	char *fieldName;
	int numberi;
	float numberf;
	relDesc rData;
	attrDesc a;

	/* Implementation */

	/* check if there are wrong number of arguments and return error if necessary */
	if (argc%2 == 1) {
		fprintf(stderr, "Wrong number of operands!\n");
		return DME_ERROR;
	}

	fileNameData = malloc(MAXNAME);
	strcpy (fileNameData, argv[1]);
	fieldName = malloc(MAXNAME);

	fileDescResults = HF_OpenFile(fileNameData);

	/* return error if the filename is wrong */
	if (fileDescResults < 0) {
		HF_PrintError("Error in HF_OpenFile called on DM_insert.");
		return DME_HFERROR;
	}


	recId = relCatFunction(&rData, fileNameData);

	/* return error for wrong recId*/
	if (recId < 0) {
		fprintf(stderr, "Wrong file name!\n");
		return DME_ERROR;
	}


	counter = 0;
	for (i = 2 ; i <= argc-2 ; i += 2) {
		counter += 1;
		memset(fieldName, 0, MAXNAME);
		strcpy(fieldName, argv[i]);
		if (attrCatFunction(&a, fileNameData, fieldName) < 0) {
			fprintf(stderr, "Wrong field name given in DM_insert!\n");
			return DME_ERROR;
		}
	}

	if (counter != rData.attrCnt) {
		fprintf(stderr, "Wrong number of fields given in DM_insert!\n");
		return DME_ERROR;
	}

	/* allocate memory for a buffer */
	buffer = malloc(rData.relWidth);
	memset (buffer, 0, rData.relWidth);

	/* copy the values to the buffer */
	for (i = 2 ; i <= argc-2 ; i += 2) {
		attrCatFunction(&a, argv[1], argv[i]);
		if (a.attrType == 'i') {
			numberi = atoi(argv[i+1]);
			memcpy(&buffer[a.offset], (char *)&numberi, sizeof(int));
		}
		else if (a.attrType == 'f') {
			numberf = atof(argv[i+1]);
			memcpy(&buffer[a.offset], (char *)&numberf, sizeof(float));
		}
		else {
			//memcpy(&buffer[a.offset], argv[i+1], a.attrLength);
			memcpy(&buffer[a.offset], argv[i+1], strlen(argv[i+1]) + 1);
		}
	}

	/* Insert records */
	recId = HF_InsertRec(fileDescResults, buffer, rData.relWidth);
	
	/* return error for wrong recId if necessary */
	if (recId < 0) {
		HF_PrintError("Error in HF_InsertRec called on DM_insert.\n");
		return DME_HFERROR;
	}

	/* there are indexes */	
	for (i = 2 ; i <= argc-2 ; i += 2) {
		if (attrCatFunction(&a, argv[1], argv[i]) < 0) return DME_ERROR;
		if (a.indexed == TRUE) {
			/* case of integer */
			if (a.attrType == 'i') {
				value = malloc(sizeof(int));
				numberi = atoi(argv[i+1]);
				memcpy(value, &numberi, sizeof(int));
			}
			/* case of float */
			else if (a.attrType == 'f') {
				value = malloc(sizeof(float));
				numberf = atof(argv[i+1]);
				memcpy(value, (char *)&numberf, sizeof(float));
			}
			/* case of char */
			else {
				value = malloc(strlen(argv[i+1]) + 1);
				strcpy(value, argv[i+1]);
			}
			/* Open the index */
			AM_fileDesc = AM_OpenIndex(fileNameData, a.indexNo);

			/* return error for wrong AM_fileDesc if necessary */
			if (AM_fileDesc < 0) {
				AM_PrintError ("Error in AM_OpenIndex called on DM_insert.\n");
				return DME_AMERROR;
			}

			/* insert the record */
			if (AM_InsertEntry(AM_fileDesc, a.attrType, a.attrLength, value, recId) < 0) {
				AM_PrintError ("Error in AM_InsertEntry called on DM_insert.\n");
				return DME_AMERROR;
			}

			/* free allocated memory for value and close the index */
			free(value);
			if (AM_CloseIndex (AM_fileDesc) < 0) {
				AM_PrintError ("Error in AM_CloseIndex called on DM_insert.\n");
				return DME_AMERROR;
			}
		}
	}
	/* Close file of results */
	if (HF_CloseFile(fileDescResults) < 0) {
		HF_PrintError("Error in HF_CloseFile called on DM_insert.\n");
		return DME_HFERROR;
	}

	/* free allocated memory */
	free(buffer);
}


/* Implementation of DM_add function */
int DM_add(int argc,char* argv[])
{
	/* Declarations */
	int scanDesc, attrScanDesc;
	int recId, attrRecId;
	int check;
	int fileDesc;
	int i;
	int numberi;
	float numberf;
	char *fileNameResults;	//relName 1
	char *fileNameData;	//relName 2
	char *record;
	char *attrRecord;
	char **add;
	attrDesc a;
	relDesc r;

	/* Implementation */
	fileNameResults = malloc (strlen(argv[1]) + 1);
	fileNameData = malloc (strlen(argv[2]) + 1);
	strcpy (fileNameResults, argv[1]);
	strcpy (fileNameData, argv[2]);


	/* check for correct data */
	check = check_add_subtract(fileNameResults, fileNameData) ;
	if (check < 0) return check;

	/* Take info for fileNameData to struct r */
	recId = relCatFunction(&r, fileNameResults);
	record = malloc(r.relWidth);

	fileDesc = HF_OpenFile(fileNameData);

	add = malloc((r.attrCnt*2 +2) * sizeof(char *));
	add[0] = malloc(strlen("insert") + 1);
	strcpy(add[0], "insert");
	add[1] = malloc(strlen(argv[1] + 1));
	strcpy(add[1], argv[1]);

	/* Open scan for relName 2 */
	scanDesc = HF_OpenFileScan(fileDesc, r.relWidth, 'c', 0, 0, 0, NULL);

	/* return error if necessary */
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on DM_add.");
		return DME_HFERROR;
	}

	recId = HF_FindNextRec(scanDesc, record);

	attrRecord = malloc(sizeof(attrDesc));

	/* scan all records */
	while (recId >= 0) {
		attrScanDesc = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c', strlen(r.relName), 0, EQUAL, r.relName);
		attrRecId = HF_FindNextRec(attrScanDesc, attrRecord);
		memcpy(&a, attrRecord, sizeof(attrDesc));
		i = 2;
		while (attrRecId >= 0 && i < (r.attrCnt*2 + 2)) {
			add[i] = malloc(MAXNAME);
			memcpy(add[i], &attrRecord[MAXNAME], MAXNAME);
			add[i+1] = malloc(a.attrLength);
			if (a.attrType == 'i') {
				memcpy(&numberi, &record[a.offset], sizeof(int));
				sprintf(add[i+1], "%d", numberi);
			}
			else if (a.attrType == 'f') {
				memcpy(&numberf, &record[a.offset], sizeof(float));
				sprintf(add[i+1], "%f", numberf);
			}
			else memcpy(add[i+1], &record[a.offset], a.attrLength);
			i += 2;
			attrRecId = HF_FindNextRec(attrScanDesc, attrRecord);
			memcpy(&a, attrRecord, sizeof(attrDesc));
		}
		/* use DM_insert */
		DM_insert(r.attrCnt*2 + 2, add);

		HF_CloseFileScan(attrScanDesc);
		/* find next record */
		recId = HF_FindNextRec(scanDesc, record);
		for (i = 2 ; i < (r.attrCnt*2 + 2) ; i++) free(add[i]);
	}

	/* close the scanning */
	HF_CloseFileScan(scanDesc);

	/* free allocated memory */
	free(add[0]);
	free(add[1]);
	free(add);

	free(fileNameData);
	free(fileNameResults);
	free(record);
}

