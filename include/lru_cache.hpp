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

	using Cache<Key,T>::cache_list;
	
	void  onKeyAccess(cacheItem<Key,T>* node)
	{
		cache_list->deleteNode(node);
		cache_list->push_front(node);
	}
	void  addCacheItem(cacheItem<Key,T>* node)
	{
		cache_list->push_front(node);
		cache_list->incrementSize();
	}
	cacheItem<Key,T>*  getCandidateCacheItem()
	{
		return cache_list->pop_back();
	}


public:
	
	LruCache(int capacity)
    :Cache<Key,T>(capacity)
	{assert(capacity);}


	void  set(const Key& key, const T& value)		{Cache<Key,T>::set(key,value);}
	bool get(const Key& key,T& value)				{return Cache<Key,T>::get(key,value);}
	void remove(const Key& key)						{Cache<Key,T>::remove(key);}
	bool contains(const Key& key) const				{return Cache<Key,T>::contains(key);}
	int size() 			const noexcept 				{return cache_list->size();}
	int capacity()   	const noexcept      		{return Cache<Key,T>::capacity();}
    int hit_count()   	const noexcept      		{return Cache<Key,T>::hit_count();}
    int miss_count()   	const noexcept      		{return Cache<Key,T>::miss_count();}
	void printlist()	const noexcept				{cache_list->printlist();}
	void clear()   									{Cache<Key,T>::clear();}
};
#endif