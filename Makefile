CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
INCLUDES := -Iinclude
BIN_DIR := bin
OBJ_DIR := $(BIN_DIR)/obj
TARGET := $(BIN_DIR)/product_sales_management

APP_SOURCES := \
	src/main.c \
	src/controllers/product_controller.c \
	src/controllers/report_controller.c \
	src/repositories/product_repository.c \
	src/repositories/sale_repository.c \
	src/services/report_service.c \
	src/views/console_view.c

APP_OBJECTS := $(APP_SOURCES:src/%.c=$(OBJ_DIR)/%.o)

TEST_TARGETS := $(BIN_DIR)/test_product_repository $(BIN_DIR)/test_report_service

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(APP_OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR)/test_product_repository: tests/test_product_repository.c src/repositories/product_repository.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BIN_DIR)/test_report_service: tests/test_report_service.c src/services/report_service.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGETS)
	./$(BIN_DIR)/test_product_repository
	./$(BIN_DIR)/test_report_service

clean:
	rm -rf $(BIN_DIR)
