##
# List data structure
#
# @file
# @version 0.1

CC = g++
SRC = test.cpp
OUTPUT = list.out

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
