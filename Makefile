
CC = clang
CFLAGS = -O3

TARGET = qsort
OBJ = qsort-main.o qsort-sequential.o qsort-cilk.o
# qsort-openmp.o
# qsort-pthreads.o

all: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(TARGET)
