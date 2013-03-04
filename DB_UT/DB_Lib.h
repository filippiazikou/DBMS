#ifndef __DB_LIB__                                             
#define __DB_LIB__ 



#include <stdio.h>



#define TRUE 1
#define FALSE 0
#define DBE_HFERROR -1


/* global file descriptors */
int relCatFileDesc;
int attrCatFileDesc;
int viewCatFileDesc;
int viewAttrCatFileDesc;


/* struct for relCat file */
typedef struct {
	char relName[MAXNAME];	/* name of table */
	int relWidth;		/* width of table in bytes */
	int attrCnt;		/* number of fields */
	int indexCnt;		/* number of table indexes */
} relDesc; 


/* struct for attrCat file */
typedef struct {
	char relName[MAXNAME];	/* name of table */
	char attrName[MAXNAME];	/* name of table's field */
	int offset;		/* distance between the begin of field and the begin of record in bytes */
	int attrLength;	/* length of field in bytes */
	char attrType;	/* type of field ('i', 'f', ή 'c') */
	int indexed;	/* TRUE if the field has index */
	int indexNo;	/* number of the index if indexed = TRUE */
} attrDesc; 


/* struct for viewCat file */
typedef struct {
	char viewname[MAXNAME];
	int type;
	char relname1[MAXNAME];
	char attrname1[MAXNAME];
	int op;
	char relname2[MAXNAME];
	char attrname2[MAXNAME];
	char value[MAXSTRINGLENGTH];
	int attrcnt;
} viewDesc;

/* struct for viewAttrCat file */
typedef struct {
        char viewName[MAXNAME];
        char viewAttrName[MAXNAME];
        char relName[MAXNAME];
        char relAttrName[MAXNAME];
} viewAttrDesc;


#endif
