##==================================================================##
 #
 # Makefile for the CILK implementation of QuickSort
 #
 # Frank Blanning <frankgou@ece.auth.gr>
 # AEM: 6698
 # Time-stamp: <2018-10-28>
 #
##==================================================================##

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CC = gcc
endif

ifeq ($(UNAME_S),Darwin)
	CC = gcc-mp-7
endif

CFLAGS = -fcilkplus -O3

TARGET = qsort-cilk
OBJ = qsort-main.o qsort-cilk.o qsort-sequential.o

all: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(TARGET)
