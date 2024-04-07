CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++2a -gdwarf-4 -fstandalone-debug -O0
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -Wno-error=unused-parameter

exec: bin/exec
tests: bin/tests

bin/exec : ./includes/shared_pointer.hpp ./includes/cord.hpp ./src/cord.cc ./includes/cord_utilities.hpp ./src/cord_utilities.cc ./src/driver.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./src/cord.cc ./src/cord_utilities.cc ./src/driver.cc -o ./bin/exec

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
