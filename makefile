CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET = railwaysim
SRCS = tracksim/SignalClass.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
