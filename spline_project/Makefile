CC = g++

CFLAGS = -Wall -g

OBJ = main.o xtspline.o xtlapack.o xtreader.o

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.cpp xtspline.h
	$(CC) $(CFLAGS) -c main.cpp

xtspline.o: xtspline.cpp xtspline.h
	$(CC) $(CFLAGS) -c xtspline.cpp

xtlapack.o: xtlapack.cpp xtlapack.h
	$(CC) $(CFLAGS) -c xtlapack.cpp

xtreader.o: xtreader.cpp xtreader.h
	$(CC) $(CFLAGS) -c xtreader.cpp

clean:
	rm -f $(OBJ) $(EXEC)
