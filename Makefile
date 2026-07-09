CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Iinclude
TARGET := scenic_matrix
SRC := src/main.c src/graph_matrix.c

ifeq ($(OS),Windows_NT)
TARGET_EXE := $(TARGET).exe
RM := del /Q
else
TARGET_EXE := $(TARGET)
RM := rm -f
endif

.PHONY: all run clean

all: $(TARGET_EXE)

$(TARGET_EXE): $(SRC) include/graph_matrix.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET_EXE)

run: all
	./$(TARGET_EXE)

clean:
	-$(RM) $(TARGET_EXE)
