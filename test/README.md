# Unit Testing using GoogleTest

The library was stress tested for different scenarios using the famous GoogleTest library(gtest) for c++. Each of the individual cache type was tested(LRU,LIFO,FIFO) and the files can be seen here.

When adding new types of cache to the module make sure all the functions mentioned in the Cache header are thoroughly tested using gtest. For reference refer to the tests written for the different libraries. Also testing for a thread safe implementation is important to avoid any problems when implementing in apllications.

This folder contains UNIT TESTS for our given library. To run any of the already present unit tests,like run "test_lru_cache.cc" ,do the following:-


1. g++ -o my_tests test_lru_cache.cc -I../include -lgtest -lgtest_main
2. ./my_tests --gtest_output=xml:./my_tests.xml

