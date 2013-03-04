#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defn.h"
#include "parser4.h"

#include "VW_Lib.h"
#include "UT_Lib.h"
#include "DM_Lib.h"
#include "AM_Lib.h"
#include "HF_Lib.h"
#include "BF_Lib.h"



/* Global variables */
int temp_counter = 0;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HELPING FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* helping function for viewCat - takes a pointer to struct and the name of the file, and it returns recId */
int viewCatFunction(viewDesc *v, char *name, int number)
{
	/* Declarations */
	int recId, scanDesc, i;
	char *record;	
	relDesc r;
	attrDesc *a;

	/* Implementation */
	if (name == NULL) {
		scanDesc = HF_OpenFileScan(viewcatFileDesc, 342*sizeof(char), 'c',0, 0, 0, NULL);
	}
	else 
		scanDesc = HF_OpenFileScan(viewcatFileDesc, 342*sizeof(char), 'c',MAXNAME, 0, EQUAL, name);
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on viewCatFunction.");
		return VWE_HFERROR;
	}

	record = malloc(sizeof(viewDesc));
	for (i = 0 ; i < number ; i++) {
		recId = HF_FindNextRec(scanDesc, record);
	}
	
	UT_relInfo("viewCat", &r, &a);
	memcpy(&(v->viewname), &record[a[0].offset], MAXNAME);
	memcpy(&(v->type), &record[a[1].offset], sizeof(int));
	memcpy(&(v->relname1), &record[a[2].offset], MAXNAME);
	memcpy(&(v->attrname1), &record[a[3].offset], MAXNAME);
	memcpy(&(v->op), &record[a[4].offset], sizeof(int));
	memcpy(&(v->relname2), &record[a[5].offset], MAXNAME);
	memcpy(&(v->attrname2), &record[a[6].offset], MAXNAME);
	memcpy(&(v->value), &record[a[7].offset], MAXSTRINGLENGTH);
	memcpy(&(v->attrcnt), &record[a[8].offset], sizeof(int));
	
	free(record);
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on relCatFunction.");
		return VWE_HFERROR;
	}
	return recId;
}


/* helping function for viewattrCat - takes a pointer to struct, to name of file, to name of field, and it returns recId */
int viewAttrCatFunction(viewAttrDesc *va, char *nameFile, int fieldNum)
{
	/* Declarations */
	int recId, scanDesc;
	int i;
	char flag = 0;
	char *record;
	relDesc r;
	attrDesc *a;

	/* Implementation */
	scanDesc = HF_OpenFileScan(viewattrcatFileDesc, sizeof(viewAttrDesc), 'c',MAXNAME, 0, EQUAL, nameFile);
	if (scanDesc < 0) {
		HF_PrintError("Error in HF_OpenFileScan called on viewattrCatFunction.");
		return VWE_HFERROR;
	}
	record = malloc(sizeof(viewAttrDesc));
	for (i = 0 ; i < fieldNum ; i++) {
		recId = HF_FindNextRec(scanDesc, record);
	}
	UT_relInfo("viewAttrCat", &r, &a);
	memcpy(&(va->viewname), &record[a[0].offset], MAXNAME);
	memcpy(&(va->viewattrname), &record[a[1].offset], MAXNAME);
	memcpy(&(va->relname), &record[a[2].offset], MAXNAME);
	memcpy(&(va->relattrname), &record[a[3].offset], MAXNAME);
	free(record);
	if (HF_CloseFileScan(scanDesc) < 0) {
		HF_PrintError("Error in HF_CloseFileScan called on viewattrCatFunction.");
		return VWE_HFERROR;
	}
	return recId;
}


/* view V in relName - temp -> record to insert  */
int recursive_update(char *V, char *relName, char *temp, int flag)
{
	 /* Declarations */
	viewDesc v, v2;
	viewAttrDesc va;
	relDesc r;
	attrDesc *a;
	char *V2;
	int i;
	int error;
	int counter;
	char *add[4];
	char *subtract[4];
	char **select;
	char **join;
	char *T;
	char *destroy[3];

	 /* Implementation */
	if (viewCatFunction(&v, V, 1) < 0) {
		fprintf(stderr, "Error in viewCatFunction\n");
		return VWE_ERROR;
	}

/**************                STEP 1               **********************/

	/* Create a temporary file */
	T = malloc(strlen("temp") + 5);
	sprintf(T, "temp%d", temp_counter);
	temp_counter++;

	/* allocate memory for join or select */
	if (v.type == SELECT) {
		select = malloc((8 + 2*v.attrcnt)*sizeof(char *));
	}
	else if (v.type == JOIN) {
		join = malloc((9 + 2*v.attrcnt)*sizeof(char *));
	}
	else if (v.type == NO) {
		select = malloc((4 + 2*v.attrcnt)*sizeof(char *));
	}
	else {
		fprintf(stderr, "Error because of wrong type given!\n");
		return VWE_ERROR;
	}

	/* values of first fields */
	if (v.type == SELECT || v.type == NO) {
		select[0] = malloc(strlen("select")+1);
		strcpy(select[0], "select");
		select[1] = malloc(strlen(T) + 1);
		strcpy(select[1], T);
		select[2] = malloc(sizeof(int));
		sprintf(select[2], "%d", v.attrcnt);
	}
	else {
		join[0] = malloc(strlen("join")+1);
		strcpy(join[0], "join");
		join[1] = malloc(strlen(T) + 1);
		strcpy(join[1], T);
		join[2] = malloc(sizeof(int));
		sprintf(join[2], "%d", v.attrcnt);
	}

	counter = 1;
	/* insert the fields */
	for (i = 1 ; i <= 2*v.attrcnt ; i += 2) {
		if (viewAttrCatFunction(&va, V, counter) < 0) {
		  fprintf(stderr, "Error in viewAttrCatFunction called in recursive_update!\n");
		  return VWE_ERROR;
		}
		counter += 1;
		if (v.type == SELECT || v.type == NO) {
			select[2+i] = malloc(strlen(temp)+1);
			strcpy(select[2+i], temp);
			select[3+i] = malloc(MAXNAME*sizeof(char));
			strcpy(select[3+i], va.viewattrname);
		}
		else {
			if (strcmp(va.relname, relName) == 0) {
				join[2+i] = malloc(MAXNAME*sizeof(char));
				strcpy(join[2+i], temp);
			}
			else {
				join[2+i] = malloc(MAXNAME*sizeof(char));
				strcpy(join[2+i], va.relname);
			}
			join[3+i] = malloc(MAXNAME);
			strcpy(join[3+i], va.relattrname);
		}
	}

	/* insert condition fields */
	if (v.type == SELECT) {
		select[7 + 2*v.attrcnt - 4] = malloc(MAXNAME*sizeof(char));
		strcpy(select[7 + 2*v.attrcnt - 4], temp );
		select[7 + 2*v.attrcnt - 3] = malloc(MAXNAME);
		strcpy(select[7 + 2*v.attrcnt - 3], v.attrname1);
		select[7 + 2*v.attrcnt - 2] = malloc(sizeof(int));
		if (v.op == EQUAL) strcpy(select[7 + 2*v.attrcnt - 2], "=");
		else if (v.op == LESS_THAN) strcpy(select[7 + 2*v.attrcnt - 2], "<");
		else if (v.op == GREATER_THAN) strcpy(select[7 + 2*v.attrcnt - 2], ">");
		else if (v.op == LESS_THAN_OR_EQUAL) strcpy(select[7 + 2*v.attrcnt - 2], "<=");
		else if (v.op == GREATER_THAN_OR_EQUAL) strcpy(select[7 + 2*v.attrcnt - 2], ">=");
		else if (v.op == NOT_EQUAL) strcpy(select[7 + 2*v.attrcnt - 2], "!=");
		else {
			fprintf(stderr, "Error because of wrong operand!\n";
		   return VWE_ERROR;
		}
		select[7 + 2*v.attrcnt - 1] = malloc(strlen(v.value) + 1);
		strcpy(select[7 + 2*v.attrcnt - 1], v.value);
		select[7 + 2*v.attrcnt] = NULL;
		error = DM_select(7 + 2*v.attrcnt, select);
		if (error < 0) {
			fprintf(stderr, "Error in DM_select in recursive_update  %d\n", error);
			return VWE_ERROR;
		}
	}
	else if (v.type == JOIN) {
		join[8 + 2*v.attrcnt - 5] = malloc(MAXNAME*sizeof(char));
		if (strcmp(v.relname1, relName) == 0)
			strcpy(join[8 + 2*v.attrcnt - 5], temp);
		else 
			strcpy(join[8 + 2*v.attrcnt - 5], v.relname1);
		join[8 + 2*v.attrcnt - 4] = malloc(MAXNAME);
		strcpy(join[8 + 2*v.attrcnt - 4], v.attrname1);
		join[8 + 2*v.attrcnt - 3] = malloc(sizeof(int));
		if (v.op == EQUAL) strcpy(join[8 + 2*v.attrcnt - 3], "=");
		else if (v.op == LESS_THAN) strcpy(join[8 + 2*v.attrcnt - 3], "<");
		else if (v.op == GREATER_THAN) strcpy(select[8 + 2*v.attrcnt - 2], ">");
		else if (v.op == LESS_THAN_OR_EQUAL) strcpy(select[8 + 2*v.attrcnt - 2], "<=");
		else if (v.op == GREATER_THAN_OR_EQUAL) strcpy(select[8 + 2*v.attrcnt - 2], ">=");
		else if (v.op == NOT_EQUAL) strcpy(select[8 + 2*v.attrcnt - 2], "!=");
		else {
			fprintf(stderr, "Error because of wrong operand!\n";
		   return VWE_ERROR;
		}
		
		join[8 + 2*v.attrcnt - 2] = malloc(MAXNAME*sizeof(char));
		if (strcmp(v.relname2, relName) == 0)
			strcpy(join[8 + 2*v.attrcnt - 2], temp);
		else 
			strcpy(join[8 + 2*v.attrcnt - 2], v.relname2);
		join[8 + 2*v.attrcnt - 1] = malloc(MAXNAME);
		strcpy(join[8 + 2*v.attrcnt - 1], v.attrname2);
		join[8 + 2*v.attrcnt] = NULL;
		error = DM_join(8 + 2*v.attrcnt, join);
		if (error < 0) {
			fprintf(stderr, "Error in DM_join in recursive_update  %d\n", error);
			return VWE_ERROR;
		}
	}
	else if (v.type == NO) {
		select[3 + 2*v.attrcnt] = NULL;
		error = DM_select(3 + 2*v.attrcnt, select);
		if (error < 0) {
			fprintf(stderr, "Error in DM_select in recursive_update  %d\n", error);
			return VWE_ERROR;
		}
	}

	/* free memory */

	if (v.type == SELECT) {
		for (i = 0 ; i < 7 + 2*v.attrcnt ; i++)
			free(select[i]);
		free(select);
	}
	else if (v.type == JOIN) {
		for (i = 0 ; i < 8 + 2*v.attrcnt ; i++)
			free(join[i]);
		free(join);
	}
	else if (v.type == NO) {
		for (i = 0 ; i < 3 + 2*v.attrcnt ; i++)
			free(select[i]);
		free(select);
	}

	/**********        STEP  2         ****************/
	/* for each view in V */
	i=1;
	while (viewCatFunction(&v2, NULL, i) >= 0) {
		if (strcmp(v2.relname1, v.viewname) == 0 || strcmp(v2.relname2, v.viewname) == 0) {
			recursive_update(v2.viewname, v.viewname, T, flag);
		}
		i += 1;
	}

	/*********        STEP 3         ****************/
	if (flag == 0) {
		add[0] = malloc(strlen("add") + 1);
		strcpy(add[0], "add");
		add[1] = malloc(strlen(V) + 1);
		strcpy(add[1], V);
		add[2] = malloc(strlen(T) + 1);
		strcpy(add[2], T);
		add[3] = NULL;
		if (DM_add(3, add) < 0) {
			fprintf(stderr, "Error in DM_add in recursive_update!\n");
			return VWE_DMERROR;
		}
		for (i=0 ; i < 3 ; i++) free(add[i]);
	}
	else {
		subtract[0] = malloc(strlen("subtract") + 1);
		strcpy(subtract[0], "subtract");
		subtract[1] = malloc(strlen(V) + 1);
		strcpy(subtract[1], V);
		subtract[2] = malloc(strlen(T) + 1);
		strcpy(subtract[2], T);
		subtract[3] = NULL;
		if (DM_subtract(3, subtract) < 0) {
			fprintf(stderr, "Error in DM_subtract in recursive_update!\n");
			return VWE_DMERROR;
		}
		for (i=0 ; i < 3 ; i++) free(subtract[i]);
	}

	/**********      STEP 4           *******************/
	destroy[0] = malloc(strlen("destroy") + 1);
	strcpy(destroy[0], "destroy");
	destroy[1] = malloc(strlen(T) + 1);
	strcpy(destroy[1], T);
	destroy[2] = NULL;
	if (UT_destroy(2, destroy) < 0) {
		fprintf(stderr, "Error in UT_destroy in recursive_update!\n");
		return VWE_DMERROR;
	}

	for (i = 0 ; i<2 ; i++) free(destroy[i]);
	free(T);
}


/* function that prints the arguments */
void printArgs(int argc, char **argv)
{
	int i;
	for (i = 0 ; i < argc ; ++i)
		printf("argv[%d] = %s\n", i, argv[i]);
	printf("argv[%d] = (null)\n\n", i);
	fflush(stdout);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ VW FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Implementation of VW_CreateSelect function */
int VW_createSelect(int argc, char* argv[])
{
	/* Declarations */
	int N;		// number of relations
	int i;
	char condition;
	char *insert[21];
	char *insert2[11];
	viewDesc v;
	viewAttrDesc va;

	/* Implementation */

	strcpy(argv[0], "select");
	if (DM_select(argc, argv) < 0) {
		fprintf(stderr, "Error in DM_select called in VW_CreateSelect!\n");
		return VWE_DMERROR;
	}


	/* Check if the optional fields exist or not */
	N = atoi(argv[2]);
	if (argv[2*N+3] != NULL) {
		condition = 1;
	}
	else if ((argv[2*N+3] == NULL) && (argv[2*N+2] != NULL)){
		condition = 0;
	}
	else {
		fprintf(stderr, "Wrong number of operands!\n");
		return VWE_ERROR;
	}

	/* Initialize struct viewDesc */
	strcpy(v.viewname, argv[1]);
	v.op = 0;
	if (condition == 1) {
		v.type = SELECT;
		strcpy(v.relname1, argv[argc-4]);
		strcpy(v.attrname1, argv[argc-3]);
		if (strcmp("=", argv[argc - 2]) == 0) v.op = EQUAL;
		else if (strcmp("<", argv[argc - 2]) == 0) v.op = LESS_THAN;
		else if (strcmp(">", argv[argc - 2]) == 0) v.op = GREATER_THAN;
		else if (strcmp("<=", argv[argc - 2]) == 0) v.op = LESS_THAN_OR_EQUAL;
		else if (strcmp(">=", argv[argc - 2]) == 0) v.op = GREATER_THAN_OR_EQUAL;
		else if (strcmp("!=", argv[argc - 2]) == 0) v.op = NOT_EQUAL;
		/* return error for wrong operator */
		else {
			fprintf(stderr, "Wrong op given!\n");
			return VWE_ERROR;
		}
		strcpy(v.value, argv[argc-1]);
	}
	else {
		strcpy(v.relname1, argv[3]);
		v.type = NO;
	}
	v.attrcnt = N;

	/*insert sto arxeio viewCat*/
	insert[0] = malloc(strlen("insert")+1);
	strcpy(insert[0], "insert");
	insert[1] = malloc(strlen("viewCat")+1);
	strcpy(insert[1], "viewCat");
	insert[2] = malloc(strlen("viewname")+1);
	strcpy(insert[2], "viewname");
	insert[3] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[3], v.viewname);
	insert[4] = malloc(strlen("type")+1);
	strcpy(insert[4], "type");
	insert[5] = malloc(sizeof(int));
	sprintf(insert[5], "%d", v.type);
	insert[6] = malloc(strlen("relname1")+1);
	strcpy(insert[6],"relname1");
	insert[7] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[7], v.relname1);
	insert[8] = malloc(strlen("attrname1")+1);
	strcpy(insert[8],"attrname1");
	insert[9] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[9], v.attrname1);
	insert[10] = malloc(strlen("op")+1);
	strcpy(insert[10],"op");
	insert[11] = malloc(sizeof(int));
	sprintf(insert[11], "%d", v.op);
	insert[12] = malloc(strlen("relname2")+1);
	strcpy(insert[12],"relname2");
	insert[13] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[13], v.relname2);
	insert[14] = malloc(strlen("attrname2")+1);
	strcpy(insert[14],"attrname2");
	insert[15] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[15], v.attrname2);	
	insert[16] = malloc(strlen("value")+1);
	strcpy(insert[16], "value");
	insert[17] = malloc(MAXSTRINGLENGTH*sizeof(char));
	memcpy(insert[17], v.value, MAXSTRINGLENGTH*sizeof(char));
	insert[18] = malloc(strlen("attrcnt")+1);
	strcpy(insert[18], "attrcnt");
	insert[19] = malloc(sizeof(int));
	sprintf(insert[19], "%d", v.attrcnt);
	insert[20] = NULL;

	if (DM_insert(20, insert) < 0) {
		fprintf(stderr, "Error in DM_insert called in VW_CreateSelect for viewCat file!\n");
		return VWE_DMERROR;
	}

	
	/* update struct viewattrcat and the file*/
	insert2[0] = malloc(strlen("insert")+1);
	strcpy(insert2[0], "insert");
	insert2[1] = malloc(strlen("viewAttrCat")+1);
	strcpy(insert2[1], "viewAttrCat");

	strcpy(va.viewname, v.viewname);
	insert2[2] = malloc(strlen("viewname")+1);
	strcpy(insert2[2], "viewname");
	insert2[3] = malloc(MAXNAME*sizeof(char));
	strcpy(insert2[3], va.viewname);
	
	insert2[4] = malloc(strlen("viewattrname") + 1);
	strcpy(insert2[4], "viewattrname");
	insert2[5] = malloc(MAXNAME*sizeof(char));
	
	strcpy(va.relname, v.relname1);
	insert2[6] = malloc(strlen("relname") + 1);
	strcpy(insert2[6], "relname");
	insert2[7] = malloc(MAXNAME*sizeof(char));
	strcpy(insert2[7], va.relname);

	insert2[8] = malloc(strlen("relattrname")+1);
	strcpy(insert2[8], "relattrname");
	insert2[9] = malloc(MAXNAME*sizeof(char));
	
	insert2[10] = NULL;

	for (i = 4 ; i <= 2*N+2 ; i+=2) {
		strcpy(insert2[5], argv[i]);
		strcpy(insert2[9], argv[i]);
		if (DM_insert(10, insert2) < 0) {
			fprintf(stderr, "Error in DM_insert called in VW_CreateSelect for viewAttrCat file!\n");
			return VWE_DMERROR;
		}
	}
	
	for (i = 0 ; i < 10 ; i++) {
		free(insert2[i]);
	}
	
	for (i = 0 ; i < 20 ; i++) {
		free(insert[i]);
	}

	return VWE_OK;
}


/* Implementation of VW_CreateJoin function */
int VW_createJoin(int argc, char* argv[])
{
	int N;		// number of relations
	int i;
	char condition;
	char *insert[21];
	char *insert2[11];
	int attrCounter;
	viewDesc v;
	viewAttrDesc va;
	relDesc r;
	attrDesc *a;

	/* Implementation */

	strcpy(argv[0], "join");
	if (DM_join(argc, argv) < 0) {
		fprintf(stderr, "Error in DM_select called in VW_CreateSelect!\n");
		return VWE_DMERROR;
	}


	/* Check if the optional fields exist or not */
	N = atoi(argv[2]);

	/* Initialize struct viewDesc */
	strcpy(v.viewname, argv[1]);
	v.type = JOIN;
	strcpy(v.relname1, argv[argc-5]);
	strcpy(v.attrname1, argv[argc-4]);
	strcpy(v.relname2, argv[argc-2]);
	strcpy(v.attrname2, argv[argc-1]);
	if (strcmp("=", argv[argc - 3]) == 0) v.op = EQUAL;
	else if (strcmp("<", argv[argc - 3]) == 0) v.op = LESS_THAN;
	else if (strcmp(">", argv[argc - 3]) == 0) v.op = GREATER_THAN;
	else if (strcmp("<=", argv[argc - 3]) == 0) v.op = LESS_THAN_OR_EQUAL;
	else if (strcmp(">=", argv[argc - 3]) == 0) v.op = GREATER_THAN_OR_EQUAL;
	else if (strcmp("!=", argv[argc - 3]) == 0) v.op = NOT_EQUAL;
	/* return error for wrong operator */
	else {
		fprintf(stderr, "Wrong op given!\n");
		return VWE_ERROR;
	}
	v.attrcnt = N;

	/*insert sto arxeio viewCat*/
	insert[0] = malloc(strlen("insert")+1);
	strcpy(insert[0], "insert");
	insert[1] = malloc(strlen("viewCat") + 1);
	strcpy(insert[1], "viewCat");
	insert[2] = malloc(strlen("viewname")+1);
	strcpy(insert[2], "viewname");
	insert[3] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[3], v.viewname);
	insert[4] = malloc(strlen("type")+1);
	strcpy(insert[4], "type");
	insert[5] = malloc(sizeof(int));
	sprintf(insert[5], "%d", v.type);
	insert[6] = malloc(strlen("relname1")+1);
	strcpy(insert[6],"relname1");
	insert[7] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[7], v.relname1);
	insert[8] = malloc(strlen("attrname1")+1);
	strcpy(insert[8],"attrname1");
	insert[9] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[9], v.attrname1);
	insert[10] = malloc(strlen("op") + 1);
	strcpy(insert[10],"op");
	insert[11] = malloc(sizeof(int));
	sprintf(insert[11], "%d", v.op);
	insert[12] = malloc(strlen("relname2")+1);
	strcpy(insert[12],"relname2");
	insert[13] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[13], v.relname2);
	insert[14] = malloc(strlen("attrname2")+1);
	strcpy(insert[14],"attrname2");
	insert[15] = malloc(MAXNAME*sizeof(char));
	strcpy(insert[15], v.attrname2);	
	insert[16] = malloc(strlen("value")+1);
	strcpy(insert[16], "value");
	insert[17] = malloc(MAXSTRINGLENGTH*sizeof(char));
	memcpy(insert[17], v.value, MAXSTRINGLENGTH*sizeof(char));
	insert[18] = malloc(strlen("attrcnt")+1);
	strcpy(insert[18], "attrcnt");
	insert[19] = malloc(sizeof(int));
	sprintf(insert[19], "%d", v.attrcnt);
	insert[20] = NULL;

	if (DM_insert(20, insert) < 0) {
		fprintf(stderr, "Error in DM_insert called in VW_CreateSelect for viewCat file!\n");
		return VWE_DMERROR;
	}

	for (i = 0 ; i < 20 ; i++) {
		free(insert[i]);
	}

	/* take info for relName or return error if necessary */
	if (UT_relInfo(v.viewname, &r, &a) < 0) {
		return VWE_UTERROR;
	}

	/* update struct viewattrcat and the file*/
	insert2[0] = malloc(strlen("insert")+1);
	strcpy(insert2[0], "insert");
	insert2[1] = malloc(strlen("viewAttrCat")+1);
	strcpy(insert2[1], "viewAttrCat");

	strcpy(va.viewname, v.viewname);
	insert2[2] = malloc(strlen("viewname")+1);
	strcpy(insert2[2], "viewname");
	insert2[3] = malloc(MAXNAME*sizeof(char));
	strcpy(insert2[3], va.viewname);
	
	insert2[4] = malloc(strlen("viewattrname") + 1);
	strcpy(insert2[4], "viewattrname");
	insert2[5] = malloc(MAXNAME*sizeof(char));
	
	strcpy(va.relname, v.relname1);
	insert2[6] = malloc(strlen("relname") + 1);
	strcpy(insert2[6], "relname");
	insert2[7] = malloc(MAXNAME*sizeof(char));
	

	insert2[8] = malloc(strlen("relattrname")+1);
	strcpy(insert2[8], "relattrname");
	insert2[9] = malloc(MAXNAME*sizeof(char));
	
	insert2[10] = NULL;
	attrCounter = 0;
	for (i = 3 ; i <= 2*N+1 ; i+=2) {
		strcpy(insert2[5], a[attrCounter].attrname);
		strcpy(insert2[7], argv[i]);
		strcpy(insert2[9], argv[i+1]);
		if (DM_insert(10, insert2) < 0) {
			fprintf(stderr, "Error in DM_insert called in VW_CreateSelect for viewAttrCat file!\n");
			return VWE_DMERROR;
		}
		attrCounter += 1;
	}
	
	for (i = 0 ; i < 10 ; i++) {
		free(insert2[i]);
	}

	return VWE_OK;

}


/* Implementation of VW_Destroy function */
int VW_destroy(int argc, char* argv[])
{
	/* Declarations */
	char *firstargument;
	int i = 1;
	char *delete[6];
	viewDesc v;

	/* Implementation */

	/* Check if a view is depended on the file we are going to destroy */
	while (viewCatFunction(&v, NULL, i) >= 0) {
		if (strcmp(argv[1], v.relname1) == 0 || strcmp(argv[1], v.relname2) == 0) {
			fprintf(stderr, "You try to destroy a file that is depended on the file we are going to destroy!\n");
			return VWE_ERROR;
		}
		i += 1;
	}

	/* Seperate the cases of DESTROY and DESTROY MVIEW */
	/* DESTROY */
	if (strcmp(argv[0], "destroy") == 0) {
		/* check if it's a view and return error if necessary */
		i = 1;
		while (viewCatFunction(&v, NULL, i) >= 0) {
			if (strcmp(argv[1], v.viewname) == 0) {
				fprintf(stderr, "You try to destroy a View!\n");
				return VWE_ERROR;
			}
			i += 1;
		}
		/* Use UT_destroy */
		if (UT_destroy(argc,argv) < 0) {
			fprintf(stderr, "Error in UT_destroy function used in VW_destroy!\n");
			return VWE_UTERROR;
		}
	}
	/* DESTROY MVIEW */
	else if (strcmp(argv[0], "destroyMView") == 0) {
		/* check if it's a view and return error if necessary */
		if (viewCatFunction(&v, argv[1], 1) < 0) {
			fprintf(stderr, "That's not a View!\n");
			return VWE_ERROR;
		}

		strcpy(argv[0], "destroy");
		/* use UT_destroy */
		if (UT_destroy(argc,argv) < 0) {
			fprintf(stderr, "Error in UT_destroy function used in VW_destroy!\n");
			return VWE_UTERROR;
		}

		/* Delete from viewCat and viewAttrCat files */
		delete[0] = malloc(strlen("delete") + 1);
		strcpy(delete[0], "delete");
		delete[1] = malloc (MAXNAME*sizeof(char));
		strcpy (delete[1], "viewCat");
		delete[2] = malloc (MAXNAME*sizeof(char));
		strcpy(delete[2], "viewname");
		delete[3] = malloc (strlen("=")+1);
		strcpy(delete[3], "=");
		delete[4] = malloc (strlen(argv[1])+1);
		strcpy(delete[4], argv[1]);
		delete[5] = NULL;

		if (DM_delete(5, delete) < 0) {
			fprintf(stderr, "Error in DM_delete called in VW_destroy function!\n");
			return VWE_DMERROR;
		}

		strcpy (delete[1], "viewAttrCat");
		if (DM_delete(5, delete) < 0) {
			fprintf(stderr, "Error in DM_delete called in VW_destroy function!\n");
			return VWE_DMERROR;
		}

		for (i = 0 ; i < 5 ; i++) free(delete[i]);
	}
	/* error */
	else {
		fprintf(stderr, "Wrong operand in VW_Destroy function!\n");
		return VWE_ERROR;
	}

	return VWE_OK;
}


/* Implementation of VW_Insert function */
int VW_insert(int argc, char* argv[])
{
	/* Declarations */
	int i, attrCounter;
	int error;
	char *TEMP;
	char *firstName;
	char **create;
	char *destroy[3];
	relDesc fromRelDesc;
	attrDesc* fromRelAttrs;
	viewDesc v;

	/* Implementation */



	/* take info for relName or return error if necessary */
	if (UT_relInfo(argv[1], &fromRelDesc, &fromRelAttrs) < 0) {
		return VWE_UTERROR;
	}



	TEMP = malloc(strlen("temp") + 5);
	memset(TEMP, 0, strlen("temp") + 4);
	sprintf(TEMP, "temp%d", temp_counter);
	temp_counter++;

	/* allocate memory for UT_create arguments */
	create = malloc ((2*fromRelDesc.attrcnt+3) * sizeof(char *));

	create[0] = malloc(strlen("create")+1);
	strcpy(create[0], "create");
	create[1] = malloc(strlen(TEMP)+1);
	strcpy(create[1], TEMP);
	attrCounter = 0;
	for (i = 2 ; i < 2*fromRelDesc.attrcnt+1 ; i+=2) {
		create[i] = malloc(MAXNAME*sizeof(char));
		strcpy(create[i], fromRelAttrs[attrCounter].attrname);
		if (fromRelAttrs[attrCounter].attrtype == 'i' || fromRelAttrs[attrCounter].attrtype == 'f') {
			create[i+1] = malloc(sizeof(int));
			sprintf(create[i+1], "'%c'", fromRelAttrs[attrCounter].attrtype);
		}
		else {
			create[i+1] = malloc(7*sizeof(char));
			sprintf(create[i+1], "'%c%d'", fromRelAttrs[attrCounter].attrtype, fromRelAttrs[attrCounter].attrlength);
		}
		attrCounter++;
	}
	create[2*fromRelDesc.attrcnt+2] = NULL;


	/* create a temporary file */
	error = UT_create (2*fromRelDesc.attrcnt+2, create);
	if (error < 0) {
		fprintf(stderr, "Error while calling UT_create in VW_insert function! : %d\n", error);
		return VWE_UTERROR;
	}

	firstName = malloc(MAXNAME);
	strcpy(firstName, argv[1]);
	argv[1] = TEMP;
	if (DM_insert(argc, argv) < 0) {
		fprintf(stderr, "Error while calling DM_insert in VW_insert function!\n");
		return VWE_DMERROR;
	}

	
	argv[1] = firstName;

	/* Call recursive update function */

	i=1;
	while (viewCatFunction(&v, NULL, i) >= 0) {
		if (strcmp(v.relname1, argv[1]) == 0 || strcmp(v.relname2, argv[1]) == 0) {
			recursive_update(v.viewname, argv[1], TEMP, 0);
		}
		i++;
	}

	/* Destroy the temporary file */
	destroy[0] = malloc(strlen("destroy") + 1);
	strcpy(destroy[0], "destroy");
	destroy[1] = malloc(strlen(TEMP) + 1);
	strcpy(destroy[1], TEMP);
	destroy[2] = NULL;
	if (UT_destroy(2, destroy) < 0) {
		fprintf(stderr, "Error in UT_destroy in VW_insert function!\n");
		return VWE_DMERROR;
	}

	/* use DM_insert for inserting the record */
	if (DM_insert(argc,argv) < 0) {
		fprintf(stderr, "Error while calling DM_insert in VW_insert function!\n");
		return VWE_DMERROR;
	}

	/* free allocated memory */
	free(TEMP);
	for (i = 0 ; i < 2*fromRelDesc.attrcnt+2 ; i++)
		free(create[i]);
	free(create);
	for (i = 0 ; i<2 ; i++) free(destroy[i]);
	free(firstName);
	free(fromRelAttrs);
	return VWE_OK;
}


/* Implementation of VW_Delete function */
int VW_delete(int argc, char* argv[])
{
	/* Declarations */
	int i;
	int size;
	int counter=0;
	char condition;
	char *TEMP;
	char **create;
	char **select;
	char *destroy[3];
	relDesc fromRelDesc;
	attrDesc* fromRelAttrs;
	viewDesc v;

	/* Implementation */

	/* Check if the optional fields exist or not */
	if (argc == 2)
		condition = 0;
	else if (argc == 5)
		condition = 1;
	else {
		fprintf(stderr, "Wrong number of operands!\n");
		return VWE_ERROR;
	}

	/* take info for relName or return error if necessary */
	if (UT_relInfo(argv[1], &fromRelDesc, &fromRelAttrs) < 0) {
		return VWE_UTERROR;
	}

	TEMP = malloc(strlen("temp") + 5);
	memset(TEMP, 0, strlen("temp") + 5);
	sprintf(TEMP, "temp%d", temp_counter);
	temp_counter++;

	if (condition == 0)
		size = 4 + 2*fromRelDesc.attrcnt;
	else
		size = 8 + 2*fromRelDesc.attrcnt;

	/* allocate memory buffer to use DM_insert */
	select = malloc (size * sizeof(char *));
	if (select == NULL) {
		fprintf(stderr, "Cannot allocate memory buffer\n");
		return VWE_ERROR;
	}

	select[0] = malloc(strlen("select")+1);
	strcpy(select[0], "select");
	select[1] = malloc (strlen(TEMP)+1);
	strcpy (select[1], TEMP);
	select[2] = malloc (sizeof(int));
	sprintf(select[2], "%d", fromRelDesc.attrcnt);
	for (i = 3 ; i < 3 + 2*fromRelDesc.attrcnt ; i+=2) {
		select[i] = malloc (MAXNAME*sizeof(char));
		strcpy(select[i], argv[1]);
		select[i+1] = malloc (MAXNAME*sizeof(char));
		strcpy(select[i+1], fromRelAttrs[counter].attrname);
		counter += 1;
	}
	if (condition == 1) {
		select[size-5] = malloc (MAXNAME*sizeof(char));
		strcpy(select[size-5], argv[1]);
		select[size-4] = malloc (MAXNAME*sizeof(char));
		strcpy(select[size-4], argv[2]);
		select[size-3] = malloc(sizeof(int));
		strcpy(select[size-3], argv[3]);
		select[size-2] = malloc(strlen(argv[4])+1);
		strcpy(select[size-2], argv[4]);
	}
	select[size-1] = NULL;

	/* Use DM_insert to insert all records that agree to the condition given */
	
	if (DM_select(size-1, select) < 0) {
		fprintf(stderr, "Error while calling DM_insert in VW_insert function!\n");
		return VWE_DMERROR;
	}

	for (i = 0 ; i < size-1 ; i++) {
		free(select[i]);
	}
	free(select);

	/* Call recursive update function */
	i=1;
	while (viewCatFunction(&v, NULL, i) >= 0) {
		if (strcmp(v.relname1, argv[1]) == 0 || strcmp(v.relname2, argv[1]) == 0) {
			recursive_update(v.viewname, argv[1], TEMP, 1);
		}
		i++;
	}

	/* Destroy the temporary file */
	destroy[0] = malloc(strlen("destroy") + 1);
	strcpy(destroy[0], "destroy");
	destroy[1] = malloc(strlen(TEMP) + 1);
	strcpy(destroy[1], TEMP);
	destroy[2] = NULL;
	if (UT_destroy(2, destroy) < 0) {
		fprintf(stderr, "Error in UT_destroy in VW_insert function!\n");
		return VWE_DMERROR;
	}
	for (i = 0 ; i<2 ; i++) free(destroy[i]);

	/* free allocated memory */
	free(TEMP);

	/* use DM_delete for deleting the records */
	if (DM_delete(argc, argv) < 0) {
		fprintf(stderr, "Error while calling DM_delete in VW_insert function!\n");
		return VWE_DMERROR;
	}

	return VWE_OK;
}
