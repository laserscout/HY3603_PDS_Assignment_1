CC = gcc-mp-7
CFLAGS = -fopenmp -O3

TARGET = qsort-omp
OBJ = qsort-main.o qsort-omp.o

all: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(TARGET)
