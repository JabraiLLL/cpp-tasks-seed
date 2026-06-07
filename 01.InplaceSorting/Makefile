include ../Makefile.inc

CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall -I.
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: run_utest run_itest

utest: sort_test.o
	$(CXX) -o $@ $^ $(GTEST_LIBS)

sort_test.o: sort_test.cpp sorting.h
	$(CXX) $(CXXFLAGS) -c sort_test.cpp -o $@

run_utest: utest
	./$<

run_itest: utest
	@echo "Running integration tests (different sizes)"
	./utest --gtest_filter=IntegrationTest.*

astyle:
	astyle --options=../astyle.ini *.h *.cpp

tidy:
	../tidy.sh

clean:
	rm -f utest sort_test.o

.PHONY: all run_utest run_itest astyle tidy clean