#ifndef __VW_LIB__
#define __VW_LIB__

#include <stdio.h>

#define VWE_OK 0
#define NO 1
#define SELECT 2
#define JOIN 3
#define VWE_ERROR -1
#define VWE_DMERROR -2
#define VWE_UTERROR -3
#define VWE_HFERROR -4


/* Declaration of helping functions */
int viewCatFunction(viewDesc *v, char *name, int number);
int viewAttrCatFunction(viewAttrDesc *va, char *nameFile, int fieldNum);
int recursive_update(char *V, char *relName, char *temp, int flag);
void printArgs(int argc, char **argv);

/* Declaration of VM functions */

int VW_createSelect(int argc, char* argv[]);
int VW_createJoin(int argc, char* argv[]);
int VW_destroy(int argc, char* argv[]);
int VW_insert(int argc, char* argv[]);
int VW_delete(int argc, char* argv[]);

#endif
