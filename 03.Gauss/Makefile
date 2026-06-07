include ../Makefile.inc

CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall -I.
EIGEN_FLAGS = -I/usr/include/eigen3
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: release debug utest

depends:
	@echo "Depends check skipped"

release:
	@echo "Release build skipped for test-only target"

debug:
	@echo "Debug build skipped for test-only target"

utest: Gauss_test.o Gauss_solve.o util.o
	$(CXX) -o $@ $^ $(GTEST_LIBS) $(EIGEN_FLAGS)

run_utest: utest
	./$<

run_itest:
	@echo "Integration tests skipped for Gauss"

Gauss_solve.o: Gauss_solve.cpp Gauss_solve.h util.h
	$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) -c Gauss_solve.cpp -o $@

Gauss_test.o: Gauss_test.cpp Gauss_solve.h util.h
	$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) -c Gauss_test.cpp -o $@

util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(EIGEN_FLAGS) -c util.cpp -o $@

astyle:
	astyle --options=../astyle.ini *.h *.cpp

tidy:
	../tidy.sh

clean:
	rm -f *.o utest release debug gauss

.PHONY: all depends release debug utest run_utest run_itest astyle tidy clean