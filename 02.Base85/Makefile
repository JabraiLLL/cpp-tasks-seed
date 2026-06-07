include ../Makefile.inc

CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall -I.
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: release debug utest

depends:
	@echo "Depends check skipped"

release:
	@echo "Release build skipped for test-only target"

debug:
	@echo "Debug build skipped for test-only target"

utest: base85ed_test.o base85ed.o
	$(CXX) -o $@ $^ $(GTEST_LIBS)

run_utest: utest
	./$<

run_itest: utest
	@echo "Integration tests for Base85"
	./utest

base85ed.o: base85ed.cpp base85ed.h
	$(CXX) $(CXXFLAGS) -c base85ed.cpp -o $@

base85ed_test.o: base85ed_test.cpp base85ed.h
	$(CXX) $(CXXFLAGS) -c base85ed_test.cpp -o $@

astyle:
	astyle --options=../astyle.ini *.h *.cpp

tidy:
	../tidy.sh

clean:
	rm -f *.o utest

.PHONY: all depends release debug utest run_utest run_itest astyle tidy clean
