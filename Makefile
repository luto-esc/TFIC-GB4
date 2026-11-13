CC = gcc
CFLAGS = -Wall -Wextra
SRC = main.c artemis.c validaciones.c
TARGET = programa

all: $(TARGET)

$(TARGET): $(SRC) artemis.h validaciones.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm -f $(TARGET) $(TARGET).exe