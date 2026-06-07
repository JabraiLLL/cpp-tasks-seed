CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: test

test: sort_test.cpp sorting.h
	$(CXX) $(CXXFLAGS) sort_test.cpp -o test $(GTEST_LIBS)
	./test

clean:
	rm -f test

.PHONY: all test clean
