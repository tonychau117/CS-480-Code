# Tony Chau, Enrique Rodriguez

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

TECH ?= ff

ifeq ($(TECH),ff)
FIT_SRC = first_fit.c
else ifeq ($(TECH),bf)
FIT_SRC = best_fit.c
else
$(error TECH must be ff or bf)
endif

SRC = main.c request.c stats.c $(FIT_SRC)
OBJ = $(SRC:.c=.o)
TARGET = sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(TARGET)

ff:
	 $(MAKE) clean
	 $(MAKE) TECH=ff

bf:
	 $(MAKE) clean
	 $(MAKE) TECH=bf

rebuild: clean all

