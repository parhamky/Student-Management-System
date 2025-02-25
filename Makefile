# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra 
LDFLAGS = -lsqlite3 -lstdc++fs

# Executable name
TARGET = main

# Source files
SRCS = main.cpp db.h models.h control.h

# Migrations directory
UP_MIGRATIONS_DIR = migrations/up
DOWN_MIGRATIONS_DIR = migrations/down

# Database name
DB_NAME = test

# Phony targets
.PHONY: all compile migrate run clean

# Default target
all: compile migrate run

# Compile the program
compile: $(SRCS)
	@echo "Compiling..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)
	@echo "Compilation complete."

# Apply up migrations
migrate:
	@echo "Applying up migrations..."
	@if [ ! -d "$(UP_MIGRATIONS_DIR)" ]; then \
		echo "Error: Up migrations directory '$(UP_MIGRATIONS_DIR)' does not exist."; \
		exit 1; \
	fi
	@./$(TARGET) migrate $(UP_MIGRATIONS_DIR)
	@echo "Up migrations applied."

# Apply down migrations
down:
	@echo "Applying down migrations..."
	@if [ ! -d "$(DOWN_MIGRATIONS_DIR)" ]; then \
		echo "Error: Down migrations directory '$(DOWN_MIGRATIONS_DIR)' does not exist."; \
		exit 1; \
	fi
	@./$(TARGET) migrate $(DOWN_MIGRATIONS_DIR)
	@echo "Down migrations applied."

# Run the program
run:
	@echo "Running the program..."
	@./$(TARGET) run
	@echo "Program execution complete."

# Clean up
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET) $(DB_NAME).db
	@echo "Cleanup complete."

