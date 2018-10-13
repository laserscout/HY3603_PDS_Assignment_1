export DYLD_LIBRARY_PATH=./cilk/lib/
export LIBRARY_PATH=./cilk/lib/
export C_INCLUDE_PATH=./cilk/lib/:/Applications/Xcode-beta.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
CC = ./cilk/bin/clang
CFLAGS = -fcilkplus -O3

TARGET = qsort-cilk
OBJ = qsort-main.o qsort-cilk.o

all: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(TARGET)
