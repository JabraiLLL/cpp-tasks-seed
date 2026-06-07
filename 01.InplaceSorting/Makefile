include ../Makefile.inc

CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall -I.
GTEST_LIBS = -lgtest -lgtest_main -lpthread

all: release debug utest

depends:
	@echo "Depends check skipped"

release: sort_demo.r.o
	$(LD) -o $@ $^

debug: sort_demo.d.o
	$(LD) -o $@ $^

utest: sort_test.d.o
	$(LD) -o $@ $^ $(GTEST_LIBS)

run_utest: utest
	./$<

run_itest: utest
	@echo "=== Integration tests ==="
	./utest --gtest_filter=IntegrationTest.*

sort_demo.r.o: sort_demo.cpp sorting.h
	$(CXX) $(CXXFLAGS) -O3 -DNDEBUG -c sort_demo.cpp -o $@

sort_demo.d.o: sort_demo.cpp sorting.h
	$(CXX) $(CXXFLAGS) -g -DDEBUG -c sort_demo.cpp -o $@

sort_test.d.o: sort_test.cpp sorting.h
	$(CXX) $(CXXFLAGS) -g -DDEBUG -c sort_test.cpp -o $@

astyle:
	astyle --options=../astyle.ini *.h *.cpp

tidy:
	../tidy.sh

clean:
	rm -f *.o release debug utest

.PHONY: all depends release debug utest run_utest run_itest astyle tidy clean
