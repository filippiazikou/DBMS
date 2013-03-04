#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "DB_Lib.h"
#include "BF_Lib.h"
#include "AM_Lib.h"
#include "HF_Lib.h"
#include "DM_Lib.h"
#include "UT_Lib.h"




int main (int argc, char* argv[]) {
	char command[80];
	char* dbname;
	char* record;
	int fileDesc;
	int structStartMem;
	int attrStartMem;
	relDesc r;
	attrDesc a;
	HF_Init();

	if (argc != 2) {
		printf("Χρήση: %s dbname \n", argv[0]);
		return (1);
	}

	dbname = argv[1];
	sprintf(command, "mkdir %s", dbname);
	system(command);
	if (chdir(dbname)) {
		printf("Δεν είναι δυνατή η δημιουργία της βάσης\n");
		return (2);
	}
	
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Create and Initialize relCat ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* If cannot create file relCat --> return error */
	if (HF_CreateFile("relCat") < 0) {
		HF_PrintError("Error in HF_CreateFile called on dbcreate.");
		return DBE_HFERROR;
	}

	/* Open file relCat */
	fileDesc = HF_OpenFile("relCat");

	/* return error in opening the file */
	if (fileDesc < 0) {
		HF_PrintError("Error in HF_OpenFile called on dbcreate.");
		return DBE_HFERROR;
	}

	/* allocate memory for relCat */
	record = malloc(sizeof(relDesc));

	/* give the values of the relCat struct */
	strcpy(r.relName, "relCat");
	r.relWidth = sizeof(relDesc);
	r.attrCnt = 4;
	r.indexCnt = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(relDesc));
	memcpy (record, &r, sizeof(relDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc, record , sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the relCat struct */
	strcpy(r.relName, "attrCat");
	r.relWidth = sizeof(attrDesc);
	r.attrCnt = 7;
	r.indexCnt = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(relDesc));
	memcpy (record, &r, sizeof(relDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the relCat struct */
	strcpy(r.relName, "viewCat");
	r.relWidth = sizeof(viewDesc);
	r.attrCnt = 9;
	r.indexCnt = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(relDesc));
	memcpy (record, &r, sizeof(relDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the relCat struct */
	strcpy(r.relName, "viewAttrCat");
	r.relWidth = sizeof(viewAttrDesc);
	r.attrCnt = 4;
	r.indexCnt = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(relDesc));
	memcpy (record, &r, sizeof(relDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(relDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* if cannot close the file --> return error */
	if  (HF_CloseFile(fileDesc) < 0) {
		HF_PrintError("Error in HF_CloseFile called on dbcreate.");
		return DBE_HFERROR;
	}

	/* free the allocated memory */
	free(record);

/*~~~~~~~~~~~~~~~~~~~~~~~~~ Create and Initialize attrCat ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* If cannot create file attrCat --> return error */
	if (HF_CreateFile("attrCat") < 0) {
		HF_PrintError("Error in HF_CreateFile called on dbcreate.");
		return DBE_HFERROR;
	}

	/* Open file attrCat */
	fileDesc = HF_OpenFile("attrCat");

	/* return error in opening the file */
	if (fileDesc < 0) {
		HF_PrintError("Error in HF_OpenFile called on dbcreate.");
		return DBE_HFERROR;
	}

	/* allocate memory for attrCat */
	record = malloc(sizeof(attrDesc));

	/***************/
	/* relCat file */
	/***************/

	/* give the values of the attrCat struct */
	strcpy(a.relName, "relCat");
	strcpy(a.attrName, "relName");
	a.offset = 0;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */	
	strcpy(a.relName, "relCat");
	strcpy(a.attrName, "relWidth");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc, record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "relCat");
	strcpy(a.attrName, "attrCnt");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "relCat");
	strcpy(a.attrName, "indexCnt");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/****************/
	/* attrCat file */
	/****************/

	/* give the values of the attrCat struct */
	strcpy(a.relName, "attrCat");
	strcpy(a.attrName, "relName");
	a.offset = 0;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "attrCat");
	strcpy(a.attrName, "attrName");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "attrCat");
	strcpy(a.attrName, "offset");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "attrCat");
	strcpy(a.attrName, "attrLength");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "attrCat");
	strcpy(a.attrName, "attrType");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(char);
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "attrCat");
	strcpy(a.attrName, "indexed");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "attrCat");
	strcpy(a.attrName, "indexNo");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/****************/
	/* viewCat file */
	/****************/

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "viewName");
	a.offset = 0;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "type");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "relname1");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "attrname1");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "op");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "relname2");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}
	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "attrname2");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "value");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXSTRINGLENGTH;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewCat");
	strcpy(a.attrName, "attrcnt");
	a.offset = a.offset + a.attrLength;
	a.attrLength = sizeof(int);
	a.attrType = 'i';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc) );

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/********************/
	/* viewAttrCat file */
	/********************/

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewAttrCat");
	strcpy(a.attrName, "viewName");
	a.offset = 0;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewAttrCat");
	strcpy(a.attrName, "viewAttrName");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewAttrCat");
	strcpy(a.attrName, "relName");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* give the values of the attrCat struct */
	strcpy(a.relName, "viewAttrCat");
	strcpy(a.attrName, "relAttrName");
	a.offset = a.offset + a.attrLength;
	a.attrLength = MAXNAME;
	a.attrType = 'c';
	a.indexed = FALSE;
	a.indexNo = 0;

	/* fill memory with zeros and then copy the struct in memory */
	memset(record, 0, sizeof(attrDesc));
	memcpy (record, &a, sizeof(attrDesc));

	/* if cannot insert the records --> return error */
	if (HF_InsertRec(fileDesc,record ,sizeof(attrDesc)) < 0) {
		HF_PrintError("Error in HF_InsertRec called on dbcreate.");
		return DBE_HFERROR;
	}

	/* if cannot close the file --> return error */
	if  (HF_CloseFile(fileDesc) < 0) {
		HF_PrintError("Error in HF_CloseFile called on dbcreate.");
		return DBE_HFERROR;
	}

	/* free the allocated memory */
	free(record);


/*~~~~~~~~~~~~~~~~~~~~~~~ Create ViewCat ~~~~~~~~~~~~~~~~~~~~~~~*/

	/* If cannot create file viewCat --> return error */
	if (HF_CreateFile("viewCat") < 0) {
		HF_PrintError("Error in HF_CreateFile called on dbcreate.");
		return DBE_HFERROR;
	}


/*~~~~~~~~~~~~~~~~~~~~~~~~ Create viewAttrCat ~~~~~~~~~~~~~~~~~~~~*/

	/* If cannot create file viewattrCat --> return error */
	if (HF_CreateFile("viewAttrCat") < 0) {
		HF_PrintError("Error in HF_CreateFile called on dbcreate.");
		return DBE_HFERROR;
	}

	return 0;
}
