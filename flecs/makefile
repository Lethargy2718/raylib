CXX := g++                     # For C++ files
CC := gcc                      # For C files
CXXFLAGS := -Wall -std=c++23 -Ilib
CFLAGS := -Wall -std=c99 -Ilib -D_POSIX_C_SOURCE=200809L
LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS_CPP := main.cpp
SRCS_C := lib/flecs.c
OBJS := $(SRCS_CPP:.cpp=.o) $(SRCS_C:.c=.o)

TARGET := main

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)  # Link with g++

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
