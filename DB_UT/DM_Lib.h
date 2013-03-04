#ifndef __DM_LIB__                                             
#define __DM_LIB__                                             

#pragma pack (1)

#include <stdio.h>

#define DME_OK 0
#define DME_HFERROR -1
#define DME_ERROR -2
#define DME_AMERROR -3

/* Declaration of DM functions */

int DM_select(int argc, char* argv[]);
int DM_join(int argc, char* argv[]);
int DM_delete(int argc, char* argv[]);
int DM_subtract(int argc,char* argv[]);
int DM_insert(int argc,char* argv[]);
int DM_add(int argc,char* argv[]);

#endif
