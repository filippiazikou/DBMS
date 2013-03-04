#include <stdio.h>
#include <stdlib.h>

#include "DB_Lib.h"
#include "UT_Lib.h"
#include "DM_Lib.h"
#include "HF_Lib.h"
#include "AM_Lib.h"
#include "BF_Lib.h"
#include "parser3.h"


int main(int argc, char* argv[]) {
	char command[80];
	char* dbname;

	HF_Init();
	AM_Init();

	if(argc != 2) {
		printf("Χρήση: %s aminirel \n", argv[0]);
		return(1);
	}
	dbname=argv[1];
	sprintf(command, "chdir %s", dbname);
	system(command);
	if (chdir(dbname)) {
		printf("Δεν είναι δυνατή η δημιουργία της βάσης\n");
		return (2);
	}


	relCatFileDesc = HF_OpenFile(RELCAT);
	if (relCatFileDesc < 0) {
		printf ("Error in opening relCat. Error = %d\n", relCatFileDesc);
		exit(0);
	}

	attrCatFileDesc = HF_OpenFile(ATTRCAT);
	if (attrCatFileDesc < 0) {
		printf ("Error in opening relCat. Error = %d\n", attrCatFileDesc);
		exit(0);
	} 

	viewCatFileDesc = HF_OpenFile(VIEWCAT);
	if (viewCatFileDesc < 0) {
		printf ("Error in opening relCat. Error = %d\n", viewCatFileDesc);
		exit(0);
	} 

	viewAttrCatFileDesc = HF_OpenFile(VIEWATTRCAT);
	if (viewAttrCatFileDesc < 0) {
		printf ("Error in opening relCat. Error = %d\n", viewAttrCatFileDesc);
		exit(0);
	} 

	while(yyparse() == RESTART);

	return 0;
}

