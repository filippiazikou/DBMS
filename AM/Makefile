CC = gcc
CFLAGS = -lm

all: ask0 ask1 ask2 ask3

ask0 : epipedo_AM.o BF_Lib.o ConstructionMain.o HF_Lib.o
	$(CC) -o ask0 epipedo_AM.o BF_Lib.o ConstructionMain.o HF_Lib.o $(CFLAGS)

ask1 : epipedo_AM.o BF_Lib.o main1.o HF_Lib.o
	$(CC) -o ask1 epipedo_AM.o BF_Lib.o main1.o HF_Lib.o $(CFLAGS)

ask2 : epipedo_AM.o BF_Lib.o main2.o HF_Lib.o
	$(CC) -o ask2 epipedo_AM.o BF_Lib.o main2.o HF_Lib.o $(CFLAGS)

ask3 : epipedo_AM.o BF_Lib.o main3.o HF_Lib.o
	$(CC) -o ask3 epipedo_AM.o BF_Lib.o main3.o HF_Lib.o $(CFLAGS)

ConstructionMain.o: ConstructionMain.c AM_Lib.h HF_Lib.h
	$(CC) -c ConstructionMain.c

main1.o: main1.c AM_Lib.h HF_Lib.h
	$(CC) -c main1.c

main2.o: main2.c AM_Lib.h HF_Lib.h
	$(CC) -c main2.c

main3.o: main3.c AM_Lib.h HF_Lib.h
	$(CC) -c main3.c

epipedo_AM.o: epipedo_AM.c BF_Lib.h AM_Lib.h
	$(CC) -c epipedo_AM.c

clean :
	rm epipedo_AM.o ATHLETES ATHLETES.0 ATHLETES.1 ATHLETES.2 EVENTS EVENTS.0 EVENTS.1 PARTICIPATIONS PARTICIPATIONS.0 PARTICIPATIONS.1 PARTICIPATIONS.2 
