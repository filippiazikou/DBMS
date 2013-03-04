#ifndef __BF_LIB__
#define __BF_LIB__

#include <stdio.h>

#define BF_BUFFER_SIZE 20
#define BF_BLOCK_SIZE 1024
#define MAXOPENFILES 25
#define TRUE 1
#define FALSE 0
#define BFE_OK 0	/* OK */
#define BFE_NOMEM -1	/* lack of memory */
#define BFE_NOBUF -2	/* lack of buffer */
#define BFE_BLOCKFIXED -3	/* block is already pinned in buffer */
#define BFE_BLOCKNOTINBUF -4	/* block for unpin is not in buffer */
#define BFE_BLOCKINBUF -5	/* block already in buffer */
#define BFE_OS -6	/* general error of the Operating System */
#define BFE_INCOMPLETEREAD -7	/* incomplete reading of block */
#define BFE_INCOMPLETEWRITE -8	/* incomplete writing in block */
#define BFE_INCOMPLETEHDRREAD -9	/* incomplete reading of header block */
#define BFE_INCOMPLETEHDRWRITE -10	/* incomplete writing in header block */
#define BFE_INVALIDBLOCK -11	/* invalid number for recognising a block */
#define BFE_FILEOPEN -12	/* file already open */
#define BFE_FTABFULL -13	/* the list of open files is full */
#define BFE_FD -14	/* invalid recognition number of file */
#define BFE_EOF -15	/* end of file */
#define BFE_BLOCKFREE -16	/* block already free */
#define BFE_BLOCKUNFIXED -17	/* block already unpinned */
#define BFE_CANNOTCREATE -18	/* cannot create a new file */
#define BFE_TOOBIGFILE -19	/* the file can have only 1024 * 8 blocks */

/*Struct for open files*/
typedef struct open_file o_f;

struct open_file {
	int pinned_blocks[BF_BUFFER_SIZE];	//arithmos tou block pou exei apothikeytei sti mnimi sti sigkekrimeni thesi alliws einai 0
	char *filename;	//The name of the file
	char *header;	//Το header mporei na einai orato mono apo edw
	FILE *fp;
	int valid;	//Takes values 0 if there isn't an open file and 1 if there is (I wish there was a bool in C)
};

o_f f[MAXOPENFILES];

/* Struct for blocks */
typedef struct block bl;

struct block {
	char data[BF_BLOCK_SIZE];
	char *filename;
	int pinned;	//0 if unpinned, 1 if pinned
	int timestamp;	//LRU
	int dirty;	//0 if not dirty (not changed in the buffer), 1 if dirty (chaned in the buffer)
	int valid;	//0 if not valid, 1 if valid - 1 an den exei enimerwthei o diskos
	int BlN;
};

bl b[BF_BUFFER_SIZE];

/*Declaration of helping functions*/
char is_bit_set(char data,int n);
char clear_bit(char data,int n);
char set_bit(char data,int n);

int find_place(void);

/*Declaration of basic functions*/
void BF_Init (void);
int BF_CreateFile (char *fileName);
int BF_DestroyFile (char *fileName);
int BF_OpenFile(char *fileName);
int BF_CloseFile (int fileDesc);
int BF_GetFirstBlock (int fileDesc, int *blockNum, char **blockBuf);
int BF_GetNextBlock (int fileDesc, int *blockNum, char **blockBuf);
int BF_GetThisBlock (int fileDesc, int blockNum, char **blockBuf);
int BF_AllocBlock (int fileDesc, int *blockNum, char **blockBuf);
int BF_DisposeBlock (int fileDesc, int *blockNum);
int BF_UnpinBlock (int fileDesc, int blockNum, int dirty);
void BF_PrintError (char *errString);

#endif
