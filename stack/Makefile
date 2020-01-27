##
# Stack Data Structure
#
# @file
# @version 0.1

CC = g++
SRC = test.cpp
OUTPUT = stack.out

build:
	${CC} ${SRC} -o ${OUTPUT}

clean:
	rm -f *.o *.out

run:
	./${OUTPUT} 10

debug:
	gdb ${OUTPUT}

all: clean build run

# end
