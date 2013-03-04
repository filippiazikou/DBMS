#include<stdio.h>
#include"DM_Lib.h"
#include"UT_Lib.h"

void printArgs(int argc, char **argv){
	int i;
	for(i=0;i<argc;++i)
		printf("argv[%d]=%s\n",i,argv[i]);
	printf("argv[%d]=(null)\n\n", i);
	fflush(stdout);
}

int VW_createSelect(int argc, char *argv[]){
	printArgs(argc,argv);
	return 0;
}

int VW_createJoin(int argc, char *argv[]){
	printArgs(argc,argv);
	return 0;
}

int VW_delete(int argc, char *argv[]){
	return DM_delete(argc,argv);
}

int VW_insert(int argc, char *argv[]){
	return DM_insert(argc,argv);
}

int VW_destroy(int argc, char *argv[]){
	return UT_destroy(argc,argv);
}

