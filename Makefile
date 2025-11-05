CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = todo
SRC = todo.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
