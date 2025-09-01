SRC_DIR = ./src
BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/script

SRC = $(wildcard $(SRC_DIR)/*.c ./main.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

COMPOLER = gcc
CFLAGS = -Wall

all: $(TARGET)

$(TARGET): $(OBJ)
	$(COMPOLER) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(COMPOLER) -c $(CFLAGS) $< -o $@

.PHONY: clean test
clean:
	rm -rf $(BUILD_DIR)/*

test:
	echo "test..."