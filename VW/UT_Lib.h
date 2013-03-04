#ifndef __UT_LIB_H__
#define __UT_LIB_H__

#include "defn.h"

#define OK 0
#define WRONG_USAGE -1
#define CANNOT_CREATE_DATABASE -2
#define MALLOC_ERROR -3
#define UTE_INVALID_ARGUMENTS -4
#define UTE_FILE_ALREADY_EXISTS -5
#define UTE_CREATE_FILE_ERROR -6
#define UTE_INSERT_ERROR -7
#define UTE_INVALID_TYPE -8
#define UTE_MALLOC_ERROR -9
#define UTE_REC_NOT_FOUND -10
#define UTE_SEARCHING_REC -11
#define UTE_ATTR_ALREADY_INDEXED -12
#define UTE_CREATE_INDEX_ERROR -13
#define UTE_OPEN_ERROR -14
#define UTE_GETTING_REC -15
#define UTE_CLOSE_ERROR -16
#define UTE_DELETE_ERROR -17
#define UTE_FILE_NOT_EXISTS -18
#define UTE_DESTROY_ERROR -19
#define UTE_CLOSE_SCAN_ERROR -20
#define UTE_OPEN_SCAN_ERROR -21

/* Utility Functions   */
int UT_create(int argc,char* argv[]);
int UT_buildindex(int argc,char* argv[]);
int UT_destroy(int argc,char* argv[]);
int UT_relInfo(char* relname, relDesc *rel, attrDesc** attrs);
int UT_quit(void);

#endif   /*  __UT_LIB_H__  */

