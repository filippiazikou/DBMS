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
	int flag;

	int eventsFd;
	int eventsBlockNum;
	char *eventsBlockBuf;
	int eventId;
	int eventId1;
	char eventName[BF_MAIN_EVENT_NAME_SIZE];
	int eventBlockCounter;

	int athletesFd;
	int athletesBlockNum;
	char *athletesBlockBuf;
	int athleteId;
	char athleteName[BF_MAIN_NAME_SIZE];
	char athleteSurName[BF_MAIN_NAME_SIZE];

	int athletesFd1;
	int athletesBlockNum1;
	int athletesBlockNum2;
	int athletesBlockNum3;
	char *athletesBlockBuf1;
	int athleteId1;

	int athletesFd2;
	int athletesBlockNum4;
	char *athletesBlockBuf2;

	int participationsFd;
	int participationsBlockNum;
	char *participationsBlockBuf;
	char participationDate[BF_MAIN_DATE_SIZE];
	
	
	int block=0;
	int disposeBlock=0;
	char *athletesBlockBufDisp;


	/* Αρχικοποίηση του επιπέδου αρχείου μπλοκ */
	BF_Init();
	
	/* ’νοιγμα τριών αρχείων */
	eventsFd = BF_OpenFile("EVENTS");
	if (eventsFd < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on EVENTS.");
		return;
	}

	athletesFd = BF_OpenFile("ATHLETES");
	if (athletesFd < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on ATHLETES.");
		return;
	}

	participationsFd = BF_OpenFile("PARTICIPATIONS");
	if (participationsFd < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on PARTICIPATIONS.");
		return;
	}

	/* ’νοιγμα του αρχείου ATHLETES 2η φορά */
	athletesFd1 = BF_OpenFile("ATHLETES");
	if (athletesFd1 < 0)
	{
		BF_PrintError("Error in BF_OpenFile called on ATHLETES.");
		return;
	}

	/* Εκτύπωση όλων των αθλημάτων */
	if (BF_GetFirstBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetFirstBlock called on EVENTS.");

	printf("File EVENTS contains the following events:\nID NAME\n-- ----------------------------\n");
	do
	{
		int i;

		for (i = 0; i < BF_MAIN_MAX_NUM_OF_RECS; i++)
		{
			eventId = * (int *) eventsBlockBuf;
			eventsBlockBuf += sizeof(int);
			strcpy(eventName, eventsBlockBuf);
			eventsBlockBuf += BF_MAIN_EVENT_NAME_SIZE;

			if (strlen(eventName) == 0) break;
			
			printf("%02d %s\n", eventId, eventName);
		}
		BF_UnpinBlock(eventsFd, eventsBlockNum, FALSE);
	} while(BF_GetNextBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf) == BFE_OK);

	printf("\n**********************\n\n");

	/* Διαγραφή του 1ου μπλοκ από το αρχείο ATHLETES χρησιμοποιώντας το 2ο άνοιγμα. */
	athletesBlockNum1 = 0;
	
	/* Εκτύπωση όλων των αθλημάτων */
	if (BF_GetFirstBlock(athletesFd1, &athletesBlockNum1, &athletesBlockBufDisp) != BFE_OK)
		BF_PrintError("Error in BF_GetFirstBlock called on EVENTS.");	
	BF_UnpinBlock(athletesFd1, athletesBlockNum1, FALSE);

	printf("Before dispose: First block is %d\n", athletesBlockNum1);
		
	if (BF_DisposeBlock(athletesFd1, &athletesBlockNum1) == BFE_OK)
		printf("Block %d successfully disposed from file ATHLETES.\n", athletesBlockNum1);
	else
		BF_PrintError("Error in BF_DisposeBlock called on ATHLETES.");

	printf("\n**********************\n\n");

	/* ’νοιγμα του αρχείου ATHLETES για 3η φορά και εκτύπωση όλων των αθλητών. */
	athletesFd2 = BF_OpenFile("ATHLETES");

	if (BF_GetFirstBlock(athletesFd2, &athletesBlockNum4, &athletesBlockBuf2) != BFE_OK)
		BF_PrintError("Error in BF_GetFirstBlock called on ATHLETES.");

	printf("After dispose: First block is %d\n", athletesBlockNum4);

	printf("File ATHLETES contains the following athletes:\nID  NAME\n--- ----------------------------\n");

	do
	{
		int i;

		if(block == 1)
			disposeBlock = athletesBlockNum4;
		for (i = 0; i < BF_MAIN_MAX_NUM_OF_RECS; i++)
		{
			athleteId = * (int *) athletesBlockBuf2;
			athletesBlockBuf2 += sizeof(int);
			strcpy(athleteName, athletesBlockBuf2);
			athletesBlockBuf2 += BF_MAIN_NAME_SIZE;
			strcpy(athleteSurName, athletesBlockBuf2);
			athletesBlockBuf2 += BF_MAIN_NAME_SIZE;

			if (strlen(athleteName) == 0) break;
			
			printf("%03d %s %s\n", athleteId, athleteName, athleteSurName);
		}
		BF_UnpinBlock(athletesFd2, athletesBlockNum4, FALSE);
		block++;
	} while(BF_GetNextBlock(athletesFd2, &athletesBlockNum4, &athletesBlockBuf2) == BFE_OK);

	if (BF_CloseFile(athletesFd2) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");

	printf("\n**********************\n\n");

	/* Διαγραφή του 3ου μπλοκ από το αρχείο ATHLETES χρησιμοποιώντας το 2ο άνοιγμα. */
	athletesBlockNum1 = disposeBlock;
	if (BF_DisposeBlock(athletesFd1, &athletesBlockNum1) == BFE_OK)
		printf("Block %d successfully disposed from file ATHLETES.\n", athletesBlockNum1);
	else
		BF_PrintError("Error in BF_DisposeBlock called on ATHLETES.");

	printf("\n**********************\n\n");

	/* Ανάγνωση του νέου 1ου μπλοκ του αρχείου ATHLETES. Ο αριθμός του πρέπει να ισούται με 1 */
	if (BF_GetFirstBlock(athletesFd1, &athletesBlockNum1, &athletesBlockBuf1) != BFE_OK)
		BF_PrintError("Error in BF_GetFirstBlock called on ATHLETES.");
	else printf("The number of the first block in file ATHLETES is %d and is placed in memory address %d\n", athletesBlockNum1, athletesBlockBuf1);

	BF_UnpinBlock(athletesFd1, athletesBlockNum1, FALSE);

	/* Εκτύπωση των συμμετοχών του αθλητή AFROYDAKHS XRHSTOS */
	/* Πρώτα αναζητούμε τον κωδικό του αθλητή */
	if (BF_GetFirstBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetFirstBlock called on ATHLETES.");
	else printf("The following numbers must be equal: %d = %d, %d = %d\n", athletesBlockNum, athletesBlockNum1, athletesBlockBuf, athletesBlockBuf1);

	printf("\n**********************\n\n");

	flag = 0;
	do
	{
		int i;

		for (i = 0; i < BF_MAIN_MAX_NUM_OF_RECS; i++)
		{
			athleteId = * (int *) athletesBlockBuf;
			athletesBlockBuf += sizeof(int);
			strcpy(athleteSurName, athletesBlockBuf);
			athletesBlockBuf += BF_MAIN_NAME_SIZE;
			strcpy(athleteName, athletesBlockBuf);
			athletesBlockBuf += BF_MAIN_NAME_SIZE;

			if (strlen(athleteSurName) == 0) break;

			if (strcmp(athleteSurName, "XALKIDHS") == 0 && strcmp(athleteName, "GEVRGIOS") == 0)
			{
				flag = 1;
				break;
			}
		}
		BF_UnpinBlock(athletesFd, athletesBlockNum, FALSE);
		if (flag == 1) break;
	} while(BF_GetNextBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf) == BFE_OK);


	/* Έπειτα ψάχνουμε τις συμμετοχές όπου εμφανίζεται αθλητής με τον κωδικό του XALKIDHS GEVRGIOS */
	if (BF_GetFirstBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetFirstBlock called on PARTICIPATIONS.");

	do
	{
		int i;

		for (i = 0; i < BF_MAIN_MAX_NUM_OF_EVENT_RECS; i++)
		{
			eventId1 = * (int *) participationsBlockBuf;
			participationsBlockBuf += sizeof(int);
			athleteId1 = * (int *) participationsBlockBuf;
			participationsBlockBuf += sizeof(int);
			strcpy(participationDate, participationsBlockBuf);
			participationsBlockBuf += BF_MAIN_DATE_SIZE;

			if (strlen(athleteSurName) == 0) break;

			if (athleteId == athleteId1)
			{
				flag = 0;
				/* Βρίσκουμε και το άθλημα στο οποίο συμμετείχε */
				if (BF_GetFirstBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf) != BFE_OK)
					BF_PrintError("Error in BF_GetFirstBlock called on EVENTS.");
				eventBlockCounter = eventsBlockNum;

				do
				{
					int i;

					for (i = 0; i < BF_MAIN_MAX_NUM_OF_RECS; i++)
					{
						eventId = * (int *) eventsBlockBuf;
						eventsBlockBuf += sizeof(int);
						strcpy(eventName, eventsBlockBuf);
						eventsBlockBuf += BF_MAIN_EVENT_NAME_SIZE;

						if (strlen(eventName) == 0) break;

						if (eventId == eventId1)
						{
							flag = 1;
							break;
						}
					}
					/* Τα μπλοκ του αρχείου EVENT δεν ξεκαρφώνονται στο σημείο αυτό, αφού χρησιμοποιούνται
					   συνέχεια σε αυτόν τον εμφωλιασμένο βρόγχο. Κανονικά, οι BF_GetFirstBlock και
					   BF_GetNextBlock πρέπει να τα βρίσκουν στη μνήμη και να επιστρέφουν μόνο ένα δείκτη
					   χωρίς να μεταφέρουν τίποτα από το δίσκο. Το ξεκάρφωμα των μπλοκ γίνεται περίπου
					   15 γραμμές πιο κάτω, αφού ολοκληρωθούν οι εμφωλιασμένοι βρόγχοι. Το αρχείο EVENT
					   είναι μικρό και το κράτημα στη μνήμη των μπλοκ του δεν πρέπει να δημιουργεί προβλήματα 
					   στον αλγόριθμο αντικατάστασης. Η επόμενη γραμμή είναι εσκεμμένα σχολιασμένη. */
					/* BF_UnpinBlock(eventsFd, eventsBlockNum, FALSE); */
					if (flag == 1) break;
				} while(BF_GetNextBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf) == BFE_OK);

				/* Εκτύπωση της πληροφορίας που εντοπίσαμε */
				if (flag == 1)
					printf("%s %s played %s on %s\n", athleteName, athleteSurName, eventName, participationDate);
				else
					printf("%s %s participated in an unknown event on %s\n", athleteName, athleteSurName, participationDate);
			}
		}
		BF_UnpinBlock(participationsFd, participationsBlockNum, FALSE);
	} while(BF_GetNextBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf) == BFE_OK);

	/* Αφού τελείωσαν οι εμφωλιασμένοι βρόγχοι, απελευθερώνουμε τα μπλοκ του αρχείου EVENT. */
	while (BF_UnpinBlock(eventsFd, eventBlockCounter, FALSE) == BFE_OK)
	{
		eventBlockCounter++;
	}

	printf("\n**********************\n\n");

	/* Λανθασμένη προσπάθεια ανάγνωσης του σβησμένου μπλοκ 0 από το αρχείο ATHLETES */
	if (BF_GetThisBlock(athletesFd1, disposeBlock, &athletesBlockBufDisp) != BFE_OK)
		BF_PrintError("Expected error in BF_GetThisBlock called on ATHLETES.");
	else
	{
		printf("Block 0 in file ATHLETES should have been disposed!\n");
		BF_UnpinBlock(athletesFd1, disposeBlock, FALSE);
	}

	/* Δέσμευση νέου μπλοκ στο αρχείο ATHLETES χρησιμοποιώντας το 2ο άνοιγμα.
	   Πρέπει να πάρει κωδικό 0 ή 2 ανάλογα με την υλοποίηση */
	if (BF_AllocBlock(athletesFd1, &athletesBlockNum1, &athletesBlockBuf1) < 0)
		BF_PrintError("Error in BF_AllocBlock called on ATHLETES.");
	else
	{
		printf("The following number must be either 0 or 2 (asuming that blocks' counting starts from 0): %d\n", athletesBlockNum1);
		memset((void *) athletesBlockBuf1, 0, BF_BLOCK_SIZE);

		/* Εισαγωγή μίας ακόμη εγγραφής στο νέο μπλοκ */
		athleteId = 550;
		memcpy((void *) athletesBlockBuf1, (void *) &athleteId, sizeof(int));
		athletesBlockBuf1 += sizeof(int);
		strcpy(athletesBlockBuf1, "XARISTEAS");
		athletesBlockBuf1 += BF_MAIN_NAME_SIZE;
		strcpy(athletesBlockBuf1, "AGGELOS");
		athletesBlockBuf1 += BF_MAIN_NAME_SIZE;
		
		BF_UnpinBlock(athletesFd1, athletesBlockNum1, TRUE);
	}

	/* Δέσμευση νέου μπλοκ στο αρχείο ATHLETES χρησιμοποιώντας το 2ο άνοιγμα.
	   Πρέπει να πάρει κωδικό 0 ή 2 ανάλογα με την υλοποίηση */
	if (BF_AllocBlock(athletesFd1, &athletesBlockNum2, &athletesBlockBuf1) < 0)
		BF_PrintError("Error in BF_AllocBlock called on ATHLETES.");
	else
	{
		printf("The following number must be either 0 or 2 (asuming that blocks' counting starts from 0): %d\n", athletesBlockNum2);
		memset((void *) athletesBlockBuf1, 0, BF_BLOCK_SIZE);

		/* Εισαγωγή μίας ακόμη εγγραφής στο νέο μπλοκ */
		athleteId = 551;
		memcpy((void *) athletesBlockBuf1, (void *) &athleteId, sizeof(int));
		athletesBlockBuf1 += sizeof(int);
		strcpy(athletesBlockBuf1, "ZAGORAKHS");
		athletesBlockBuf1 += BF_MAIN_NAME_SIZE;
		strcpy(athletesBlockBuf1, "THEODVROS");
		athletesBlockBuf1 += BF_MAIN_NAME_SIZE;
		
		BF_UnpinBlock(athletesFd1, athletesBlockNum2, TRUE);
	}

	/* Δέσμευση νέου μπλοκ στο αρχείο ATHLETES χρησιμοποιώντας το 2ο άνοιγμα. Το αρχείο πρέπει να μεγαλώσει. */
	if (BF_AllocBlock(athletesFd1, &athletesBlockNum3, &athletesBlockBuf1) < 0)
		BF_PrintError("Error in BF_AllocBlock called on ATHLETES.");
	else
	{
		printf("The new block must be appended at the end: %d\n", athletesBlockNum3);
		memset((void *) athletesBlockBuf1, 0, BF_BLOCK_SIZE);

		/* Εισαγωγή μίας ακόμη εγγραφής στο νέο μπλοκ */
		athleteId = 552;
		memcpy((void *) athletesBlockBuf1, (void *) &athleteId, sizeof(int));
		athletesBlockBuf1 += sizeof(int);
		strcpy(athletesBlockBuf1, "VRYZAS");
		athletesBlockBuf1 += BF_MAIN_NAME_SIZE;
		strcpy(athletesBlockBuf1, "ZHSHS");
		athletesBlockBuf1 += BF_MAIN_NAME_SIZE;
		
		BF_UnpinBlock(athletesFd1, athletesBlockNum3, TRUE);
	}

	/* Τα νέα μπλοκ φτάνουν στο δίσκο */
	if (BF_CloseFile(athletesFd1) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");

	printf("\n**********************\n\n");

	/* Νέα ανάγνωση των νέων μπλοκ και εκτύπωση των εγγραφών τους */
	if (BF_GetThisBlock(athletesFd, athletesBlockNum1, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetThisBlock called on ATHLETES.");
	
	athleteId = * (int *) athletesBlockBuf;
	athletesBlockBuf += sizeof(int);
	strcpy(athleteSurName, athletesBlockBuf);
	athletesBlockBuf += BF_MAIN_NAME_SIZE;
	strcpy(athleteName, athletesBlockBuf);
	athletesBlockBuf += BF_MAIN_NAME_SIZE;
	printf("%d %s %s\n", athleteId, athleteName, athleteSurName);

	if (BF_GetThisBlock(athletesFd, athletesBlockNum2, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetThisBlock called on ATHLETES.");
	
	athleteId = * (int *) athletesBlockBuf;
	athletesBlockBuf += sizeof(int);
	strcpy(athleteSurName, athletesBlockBuf);
	athletesBlockBuf += BF_MAIN_NAME_SIZE;
	strcpy(athleteName, athletesBlockBuf);
	athletesBlockBuf += BF_MAIN_NAME_SIZE;
	printf("%d %s %s\n", athleteId, athleteName, athleteSurName);

	if (BF_GetThisBlock(athletesFd, athletesBlockNum3, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetThisBlock called on ATHLETES.");
	
	athleteId = * (int *) athletesBlockBuf;
	athletesBlockBuf += sizeof(int);
	strcpy(athleteSurName, athletesBlockBuf);
	athletesBlockBuf += BF_MAIN_NAME_SIZE;
	strcpy(athleteName, athletesBlockBuf);
	athletesBlockBuf += BF_MAIN_NAME_SIZE;
	printf("%d %s %s\n", athleteId, athleteName, athleteSurName);

	printf("\n**********************\n\n");

	/* ’νοιγμα εκ νέου του αρχείου ATHLETES (που είναι ήδη ανοιχτό) */
	/* και "κάρφωμα" των 3 μπλοκ που είναι ήδη καρφωμένα. */
	athletesFd1 = BF_OpenFile("ATHLETES");
	if (BF_GetThisBlock(athletesFd1, athletesBlockNum1, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetThisBlock called on ATHLETES.");
	if (BF_GetThisBlock(athletesFd1, athletesBlockNum2, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetThisBlock called on ATHLETES.");
	if (BF_GetThisBlock(athletesFd1, athletesBlockNum3, &athletesBlockBuf) != BFE_OK)
		BF_PrintError("Error in BF_GetThisBlock called on ATHLETES.");

	/* Λανθασμένη απόπειρα κλεισίματος του αρχείου, ενώ έχει καρφωμένα μπλοκ. */
	if (BF_CloseFile(athletesFd1) != BFE_OK)
		BF_PrintError("Expected error in BF_CloseFile called on ATHLETES.");
	else printf("This call to BF_CloseFile called on ATHLETES should have failed.\n");

	/* Ξεκάρφωμα των μπλοκ (τα οποία όμως πρέπει να παραμείνουν καρφωμένα αφού χρησιμοποιούνται από άλλο χρήστη) */
	BF_UnpinBlock(athletesFd1, athletesBlockNum1, FALSE);
	BF_UnpinBlock(athletesFd1, athletesBlockNum2, FALSE);
	BF_UnpinBlock(athletesFd1, athletesBlockNum3, FALSE);
	
	/* Tώρα το αρχείο πρέπει να μπορεί να κλέισει. */
	if (BF_CloseFile(athletesFd1) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");
	else printf("BF_CloseFile called on ATHLETES succeeded.\n");

	/* Λανθασμένη απόπειρα κλεισίματος του αρχείου, ενώ έχει καρφωμένα μπλοκ. */
	if (BF_CloseFile(athletesFd) != BFE_OK)
		BF_PrintError("Expected error in BF_CloseFile called on ATHLETES.");
	else printf("This call to BF_CloseFile called on ATHLETES should have failed.\n");

	BF_UnpinBlock(athletesFd, athletesBlockNum1, FALSE);
	BF_UnpinBlock(athletesFd, athletesBlockNum2, FALSE);
	BF_UnpinBlock(athletesFd, athletesBlockNum3, FALSE);

	/* Κλείσιμο των ανοιχτών αρχείων. */
	if (BF_CloseFile(eventsFd) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on EVENTS.");
	else printf("BF_CloseFile called on EVENTS succeeded.\n");

	if (BF_CloseFile(athletesFd) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");
	else printf("BF_CloseFile called on ATHLETES succeeded.\n");

	if (BF_CloseFile(participationsFd) != BFE_OK)
		BF_PrintError("Error in BF_CloseFile called on PARTICIPATIONS.");
	else printf("BF_CloseFile called on PARTICIPATIONS succeeded.\n");

	return 0;
}
