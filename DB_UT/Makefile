CC = gcc
CFLAGS = -lm

all: askc askd aska

askc : dbcreate.o AM_Lib.o HF_Lib.o BF_Lib.o DB_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -o askc dbcreate.o AM_Lib.o HF_Lib.o BF_Lib.o $(CFLAGS) 

askd : dbdestroy.o AM_Lib.o HF_Lib.o BF_Lib.o DB_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -o askd dbdestroy.o AM_Lib.o HF_Lib.o BF_Lib.o $(CFLAGS)

aska : aminirel.o parser3.tab.o lex.yy.o DM.o UT.o AM_Lib.o HF_Lib.o BF_Lib.o parser3.h DB_Lib.h DM_Lib.h UT_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -g -o aska aminirel.o DM.o UT.o parser3.tab.o lex.yy.o AM_Lib.o HF_Lib.o BF_Lib.o $(CFLAGS)

dbcreate.o: dbcreate.c DB_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -c dbcreate.c

dbdestroy.o: dbdestroy.c DB_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -c dbdestroy.c

aminirel.o: aminirel.c parser3.h DB_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -g -c aminirel.c

DM.o: DM.c DM_Lib.h DB_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -g -c DM.c

UT.o: UT.c UT_Lib.h DB_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -g -c UT.c

parser3.tab.o: parser3.tab.c
	$(CC) -c parser3.tab.c

lex.yy.o: lex.yy.c parser3.h
	$(CC) -c lex.yy.c


clean :
	rm dbcreate.o dbdestroy.o aminirel.o parser3.tab.o lex.yy.o UT.o DM.o
