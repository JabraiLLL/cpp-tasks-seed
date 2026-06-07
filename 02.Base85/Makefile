CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: test

test: base85ed_test.cpp base85ed.cpp base85ed.h
	$(CXX) $(CXXFLAGS) base85ed_test.cpp base85ed.cpp -o test $(GTEST_LIBS)
	./test

clean:
	rm -f test

.PHONY: all test clean