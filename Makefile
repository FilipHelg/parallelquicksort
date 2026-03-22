CC = gcc
CFLAGS = -Ofast -march=native -std=c11 -Wall -Wextra -fopenmp
LDFLAGS = -fopenmp -lm

TARGET = sort_program
SRC = main.c sorting.c distribution.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

clean:
	-if exist $(TARGET).exe del /Q $(TARGET).exe
	-if exist $(TARGET) del /Q $(TARGET)
	-del /Q *.o 2>nul
	-if exist benchmark_results.csv del /Q benchmark_results.csv

test: $(TARGET)
	./$(TARGET) --demo
