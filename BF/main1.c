#include <stdio.h>
#include <string.h>
#include "BF_Lib.h"

#define BF_MAIN_NAME_SIZE 30
#define BF_MAIN_EVENT_NAME_SIZE 60
#define BF_MAIN_DATE_SIZE 12
#define BF_MAIN_MAX_NUM_OF_RECS 16
#define BF_MAIN_MAX_NUM_OF_EVENT_RECS 50

void insertEvent(int eventId, char *eventName, char **eventsBlockBuf)
{
	memcpy((void *) *eventsBlockBuf, (void *) &eventId, sizeof(int));
	*eventsBlockBuf += sizeof(int);
	strcpy(*eventsBlockBuf, eventName);
	*eventsBlockBuf += BF_MAIN_EVENT_NAME_SIZE;
}

void insertAthlete(int athleteId, char *athleteSurname, char *athleteName, char **athletesBlockBuf)
{
	memcpy((void *) *athletesBlockBuf, (void *) &athleteId, sizeof(int));
	*athletesBlockBuf += sizeof(int);
	strcpy(*athletesBlockBuf, athleteSurname);
	*athletesBlockBuf += BF_MAIN_NAME_SIZE;
	strcpy(*athletesBlockBuf, athleteName);
	*athletesBlockBuf += BF_MAIN_NAME_SIZE;
}

void insertParticipation(int eventId, int athleteId, char *date, char **participationsBlockBuf)
{
	memcpy((void *) *participationsBlockBuf, (void *) &eventId, sizeof(int));
	*participationsBlockBuf += sizeof(int);
	memcpy((void *) *participationsBlockBuf, (void *) &athleteId, sizeof(int));
	*participationsBlockBuf += sizeof(int);
	strcpy(*participationsBlockBuf, date);
	*participationsBlockBuf += BF_MAIN_DATE_SIZE;
}

void callAllocBlock(int fileDescriptor, int *blockNum, char **blockBuf, char *fileName)
{
	char message[BF_MAIN_EVENT_NAME_SIZE];
	sprintf(message, "Error in BF_AllocBlock called on %s.", fileName);
	if (BF_AllocBlock(fileDescriptor, blockNum, blockBuf) < 0)
		BF_PrintError(message);
	else memset(*blockBuf, 0, BF_BLOCK_SIZE);
}

int main()
{
	int eventsFd;
	int eventsBlockNum;
	char *eventsBlockBuf;
	int eventId;

	int athletesFd;
	int athletesBlockNum;
	char *athletesBlockBuf;
	int athleteId;

	int participationsFd;
	int participationsBlockNum;
	char *participationsBlockBuf;

	/* Αρχικοποίηση του επιπέδου αρχείου μπλοκ */
	BF_Init();

	/* Κατασκευή τριών αρχείων */
	if (BF_CreateFile("EVENTS") != BFE_OK)
	{
		BF_PrintError("Error in BF_CreateFile called on EVENTS.");
	}

	if (BF_CreateFile("ATHLETES") != BFE_OK)
	{
		BF_PrintError("Error in BF_CreateFile called on ATHLETES.");
	}

	if (BF_CreateFile("PARTICIPATIONS") != BFE_OK)
	{
		BF_PrintError("Error in BF_CreateFile called on PARTICIPATIONS.");
	}
	
	/* ’νοιγμα τριών αρχείων */
	eventsFd = BF_OpenFile("EVENTS");
	athletesFd = BF_OpenFile("ATHLETES");
	participationsFd = BF_OpenFile("PARTICIPATIONS");

	eventId = 0;
	athleteId = 0;

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο EVENTS. */
	callAllocBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf, "EVENTS");

	/* Εισαγωγή της εγγραφής 1 στο αρχείο EVENT */
	insertEvent(eventId, "XEIROSFAIRISH", &eventsBlockBuf);

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 1 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BEMH", "PANAGOYLA", &athletesBlockBuf);

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 2 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GIOYPH", "STYLIANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 5 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 6 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 7 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 8 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 9 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 10 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 11 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 12 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 13 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 14 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 15 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 16 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 17 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 18 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 19 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 20 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 21 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 3 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKOLIA", "GRHGORIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 22 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 23 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 24 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 25 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 26 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 27 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 28 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 4 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DVROUEOY", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 29 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 30 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 31 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 32 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 33 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 34 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 35 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 36 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 37 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 38 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 39 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 40 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 41 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 42 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 43 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 44 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 45 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 5 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UEODVRIDOY", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 46 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 47 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 48 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 49 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 50 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1999", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 51 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 52 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 53 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 54 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 55 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 56 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 57 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 58 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 59 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 60 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 61 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 62 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 63 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 6 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MAYROGENH", "ELEYUERIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 64 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 65 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 66 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 67 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 68 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 69 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 70 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 71 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 7 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MIXALOPOYLOY", "MIXAELA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 72 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 73 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 74 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 75 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 8 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NIKOLH", "ELENA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 76 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 77 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 78 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 79 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 80 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 81 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 82 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 83 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 84 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 85 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 9 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PATSIOY", "ANASTASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 86 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 87 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 88 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 89 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 90 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 91 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 92 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 93 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 94 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 95 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 96 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 97 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 98 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 99 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 100 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 101 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 102 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 10 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "POIMENIDOY", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 103 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 104 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 105 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 106 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 11 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "POTARH", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 107 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 108 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 109 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 110 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 111 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 112 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 113 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 12 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SKARA", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 114 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 115 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 13 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SOYSA", "TATIANA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 116 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 117 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 118 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 14 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FVTIADOY", "IVANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 119 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 120 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 121 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 122 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 123 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 124 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 125 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 126 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 127 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 128 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 129 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 130 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 131 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 132 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 133 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 134 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 135 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 136 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 137 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 138 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 15 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "CAUA", "ANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 139 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 140 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 141 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 16 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ALBANOS", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 142 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 143 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 144 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 145 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 146 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 147 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 148 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 149 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 150 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1998", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 151 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 152 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 153 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 154 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 155 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 156 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 157 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1991", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 17 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BASILAKHS", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 158 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 159 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 160 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 161 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 162 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 163 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 164 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 165 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 18 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BOGLHS", "EYAGGELOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 166 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 167 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 168 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 169 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 170 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 171 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 172 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 173 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 174 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 175 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 176 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 19 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GRAMMATIKOS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 177 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 178 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 179 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 180 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 181 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 182 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 183 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 184 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 185 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 186 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 187 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 188 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 20 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ZARABINAS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 189 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 190 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 191 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 192 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 193 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 194 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 195 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 196 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 197 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 198 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 199 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 200 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2000", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 201 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 202 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 203 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 21 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARYPIDHS", "SABBAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 204 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 205 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 22 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAFFATOS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 206 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 207 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 208 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 209 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 210 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 23 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOKOLODHMHTRAKHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 211 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 212 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 213 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 214 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 215 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 216 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 217 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 218 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 219 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 220 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 24 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPALVMENOS", "SPYRIDVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 221 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 222 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 223 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 224 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 225 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 226 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 227 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 228 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 25 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZIMOYRTOS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 229 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 230 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 231 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 232 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 233 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 234 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 235 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 236 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 26 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TROYPHS", "ANDREAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 237 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 238 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 239 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 27 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSILIMPARHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 240 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 241 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 242 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 243 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 244 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 245 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 246 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 247 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 248 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 249 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 250 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1993", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 251 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 252 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 28 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XALKIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 253 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 254 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 29 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XATSATOYRIAN", "KRIKOR-GRHGOR", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 255 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 256 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 257 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 258 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 259 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 260 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 261 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 262 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 263 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 264 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 265 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 266 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 267 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 268 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 269 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 30 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRYSOPOYLOS", "IVANNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 270 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 271 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 272 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 273 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 274 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 275 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 276 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 277 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 278 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 279 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 280 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 281 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 282 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 283 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1989", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 2 στο αρχείο EVENT */
	insertEvent(eventId, "ANTISFAIRISH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 31 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ZAXARIADOY", "XRISTINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 284 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 285 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 286 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 287 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 288 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 289 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 290 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 291 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 292 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 293 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 294 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 295 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 296 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 297 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 298 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 299 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 300 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 32 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DANIHLIDOY", "ELENH", &athletesBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 301 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 302 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1995", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 33 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MAZARAKHS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 303 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 304 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 305 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 306 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 307 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 308 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 309 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 310 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 311 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 312 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 313 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 314 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 315 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 316 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 317 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 318 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 319 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 320 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 321 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 34 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "OIKONOMIDHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 322 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 323 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 324 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 325 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 326 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 327 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 328 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1988", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 3 στο αρχείο EVENT */
	insertEvent(eventId, "ARSH BARVN", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 35 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KASAPH", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 329 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 330 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 36 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KASTRITSH", "XARIKLEIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 331 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 332 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 37 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSAKIRH", "ANASTASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 333 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 334 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 335 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 336 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 337 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 338 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 339 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 340 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 341 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 342 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 343 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 344 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 345 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 346 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 347 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 348 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 349 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 350 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1998", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 351 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 38 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "IVANNIDH", "XRISTINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 352 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 353 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 354 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 355 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 356 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 357 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 358 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 359 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 360 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 361 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 362 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 363 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 364 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 39 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SAMPANHS", "LEVNIDAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 365 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 366 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 40 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MHTROY", "BIKTVR", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 367 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 368 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 369 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 370 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 371 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 41 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DHMAS", "PYRROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 372 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 373 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 374 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 375 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 376 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 377 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 378 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 379 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 380 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 381 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 382 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 383 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 384 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 385 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 386 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 387 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 388 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 389 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 390 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 42 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MARKOYLAS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 391 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 392 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 393 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 394 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 395 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 396 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 397 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 43 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAKIASBILHS", "AKAKIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 398 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 399 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 400 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1998", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 401 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 402 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 403 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 404 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 405 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 406 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 407 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 44 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYRTIDHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 408 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 409 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 410 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 411 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 412 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 413 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 414 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 415 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2003", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 4 στο αρχείο EVENT */
	insertEvent(eventId, "TAEKBONTO", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 45 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AUANASOPOYLOY", "ARETH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 416 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 417 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 418 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 419 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 420 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 421 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 422 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 423 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 424 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 425 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 46 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MYSTAKIDOY", "ELISABET", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 426 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 427 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 428 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 429 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 430 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 431 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 432 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 433 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 434 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 435 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 436 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 437 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 438 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 47 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NIKOLAIDHS", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 439 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 440 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 441 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 442 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 48 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MOYROYTSOS", "MIXALHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 443 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 444 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 5 στο αρχείο EVENT */
	insertEvent(eventId, "GYMNASTIKH", &eventsBlockBuf);

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 49 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "EYUYMIOY", "HLEKTRA-ELLH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 445 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 446 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 447 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 448 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 50 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAKIOY", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 449 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 450 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2001", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 451 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 452 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 453 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 454 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 455 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 456 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 457 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 51 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MAGNHSALH", "BARBARA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 458 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 459 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 52 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PANTAZH", "STERGIANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 460 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 461 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 462 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 463 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 464 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 465 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 466 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 467 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 468 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 469 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 470 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 471 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 472 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 473 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 474 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 53 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRISTIDOY", "STYLIANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 475 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 476 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 477 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 478 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 479 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 480 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 481 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 482 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 483 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 484 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 485 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 486 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 487 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 488 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 489 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 490 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 491 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 492 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 493 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 54 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRONOPOYLOY", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 494 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 495 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 496 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 497 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 498 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 499 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 500 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/2000", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 501 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 502 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 503 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 504 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 505 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 506 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 507 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 508 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 509 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 510 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 511 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 512 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 55 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ANDRIOLA", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 513 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 514 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 515 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 516 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 517 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 518 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 56 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PALLIDOY", "UEODVRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 519 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 520 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 521 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 6 στο αρχείο EVENT */
	insertEvent(eventId, "GYMNASTIKH TRAMPOLINO", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 57 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PELIBANIDHS", "MIXAHL", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 522 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 523 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 524 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 525 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 526 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 527 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 528 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 529 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 7 στο αρχείο EVENT */
	insertEvent(eventId, "GYMNASTIKH ENORGANH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 58 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "APOSTOLIDH", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 530 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 531 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 532 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 59 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPISMPIKOY", "STEFANI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 533 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 534 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 535 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 536 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 537 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 538 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 539 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 540 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 60 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MARAS", "BLASIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 541 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 542 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 543 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 544 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 61 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TAMPAKOS", "DHMOSUENHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 545 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 546 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 547 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 548 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1998", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 8 στο αρχείο EVENT */
	insertEvent(eventId, "ISTIOPLOIA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 62 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPEKATVROY", "SOFIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 549 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 550 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1999", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 551 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 552 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 553 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 554 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 555 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 556 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 557 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 558 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 559 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 560 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 561 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 63 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSOYLFA", "AIMILIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 562 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 563 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 564 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 565 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 566 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 567 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 568 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 569 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 570 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 571 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 572 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 573 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 574 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 575 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 64 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KRABARIVTH", "BIRGINIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 576 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 577 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1990", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 65 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FRAI", "AUHNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 578 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 579 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 580 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 581 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 582 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 583 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 584 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 585 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 586 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 587 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 588 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 589 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 590 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 591 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 592 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 593 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 66 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GIAKOYMIDOY", "AIKATERINH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 594 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 67 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DHMHTRAKOPOYLOY", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 595 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 596 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 597 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 598 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 599 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 600 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1987", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 601 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 602 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 603 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 68 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MANTZARAKH", "EYTYXIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 604 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 605 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 606 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 607 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 608 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 609 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 610 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 611 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 612 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 613 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 614 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 615 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 616 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 617 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 618 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 619 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 69 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOSMATOPOYLOS", "ANDREAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 620 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 621 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 622 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 623 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 624 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 625 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 626 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 627 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 628 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 629 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 630 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 631 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 632 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 633 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 634 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 635 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 636 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 70 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TRIGKVNHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 637 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 638 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 639 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 640 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 641 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 642 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 643 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 644 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 71 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAXOYMAS", "AUANASIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 645 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 646 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 647 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 72 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PORTOSALTE", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 648 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 649 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 650 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1992", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 651 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 652 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 653 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 73 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPAUANASIOY", "AIMILIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 654 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 655 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 656 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 657 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 658 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 659 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 660 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 661 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 662 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 663 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 664 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 665 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 666 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 667 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 668 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 669 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 670 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 671 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 74 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XEIMVNAS", "EYAGGELOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 672 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 673 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 674 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 675 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 676 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 677 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 678 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 679 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 680 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 681 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 682 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 683 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 684 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 75 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAKLAMANAKHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 685 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 686 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 687 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 688 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 689 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 690 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 691 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 692 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 76 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PELEKANAKHS", "LEVNIDAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 693 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 694 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 695 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 696 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 697 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 698 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 699 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 700 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1988", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 701 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 702 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 703 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 704 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 77 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KONTOGOYRHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 705 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 706 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 707 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 708 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 709 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 710 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 711 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 712 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 713 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 714 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 715 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 716 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 717 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 78 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PASXALIDHS", "IORDANHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 718 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 719 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 720 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 721 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 722 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 723 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 724 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 725 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 726 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 727 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 728 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 729 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 730 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 731 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 732 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 79 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GAREFHS", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 733 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 734 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 735 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 736 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 737 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 738 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 739 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 740 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 741 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 742 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 743 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 744 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 745 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 746 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1995", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 9 στο αρχείο EVENT */
	insertEvent(eventId, "KANOE-KAGIAK SLALOM", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 80 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FEREKIDH", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 747 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 748 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 749 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 750 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1993", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 751 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 752 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 753 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 754 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 755 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 756 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 757 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 758 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 759 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 81 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSAKMAKHS", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 760 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 761 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 762 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 763 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 764 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 765 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 766 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 767 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 768 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 769 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 770 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 771 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 772 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 773 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 774 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 775 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 776 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 777 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 82 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DHMHTRIOY", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 778 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1999", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 10 στο αρχείο EVENT */
	insertEvent(eventId, "EPITRAPEZIA ANTISFAIRISH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 83 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BOLAKAKH", "ARXONTIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 779 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 780 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 781 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 782 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 783 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 784 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 785 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 786 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 787 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 788 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 789 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 790 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 791 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 792 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 793 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 794 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 84 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MOIROY", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 795 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 796 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 797 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 798 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 799 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 800 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1995", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 801 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 802 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 85 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKIVNHS", "PANAGIVTHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 803 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 804 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 805 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 806 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 807 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 808 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 809 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 810 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 811 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 812 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 86 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KREANGKA", "KALINIKOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 813 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 814 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 815 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 816 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 817 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 818 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 819 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 820 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 821 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 822 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2004", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 11 στο αρχείο EVENT */
	insertEvent(eventId, "IPPASIA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 87 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DEMIROPOYLOY", "AGLAIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 823 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 824 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 825 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 826 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 827 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 828 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 829 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 830 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 831 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 832 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 833 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 834 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 835 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 836 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 88 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LEMAN", "GKERTA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 837 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 838 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 89 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SOYRLA", "ALEJANDRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 839 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 90 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AUANASIADH", "EMMANOYELA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 840 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 841 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 842 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 843 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 844 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 845 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 846 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 847 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 848 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 91 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ROMPERSON-MYTILHNAIOY", "XANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 849 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 850 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 851 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 852 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 853 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 854 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 855 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 856 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 857 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 858 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 859 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 860 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 861 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 862 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 863 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 864 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 865 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 866 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 92 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSATSOY", "DANAH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 867 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 868 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 869 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 870 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 871 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 872 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 873 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 874 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 875 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 93 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ANTIKATZIDH", "MIKAELA-XAINTI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 876 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 877 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 878 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 879 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 880 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 881 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 882 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 94 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PETRHS", "ANTVNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 883 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 884 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 885 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 886 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 887 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 888 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 889 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 890 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 891 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 892 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 893 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 894 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 895 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 896 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 897 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 898 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1991", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 12 στο αρχείο EVENT */
	insertEvent(eventId, "KANOE-KAGIAK TAXYTHTA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 95 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ALEJOPOYLOY", "AUHNA-UEODVRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 899 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 96 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KILIGKARIDHS", "ANDREAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 900 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1997", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 901 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 902 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 903 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 904 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 905 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 906 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 907 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2005", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 97 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPANDREOY", "APOSTOLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 908 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 909 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 910 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 911 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 912 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 913 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 914 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1999", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 13 στο αρχείο EVENT */
	insertEvent(eventId, "KVPHLASIA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 98 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPISKITZH", "XRYSH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 915 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 916 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 917 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 918 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 919 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 920 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 921 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 922 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 99 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SAKELLARIDOY", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 923 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 924 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 925 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 926 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 927 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 100 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "POLYMEROS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 928 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 929 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 101 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SKIAUITHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 930 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 931 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 932 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 933 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 934 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 935 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 936 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 937 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 938 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 939 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 940 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 14 στο αρχείο EVENT */
	insertEvent(eventId, "MONTERNO PENTAULO", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 102 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PARTITS", "KATALIN-MPEAT", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 941 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 942 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 943 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 944 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 103 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FLVROS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 945 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 946 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 947 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 948 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 949 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 950 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2001", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 951 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 952 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1990", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 15 στο αρχείο EVENT */
	insertEvent(eventId, "MPEIZMPVL", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 104 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DHMHTRELHS", "TZEIMS-XRISTODOYLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 953 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 954 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 955 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 956 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 957 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 958 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 959 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 960 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 961 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 962 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 105 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DOYROS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 963 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 964 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 965 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 966 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 967 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 968 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 969 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 970 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 971 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 972 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 973 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 974 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 975 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 976 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 977 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 978 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 979 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 980 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 981 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 982 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 106 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ZABARAS", "KLINTON", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 983 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 984 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 985 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 986 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 987 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 988 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 989 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 990 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 991 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 992 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 107 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "OYEIN", "UEODVRAKOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 993 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 994 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 995 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 996 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 997 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 998 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 999 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1000 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 108 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZARENT-GEVRGIOS", "UEODVROY", &athletesBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1001 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1002 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 109 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NIKOLAOS", "UEOXARHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1003 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1004 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1005 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1006 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1007 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1008 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1009 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1010 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1011 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1012 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1013 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 110 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KORY-ANTVNIOS", "KABOYRGIARHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1014 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1015 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1016 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1017 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1018 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1019 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1020 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 111 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DHMHTRIOS", "KINGKSMPOYRI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1021 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1022 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1023 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1024 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1025 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1026 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1027 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1028 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1029 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1030 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1031 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1032 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1033 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1034 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1035 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1036 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1037 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1038 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 112 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ROMPERT-REIMONT", "KOTTARAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1039 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1040 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1041 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1042 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1043 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1044 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1045 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1046 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1047 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/2000", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 113 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GEVRGIOS", "KOYTSANTVNAKHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1048 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1049 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1050 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 114 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MIXAHL", "KREMMYDAS", &athletesBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1051 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1052 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1053 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1054 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1055 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1056 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1057 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1058 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1059 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1060 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1061 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1062 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1063 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1064 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1065 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1066 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1067 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1068 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1069 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1070 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 115 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ALEJANDROS", "MAHSTRALHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1071 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1072 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 116 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PHTER", "GKAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1073 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1074 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1075 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1076 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1077 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1078 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1079 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1080 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1081 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1082 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1083 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1084 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1085 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 117 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MARKAKHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1086 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1087 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1088 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1089 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1090 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1091 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1092 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1093 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 118 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MELEXES", "MELETI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1094 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1095 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1096 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1097 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1098 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1099 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1100 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2003", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1101 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1102 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1103 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 119 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ROSS", "MPELINTZER", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1104 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1105 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1106 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1107 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1108 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1109 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1110 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1111 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1112 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1113 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1114 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1115 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1116 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1117 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1118 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1119 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1120 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1121 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 120 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KLEHTON", "MPOYRAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1122 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1123 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1124 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1125 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1126 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1127 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1128 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1129 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1130 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1131 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1132 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1133 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 121 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPRANTLH", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1134 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1135 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1136 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1137 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1138 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1139 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1140 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1141 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1142 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1143 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1144 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1145 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1146 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 122 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPRAK", "ANDREAS-TZEHMS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1147 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 123 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPALYMPERHS", "ERIK-NTANIEL", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1148 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1149 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1150 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1151 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1152 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1153 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1154 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 124 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ROMPINSON", "XRISTOFOROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1155 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1156 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1157 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1158 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1159 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1160 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1161 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1162 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1163 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1164 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 125 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SPANOS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1165 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1166 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1167 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 126 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SPENSER", "SVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1168 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1169 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1170 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1171 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1172 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1173 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1174 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1175 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1176 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 127 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZEIMS", "SYKARAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1177 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1178 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1179 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1180 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1181 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1182 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1183 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1184 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1185 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1186 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1187 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1188 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1189 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1190 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1191 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1192 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1193 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1194 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1195 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 128 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PANAGIVTHS", "SVTHROPOYLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1196 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1197 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1198 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1199 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1200 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1987", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1201 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1202 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1203 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1204 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1205 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1206 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1207 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1208 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1209 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1210 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1211 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1212 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1213 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1214 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1215 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1989", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 129 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PANAGIVTHS", "XAISLER", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1216 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1217 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1218 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1219 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1220 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1221 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1222 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1993", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 16 στο αρχείο EVENT */
	insertEvent(eventId, "KATADYSEIS", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 130 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPPA-PAPABASILOPOYLOY", "EYTYXIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1223 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1224 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1225 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1226 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1227 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1228 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1229 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1230 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 131 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SFAKIANOY", "FLVRENTIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1231 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1232 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 132 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GEVRGATOY", "DIAMANTINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1233 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1234 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1235 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1236 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1237 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1238 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1239 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1240 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1241 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1242 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1243 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1244 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1245 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1246 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1247 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1248 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1249 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1250 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1990", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1251 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1252 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 133 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYTSOPETROY", "SVTHRIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1253 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1254 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1255 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1256 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1257 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1258 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1259 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1260 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1261 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1262 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 134 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GABRIHLIDHS", "IVANNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1263 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1264 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1265 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1266 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1267 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1268 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1269 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1270 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1271 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1272 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1273 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1274 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1275 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1276 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1277 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1278 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1279 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1280 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1281 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 135 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TRAKAS", "SVTHRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1282 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1283 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1284 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1285 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1286 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1287 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1288 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1289 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1290 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1291 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1292 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 136 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPIMHS", "UVMAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1293 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1294 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1295 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1296 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1297 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1298 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1299 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1300 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1991", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1301 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1302 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1303 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1304 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1305 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1306 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1307 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 137 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SIRANIDHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1308 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1309 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1310 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1311 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1312 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2001", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Το μπλοκ του αρχείου EVENTS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(eventsFd, eventsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on EVENTS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο EVENTS. */
	callAllocBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf, "EVENTS");

	/* Εισαγωγή της εγγραφής 17 στο αρχείο EVENT */
	insertEvent(eventId, "KOLYMBHSH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 138 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KABARNOY", "EIRHNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1313 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 139 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SARAKATSANH", "AIKATERINH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1314 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1315 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1316 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1317 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1318 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1319 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1320 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1321 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1322 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1323 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1324 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1325 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1326 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1327 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1328 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1329 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1330 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 140 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARASTERGIOY", "EIRHNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1331 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1332 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1333 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1334 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1335 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1336 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1337 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1338 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1339 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 141 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DHMOSXAKH", "ZVH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1340 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1341 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1342 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1343 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1344 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1345 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1346 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1347 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1348 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 142 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AGGELOPOYLOY", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1349 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1350 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2004", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1351 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1352 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1353 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1354 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1355 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1356 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1357 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1358 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1359 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1360 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1361 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 143 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZABELLA", "AUHNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1362 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1363 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1364 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1365 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1366 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1367 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1368 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1369 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1370 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1371 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1372 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 144 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KVSTA", "EIRHNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1373 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1374 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1375 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1376 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1377 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1378 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1379 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1999", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 145 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KVSTH", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1380 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1381 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1382 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1383 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1384 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1385 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1386 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1387 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1388 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1389 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1390 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1391 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1392 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1393 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1394 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1395 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 146 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MAXAIRA", "ANTVNIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1396 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1397 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1398 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1399 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1400 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1990", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1401 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1402 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1403 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1404 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1405 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1406 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1407 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1408 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1409 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1410 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1411 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1412 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 147 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MANVLH", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1413 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1414 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1415 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1416 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1417 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1418 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1419 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 148 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSAGKA", "EYAGGELIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1420 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1421 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1422 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1423 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 149 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MATSA", "MARUA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1424 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1425 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1426 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1427 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1428 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1429 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1430 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1431 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1432 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1433 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1434 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1435 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1436 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1437 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1438 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1439 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 150 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NIANGKOYARA", "NERY-MANTEY", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1440 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1441 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1442 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1443 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1444 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1445 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1446 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1447 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1448 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1449 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1450 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/2002", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1451 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1452 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1453 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1454 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1455 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 151 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LYMPERTA", "MARIANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1456 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1457 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1458 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1459 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1460 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1461 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1462 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1463 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1464 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1465 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1466 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 152 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GRHGORIADHS", "ARISTEIDHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1467 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1468 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1469 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1470 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1471 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1472 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1473 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1474 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1475 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1476 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 153 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PASTRAS", "SVTHRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1477 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1478 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1479 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1480 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1481 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1482 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1483 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 154 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOS", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1484 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1485 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1486 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 155 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DIAMANTIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1487 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1488 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1489 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1490 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1491 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1492 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1493 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1494 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1495 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1496 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1497 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1498 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1499 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1500 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1988", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1501 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 156 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ZHSIMOS", "ANDREAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1502 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1503 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1504 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1505 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1506 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1507 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1508 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1509 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1510 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1511 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1512 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1513 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1514 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1515 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1516 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 157 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOKKVDHS", "IVANNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1517 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1518 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1519 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1520 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1521 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1522 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1523 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1524 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1525 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1526 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1527 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1528 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 158 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DRYMVNAKOS", "IVANNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1529 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1530 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1531 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1532 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1533 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1534 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1535 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1536 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1537 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1538 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1539 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1540 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1541 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1542 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1543 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1544 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1545 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1546 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1547 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1548 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 159 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ALYFANTHS", "RVMANOS-IASVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1549 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1550 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1998", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1551 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1552 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 160 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKIOYLMPAS", "ANTVNIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1553 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1554 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1555 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1556 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1557 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1558 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1559 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1560 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1561 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1562 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1563 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1564 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1565 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1566 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1567 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1568 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1569 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1570 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1571 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1572 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2005", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 161 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GIANNIVTHS", "SPYRIDVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1573 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1574 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1575 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1576 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1577 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1578 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1579 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1580 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1581 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1582 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1583 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1584 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1585 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1586 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1587 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1588 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1589 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1590 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 162 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MAGGANAS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1591 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1592 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1593 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1594 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1595 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1596 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1597 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 163 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPITSAKHS", "SPYRIDVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1598 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1599 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1600 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1989", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1601 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1602 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1603 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1604 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1605 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1606 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 164 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSOLTOS", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1607 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 165 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ANTVNOPOYLOS", "APOSTOLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1608 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1609 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1610 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1611 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 166 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "JYLOYRHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1612 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1613 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1614 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1615 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1616 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1617 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1618 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1619 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1620 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1621 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 167 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSAGKARAKHS", "APOSTOLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1622 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1623 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1624 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1625 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1626 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1627 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1628 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1629 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1630 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 18 στο αρχείο EVENT */
	insertEvent(eventId, "PALH ELEYUERA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 168 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "CAUA", "FANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1631 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1632 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1633 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1634 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1635 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1636 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1637 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1638 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1639 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1640 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 169 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "POYMPOYRIDOY", "SOFIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1641 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1642 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1643 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1644 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1645 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1646 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1647 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1648 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1649 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1650 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1651 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1652 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1653 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1654 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1655 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 170 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ZYGOYRH", "STAYROYLA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1656 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1657 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1658 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1659 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1660 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1661 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1662 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1663 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1664 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 171 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BRYVNH", "MARIA-LOYIZA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1665 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1666 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1667 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1668 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1669 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1670 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 172 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPATZELAS", "NESTVRAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1671 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1672 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1673 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1674 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1675 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1676 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1677 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1678 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1679 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1680 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1681 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1682 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1683 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1684 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1685 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1686 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1687 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 173 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARNTANOB", "AMIRAN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1688 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1689 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1690 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1691 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1692 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1693 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1694 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1695 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1696 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1697 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1698 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1699 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 174 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ASLANASBILI", "MPESIK", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1700 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2004", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1701 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1702 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1703 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1704 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1705 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1706 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1707 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1708 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1709 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1710 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1711 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1712 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1713 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1714 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1715 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1716 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1717 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1718 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 175 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TASKOYDHS", "APOSTOLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1719 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1720 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1721 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 176 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPETINIDHS", "EMZARIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1722 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1723 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1724 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1725 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1726 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1727 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1728 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1729 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1730 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1731 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1732 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1733 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1992", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 177 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LOIZIDHS", "LAZAROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1734 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1735 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1736 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1737 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1738 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1739 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1740 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1741 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1742 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1743 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1744 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1745 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1746 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 178 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LALIVTHS", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1747 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1748 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1749 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1750 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1997", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1751 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1752 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1753 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1754 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1755 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1756 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1757 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1758 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1759 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1760 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1761 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1762 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1988", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 19 στο αρχείο EVENT */
	insertEvent(eventId, "PALH ELLHNORVMAIKH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 179 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYTSIOYMPAS", "JENOFVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1763 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1764 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1765 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1766 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1767 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1768 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1769 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1770 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1771 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1772 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1773 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1774 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1775 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1776 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1777 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1778 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1779 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 180 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KIOYREGKIAN", "ARTIOM", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1780 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1781 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1782 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1783 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1784 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1785 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1786 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1787 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1788 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1789 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1790 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1791 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1792 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1793 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1794 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 181 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKIKAS", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1795 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1796 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1797 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1798 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1799 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1800 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1993", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1801 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1802 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1803 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1804 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1805 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1806 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1807 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 182 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ARKOYDEAS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1808 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1809 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1810 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1811 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1812 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1813 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1814 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1815 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 183 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOLITSOPOYLOS", "ALEJIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1816 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1817 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1818 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1819 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 184 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ABRAMHS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1820 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1821 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1822 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1823 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1824 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1825 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1826 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1827 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1828 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1829 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1830 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1831 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 185 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UANOS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1832 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1833 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1834 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1835 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1836 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1837 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1838 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1839 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1840 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1841 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1842 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1843 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1844 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1845 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 20 στο αρχείο EVENT */
	insertEvent(eventId, "PETOSFAIRISH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 186 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BLAXOY", "IVANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1846 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1847 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1848 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1849 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1850 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2005", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1851 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1852 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1853 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1854 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1855 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1856 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1857 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1858 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1859 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1860 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 187 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKARAGKOYNH", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1861 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1862 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1863 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1864 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1865 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1866 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1867 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1868 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1869 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1870 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1871 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1872 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1873 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1874 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1875 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1876 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1877 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1878 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 188 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKARAGKOYNH", "NIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1879 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1880 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 189 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "IORDANIDOY", "SOFIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1881 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1882 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1883 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1884 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1885 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1886 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1887 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 190 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KIOSH", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1888 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1889 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1890 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1891 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1892 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1893 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 191 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MEMETZH", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1894 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1895 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1896 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1897 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1898 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1899 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1900 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1991", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1901 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1902 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1903 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 192 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NTOYMITRESKOY", "ROYJANTRA-KONTROYTSA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1904 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1905 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1906 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1907 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1908 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1909 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1910 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1911 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1912 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1913 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1914 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1915 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1916 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1917 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/2005", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 193 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPAZOGLOY", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1918 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1919 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1920 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1921 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1922 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1923 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1924 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1925 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1926 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1927 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1928 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1929 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1930 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 194 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PRONIADOY", "ZANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1931 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1932 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1933 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1934 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1935 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1936 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1937 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1938 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1939 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1940 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 195 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SAKKOYLA", "XARIKLEIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1941 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1942 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1943 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1944 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1945 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1946 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1947 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1948 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1949 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1950 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1988", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 1951 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1952 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1953 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1954 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1955 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1956 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1957 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1958 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 196 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZANAKAKH", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1959 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1960 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1961 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1962 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1963 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1964 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1965 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1966 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1967 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1968 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1969 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 197 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XATZHNIKOY", "ELEYUERIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1970 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 198 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKIOYRDAS", "MARIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1971 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1972 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1973 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1974 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1975 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1976 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1977 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 199 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYRNETAS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1978 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1979 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1980 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1981 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1982 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1983 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 200 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KRABARIK", "ANTREI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1984 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1985 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1986 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 201 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LAPPAS", "HLIAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 1987 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1988 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1989 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1990 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1991 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1992 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1993 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1994 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1995 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1996 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1997 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1998 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 1999 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2000 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1999", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2001 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2002 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 202 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPAEF", "TONTOR-ZLATKOB", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2003 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2004 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2005 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2006 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2007 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2008 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2009 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2010 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2011 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2012 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 203 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PANTALEVN", "SVTHRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2013 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2014 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2015 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2016 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2017 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2018 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 204 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PROYSALHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2019 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2020 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2021 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2022 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2023 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2024 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2025 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2026 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2027 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2028 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2029 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2030 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 205 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ROYMELIVTHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2031 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2032 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2033 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2034 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 206 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "STEFANOY", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2035 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2036 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2037 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 207 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSAKIROPOYLOS", "ANTVNIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2038 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2039 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2040 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2041 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2042 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2043 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2044 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2045 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2046 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2047 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2048 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2049 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2050 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2051 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2052 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 208 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XATZHANTVNIOY", "UEODVROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2053 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2054 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2055 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2056 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2057 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2058 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2059 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2060 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2061 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2062 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2063 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2064 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2065 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2066 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2067 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2068 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2069 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2070 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2071 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2004", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 209 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRISTOFIDELHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2072 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2073 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2074 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2075 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2004", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 21 στο αρχείο EVENT */
	insertEvent(eventId, "MPITS BOLLEY", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 210 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ARBANITH", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2076 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2077 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2078 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2079 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2080 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2081 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2082 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2083 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2084 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2085 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2086 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2087 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2088 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2089 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2090 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2091 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2092 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 211 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARANTASIOY", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2093 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2094 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2095 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2096 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2097 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2098 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2099 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2100 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/2000", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2101 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2102 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2103 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 212 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYTROYMANIDOY", "EYUALIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2104 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2105 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2106 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2107 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2108 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2109 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2110 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2111 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2112 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2113 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2114 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2115 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2116 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2117 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2118 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2119 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2120 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 213 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SFYRH", "EYFROSYNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2121 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2122 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2123 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 214 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MIXALOPOYLOS", "AUANASIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2124 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2125 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2126 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2127 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2128 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2129 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2130 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2131 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2132 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 215 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPELIGRATHS", "PAYLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2133 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2134 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 22 στο αρχείο EVENT */
	insertEvent(eventId, "JIFASKIA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 216 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "RENTOYMH", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2135 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2136 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2137 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2138 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2139 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2140 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2141 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2142 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2143 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2144 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2145 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2146 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2147 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2148 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2149 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2150 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1987", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2151 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2152 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2153 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 217 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MAGKANOYDAKH", "DHMHTRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2154 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2155 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2156 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2157 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2158 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2159 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2160 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2161 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2162 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2163 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2164 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2165 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 218 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SIDHROPOYLOY", "NIKH-KATERINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2166 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2167 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2168 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2169 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2170 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2171 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2172 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2173 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2174 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2175 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2176 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2177 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2178 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2179 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2180 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2181 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 219 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRHSTOY", "IVANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2182 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2183 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2184 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2185 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2186 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2187 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2188 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2189 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2190 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2191 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2192 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2193 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2194 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2195 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2196 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2197 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 220 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AMPALOB", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2198 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2199 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2200 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1988", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2201 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2202 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2203 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2204 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2205 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2206 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2207 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 221 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MANETAS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2208 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2209 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2210 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2211 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2212 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2213 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2214 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2215 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2216 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2217 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2218 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2219 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 222 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPASMATZIAN", "MARIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2220 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2221 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2222 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2223 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2224 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2225 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2226 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 223 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NTOYRAKOS", "TZEHSON-MAIKL", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2227 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2228 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2229 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2230 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2231 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2232 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 23 στο αρχείο EVENT */
	insertEvent(eventId, "PODHLASIA OREINH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 224 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KVTOYLAS", "EMMANOYHL", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2233 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2234 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2235 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2236 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2237 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2238 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2239 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1989", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 24 στο αρχείο EVENT */
	insertEvent(eventId, "PODOSFAIRO", &eventsBlockBuf);

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 225 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GIATRAKOY", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2240 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 226 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KABBADA", "ALEJANDRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2241 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2242 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2243 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2244 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2245 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2246 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2247 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2248 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2249 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2250 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2002", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2251 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2252 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2253 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 227 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KALYBA", "TANYA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2254 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2255 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2256 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2257 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2258 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2259 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2260 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2261 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2262 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 228 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ELENH", "KATSAITH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2263 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2264 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2265 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2266 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2267 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2268 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2269 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2270 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2271 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2272 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2273 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2274 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2275 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2276 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2277 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2278 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2279 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 229 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KVNSTANTINA", "LAGOYMTZH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2280 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2281 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2282 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2283 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2284 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2285 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2286 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2287 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2288 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2289 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2290 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2291 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 230 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AGGELIKH", "LAZAROY", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2292 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2293 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2294 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2295 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 231 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MARIA", "LOSENO", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2296 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2297 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2298 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2299 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2300 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1992", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2301 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2302 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2303 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2304 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2305 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2306 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2307 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2308 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2309 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2310 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2311 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2312 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 232 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GOYOLKER", "AMAL", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2313 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2314 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2315 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2316 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2317 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2318 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2319 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2320 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2321 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2322 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 233 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MIXAHLIDOY", "EYTYXIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2323 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2324 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2325 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2326 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 234 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MOSXOY", "ILHANA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2327 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2328 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2329 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2330 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2331 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2332 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2333 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2334 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2335 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2336 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2337 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 235 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPENSON", "ELENH-MARI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2338 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2339 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2340 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2341 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2342 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2343 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2344 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2345 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2346 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2347 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2348 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2349 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 236 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PANTELEIADOY", "DHMHTRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2350 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1991", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2351 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2352 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2353 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2354 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2355 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2356 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2357 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2358 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2359 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2360 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2361 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2362 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2363 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2364 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 237 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOY", "ANASTASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2365 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2366 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2367 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2368 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2369 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2370 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2371 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2372 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2373 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2374 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2375 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2376 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2377 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2378 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2379 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2380 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2381 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2382 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2383 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2384 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 238 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "POYRIDOY", "AUANASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2385 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 239 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SMIU", "SOFIA-ANTVNIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2386 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2387 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2388 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2389 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2390 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2391 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2392 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2393 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2394 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2395 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2396 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2397 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2398 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2399 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 240 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SOYPIADOY", "BASILIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2400 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1990", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2401 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2402 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2403 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2404 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2405 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2406 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2407 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2408 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2409 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2410 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2411 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2412 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2413 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2414 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2415 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2416 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1997", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 241 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "STRATAKH", "KALLIOPH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2417 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2418 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2419 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2420 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2421 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2422 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2423 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2424 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2425 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 242 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TEFANH", "AGGELIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2426 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2427 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2428 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2429 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2430 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2431 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2432 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2433 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 243 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XATZHGIANNIDOY", "NATALIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2434 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2435 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2436 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2437 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2438 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2439 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2440 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2441 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2442 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2443 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2444 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2445 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2446 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2447 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2448 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2449 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2450 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2002", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2451 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 244 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AGRITHS", "ANASTASIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2452 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2453 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2454 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2455 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2456 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2457 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2458 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2459 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2460 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2461 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2462 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2463 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2464 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2465 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2466 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2467 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2468 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 245 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AMANATIDHS", "IVANNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2469 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2470 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2471 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2472 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2473 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2474 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2475 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2476 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2477 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2478 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2479 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2480 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 246 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AMPARHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2481 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2482 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2483 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2484 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2485 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2486 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2487 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 247 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BALLAS", "SPYRIDVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2488 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2489 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2490 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2491 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2492 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2493 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2494 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2495 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2496 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2497 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2498 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2499 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2500 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1993", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2501 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2502 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2503 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2504 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 248 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BYNTRA", "LOYKAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2505 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2506 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2507 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2508 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2509 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2510 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2511 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2512 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2513 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 249 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GALANOPOYLOS", "ARISTEIDHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2514 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2515 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2516 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2517 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2518 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2519 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2520 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2521 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2522 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2523 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2524 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2525 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 250 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GIANNOY", "KLEOPAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2526 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2527 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2528 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2529 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 251 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GOYNDOYLAKHS", "FANOYRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2530 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2531 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 252 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARYPIDHS", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2532 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2533 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2534 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2535 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 253 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LAGOS", "PANAGIVTHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2536 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2537 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2538 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2539 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2540 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2541 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2542 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2543 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2544 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2545 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2546 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2547 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2548 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2549 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2550 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/2004", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2551 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2552 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2553 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2554 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 254 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MORAS", "EYAGGELOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2555 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2556 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2557 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2558 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 255 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NEMPEGLERAS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2559 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2560 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2561 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2562 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2563 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2564 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 256 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2565 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2566 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2567 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2568 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2569 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2570 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2571 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2572 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2573 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2574 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2575 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2576 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2003", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 257 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SALPIGGIDHS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2577 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2578 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2579 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2580 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2581 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2582 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2583 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2584 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2585 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2586 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2587 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2588 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2589 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2590 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2591 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 258 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SAPANHS", "MILTIADHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2592 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2593 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2594 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2595 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2596 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2597 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2598 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2599 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2600 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2004", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2601 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 259 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "STOLTIDHS", "IEROKLHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2602 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 260 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TARALIDHS", "IVANNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2603 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2604 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2605 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2606 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2607 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 261 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FVTAKHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2608 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2609 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2610 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2611 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2612 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2613 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1992", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 25 στο αρχείο EVENT */
	insertEvent(eventId, "PYGMAXIA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 262 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAPERVNHS", "MARIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2614 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2615 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2616 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2617 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2618 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2619 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2620 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2621 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 263 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "IVANNIDHS", "SPYRIDVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2622 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2623 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2624 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2625 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2626 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2627 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2628 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2629 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 264 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOTAKOS", "UEODVROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2630 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2631 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 265 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GAZHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2632 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2633 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2634 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2635 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2636 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2637 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2638 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2639 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2640 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2641 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2642 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2643 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2644 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2645 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2646 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 266 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAYLIDHS", "HLIAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2647 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2648 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2649 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2650 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1994", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2651 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2652 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2653 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 267 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KLADOYXAS", "SPYRIDVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2654 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2655 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2656 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2657 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2658 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2659 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2660 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2661 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2662 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2663 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2664 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2665 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2666 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2667 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2668 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2669 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2670 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2671 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2672 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2673 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1995", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 26 στο αρχείο EVENT */
	insertEvent(eventId, "SKOPOBOLH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 268 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARAFLOY", "MARINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2674 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2675 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2676 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2677 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2678 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2679 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 269 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SMYRLH", "ALEJIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2680 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2681 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2682 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2683 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2684 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2685 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2686 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2687 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2688 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 270 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FAKA", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2689 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2690 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2691 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2692 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2693 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2694 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 271 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KASOYMH", "AGAUH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2695 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2696 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2697 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2698 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2699 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2700 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1992", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2701 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2702 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2703 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 272 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GEVRGAKOPOYLOS", "DIONYSIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2704 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2705 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2706 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2707 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2708 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2709 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2710 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2711 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2712 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2713 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2714 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/2004", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 273 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PETSANHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2715 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2716 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2717 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2718 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2719 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2720 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2721 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2722 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2723 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2724 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2725 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2726 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2727 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2728 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2729 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2730 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2731 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2732 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2733 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 274 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SABORGIANNAKHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2734 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2735 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2736 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2737 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2738 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2739 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2740 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 275 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SPYROPOYLOS", "AGGELOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2741 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2742 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2743 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2744 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2745 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2746 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2747 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2748 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2749 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 276 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LIOGRHS", "EYAGGELOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2750 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1987", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2751 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2752 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 277 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SALABANTAKHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2753 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2754 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2755 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2756 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2757 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2758 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2759 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2760 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2761 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2762 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2763 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2764 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2765 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2766 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2767 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2768 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2769 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 278 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ANTVNIADHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2770 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2771 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2772 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2773 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2774 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2775 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2776 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2777 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2778 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2779 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1996", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 27 στο αρχείο EVENT */
	insertEvent(eventId, "SYGXRONISMENH KOLYMBHSH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 279 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ANASTASIOY", "AGLAIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2780 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2781 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2782 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2783 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2784 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2785 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2786 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2787 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2788 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 280 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GEVRGIOY", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2789 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2790 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2791 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2792 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2793 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2794 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2795 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2796 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2797 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2798 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2799 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2800 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1992", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2801 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2802 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2803 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2804 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 281 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GOYDA", "EYFROSYNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2805 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2806 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2807 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2808 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2809 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2810 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2811 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2812 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2813 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 282 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UALASSINIDOY", "XRISTINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2814 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2815 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2816 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2817 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 283 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "IVANNOY", "APOSTOLIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2818 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2819 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2820 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 284 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYTSOYDH", "EYGENIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2821 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2822 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2823 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2824 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2825 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2826 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2827 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2828 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2829 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2830 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2831 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2832 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2833 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2834 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2835 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2836 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2837 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2838 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2839 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 285 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PELEKANOY", "OLGA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2840 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2841 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2842 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2843 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 286 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FTOYLH", "ELEYUERIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2844 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 287 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRISTODOYLOY", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2845 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2846 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2847 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2848 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 28 στο αρχείο EVENT */
	insertEvent(eventId, "SOFTMPVL", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 288 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GEVRGANTA", "TZHNNY", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2849 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2850 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1989", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2851 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2852 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1998", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 289 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MARI", "GKEIL", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2853 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2854 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2855 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2856 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2857 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2858 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2859 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2860 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2861 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 290 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZOANNA", "ANTALI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2862 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2863 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2864 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 291 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KANELAKH-KLOOYZMAN", "XLOH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2865 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2866 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2867 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2868 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2869 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2870 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2871 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2872 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2873 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 292 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MARIA", "KARANTZA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2874 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2875 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2876 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2877 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2878 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2879 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2880 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2881 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2882 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2883 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2884 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2885 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2886 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2887 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 293 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRISTINA", "KOYTOYGKOY", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2888 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2889 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2890 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2891 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2892 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2893 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2894 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2895 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2896 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2897 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2898 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2899 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2900 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1996", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2901 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2902 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2903 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2904 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 294 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AIKATERINH", "KROMYDA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2905 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2906 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2907 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2908 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2909 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2910 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2911 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2912 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2913 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2914 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2915 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2916 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2917 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2918 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2919 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2920 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2921 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 295 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AIKATERINH", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2922 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2923 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2924 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2925 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2926 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2927 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2928 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2929 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 296 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPASOR", "TZESIKA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2930 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 297 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LYN", "MPASOR", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2931 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2932 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2933 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2934 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2935 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2936 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2937 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2938 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2939 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2940 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2941 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2942 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2943 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2944 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2945 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2946 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 298 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LINTSEI", "KRISTIN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2947 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2948 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2949 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2950 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 2951 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2952 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2953 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2954 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2955 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2956 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2957 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2958 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2959 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2960 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2961 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 299 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPOYZIOY", "IVANNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2962 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 300 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SKIGKAS", "STEFANI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2963 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2964 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2965 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2966 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2967 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2968 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2969 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2970 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2971 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2972 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2973 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 301 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZARNESKI", "BANESSA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2974 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2975 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2976 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2977 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2978 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2979 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2980 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2981 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2982 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 302 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZEIMS", "LINTZY", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2983 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2984 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2985 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2986 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2987 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2988 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2989 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 303 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LVREN", "FARNGOYORU", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 2990 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2991 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2992 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2993 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2994 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2995 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2996 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2997 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2998 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 2999 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3000 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 304 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TZEIMI", "LYN", &athletesBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3001 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3002 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3003 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3004 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3005 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3006 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3007 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3008 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3009 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3010 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3011 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3012 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3013 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3014 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3015 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3016 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3017 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3018 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3019 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3020 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/2005", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 305 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FARNGOYORU", "STEISI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3021 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3022 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3023 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3024 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3025 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3026 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3027 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3028 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3029 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3030 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3031 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3032 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 306 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LH", "FARNGOYORU", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3033 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3034 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3035 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3036 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3037 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 307 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SARA", "RENE", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3038 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3039 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3040 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3041 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 29 στο αρχείο EVENT */
	insertEvent(eventId, "STIBOS", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 308 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UANOY", "AIKATERINH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3042 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3043 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3044 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3045 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3046 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3047 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3048 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3049 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3050 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1986", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3051 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3052 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3053 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 309 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "RENTOYMH", "FLVRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3054 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3055 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3056 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 310 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "EFENTAKH", "KVNSTANTINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3057 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3058 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3059 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3060 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3061 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3062 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3063 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3064 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3065 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3066 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3067 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3068 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3069 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 311 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOKOTOY", "XRISTINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3070 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3071 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3072 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 312 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPAGIANNH", "AUHNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3073 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3074 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3075 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3076 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3077 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3078 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 313 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSOYMELEKA", "AUANASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3079 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3080 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3081 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3082 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3083 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 314 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAIDANTZH", "OLGA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3084 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3085 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3086 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3087 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3088 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3089 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3090 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3091 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3092 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3093 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3094 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3095 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3096 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3097 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3098 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3099 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3100 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1986", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3101 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 315 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKOYNTENOYDH", "XRYSOYLA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3102 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3103 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3104 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3105 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3106 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3107 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3108 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3109 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3110 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3111 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3112 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3113 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3114 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3115 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 316 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XALKIA", "FANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3116 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3117 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3118 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3119 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 317 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BASARMIDOY", "MARINA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3120 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3121 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3122 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3123 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3124 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3125 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3126 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3127 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3128 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3129 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3130 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3131 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3132 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3133 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3134 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3135 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3136 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3137 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 318 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARASTAMATH", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3138 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3139 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3140 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3141 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3142 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3143 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3144 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3145 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3146 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3147 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3148 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3149 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3150 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2001", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3151 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3152 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3153 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3154 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3155 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3156 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 319 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOKLVNH", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3157 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3158 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3159 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3160 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3161 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3162 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3163 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3164 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3165 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3166 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3167 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3168 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3169 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3170 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3171 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3172 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3173 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 320 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PATOYLIDOY", "PARASKEYH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3174 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3175 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3176 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3177 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3178 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3179 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1989", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 321 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PATSOY", "EYFROSYNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3180 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3181 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3182 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3183 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3184 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3185 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3186 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3187 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/03/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 322 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYMNAKH", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3188 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3189 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3190 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3191 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3192 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3193 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3194 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3195 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3196 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3197 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3198 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3199 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3200 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1990", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3201 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 323 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPOYNTA", "XARIKLEIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3202 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3203 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3204 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3205 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3206 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3207 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3208 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3209 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3210 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3211 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3212 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3213 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3214 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3215 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 324 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NTOBA", "DHMHTRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3216 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3217 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3218 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3219 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3220 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3221 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3222 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3223 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3224 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3225 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3226 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3227 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3228 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3229 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3230 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3231 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 325 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "IAKVBOY", "XRYSOSTOMIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3232 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3233 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3234 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3235 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 326 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LIKA", "BOISABA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3236 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3237 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 327 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MANIANI", "MIRELA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3238 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3239 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3240 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3241 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3242 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3243 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3244 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 328 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSIOLAKOYDH", "AGGELIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3245 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3246 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3247 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3248 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3249 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3250 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/2005", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3251 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3252 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3253 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3254 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 329 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BOGGOLH", "AIKATERINH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3255 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3256 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3257 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3258 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3259 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3260 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3261 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3262 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3263 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3264 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3265 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3266 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3267 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3268 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3269 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3270 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 330 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KELESIDOY", "ANASTASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3271 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3272 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3273 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3274 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3275 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3276 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3277 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3278 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3279 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3280 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3281 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3282 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3283 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3284 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3285 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 331 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSIKOYNA", "STYLIANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3286 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3287 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3288 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3289 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3290 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3291 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3292 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3293 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3294 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3295 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3296 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3297 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3298 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/10/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 332 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SKAFIDA", "AFRODITH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3299 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3300 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1993", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3301 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3302 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3303 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3304 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3305 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3306 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3307 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3308 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3309 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3310 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3311 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3312 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3313 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3314 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3315 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3316 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3317 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3318 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 333 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSILIGKIRH", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3319 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3320 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3321 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3322 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3323 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3324 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3325 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3326 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3327 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3328 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3329 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3330 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3331 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 334 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "STRATAKH", "ARGYRV", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3332 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3333 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3334 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3335 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3336 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3337 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3338 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3339 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3340 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3341 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3342 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3343 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3344 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3345 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3346 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3347 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3348 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3349 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3350 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 335 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AMPATZIDOY", "GEVRGIA", &athletesBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3351 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3352 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3353 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3354 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3355 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3356 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3357 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3358 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3359 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 336 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAFETZH", "GIANNOYLA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3360 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3361 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3362 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3363 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3364 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3365 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3366 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3367 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3368 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3369 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3370 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3371 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3372 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3373 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3374 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3375 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3376 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3377 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1993", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 337 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "JANUOY", "NIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3378 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3379 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3380 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3381 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3382 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3383 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3384 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3385 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3386 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3387 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3388 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3389 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3390 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3391 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3392 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3393 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3394 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 338 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PILATOY", "STYLIANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3395 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3396 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3397 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3398 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3399 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3400 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1993", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3401 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3402 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/11/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 339 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "OYZOYNH", "KALLIOPH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3403 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3404 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3405 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3406 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3407 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3408 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3409 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3410 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3411 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3412 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3413 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3414 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3415 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 340 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TERZOGLOY", "EIRHNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3416 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3417 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3418 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3419 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3420 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3421 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3422 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3423 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3424 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3425 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3426 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3427 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3428 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3429 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3430 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3431 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3432 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3433 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 341 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPAGEVRGIOY", "ALEJANDRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3434 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3435 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3436 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3437 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 342 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPADOPOYLOY", "STYLIANH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3438 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 343 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSAMOGLOY", "EYDOKIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3439 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3440 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3441 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3442 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3443 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3444 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3445 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3446 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3447 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3448 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3449 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3450 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1992", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3451 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3452 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3453 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3454 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3455 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3456 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 344 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BASDEKH", "OLGA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3457 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 345 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DEBETZH", "XRYSOPHGH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3458 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3459 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3460 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3461 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3462 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3463 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3464 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3465 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3466 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 346 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PERRA", "AUANASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3467 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3468 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3469 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3470 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3471 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3472 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3473 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3474 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3475 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3476 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3477 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 347 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MHTROPOYLOY", "NIKOLITSA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3478 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3479 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3480 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 348 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UEODVRIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3481 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/11/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3482 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3483 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3484 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3485 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3486 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3487 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3488 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3489 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3490 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3491 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3492 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3493 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3494 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3495 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3496 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3497 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3498 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3499 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 349 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XOIDHS", "XRISTOFOROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3500 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1990", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3501 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3502 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3503 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3504 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3505 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3506 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3507 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3508 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3509 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3510 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3511 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3512 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3513 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3514 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3515 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 350 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PIETRHS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3516 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3517 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3518 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3519 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3520 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3521 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3522 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3523 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3524 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3525 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3526 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 351 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UANOPOYLOS", "ELEYUERIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3527 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3528 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3529 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3530 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3531 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3532 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3533 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3534 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3535 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3536 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3537 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3538 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3539 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3540 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3541 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3542 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3543 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 352 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GKOYSHS", "ANASTASIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3544 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3545 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3546 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3547 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3548 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3549 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3550 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2005", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3551 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1993", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 353 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KENTERHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3552 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3553 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3554 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3555 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3556 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 354 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SARRHS", "PANAGIVTHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3557 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3558 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3559 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3560 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3561 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3562 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3563 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3564 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3565 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/10/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3566 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3567 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3568 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3569 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3570 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3571 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3572 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3573 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3574 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3575 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3576 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 355 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DHMOTSIOS", "STYLIANOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3577 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3578 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3579 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3580 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3581 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 356 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "IAKVBAKHS", "PERIKLHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3582 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3583 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3584 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3585 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3586 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3587 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3588 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3589 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3590 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3591 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3592 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3593 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3594 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3595 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 357 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GRABALOS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3596 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3597 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3598 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3599 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3600 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/2003", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3601 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3602 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3603 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3604 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3605 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3606 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 358 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NTOYPHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3607 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3608 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3609 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3610 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3611 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3612 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3613 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 359 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "OIKONOMIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3614 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3615 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3616 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3617 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3618 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3619 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3620 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3621 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3622 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3623 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3624 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3625 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3626 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3627 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 360 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ARGYROPOYLOS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3628 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3629 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3630 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3631 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3632 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3633 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 361 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KASTANHS", "SPYRIDVN", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3634 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3635 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3636 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3637 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3638 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3639 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3640 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3641 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3642 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3643 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3644 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3645 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3646 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3647 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3648 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3649 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3650 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1999", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3651 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 362 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "STAMATOPOYLOS", "UEODVROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3652 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3653 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3654 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3655 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3656 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3657 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3658 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3659 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3660 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3661 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3662 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3663 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3664 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3665 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/09/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3666 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3667 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3668 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 363 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "STROYMPAKOS", "PANAGIVTHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3669 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3670 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3671 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3672 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3673 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3674 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3675 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3676 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3677 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3678 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3679 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3680 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3681 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3682 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3683 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3684 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 364 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KORKIZOGLOY", "PRODROMOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3685 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3686 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3687 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3688 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3689 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 365 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PANABOGLOY", "SABBAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3690 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3691 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3692 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3693 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3694 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3695 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3696 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 366 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "EYAGGELOY", "MARIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3697 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3698 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3699 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3700 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/05/1997", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3701 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3702 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3703 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3704 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 367 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "POLIAS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3705 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3706 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3707 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3708 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3709 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3710 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3711 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 368 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SERELHS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3712 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3713 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3714 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3715 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3716 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3717 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3718 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3719 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3720 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3721 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3722 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3723 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3724 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3725 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/2002", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 369 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSATOYMAS", "LOYHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3726 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3727 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3728 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3729 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3730 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3731 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3732 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3733 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 370 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FILINDRAS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3734 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3735 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3736 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3737 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3738 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3739 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3740 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 371 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPADHMHTRIOY", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3741 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3742 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3743 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3744 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3745 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3746 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3747 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3748 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3749 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3750 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1995", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3751 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3752 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3753 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3754 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3755 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3756 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/09/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 372 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MELETOGLOY", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3757 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3758 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3759 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3760 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3761 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3762 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3763 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3764 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3765 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3766 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3767 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3768 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3769 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3770 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/2005", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 30 στο αρχείο EVENT */
	insertEvent(eventId, "TZOYNTO", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 373 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "IVANNOY", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3771 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3772 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3773 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3774 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3775 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3776 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3777 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3778 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3779 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3780 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3781 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3782 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3783 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3784 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3785 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3786 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 374 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARAGIANNOPOYLOY", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3787 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3788 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3789 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3790 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3791 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3792 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3793 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3794 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3795 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3796 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3797 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3798 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3799 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3800 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1990", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3801 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 375 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSELARIDOY", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3802 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3803 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3804 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3805 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3806 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3807 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3808 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3809 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3810 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3811 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3812 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3813 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3814 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3815 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3816 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 376 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MPOYKOYBALA", "IOYLIETA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3817 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3818 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3819 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3820 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3821 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3822 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3823 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3824 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3825 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 377 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TAMPASH", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3826 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3827 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/02/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3828 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3829 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3830 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3831 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3832 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3833 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3834 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3835 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3836 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3837 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3838 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3839 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3840 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3841 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2001", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 378 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOYRTELESH", "ALEJIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3842 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3843 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3844 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3845 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3846 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 379 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AKRITIDOY", "BARBARA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3847 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3848 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3849 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3850 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2003", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3851 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3852 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3853 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3854 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3855 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3856 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3857 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3858 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3859 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3860 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3861 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3862 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3863 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3864 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3865 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3866 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 380 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPAIVANNOY", "XARALAMPOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3867 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3868 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3869 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3870 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3871 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3872 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3873 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3874 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3875 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3876 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3877 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3878 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3879 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3880 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3881 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 381 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "HLIADHS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3882 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3883 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3884 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3885 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3886 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3887 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3888 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3889 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3890 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3891 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3892 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3893 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/04/2002", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 382 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ZINTIRIDHS", "REBAZI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3894 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3895 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3896 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3897 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3898 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3899 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3900 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/2002", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3901 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3902 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3903 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3904 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3905 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3906 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3907 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3908 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3909 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3910 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3911 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3912 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3913 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 383 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BAZAGKASBILI", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3914 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3915 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3916 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3917 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/12/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3918 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3919 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 384 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ALEJANIDHS", "LAYRENTI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3920 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3921 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3922 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3923 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3924 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3925 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3926 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3927 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3928 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2002", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 385 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "HLIADHS", "HLIAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3929 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3930 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3931 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3932 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3933 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3934 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3935 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3936 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3937 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3938 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3939 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3940 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3941 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3942 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3943 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3944 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3945 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3946 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 386 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "HLIADHS", "DIONYSIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3947 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3948 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3949 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3950 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/2004", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 3951 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3952 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3953 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3954 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3955 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3956 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3957 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3958 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/12/2002", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 31 στο αρχείο EVENT */
	insertEvent(eventId, "KALAUOSFAIRISH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 387 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BASILEIOY", "ELENH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3959 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3960 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3961 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3962 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3963 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3964 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3965 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3966 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3967 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 388 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DELH", "AIKATERINH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3968 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3969 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3970 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3971 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3972 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3973 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3974 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3975 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3976 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3977 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3978 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3979 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1990", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 389 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KABBADIA", "TATIANA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3980 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3981 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3982 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3983 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3984 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3985 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/05/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 390 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KALENTZOY", "DHMHTRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 3986 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3987 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3988 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3989 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3990 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3991 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3992 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3993 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3994 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3995 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3996 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3997 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3998 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 3999 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4000 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/10/1987", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4001 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 391 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KLIGKOPOYLOY", "SOFIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4002 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4003 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4004 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4005 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4006 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4007 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4008 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4009 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 392 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KVSTAKH", "ANASTASIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4010 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4011 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 393 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MALTSH", "EYANUIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4012 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4013 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4014 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4015 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4016 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 394 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SAMOROYKOBA", "MARIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4017 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4018 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4019 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4020 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4021 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4022 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4023 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4024 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4025 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4026 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4027 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4028 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4029 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4030 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4031 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4032 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 395 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SAREGKOY", "POLYMNIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4033 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4034 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4035 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4036 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4037 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/12/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4038 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4039 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4040 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4041 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4042 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4043 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4044 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4045 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/05/2000", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 396 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "STAXTIARH", "EIRHNH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4046 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4047 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4048 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4049 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4050 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1999", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4051 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1999", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 397 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TASOYLH", "ATALANTH-MARI", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4052 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/06/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4053 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4054 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4055 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/11/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 398 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XRISTOFORAKH", "AUHNA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4056 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4057 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4058 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4059 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4060 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4061 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4062 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4063 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 399 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GLYNIADAKHS", "ANDREAS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4064 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4065 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4066 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4067 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4068 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4069 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4070 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/02/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4071 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/10/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4072 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4073 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4074 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4075 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4076 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4077 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4078 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4079 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4080 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4081 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 400 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DIAMANTIDHS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4082 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4083 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4084 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4085 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4086 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4087 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4088 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4089 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4090 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4091 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4092 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4093 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4094 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4095 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4096 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4097 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4098 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1993", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 401 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ZHSHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4099 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4100 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/2004", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4101 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4102 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4103 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4104 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4105 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4106 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4107 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 402 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KAKIOYZHS", "MIXAHL", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4108 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4109 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4110 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4111 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4112 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4113 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4114 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4115 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4116 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 403 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NTIKOYDHS", "DHMOSUENHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4117 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4118 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4119 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4120 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4121 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4122 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4123 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 404 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPALOYKAS", "UEODVROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4124 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4125 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4126 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4127 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4128 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4129 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4130 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4131 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4132 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4133 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 405 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "PAPANIKOLAOY", "DHMHTRHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4134 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4135 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 406 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SPANOYLHS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4136 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4137 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4138 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4139 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4140 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4141 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4142 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4143 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4144 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/05/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4145 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4146 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4147 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 407 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "TSARTSARHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4148 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4149 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1998", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 408 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "FVTSHS", "ANTVNIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4150 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1987", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4151 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/06/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4152 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4153 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4154 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4155 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4156 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4157 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1989", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 409 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XARISHS", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4158 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/03/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4159 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4160 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4161 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4162 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4163 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4164 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4165 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4166 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4167 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4168 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4169 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 410 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XATZHBRETTAS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4170 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4171 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4172 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4173 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4174 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4175 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/11/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4176 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2003", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 32 στο αρχείο EVENT */
	insertEvent(eventId, "TOJOBOLIA", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 411 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BABATSH", "FVTEINH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4177 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/04/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4178 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/09/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4179 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4180 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4181 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4182 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4183 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4184 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4185 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4186 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 412 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "RVMANTZH", "ELPIDA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4187 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4188 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4189 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4190 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/05/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4191 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4192 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4193 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4194 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4195 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4196 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 413 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "CARRA", "EYAGGELIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4197 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4198 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4199 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4200 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/09/1986", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4201 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4202 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1994", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 414 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KALOGIANNIDHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4203 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4204 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4205 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/04/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4206 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4207 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4208 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4209 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4210 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4211 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4212 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4213 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4214 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4215 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4216 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4217 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4218 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4219 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1991", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 415 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARAGEVRGIOY", "ALEJANDROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4220 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/06/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4221 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 416 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "NANOS", "APOSTOLOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4222 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1997", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Το μπλοκ του αρχείου EVENTS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(eventsFd, eventsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on EVENTS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο EVENTS. */
	callAllocBlock(eventsFd, &eventsBlockNum, &eventsBlockBuf, "EVENTS");

	/* Εισαγωγή της εγγραφής 33 στο αρχείο EVENT */
	insertEvent(eventId, "TRIAULO", &eventsBlockBuf);

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 417 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KROMMYDAS", "BASILEIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4223 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4224 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/12/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4225 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4226 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4227 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4228 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4229 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4230 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4231 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4232 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/03/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4233 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/10/2004", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 34 στο αρχείο EVENT */
	insertEvent(eventId, "PODHLASIA PISTAS", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 418 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KVNSTANTINIDOY", "KYRIAKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4234 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4235 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4236 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4237 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4238 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4239 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4240 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/04/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4241 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4242 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4243 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/09/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 419 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BASILOPOYLOS", "LAMPROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4244 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/08/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4245 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 420 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "GEVRGALHS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4246 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4247 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4248 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4249 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4250 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1989", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4251 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4252 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4253 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/04/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4254 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4255 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4256 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4257 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4258 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4259 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/05/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4260 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4261 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4262 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4263 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 421 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XEIMVNETOS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4264 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4265 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4266 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4267 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4268 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4269 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4270 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4271 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4272 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4273 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4274 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4275 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4276 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4277 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4278 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4279 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4280 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4281 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/01/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4282 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1995", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 35 στο αρχείο EVENT */
	insertEvent(eventId, "YDATOSFAIRISH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 422 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ASILIAN", "DHMHTRA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4283 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4284 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/10/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4285 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4286 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4287 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4288 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4289 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/03/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4290 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4291 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/10/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4292 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4293 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4294 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4295 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4296 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4297 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/06/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4298 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4299 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4300 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1989", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4301 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4302 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/09/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 423 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ELLHNAKH", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4303 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/12/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4304 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4305 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4306 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4307 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4308 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4309 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4310 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/01/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 424 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARAGIANNH", "EYTYXIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4311 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4312 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4313 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/01/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4314 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/04/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4315 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 425 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KARAPATAKH", "AGGELIKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4316 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/05/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4317 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4318 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4319 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4320 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/10/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4321 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4322 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4323 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4324 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4325 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4326 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4327 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4328 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4329 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/06/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4330 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4331 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4332 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4333 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4334 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4335 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/07/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 426 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KOZOMPOLH", "STAYROYLA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4336 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4337 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4338 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/11/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4339 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4340 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4341 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4342 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4343 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/08/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4344 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4345 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4346 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/07/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4347 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/04/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4348 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4349 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4350 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/1989", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4351 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 427 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LARA", "GEVRGIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4352 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/08/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4353 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4354 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4355 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4356 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/03/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4357 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4358 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/03/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4359 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4360 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4361 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4362 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4363 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4364 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4365 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/12/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4366 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4367 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4368 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4369 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/04/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4370 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4371 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/08/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 428 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LIOSH", "KYRIAKH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4372 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4373 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4374 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4375 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4376 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4377 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4378 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4379 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4380 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4381 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/07/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4382 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4383 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4384 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/02/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 429 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MELIDVNH", "ANTIOPH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4385 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4386 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4387 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4388 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/07/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4389 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4390 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4391 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/01/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4392 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4393 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 430 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MYLVNAKH", "ANUOYLA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4394 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4395 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4396 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4397 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/01/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4398 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4399 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4400 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/1989", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4401 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 431 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MVRAITH", "ANTVNIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4402 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4403 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4404 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/09/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4405 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/03/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4406 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/09/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4407 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/10/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4408 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/11/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4409 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/10/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4410 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4411 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4412 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4413 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/01/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4414 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/04/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4415 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/03/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4416 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1996", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 432 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MVRAITIDOY", "EYAGGELIA", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4417 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4418 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4419 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/01/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4420 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/03/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4421 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/05/1990", &participationsBlockBuf);

	athleteId++;

	/* Το μπλοκ του αρχείου ATHLETES είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο ATHLETES */
	callAllocBlock(athletesFd, &athletesBlockNum, &athletesBlockBuf, "ATHLETES");

	/* Εισαγωγή της εγγραφής 433 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "OIKONOMOPOYLOY", "AIKATERINH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4422 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/10/1997", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 434 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "ROYMPESH", "ANTIGONH", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4423 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/07/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4424 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4425 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/10/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4426 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4427 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4428 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4429 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/02/2004", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 435 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AFROYDAKHS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4430 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4431 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4432 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4433 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/09/1986", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 436 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "AFROYDAKHS", "XRHSTOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4434 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4435 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/08/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4436 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4437 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4438 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4439 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4440 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/03/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 437 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BLONTAKHS", "ANTVNIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4441 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4442 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4443 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 438 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "DELHGIANNHS", "NIKOLAOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4444 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4445 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4446 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4447 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "05/03/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4448 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/08/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4449 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/11/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4450 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/09/2005", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4451 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4452 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/05/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4453 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/07/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4454 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4455 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "13/02/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4456 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4457 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4458 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4459 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/06/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4460 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/02/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4461 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/02/2003", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 439 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UEODVROPOYLOS", "ARGYRHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4462 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/11/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4463 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/11/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4464 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4465 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4466 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/06/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4467 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/05/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4468 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/10/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4469 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "27/01/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4470 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/06/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4471 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/06/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4472 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/02/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4473 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4474 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/04/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4475 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4476 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/03/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4477 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/12/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4478 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/07/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4479 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/03/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4480 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1993", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 440 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "UVMAKOS", "IVANNHS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4481 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4482 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/06/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4483 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4484 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/07/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4485 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4486 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4487 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/05/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4488 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/11/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4489 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/09/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4490 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4491 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/12/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4492 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4493 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/04/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4494 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4495 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/07/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4496 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/12/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 441 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "KALAKVNAS", "UEODVROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4497 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/07/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4498 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/12/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4499 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "15/10/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4500 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/12/1992", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4501 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/10/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4502 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/09/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4503 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "12/07/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4504 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/02/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4505 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/07/1992", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 442 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "LOYDHS", "KVNSTANTINOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4506 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/02/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4507 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4508 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4509 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4510 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4511 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "02/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4512 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/01/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4513 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4514 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/05/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4515 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4516 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4517 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/04/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4518 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/11/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4519 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4520 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/01/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4521 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "28/01/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4522 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4523 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/08/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 443 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "MAZHS", "DHMHTRIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4524 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/09/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4525 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4526 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/03/1995", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4527 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/11/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4528 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/12/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4529 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/02/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4530 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/07/1994", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4531 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "17/03/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4532 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4533 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/08/1995", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 444 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "REPPAS", "GEVRGIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4534 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "20/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4535 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "11/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4536 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/08/2005", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4537 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/12/1988", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 445 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SANTA", "STEFANOS-PETR", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4538 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/12/1988", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4539 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/01/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4540 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/05/2005", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 446 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "SXIZAS", "ANASTASIOS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4541 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "23/08/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4542 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "04/12/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4543 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/11/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4544 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "10/04/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4545 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/05/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4546 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/12/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4547 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/04/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4548 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/12/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4549 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "26/01/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4550 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/05/2005", &participationsBlockBuf);

	/* Το μπλοκ του αρχείου PARTICIPATIONS είναι γεμάτο και μπορεί να ξεκαρφωθεί. */
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Δέσμευσε ένα νέο μπλοκ για το αρχείο PARTICIPATIONS */
	callAllocBlock(participationsFd, &participationsBlockNum, &participationsBlockBuf, "PARTICIPATIONS");

	/* Εισαγωγή της εγγραφής 4551 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/09/1993", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4552 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/01/2003", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4553 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/06/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4554 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "03/09/1989", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4555 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/02/1990", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4556 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "24/11/1987", &participationsBlockBuf);

	athleteId++;

	/* Εισαγωγή της εγγραφής 447 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "XATZHUEODVROY", "UEODVROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4557 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "06/02/1996", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4558 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "19/11/2001", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4559 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "22/05/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4560 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/01/2003", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Εισαγωγή της εγγραφής 36 στο αρχείο EVENT */
	insertEvent(eventId, "ANTIPTERISH", &eventsBlockBuf);

	/* Εισαγωγή της εγγραφής 448 στο αρχείο ATHLETES */
	insertAthlete(athleteId, "BELKOS", "UEODVROS", &athletesBlockBuf);

	/* Εισαγωγή της εγγραφής 4561 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "01/10/1987", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4562 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "14/09/2004", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4563 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "08/08/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4564 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "18/11/2002", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4565 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "25/06/1991", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4566 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/09/1998", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4567 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "09/03/1997", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4568 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/11/1999", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4569 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "07/04/2000", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4570 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/09/1986", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4571 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "16/08/1992", &participationsBlockBuf);

	/* Εισαγωγή της εγγραφής 4572 στο αρχείο PARTICIPATIONS */
	insertParticipation(eventId, athleteId, "21/12/1988", &participationsBlockBuf);

	athleteId++;
	eventId++;

	/* Ξεκάρφωσε τα τελευταία μπλοκ πριν κλείσεις τα αρχεία. */
	if (BF_UnpinBlock(eventsFd, eventsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on EVENTS.");
	if (BF_UnpinBlock(athletesFd, athletesBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on ATHLETES.");
	if (BF_UnpinBlock(participationsFd, participationsBlockNum, TRUE) < 0)
		BF_PrintError("Error in BF_UnpinBlock called on PARTICIPATIONS.");

	/* Κλείσιμο των τριών αρχείων. */
	if (BF_CloseFile(eventsFd) < 0)
		BF_PrintError("Error in BF_CloseFile called on EVENTS.");
	if (BF_CloseFile(athletesFd) < 0)
		BF_PrintError("Error in BF_CloseFile called on ATHLETES.");
	if (BF_CloseFile(participationsFd) < 0)
		BF_PrintError("Error in BF_CloseFile called on PARTICIPATIONS.");

	return 0;
}
