CC = gcc
CFLAGS = -lm

all: ask

ask : VW.o aminirel.o defn.o parser4.tab.o lex.yy.o DM_Lib.o UT_Lib.o AM_Lib.o HF_Lib.o BF_Lib.o defn.h DM_Lib.h UT_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -o ask VW.o aminirel.o defn.o parser4.tab.o lex.yy.o DM_Lib.o UT_Lib.o AM_Lib.o HF_Lib.o BF_Lib.o $(CFLAGS)

VW.o : VW.c VW_Lib.h defn.h DM_Lib.h UT_Lib.h AM_Lib.h HF_Lib.h BF_Lib.h
	$(CC) -c VW.c

parser4.tab.o : parser4.tab.c parser4.tab.h
	$(CC) -c parser4.tab.c

lex.yy.o : lex.yy.c parser4.h
	$(CC) -c lex.yy.c


clean :
	rm VW.o parser4.tab.o lex.yy.o
