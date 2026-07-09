CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -pedantic -Iinclude
TARGET := build/graph_practice.exe
SOURCES := src/main.c src/adj_list_graph.c src/adj_matrix_graph.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf build
