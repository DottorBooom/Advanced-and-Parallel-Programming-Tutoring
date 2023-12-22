LIB = lib
CC = gcc
STATIC = yes
ifeq ($(STATIC),yes) 
	CFLAGS = -O3 -Wall -pedantic -std=c17
else
	CFLAGS = -fPIC -O3 -Wall -pedantic -std=c17
endif

all: main

ifeq "${STATIC}" "yes"
main: main.o ${LIB}/libbst.a
	${CC} ${CFLAGS} -o main main.o -L./${LIB}/ -lbst
else
main: main.o ${LIB}/libbst.dylib
		${CC} ${CFLAGS} -o main main.O -L./${LIB} -lbst
endif
${LIB}:
	mkdir -p ${LIB}

${LIB}/libbst.a: nodeTree.o binaryTree.o lib
	ar rs ${LIB}/libbst.a nodeTree.o binaryTree.o

${LIB}/libbst.dylib: nodeTree.o binaryTree.o lib
	${CC} ${CFLAGS} -o ${LIB}/libbst.dylib -shared nodeTree.o binaryTree.o 

main.o: main.c statNode.h statTree.h
	${CC} ${CFLAGS} -c main.c 

nodeTree.o: nodeTree.c statNode.h
	${CC} ${CFLAGS} -c nodeTree.c

binaryTree.o: binaryTree.c statTree.h
	${CC} ${CFLAGS} -c binaryTree.c

.PHONY: clean
clean:
	rm -f *.o
	rm -rf ${LIB}/*.a  ${LIB}/*.${SHARED_EXT}
	rmdir -p ${LIB}
	rm main