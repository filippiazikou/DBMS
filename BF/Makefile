CC = gcc

all: ask1 ask2 ask3
ask1 : epipedo_BF.o main1.o
	$(CC) $(CFLAGS) -o ask1 epipedo_BF.o main1.o

ask2 : epipedo_BF.o main2.o
	$(CC) $(CFLAGS) -o ask2 epipedo_BF.o main2.o

ask3 : epipedo_BF.o main3.o
	$(CC) $(CFLAGS) -o ask3 epipedo_BF.o main3.o

main1.o: main1.c BF_Lib.h
	$(CC) $(CFLAGS) -c main1.c

main2.o: main2.c BF_Lib.h
	$(CC) $(CFLAGS) -c main2.c

main3.o: main3.c BF_Lib.h
	$(CC) $(CFLAGS) -c main3.c

epipedo_BF.o: epipedo_BF.c BF_Lib.h
	$(CC) $(CFLAGS) -c epipedo_BF.c

clean :
	rm epipedo_BF.o main1.o main2.o main3.o
