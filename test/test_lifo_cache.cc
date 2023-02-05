#include "lifo_cache.hpp"

#include <gtest/gtest.h>
#include<iostream>
#include<thread>
#include <string>
using namespace std;


TEST(LIFOCacheTest, InitTest) {
  
    LifoCache<string,int> cache(42);

    ASSERT_EQ(cache.capacity(), 42);
    ASSERT_EQ(cache.size(), 0);
    ASSERT_EQ(cache.hit_count(), 0);
    ASSERT_EQ(cache.miss_count(), 0);
    
    EXPECT_TRUE(cache.empty());
}

TEST(LIFOCacheTest, Insert) {
	LifoCache<int, int> cache(1);

/*
    Initially the cache is empty so while setting key 
    there is a cache miss and hence the key is inserted into the cache 
*/
    EXPECT_TRUE(cache.empty());
	
    cache.set(1, 3);

    ASSERT_EQ(cache.miss_count(), 1);
    ASSERT_EQ(cache.hit_count(), 0);    
    
    int resp=0;

	EXPECT_TRUE(cache.get(1,resp));
	ASSERT_EQ(resp, 3);

	ASSERT_EQ(cache.size(), 1);
	ASSERT_EQ(cache.hit_count(), 1);
    EXPECT_FALSE(cache.empty());
}

TEST(LIFOCacheTest, ReplaceValueInCache)
{
	LifoCache<int, int> cache(1);

	cache.set(1, 1);
    int response;
	EXPECT_TRUE(cache.get(1,response));
    ASSERT_EQ(response, 1);


	cache.set(1, 2);

	EXPECT_TRUE(cache.contains(1));
    response=0;
	EXPECT_TRUE(cache.get(1,response));

	ASSERT_EQ(response, 2);

	ASSERT_EQ(cache.hit_count(), 3);
    ASSERT_EQ(cache.miss_count(), 1);
}

TEST(LIFOCacheTest, Clear)
{
	LifoCache<int, int> cache(3);

	cache.set(1, 1);
    cache.set(2, 2);
	cache.set(3, 3);
    ASSERT_EQ(cache.size(),3);
	
    
    cache.clear();

	EXPECT_TRUE(cache.empty());
	ASSERT_EQ(cache.size(),0);
    ASSERT_EQ(cache.capacity(),3);
}


TEST(LIFOCacheTest, Remove)
{
	LifoCache<int, int> cache(3);
    int response;

	cache.set(1, 1);
	cache.set(2, 2);
	cache.set(3, 3);
    ASSERT_EQ(cache.size(),3);

	cache.remove(2);
	EXPECT_FALSE(cache.get(2,response));
    EXPECT_FALSE(cache.contains(2));
    ASSERT_EQ(cache.size(),2);

    // 3 Misses during insertion into cache + 1 more miss after deletion
	ASSERT_EQ(cache.miss_count(), 4); 
}

TEST(LIFOCacheTest, GetValueFromCache)
{
	LifoCache<int, string> cache(1);
    string response,response2;

	cache.set(1, "a");

	EXPECT_TRUE(cache.get(1,response));
    ASSERT_EQ(response,"a" );
	EXPECT_FALSE(cache.get(2,response2));

	ASSERT_EQ(cache.miss_count(), 2);
	ASSERT_EQ(cache.hit_count(), 1);
    
}


TEST(LIFOCacheTest, Evict)
{
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

	LifoCache<string, int> cache(4);
	int resp;

    cache.set("a", 1);
	cache.set("b", 2);
    cache.set("c", 3);
    cache.set("d", 4);
    
    cache.printlist();
    
    cache.get("a",resp);
	ASSERT_EQ(resp, 1);

    cache.printlist();

	cache.set("e", 5);
	EXPECT_FALSE(cache.contains("d"));
    EXPECT_TRUE(cache.contains("a"));
	
    cache.printlist();

	cache.set("f", 6);
	EXPECT_FALSE(cache.contains("e"));

	EXPECT_TRUE(cache.get("a",resp));
    cache.printlist();
	ASSERT_EQ(cache.size(), 4);

    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    std::cout<<output;
    testing::Test::RecordProperty("output", output);
}


TEST(LIFOCacheTest, ThreadSafety)
{
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

	LifoCache<int, int>* cache=new LifoCache<int,int>(4);
	int resp;
    thread t[8];
    auto f=[](LifoCache<int, int>* cache,int key,int value)
    {
        cache->set(key,value);
    };

    for(int i=1;i<=8;i++)
    {
        t[i-1]= thread(f,cache,i,i);
    }
    for(int i=0;i<8;i++)
    {
        t[i].join();
    }
    
    cache->printlist();
	ASSERT_EQ(cache->size(), 4);

    
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    std::cout<<output;
    testing::Test::RecordProperty("output", output);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
