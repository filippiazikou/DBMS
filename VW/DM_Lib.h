#ifndef __DM_LIB_H__
#define __DM_LIB_H__

#define DME_OK 0
#define DME_INVALID_ARGUMENTS -1
#define DME_MALLOC_ERROR -2
#define DME_INVALID_RELNAME -3
#define DME_INVALID_ATTRIBUTE -4
#define DME_OPEN_ERROR -5
#define DME_FILE_NOT_EXISTS -6
#define DME_OPEN_SCAN_ERROR -7
#define DME_CLOSE_SCAN_ERROR -8
#define DME_GET_REC_ERROR -9
#define DME_INSERT_ERROR -10
#define DME_SEARCH_REC_ERROR -11
#define DME_CREATE_FILE_ERROR -12
#define DME_CREATE_INDEX_ERROR -13
#define DME_FILE_ALREADY_EXISTS -14
#define DME_INVALID_TYPE -15
#define DME_CLOSE_ERROR -16
#define DME_DELETE_ERROR -17
#define DME_DESTROY_ERROR -19 
#define DME_STRDUP_ERROR -20
#define DME_SELECT_ERROR -21
#define DME_REC_NOT_FOUND -22
#define DME_ATTR_ALREADY_INDEXED -23
#define DME_INVALID_OPERATOR -24
#define DME_INCOMPATIBLE_VALUE -25
#define DME_TOO_MANY_COLUMNS -26
#define DME_HF_ERROR -27
#define DME_AM_ERROR -28
#define DME_NOTCOMPATIBLE -29 

/* Data Manipulation Functions  */
int DM_select(int argc, char* argv[]);
int DM_join(int argc, char* argv[]);
int DM_delete(int argc, char* argv[]);
int DM_insert(int argc,char* argv[]);
int DM_add(int argc,char* argv[]);
int DM_subtract(int argc,char* argv[]);


#endif   /*  __DM_LIB_H__  */
