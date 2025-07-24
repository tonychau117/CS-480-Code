CC = gcc
CFLAGS = -Wall -g
TARGET = dsh

all: $(TARGET)
$(TARGET): main.o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o utils.o

main.o: main.c xsh.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c xsh.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o $(TARGET)
