CXX := g++
CXXFLAGS := -Wall -std=c++23
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
