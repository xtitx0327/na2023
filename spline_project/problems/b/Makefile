CC = g++

CFLAGS = -Wall -g

OBJ = problem_b.o ../../xtspline.o ../../xtlapack.o ../../xtreader.o

EXEC = problem_b

all: $(EXEC)

$(EXEC): problem_b.o
	$(CC) $(OBJ) -o $(EXEC)

problem_b.o: problem_b.cpp ../../xtspline.h
	$(CC) $(CFLAGS) -c problem_b.cpp

clean:
	rm -f $(OBJ) $(EXEC)
