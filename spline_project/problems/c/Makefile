CC = g++

CFLAGS = -Wall -g

OBJ = problem_c.o ../../xtspline.o ../../xtlapack.o ../../xtreader.o

EXEC = problem_c

all: $(EXEC)

$(EXEC): problem_c.o
	$(CC) $(OBJ) -o $(EXEC)

problem_c.o: problem_c.cpp ../../xtspline.h
	$(CC) $(CFLAGS) -c problem_c.cpp

clean:
	rm -f $(OBJ) $(EXEC)
