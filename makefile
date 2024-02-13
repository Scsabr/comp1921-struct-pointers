# Example makefile - you can use this in your own programs without crediting me.

# this is the compiler and flags
CC = gcc

CFLAGS = -Wall -Werror -g

SRCS = code.c

OBJS = $(SRCS:.c=.o)

TARGET = pgmCheck

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)