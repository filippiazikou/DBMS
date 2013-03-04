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
#define HFE_NOMEM -1				/* ������� ������ */  
#define HFE_NOBUF -2				/* ������� ����� ���������� ������ */  
#define HFE_BLOCKFIXED -3			/* ����� ��� ``���������'' ��� ����� */  
#define HFE_BLOCKNOTINBUF -4		/* ����� ��� ``���������'' ��� ����� ��� ����� */  
#define HFE_BLOCKINBUF -5			/* ����� ��� ��� ����� */  
#define HFE_OS -6					/* ������ ������ ������������ ���������� */  
#define HFE_INCOMPLETEREAD -7		/* ������ �������� ����� */  
#define HFE_INCOMPLETEWRITE -8		/* ������ ������� �� ����� */  
#define HFE_INCOMPLETEHDRREAD -9	/* ������ �������� �����-��������� */  
#define HFE_INCOMPLETEHDRWRITE -10  /* ������ ������� �� �����-�������� */  
#define HFE_INVALIDBLOCK -11	    /* �� ������� �������������� ������� ����� */  
#define HFE_FILEOPEN -12		    /* ������ ��� ������� */  
#define HFE_FTABFULL -13			/* ����� �������� ������� ������ */  
#define HFE_FD -14					/* �� ������� �������������� ������� ������� */  
#define HFE_EOF -15				    /* ����� ������� */  
#define HFE_BLOCKFREE -16			/* ����� ��� ��������� */  
#define HFE_BLOCKUNFIXED -17        /* ����� ��� ``�����������'' */  
#define HFE_FILE_EXISTS -18		    /* ������ ������� ��� */
#define HFE_FILE_NOT_EXISTS -19	    /* ������ ��� ������� */
#define HFE_FOPEN_ERROR  -20		/* ������ ��� ������� ��� ������� */
#define HFE_FILE_CLOSED -21		    /* ������ ��� ������� */
#define HFE_INVALID_FILEDESC -22    /* �� ������ ������������� ������� */
#define HFE_MALLOC_ERROR -23        /* ������ malloc */
#define HFE_FWRITE_ERROR -24		/* ������ fwrite */
#define HFE_FCLOSE_ERROR -25		/* ������ fclose */
#define HFE_NULL_POINTER -26		/* ����� ������� */
#define HFE_FSEEK_ERROR -27         /* ������ fseek */
#define HFE_FREAD_ERROR -28			/* ������ fread */
#define HFE_FTELL_ERROR -29         /* ������ ftell */
#define HFE_REALLOC_ERROR -30		/* ������ realloc */
#define HFE_TOO_BIG_FILENAME -31	/* ���� ������ ����� ������� */
#define HFE_SCAN_IN_PROGRESS -32	/* ������� ������ ��� ������ */
#define HFE_INSERTION_FAILED -33	/* ������������� ����������� �������� �������� */
#define HFE_INVALIDRECORD -34		/* �� ������ ������� */
#define HFE_STABFULL -35			/* ����� �������� �������� ������ */
#define HFE_INVALID_SCANDESC -36	/* �� ������ ������������� ������� */
#define HFE_INVALID_OP -37			/* �� ������� �������� ��������� */
#define HFE_INVALID_ATTRTYPE -38	/* �� ������� ����� �������� */
#define HFE_GETFIRSTREC_FAILED -39	/* ������������� �������� ��� GetFirstRec */
#define HFE_GETNEXTREC_FAILED -40	/* ������������� �������� ��� GetNextRec */
#define HFE_INVALID_RECID -41		/* �� ������ ������������� �������� */

/* ������� ��������� ���������� ��������� */
int HF_errno;

/* �������� ����������� �������� �������� */
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
