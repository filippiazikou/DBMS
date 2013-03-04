#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UT_Lib.h"
#include "DB_Lib.h"
#include "DM_Lib.h"
#include "HF_Lib.h"
#include "AM_Lib.h"
#include "BF_Lib.h"


/* Implementation of UT create function */
int UT_create(int argc,char* argv[])
{
	/* Declarations */
	relDesc r;
	attrDesc a;
	char *record;
	int i, recId, scandesc;
	int tmp;

	/* Implementation */

	/* Use less than 4 arguments in commant line --> return error */
	if (argc < 4) {
		fprintf(stderr, "Too few arguments!\n");
		return UTE_ERROR;
	}

	/* create file or return error if necessary */
	if (HF_CreateFile(argv[1]) < 0) {
		HF_PrintError("Error in HF_CreateFile called on UT_create.");
		return UTE_HFERROR;
	}

	//////////////////////////
	/******** RELCAT ********/
	//////////////////////////

	/* allocate memory for relCat */
	record = malloc(sizeof(relDesc));

	/* update file relCat */

	strcpy(r.relName, argv[1]);
	r.relWidth = 0;
	for (i = 3 ; i < argc ; i += 2) {
		/* Case of integer */
		if (argv[i][1] == 'i') r.relWidth = r.relWidth + sizeof(int);
		/* Case of float */
		else if (argv[i][1] == 'f') r.relWidth = r.relWidth + sizeof(float);
		/* Case of char */
		else if (argv[i][1] == 'c') {//r.relWidth = r.relWidth + atoi(&argv[i][2]);
				sscanf(argv[i], "'c%d'", &tmp );
				r.relWidth = r.relWidth + tmp;
					
		}
		/* Wrong value --> return error */
		else return UTE_HFERROR;
	}

	/* find the number of indexes */
	r.attrCnt = (argc-2) / 2;
	r.indexCnt = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(relDesc));
	memcpy(record, &r, sizeof(relDesc));
	if (HF_InsertRec(relCatFileDesc,(char *) &r ,sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on UT_create.");
		return UTE_HFERROR;
	}

	/* free memory allocated for relCat */
	free(record);

	//////////////////////////
	/******* ATTRCAT ********/
	//////////////////////////
	
	/* allocate memory for attrCat */
	record = malloc(sizeof(attrDesc));

	/* update file attrCat */

	a.offset = 0;
	strcpy(a.relName, argv[1]);
	for (i = 2 ; i < argc-1 ; i += 2) {
		strcpy(a.attrName, argv[i]);
		/* Case of integer */
		if (argv[i+1][1] == 'i') {
			a.attrLength = sizeof(int);
			a.attrType = 'i';
		}
		/* Case of float */
		else if (argv[i+1][1] == 'f') {
			a.attrLength = sizeof(float);
			a.attrType = 'f';
		}	
		/* Case of char */
		else if (argv[i+1][1] == 'c') {
			sscanf(argv[i], "'c%d'", &tmp );
			//a.attrLength = atoi(&argv[i+1][2]);
			a.attrLength = tmp;
			a.attrType = 'c';
		}		
		/* Wrong value --> return error */
		else return UTE_HFERROR;
	
		a.indexed = FALSE;
		a.indexNo = 0;


		/* fill memory with zeros and then copy the struct in memory */
		memset(record, 0, sizeof(attrDesc));
		memcpy (record, &a, sizeof(attrDesc));

		/* if cannot insert the records --> return error */
		if (HF_InsertRec(attrCatFileDesc, record ,sizeof(attrDesc)) < 0) {
			HF_PrintError("Error in HF_InsertRec called on UT_create.");
			return UTE_HFERROR;
		}
		a.offset = a.offset + a.attrLength;
	}

	/* free memory allocated for attrCat */
	free(record);
}


/* Implementation of UT buildindex function */
int UT_buildindex(int argc,char* argv[])
{
	/* Declarations */
	int scanDesc, recId, flag = 0, AMfileDesc;
	char *record;
	int fileDesc;
	relDesc r;
	attrDesc a;

	/* Implementation */

	/* return error for less arguments in buildindex call */
	if (argc < 3) {
		fprintf(stderr, "Too few arguments!\n");
		return UTE_ERROR;
	}
	
	/* find the index in relCat */

	/* allocate memory  for relCat */
	record = malloc(sizeof(relDesc));

	scanDesc = HF_OpenFileScan(relCatFileDesc, sizeof(relDesc), 'c', strlen(argv[1]),0 , 1, argv[1]);

	/* return error in OpenFileScan if necessary*/
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* find the next record */
	recId = HF_FindNextRec(scanDesc, record);

	/* return error in FindNextRec */
	if (recId < 0) {
		HF_PrintError("Error in HF_FindNextRec called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* stop scanning or return error if necessary */
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}

	memcpy(&r, record, sizeof(relDesc));
	r.indexCnt += 1;
	memcpy(record, &r, sizeof(relDesc));

	/* Delete record or return error if necessary */
	if (HF_DeleteRec(relCatFileDesc,recId, sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_DeleteRec called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* Insert record or return error if necessary */
	if (HF_InsertRec(relCatFileDesc,record, sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* free allocated memory */
	free(record);

	/* find the index in attrCat */

	record = malloc(sizeof(attrDesc));

	/* find the field with the same onoma-sxesis */
	scanDesc = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c', strlen(argv[1]), 0 , 1, argv[1]);
	/* and return error if necessary */
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* from the fileds that have the same onoma-sxesis, find the one that has onoma-pediou that we want for index */
	while (flag == 0) {
		recId = HF_FindNextRec(scanDesc, record);
		/* return error if necessary */
		if (recId < 0) {
			HF_PrintError("Error in HF_FindNextRec called on UT_buildindex.");
			return UTE_HFERROR;
		}
		
		memcpy(&a, record, sizeof(attrDesc));
		if (strcmp(a.attrName, argv[2]) == 0) flag = 1;
	}

	/* indexes exist */
	a.indexed = TRUE;
	a.indexNo = r.indexCnt;

	memcpy(record, &a, sizeof(attrDesc));

	/* Delete record or return error if necessary */
	if (HF_DeleteRec(attrCatFileDesc,recId, sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_DeleteRec called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* Insert record or return error if necessaty */
	if (HF_InsertRec(attrCatFileDesc,record, sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* close the scans or return error if necessary */
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}
	
	/* free the allocated memory */
	free(record);

	/* Create the index file */
	if (AM_CreateIndex(argv[1], a.indexNo, a.attrType, a.attrLength) < 0) {
		AM_PrintError("Error in AM_CreateIndex called on UT_buildindex.");
		return UTE_AMERROR;
	}
	
	/* Put the records from HF file to AM */
	fileDesc = HF_OpenFile(argv[1]);
	if (fileDesc < 0) {
		HF_PrintError("Error in HF_OpenFile called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* open an index or return error if necessary */
	AMfileDesc = AM_OpenIndex (argv[1], a.indexNo);
	if (AMfileDesc < 0) {
		AM_PrintError("Error in AM_OpenIndex called on UT_buildindex.");
		return UTE_AMERROR;
	}	

	/* allocate memory for relCat */
	record = malloc (sizeof(r.relWidth));

	/* open a scanning */
	scanDesc = HF_OpenFileScan(fileDesc, r.relWidth, 'c', 0, 0, 0, NULL);

	/* find next record or return error if necessary */
	recId = HF_FindNextRec(scanDesc, record);
	while (recId >= 0) {
		AM_InsertEntry(AMfileDesc, a.attrType, a.attrLength, &record[a.offset], recId);
		recId = HF_FindNextRec(scanDesc, record);
	}

	/* free allocated memory for relCat */
	free(record);

	/* Close indexes, scannings and file */
	AM_CloseIndex (AMfileDesc);
	HF_CloseFileScan(scanDesc);
	HF_CloseFile(fileDesc);
}


/* Implementation of UT destroy function */
int UT_destroy(int argc,char* argv[])
{
	/* Declarations */
	int fileDesc, scanDesc, recId, flag = 0, i;
	char *record;
	relDesc r;
	attrDesc a;

	/* Implementation */

	/* return error if the arguments are less in calling of the function */
	if (argc < 2) {
		fprintf(stderr, "Too few arguments!\n");
		return UTE_ERROR;
	}

	/* put in memory the record that we need from relCat file - Initialize struct r */

	record = malloc(sizeof(relDesc));

	/* open a scanning or return error if necessary */
	scanDesc = HF_OpenFileScan(relCatFileDesc, sizeof(relDesc), 'c', strlen(argv[1]), 0 , 1, argv[1]);
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* Find next record or return error if necessary */
	recId = HF_FindNextRec(scanDesc, record);
	if (recId < 0) {
		HF_PrintError("Error in HF_FindNextRec called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* close the scanning or return error if necessary */
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}

	memcpy(&r, record, sizeof(relDesc));

	/* Delete indexes */
	for(i = 1 ; i <= r.indexCnt ; i++) {
		if (AM_DestroyIndex(argv[1], i) < 0) {
			AM_PrintError("Error in AM_DestroyIndex.");
			return UTE_AMERROR;
		}
	}

	/* Delete record from relCat or return error if necessary*/
	if (HF_DeleteRec(relCatFileDesc,recId, sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_DeleteRec called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* free the allocated buffer for relCat */
	free(record);

	/* Delete records from attrCat */

	/* allocate memory for attrCat */
	record = malloc(sizeof(attrDesc));

	/* open scanning for attrCat or return error if necessary */
	scanDesc = HF_OpenFileScan(attrCatFileDesc, sizeof(attrDesc), 'c', strlen(argv[1]),0 , 1, argv[1]);
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* Find next records */
	recId = HF_FindNextRec(scanDesc, record);
	while (recId >= 0) {
		/* Delete record or return error if necessary */
		if (HF_DeleteRec(attrCatFileDesc,recId, sizeof(attrDesc)) < 0) {
			HF_PrintError("Error in HF_DeleteRec called on UT_buildindex.");
			return UTE_HFERROR;
		}
		recId = HF_FindNextRec(scanDesc, record);
	}

	/* Close the scanning or return error if necessary */
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* Destroy the file or return error if necessary */
	if (HF_DestroyFile(argv[1]) < 0) {
		HF_PrintError("Error in HF_DestroyFile called on UT_buildindex.");
		return UTE_HFERROR;
	}

	/* free allocated memory for attrCat */
	free(record);
}


/* Implementation of UT quit function */
int UT_quit(void)
{
	/* Implementation */

	/* close relCat file or return error if necessary */
	if  (HF_CloseFile(relCatFileDesc) < 0) {
		HF_PrintError("Error in HF_CloseFile called on UT_quit.");
		return UTE_HFERROR;
	}

	/* close attrCat file or return error if necessary */
	if  (HF_CloseFile(attrCatFileDesc) < 0) {
		HF_PrintError("Error in HF_CloseFile called on UT_quit.");
		return UTE_HFERROR;
	}

	/* close viewCat file or return error if necessary */
	if  (HF_CloseFile(viewCatFileDesc) < 0) {
		HF_PrintError("Error in HF_CloseFile called on UT_quit.");
		return UTE_HFERROR;
	}

	/* close viewAttrCat file or return error if necessary */
	if  (HF_CloseFile(viewAttrCatFileDesc) < 0) {
		HF_PrintError("Error in HF_CloseFile called on UT_quit.");
		return UTE_HFERROR;
	}

	/* print QUIT and exit */
	printf("QUIT\n");
	exit(0);
}

