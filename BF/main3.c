#include <stdio.h>
#include <string.h>
#include "BF_Lib.h"

#define BF_MAIN_NAME_SIZE 30
#define BF_MAIN_EVENT_NAME_SIZE 60
#define BF_MAIN_DATE_SIZE 12
#define BF_MAIN_MAX_NUM_OF_RECS 16
#define BF_MAIN_MAX_NUM_OF_EVENT_RECS 50

int main()
{
	int athletesFd;
	int athletesBlockNum;
	char *athletesBlockBuf;
	int athleteId;
	char athleteName[BF_MAIN_NAME_SIZE];
	char athleteSurName[BF_MAIN_NAME_SIZE];

	/* Αρχικοποίηση του επιπέδου αρχείου μπλοκ */
	BF_Init();
	
	/* ’νοιγμα του αρχείου ATHLETES */
	athletesFd = BF_OpenFile("ATHLETES");
	if (athletesFd < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on ATHLETES.");
		return;
	}

	/* Εκτύπωση όλων των αθλητών */
	if (BF_GetFirstBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetFirstBlock called on ATHLETES.");

	printf("File ATHLETES contains the following athletes:\nID  NAME\n--- ----------------------------\n");

	do
	{
		int i;

		for (i = 0; i < BF_MAIN_MAX_NUM_OF_RECS; i++)
		{
			athleteId = * (int *) athletesBlockBuf;
			athletesBlockBuf += sizeof(int);
			strcpy(athleteName, athletesBlockBuf);
			athletesBlockBuf += BF_MAIN_NAME_SIZE;
			strcpy(athleteSurName, athletesBlockBuf);
			athletesBlockBuf += BF_MAIN_NAME_SIZE;

			if (strlen(athleteName) == 0) break;
			
			printf("%03d %s %s\n", athleteId, athleteName, athleteSurName);
		}
		BF_UnpinBlock(athletesFd, athletesBlockNum, FALSE);
	} while(BF_GetNextBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf) == BFE_OK);


	printf("\n**********************\n\n");

	/* Κλείσιμο του αρχείου ATHLETES. */
	if (BF_CloseFile(athletesFd) < 0)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");

	/* Σβήσιμο των τριών αρχείων */
	if (BF_DestroyFile("EVENTS") != BFE_OK)
		BF_PrintError("Error in BF_DestroyFile called on EVENTS.");
	else printf("File EVENTS successfully destroyed.\n");

	if (BF_DestroyFile("ATHLETES") != BFE_OK)
		BF_PrintError("Error in BF_DestroyFile called on ATHLETES.");
	else printf("File ATHLETES successfully destroyed.\n");
	
	if (BF_DestroyFile("PARTICIPATIONS") != BFE_OK)
		BF_PrintError("Error in BF_DestroyFile called on PARTICIPATIONS.");
	else printf("File PARTICIPATIONS successfully destroyed.\n");

	return 0;
}
