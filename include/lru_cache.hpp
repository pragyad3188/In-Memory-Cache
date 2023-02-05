#ifndef LRU_CACHE_H
#define LRU_CACHE_H
#include "base_cache.hpp"
#include "cache_item.hpp"
#include<cassert>
#include<mutex>
#include<shared_mutex>


template<typename Key,typename T>
class LruCache: public Cache<Key,T>
{

	using Cache<Key,T>::key_mapping;
	using Cache<Key,T>::deleteNode;
	using Cache<Key,T>::push_front;
	using Cache<Key,T>::push_back;
	using Cache<Key,T>::pop_front;
	using Cache<Key,T>::pop_back;
	using Cache<Key,T>::incrementSize;
	using Cache<Key,T>::decrementSize;
    using Cache<Key,T>::incrementHitCount;
	using Cache<Key,T>::decrementHitCount;
    using Cache<Key,T>::incrementMissCount;
	using Cache<Key,T>::decrementMissCount;


	typedef typename Cache<Key,T>::key_iterator key_iterator;	
	std::shared_timed_mutex _cache_mutex;

public:
	
	LruCache(int capacity)
    :Cache<Key,T>(capacity)
	{assert(capacity);}

	void  set(const Key& key, const T& value)
    {
		std::unique_lock<std::shared_timed_mutex> lock(_cache_mutex);


		key_iterator itr=key_mapping.find(key);
		if(itr != key_mapping.end())
		{
            incrementHitCount();
			cacheItem<Key,T>* temp=itr->second;
			deleteNode(temp);
			temp->value=value;
			push_front(temp);
			key_mapping[key]=temp;
			return;
		}
		else
		{
            incrementMissCount();
			cacheItem<Key,T>* node=new cacheItem<Key,T>(key,value);
			key_mapping[key]=node;
			if(Cache<Key,T>::size()<Cache<Key,T>::capacity())
			{
				push_front(node);
				incrementSize();
			}
			else
			{
				push_front(node);
				cacheItem<Key,T>* temp=pop_back();
				Key k=temp->key;
				key_mapping.erase(k);
				delete temp;
			}
		}
	}
	bool get(const Key& key,T& value)
    {
		std::shared_lock<std::shared_timed_mutex> lock(_cache_mutex);

		key_iterator itr=key_mapping.find(key);
		if(itr==key_mapping.end()){
            incrementMissCount();
			return false;
		}
        incrementHitCount();
		cacheItem<Key,T>* temp=itr->second;
		deleteNode(temp);
		push_front(temp);
		value=temp->value;
		return true;
	}

	void remove(const Key& key)
    {
		std::unique_lock<std::shared_timed_mutex> lock(_cache_mutex);
		key_iterator itr=key_mapping.find(key);
		if(itr==key_mapping.end())
        {
            incrementMissCount();
			return ;
        }
        incrementHitCount();
		cacheItem<Key,T>* temp=itr->second;
		deleteNode(temp);
		key_mapping.erase(key);
		delete temp;
		decrementSize();
	}


	bool contains(const Key& key) const		{return Cache<Key,T>::contains(key);}
	int size() 			const noexcept 		{return Cache<Key,T>::size();}
	int capacity()   	const noexcept      {return Cache<Key,T>::capacity();}
    int hit_count()   	const noexcept      {return Cache<Key,T>::hit_count();}
    int miss_count()   	const noexcept      {return Cache<Key,T>::miss_count();}
	void printlist()	const noexcept		{Cache<Key,T>::printlist();}
    bool empty()		const noexcept 		{ return Cache<Key,T>::empty();}
	void clear()   							{Cache<Key,T>::clear();}
};
#endif