#ifndef LIFO_CACHE_H
#define LIFO_CACHE_H

#include "cache_item.hpp"
#include "base_cache.hpp"
#include<cassert>


template<typename Key,typename T>
class LifoCache: public Cache<Key,T>
{
	
	using Cache<Key,T>::cache_list;

	void  onKeyAccess(cacheItem<Key,T>* node)
	{
		return;
	}
	void  addCacheItem(cacheItem<Key,T>* node)
	{
		cache_list->incrementSize();
		cache_list->push_back(node);
	}
	cacheItem<Key,T>*  getCandidateCacheItem()
	{
		return cache_list->pop_back();
	}


public:
	LifoCache(int capacity): Cache<Key,T>(capacity)
	{assert(capacity); }

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