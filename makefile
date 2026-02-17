CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET = railwaysim
SRCS = $(wildcard tracksim/*.cpp)
TEST_TARGET = railwaysim_tests
TEST_SRCS = tests/test_main.cpp tests/test_track_section.cpp tests/test_axle_counter.cpp tests/test_signal.cpp
CORE_SRCS = tracksim/track_section.cpp tracksim/axle_counter.cpp tracksim/signal.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRCS) $(CORE_SRCS)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) $(CORE_SRCS) -o $(TEST_TARGET)

run-tests: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test run-tests clean
