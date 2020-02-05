##
# String Data Structure
#
# @file
# @version 0.1

CC = g++
SRC = test.cpp
OUTPUT = string.out

build:
	${CC} ${SRC} -g -o ${OUTPUT}

clean:
	rm -f *.o *.out

run:
	./${OUTPUT} 100

debug:
	gdb ${OUTPUT}

all: clean build run

# end
