#ifndef __AM_LIB__
#define __AM_LIB__

#include <stdio.h>

#define MAXSCANS 20

#define TRUE 1
#define FALSE 0
#define AME_OK 0
#define AME_BFERROR -1	//error that concern BF level
#define AME_TYPEERROR -2	//wrong attrType given
#define AME_NOTOPEN -3
#define AME_OS -4	//General error of the Operating System
#define AME_RECID -5	//Wrong recId given
#define AME_SCANERROR -6	//scanDesc error
#define AME_EOF -7

/* Helping functions */
char is_bit_set(char data,int n);
char clear_bit(char data,int n);
char set_bit(char data,int n);

/* struct for scan */
typedef struct IndexScan scan;

struct IndexScan {
	int fileDesc;
	int op;
	char *value;
	int record;	//teleytaia eggrafi pou elegxthike
	int hashNum;	//thesi tou pinaka katalermatismou pou exei to blocknum pou elegxoume
	char attrType;
	int attrLength;
	int max_recs;
};

scan s[MAXSCANS];

/* Declaration of hash function */
unsigned char JSHash(char* str, unsigned int len);

/* Declaration of functions */
void AM_Init(void);
int AM_CreateIndex(char *fileName, int indexNo, char attrType, int attrLength);
int AM_DestroyIndex(char *fileName, int indexNo);
int AM_OpenIndex(char *fileName, int indexNo);
int AM_CloseIndex(int fileDesc);
int AM_InsertEntry(int fileDesc, char attrType, int attrLength, char *value, int recId);
int AM_DeleteEntry (int fileDesc, char attrType, int attrLength, char *value, int recId);
int AM_OpenIndexScan (int fileDesc, char attrType, int attrLength, int op, char *value);
int AM_FindNextEntry (int scanDesc);
int AM_CloseIndexScan (int scanDesc);
void AM_PrintError (char *errString);

#endif
