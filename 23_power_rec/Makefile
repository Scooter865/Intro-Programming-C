test-my-power: test-power.o power.o
	gcc -o test-my-power test-power.o power.o
power.o: power.c
	gcc -pedantic -std=gnu99 -Wall -Werror -ggdb3 -c power.c
test-power.o: test-power.c
	gcc -pedantic -std=gnu99 -Wall -Werror -ggdb3 -c test-power.c
