ifndef GTEST_DIR
	export GTEST_DIR=~/googletest/googletest
endif
PROJ=linked_list
TEST_CASE_BASIC=linked_list_testcase_basic
TEST_CASE_ADDITIONAL=linked_list_testcase_additional
HELPER = helper
COPTS=-fprofile-arcs -ftest-coverage
LDFLAGS=-fprofile-arcs -ftest-coverage
COV_OUTPUT=./cov_output

default: test

main: main.o $(PROJ).o
	gcc main.o $(PROJ).o -o main

test: Gtest_main.o $(TEST_CASE_BASIC).o $(TEST_CASE_ADDITIONAL).o $(HELPER).o $(PROJ)_test.o libgtest.a
	g++ -I $(GTEST_DIR)/include -pthread $(HELPER).o $(TEST_CASE_BASIC).o $(TEST_CASE_ADDITIONAL).o $(PROJ)_test.o Gtest_main.o libgtest.a $(COPTS) -o my_test

######## Googletest Lib ##########
libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I $(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
##### Test ###############
Gtest_main.o: Gtest_main.c
	g++ -c -isystem $(GTEST_DIR)/include $(COPTS) -I $(GTEST_DIR) Gtest_main.c

$(PROJ)_test.o: $(PROJ).c $(PROJ).h
	g++ -c -isystem $(GTEST_DIR)/include $(COPTS) -I $(GTEST_DIR) $(PROJ).c -o $(PROJ)_test.o

$(TEST_CASE_BASIC).o: $(TEST_CASE_BASIC).c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR)  $(TEST_CASE_BASIC).c

$(TEST_CASE_ADDITIONAL).o: $(TEST_CASE_ADDITIONAL).c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR)  $(TEST_CASE_ADDITIONAL).c

$(HELPER).o: $(HELPER).c
	g++ -c $(HELPER).c

##### Normal #######################

$(PROJ).o: $(PROJ).c $(PROJ).h
	g++ -c $(PROJ).c

main.o: main.c $(PROJ).h
	gcc -c main.c

###########################
clean:
	rm -f *.o

report:
	lcov --rc lcov_branch_coverage=1 -c -i -d . -o .coverage.base
	lcov --rc lcov_branch_coverage=1 -c -d . -o .coverage.run
	lcov --rc lcov_branch_coverage=1 -d . -a .coverage.base -a .coverage.run -o .coverage.total
	genhtml --branch-coverage -o ${COV_OUTPUT} .coverage.total
	rm -f .coverage.base .coverage.run .coverage.total