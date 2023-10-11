# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++11

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Executable name
EXECUTABLE = toy_robot

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# Dependencies
-include $(OBJS:.o=.d)

%.d: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -MM -MT '$(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $<)' $< > $@

# Test directories and sources
TEST_DIR = tests
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/test_%.o, $(TEST_SRCS))
TEST_EXECUTABLE = run_tests

# Link against Google Test libraries and potentially include its headers.
TEST_LIBS = -lgtest -lgtest_main
GTEST_INCLUDE = -I/usr/src/gtest/include  # Adjust the path to where Google Test headers are installed on your system.

# Targets

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(GTEST_INCLUDE) -o $(TEST_EXECUTABLE) $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) $(TEST_OBJS) $(TEST_LIBS)


$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(GTEST_INCLUDE) -I$(INCLUDE_DIR) -c $< -o $@
