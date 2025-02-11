CC = gcc
CFLAGS = -Wall -Wextra
TARGET = lab2

all: $(TARGET)

$(TARGET): lab2.c
	$(CC) $(CFLAGS) -o $(TARGET) lab2.c

clean:
	rm -f $(TARGET)


