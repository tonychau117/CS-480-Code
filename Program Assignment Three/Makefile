# Tony Chau, Enrique Rodriguez

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# SWITCH BETWEEN FIRST OR BEST FIT HERE
SRC = main.c first_fit.c
#SRC = main.c best_fit.c

OBJ = $(SRC:.c=.o)
TARGET = sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

