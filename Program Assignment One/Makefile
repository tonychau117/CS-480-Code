CC = gcc # GNU C compiler
CFLAGS = -Wall -Wextra -pthread # enables pthread support
TARGET = bots # target name
SRC = AssignmentOne.C # source file

all: $(TARGET) # build rule
$(TARGET): $(SRC) # link rule
	$(CC) $(CFLAGS) -o $@ $^
clean: # clean builds
	rm -f $(TARGET) QUOTE.txt
.PHONY: all clean # force run targets
