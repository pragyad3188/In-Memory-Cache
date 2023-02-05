#include "cache_item.hpp"

#include <gtest/gtest.h>
#include<iostream>
#include <string>
using namespace std;
TEST(CacheItemTest, CheckingKeyAndValue) {
  
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  EXPECT_EQ(c->key, 1);
  EXPECT_EQ(c->value, 2);
  
  cacheItem<int,string> *d = new cacheItem<int,string>(1,"a");
  EXPECT_EQ(d->value, "a");
  ASSERT_NE(d->value, "2");
}


TEST(CacheItemTest, CaptureOutput) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  c->print();
  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
