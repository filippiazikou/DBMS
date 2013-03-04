#ifndef __DEFN_H__
#define __DEFN_H__

#define MAXNAME 15
#define MAXSTRINGLENGTH 255

#ifndef TRUE

#define TRUE 1
#define FALSE 0

#endif /* TRUE */

typedef struct {
	char relname[MAXNAME];	/* όνομα πίνακα */
	int relwidth;		/* εύρος εγγραφής πίνακα σε bytes */
	int attrcnt;		/* αριθμός πεδίων εγγραφής */
	int indexcnt;		/* αριθμός ευρετηρίων πίνακα */
}relDesc;

typedef struct {
	char relname[MAXNAME];	/* όνομα πίνακα */
	char attrname[MAXNAME];	/* όνομα πεδίου του πίνακα */
	int offset;		/* απόσταση αρχής πεδίου από την αρχή της εγγραφής σε bytes */
	int attrlength;		/* μήκος πεδίου σε bytes */
	char attrtype;		/* τύπος πεδίου ('i', 'f', ή 'c' */
	int indexed;		/* TRUE αν το πεδίο έχει ευρετήριο */
	int indexno;		/* αύξον αριθμός του ευρετηρίου αν indexed=TRUE */
}attrDesc;

typedef struct {
   char viewname[MAXNAME];
   int type;
   char relname1[MAXNAME];
   char attrname1[MAXNAME];
   int op;
   char relname2[MAXNAME];
   char attrname2[MAXNAME];
   char value[MAXSTRINGLENGTH];
   int attrcnt;
} viewDesc;

typedef struct {
       char viewname[MAXNAME];
       char viewattrname[MAXNAME];
       char relname[MAXNAME];
       char relattrname[MAXNAME];
} viewAttrDesc; 

int relcatFileDesc;
int attrcatFileDesc;
int viewcatFileDesc;
int viewattrcatFileDesc;

#endif  /*__DEFN_H__*/

