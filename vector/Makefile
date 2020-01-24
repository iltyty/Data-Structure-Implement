##
# Vector data structure in c++
#
# @file
# @version 0.1

CC = g++
SRC = test.cpp
OUTPUT = vector.out

build:
	${CC} ${SRC} -o ${OUTPUT}

clean:
	rm -f *.o

run:
	./${OUTPUT} 10

debug:
	gdb ${OUTPUT}

all: clean build run

# end
