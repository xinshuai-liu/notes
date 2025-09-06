SRC_DIR = ./src
BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/app

SRC = $(wildcard $(SRC_DIR)/*.c ./main.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

COMPILER = gcc
CFLAGS = -Wall

all: $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	$(COMPILER) -c $(CFLAGS) $< -o $@

.PHONY: clean test
clean:
	rm -rf $(BUILD_DIR)/*

test:
	echo "test..."
