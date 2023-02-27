#include "linked_list.hpp"

#include <gtest/gtest.h>
#include<iostream>
#include <string>
using namespace std;
TEST(LinkedListTest, Init) {
  
  List<int,int>* c=new List<int,int>();
  EXPECT_EQ(c->size(), 0);
  EXPECT_EQ(c->empty(), true);
}

TEST(LinkedListTest, PrintList) {
  
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  List<int,int>* c=new List<int,int>();
   cacheItem<int,int>* d=new cacheItem<int,int>(1,2);
  
  c->push_front(d);
  c->printlist();

  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}

TEST(LinkedListTest, PushFront) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  List<int,int>* l=new List<int,int>();
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  cacheItem<int,int>* d=new cacheItem<int,int>(3,4);

  l->push_front(c);
  l->push_front(d);
  l->printlist();

  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}

TEST(LinkedListTest, PushBack) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  List<int,int>* l=new List<int,int>();
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  cacheItem<int,int>* d=new cacheItem<int,int>(3,4);

  l->push_back(c);
  l->push_back(d);
  l->printlist();

  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}

TEST(LinkedListTest, PopBack) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  List<int,int>* l=new List<int,int>();
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  cacheItem<int,int>* d=new cacheItem<int,int>(3,4);

  l->push_back(c);
  l->push_back(d);
  l->printlist();
  l->pop_back();
  l->printlist();

  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}

TEST(LinkedListTest, PopFront) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  List<int,int>* l=new List<int,int>();
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  cacheItem<int,int>* d=new cacheItem<int,int>(3,4);

  l->push_front(c);
  l->push_front(d);
  l->printlist();
  l->pop_front();
  l->printlist();

  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}

TEST(LinkedListTest, DeleteNode) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  List<int,int>* l=new List<int,int>();
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  cacheItem<int,int>* d=new cacheItem<int,int>(3,4);
  cacheItem<int,int>* e=new cacheItem<int,int>(5,6);

  l->push_front(c);
  l->push_front(d);
  l->push_front(e);
  l->printlist();
  l->deleteNode(d);
  l->printlist();

  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}


TEST(LinkedListTest, ClearList) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  List<int,int>* l=new List<int,int>();
  cacheItem<int,int>* c=new cacheItem<int,int>(1,2);
  cacheItem<int,int>* d=new cacheItem<int,int>(3,4);

  l->push_front(c);
  l->push_front(d);
  l->printlist();
  l->clear_list();
  l->printlist();

  std::cout.rdbuf(old);
  std::string output = buffer.str();
  testing::Test::RecordProperty("output", output);
}



int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
