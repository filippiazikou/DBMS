#ifndef HF_LIB_H
#define HF_LIB_H

#include "BF_Lib.h"

#define EQUAL 1
#define LESS_THAN 2
#define GREATER_THAN 3
#define LESS_THAN_OR_EQUAL 4
#define GREATER_THAN_OR_EQUAL 5
#define NOT_EQUAL 6

#define HFE_OK 0					/* OK */  
#define HFE_NOMEM -1				/* έλλειψη μνήμης */  
#define HFE_NOBUF -2				/* έλλειψη χώρου ενδιάμεσης μνήμης */  
#define HFE_BLOCKFIXED -3			/* μπλοκ ήδη ``καρφωμένο'' στη μνήμη */  
#define HFE_BLOCKNOTINBUF -4		/* μπλοκ για ``ξεκάρφωμα'' δεν είναι στη μνήμη */  
#define HFE_BLOCKINBUF -5			/* μπλοκ ήδη στη μνήμη */  
#define HFE_OS -6					/* γενικό σφάλμα Λειτουργικού Συστήματος */  
#define HFE_INCOMPLETEREAD -7		/* ατελής ανάγνωση μπλοκ */  
#define HFE_INCOMPLETEWRITE -8		/* ατελές γράψιμο σε μπλοκ */  
#define HFE_INCOMPLETEHDRREAD -9	/* ατελής ανάγνωση μπλοκ-κεφαλίδας */  
#define HFE_INCOMPLETEHDRWRITE -10  /* ατελές γράψιμο σε μπλοκ-κεφαλίδα */  
#define HFE_INVALIDBLOCK -11	    /* μη έγκυρος αναγνωριστικός αριθμός μπλοκ */  
#define HFE_FILEOPEN -12		    /* αρχείο ήδη ανοιχτό */  
#define HFE_FTABFULL -13			/* λίστα ανοιχτών αρχείων πλήρης */  
#define HFE_FD -14					/* μη έγκυρος αναγνωριστικός αριθμός αρχείου */  
#define HFE_EOF -15				    /* τέλος αρχείου */  
#define HFE_BLOCKFREE -16			/* μπλοκ ήδη διαθέσιμο */  
#define HFE_BLOCKUNFIXED -17        /* μπλοκ ήδη ``ξεκαρφωμένο'' */  
#define HFE_FILE_EXISTS -18		    /* αρχειο υπάρχει ήδη */
#define HFE_FILE_NOT_EXISTS -19	    /* αρχειο δεν υπάρχει */
#define HFE_FOPEN_ERROR  -20		/* σφάλμα στο άνοιγμα του αρχείου */
#define HFE_FILE_CLOSED -21		    /* αρχείο ήδη κλειστό */
#define HFE_INVALID_FILEDESC -22    /* μη έγγυρο αναγνωριστικό αρχείου */
#define HFE_MALLOC_ERROR -23        /* σφάλμα malloc */
#define HFE_FWRITE_ERROR -24		/* σφάλμα fwrite */
#define HFE_FCLOSE_ERROR -25		/* σφάλμα fclose */
#define HFE_NULL_POINTER -26		/* κενός δείκτης */
#define HFE_FSEEK_ERROR -27         /* σφάλμα fseek */
#define HFE_FREAD_ERROR -28			/* σφάλμα fread */
#define HFE_FTELL_ERROR -29         /* σφάλμα ftell */
#define HFE_REALLOC_ERROR -30		/* σφάλμα realloc */
#define HFE_TOO_BIG_FILENAME -31	/* πολύ μεγάλο όνομα αρχείου */
#define HFE_SCAN_IN_PROGRESS -32	/* ανοιχτή σάρωση στο αρχείο */
#define HFE_INSERTION_FAILED -33	/* αδικαιολόγητα αποτυχημένη εισαγωγή εγγραφής */
#define HFE_INVALIDRECORD -34		/* μη έγκυρη εγγραφή */
#define HFE_STABFULL -35			/* λίστα ανοικτών σαρώσεων πλήρης */
#define HFE_INVALID_SCANDESC -36	/* μη έγγυρο αναγνωριστικό σάρωσης */
#define HFE_INVALID_OP -37			/* μη έγκυρος τελεστής σύγκρισης */
#define HFE_INVALID_ATTRTYPE -38	/* μη έγκυρος τύπος εγγραφής */
#define HFE_GETFIRSTREC_FAILED -39	/* αδικαιολόγητη αποτυχία της GetFirstRec */
#define HFE_GETNEXTREC_FAILED -40	/* αδικαιολόγητη αποτυχία της GetNextRec */
#define HFE_INVALID_RECID -41		/* μη έγκυρο αναγνωριστικό εγγραφής */

/* Ορισμός καθολικής μεταβλητής σφάλματος */
int HF_errno;

/* Δηλώσεις συναρτήσεων Επιπέδου Εγγραφών */
void HF_Init(void);
int HF_CreateFile(char *filename);
int HF_DestroyFile(char *filename);
int HF_OpenFile(char *filename);
int HF_CloseFile(int fileDesc);
int HF_InsertRec(int fileDesc,char *record,int recordSize);
int HF_DeleteRec(int fileDesc,int recId,int recordSize);
int HF_GetFirstRec(int fileDesc,char *record,int recordSize);
int HF_GetNextRec(int fileDesc,int recId,char *record,int recordSize);
int HF_GetThisRec(int fileDesc,int recId,char *record,int recordSize);
int HF_OpenFileScan(int fileDesc,int recordSize, char attrType,int attrLength,int attrOffset,int op,char *value);
int HF_FindNextRec(int scanDesc,char *record);
int HF_CloseFileScan(int scanDesc);
void HF_PrintError(char *errString);

#endif
