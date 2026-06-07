include ../Makefile.inc

CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall -I.
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: release debug utest

depends:
	@echo "Depends check skipped"

release: base85ed.r.o
	$(LD) -o $@ $^

debug: base85ed.d.o
	$(LD) -o $@ $^

utest: base85ed_test.d.o base85ed.d.o
	$(LD) -o $@ $^ $(GTEST_LIBS)

run_utest: utest
	./$<

base85ed.r.o: base85ed.cpp base85ed.h
	$(CXX) $(CXXFLAGS) -O3 -DNDEBUG -c base85ed.cpp -o $@

base85ed.d.o: base85ed.cpp base85ed.h
	$(CXX) $(CXXFLAGS) -g -DDEBUG -c base85ed.cpp -o $@

base85ed_test.d.o: base85ed_test.cpp base85ed.h
	$(CXX) $(CXXFLAGS) -g -DDEBUG -c base85ed_test.cpp -o $@

astyle:
	astyle --options=../astyle.ini *.h *.cpp

tidy:
	../tidy.sh

clean:
	rm -f *.o release debug utest

.PHONY: all depends release debug utest run_utest astyle tidy clean
