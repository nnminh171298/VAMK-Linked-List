ifndef GTEST_DIR
	export GTEST_DIR=~/googletest/googletest
endif
PROJ=linked_list
TEST_CASE=linked_list_testcase
COPTS=-fprofile-arcs -ftest-coverage
LDFLAGS=-fprofile-arcs -ftest-coverage

default: test

main: main.o $(PROJ).o
	gcc main.o $(PROJ).o -o main

test: Gtest_main.o $(TEST_CASE).o $(PROJ)_test.o libgtest.a
	g++ -I $(GTEST_DIR)/include -pthread $(TEST_CASE).o $(PROJ)_test.o Gtest_main.o libgtest.a $(COPTS) -o my_test

######## Googletest Lib ##########
libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
##### Test ###############
Gtest_main.o: Gtest_main.c
	g++ -c -isystem $(GTEST_DIR)/include $(COPTS) -I$(GTEST_DIR) Gtest_main.c

$(PROJ)_test.o: $(PROJ).c $(PROJ).h
	g++ -c -isystem $(GTEST_DIR)/include $(COPTS) -I$(GTEST_DIR) $(PROJ).c -o $(PROJ)_test.o

$(TEST_CASE).o: $(TEST_CASE).c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR)  $(TEST_CASE).c 
##### Normal #######################

$(PROJ).o: $(PROJ).c $(PROJ).h
	g++ -c $(PROJ).c

main.o: main.c $(PROJ).h
	gcc -c main.c

###########################
clean:
	rm -f *.o

report:
	COV_OUTPUT=./cov_output
	lcov -c -i -d . -o .coverage.base
	lcov -c -d . -o .coverage.run
	lcov -d . -a .coverage.base -a .coverage.run -o .coverage.total
	genhtml --no-branch-coverage -o $(COV_OUTPUT) .coverage.total
	rm -f .coverage.base .coverage.run .coverage.total
