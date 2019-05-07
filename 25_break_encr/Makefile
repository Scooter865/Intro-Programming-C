CFLAGS=-pedantic -std=gnu99 -Wall -Werror -ggdb3

breaker: break_encr.o
	gcc -o breaker break_encr.o
%.o: %.c
	gcc $(CFLAGS) -c $<
	
.PHONY: clean
clean:
	rm -f *.o *.c~ *.h~

#specify header dependencies here if needed
#filename.o: filename.h
