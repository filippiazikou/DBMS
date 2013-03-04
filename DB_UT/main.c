#include<stdio.h>
#include<stdlib.h>
#include"parser3.h"

void printArgs(int argc, char **argv){
	int i;
	for(i=0;i<argc;++i)
		printf("argv[%d]=%s\n",i,argv[i]);
	printf("argv[%d]=(null)\n\n", i);
	fflush(stdout);
}

int UT_create(int argc,char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int UT_buildindex(int argc,char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int UT_destroy(int argc,char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int UT_quit(void){
	printf("QUIT\n");
	exit(0);
	return 0;
}
int DM_select(int argc, char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int DM_join(int argc, char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int DM_delete(int argc, char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int DM_subtract(int argc,char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int DM_insert(int argc,char* argv[]){
	printArgs(argc,argv);
	return 0;
}

int DM_add(int argc,char* argv[]){
	printArgs(argc,argv);
	return 0;
}


int main(){
	while(yyparse() == RESTART);

	return 0;
}
