#ifndef __UT_LIB__                                             
#define __UT_LIB__ 

#include <stdio.h>

#define MAXSTRINGLENGTH 255
#define UTE_HFERROR -1
#define UTE_ERROR -2
#define UTE_AMERROR -3

#define RELCAT "relCat"
#define ATTRCAT "attrCat"
#define VIEWCAT "viewCat"
#define VIEWATTRCAT "viewAttrCat"


/* Declaration of UT functions */

int UT_create(int argc,char* argv[]);
int UT_buildindex(int argc,char* argv[]);
int UT_destroy(int argc,char* argv[]);
int UT_quit(void);

#endif

