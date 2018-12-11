rotate-matrix: read-matrix.o rotate-matrix.o
	gcc -o rotate-matrix read-matrix.o rotate-matrix.o
rotate-matrix.o: rotate-matrix.c
	gcc -pedantic -std=gnu99 -Wall -Werror -ggdb3 -c rotate-matrix.c
