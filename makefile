CC = gcc
CFLAGS = -Wall -ansi -pedantic

OBJS = randomgen.o generators.o event.o enode.o events.o laundry.o main.o

main: ${OBJS}
	${CC} -o program -lm ${OBJS}
		
clean:
	rm -f ${OBJS} program *~
        
