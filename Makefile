CC = gcc
CFLAGS = -c -g -std=c99
LDFLAGS = -g
EXEC = sudoku

all: ${EXEC}

${EXEC}: sudoku.o
	${CC} ${LDFLAGS} $^ -o $@

sudoku.o: sudoku.c sudoku.h
	${CC} ${CFLAGS} sudoku.c -o $@

clean:
	rm *.o ${EXEC}