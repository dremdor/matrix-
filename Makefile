LIBRARY = s21_matrix_oop.a
TEST = tests/test_matrix.cpp

GTEST_DIR = /usr/src/gtest
GTEST_LIB = -lgtest -lgtest_main -lpthread

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra
COVERAGE_FLAGS = --coverage
LIB_FLAGS = ar rcs

all: $(LIBRARY)

$(LIBRARY): build.o
	$(LIB_FLAGS) $(LIBRARY) *.o
	rm -rf *.o

test: build_test.o
	$(LIB_FLAGS) $(LIBRARY) *.o
	$(CXX) $(CXXFLAGS) --coverage -o "matrix_test" $(TEST) -L. -l:s21_matrix_oop.a $(GTEST_LIB)
	./matrix_test
	make gcov_report
	open report/home/dremdor/matrix-/index.html

build.o:
	$(CXX) $(CXXFLAGS) -c *.cpp

build_test.o:
	$(CXX) $(CXXFLAGS) --coverage -c *.cpp

gcov_report:
	lcov -t "test" -o test.info -c -d . --ignore-errors mismatch
	genhtml -o report test.info

clean:
	rm -rf *.o $(LIBRARY) *.gc* matrix_test *.info report/

rebuild: clean all
