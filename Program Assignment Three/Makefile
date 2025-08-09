CC = gcc
CFLAGS = -Wall -g
OBJS = main.o first_fit.o request.o stats.o

sim: $(OBJS)
	$(CC) -o sim $(OBJS)

main.o: main.c memory.h
first_fit.o: first_fit.c memory.h
request.o: request.c
stats.o: stats.c

clean:
	rm -f *.o sim
