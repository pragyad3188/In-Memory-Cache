#ifndef BASE_CACHE_H
#define BASE_CACHE_H

#include<unordered_map>
#include "cache_item.hpp"
#include "linked_list.hpp"
#include<shared_mutex>
#include<mutex>
#include<cassert>


template<typename Key,typename T>
class Cache
{
	int _capacity;
	int _hit_count;
	int _miss_count;
	std::shared_timed_mutex _cache_mutex;

protected:
	List<Key,T>* cache_list;
	
	Cache<Key,T>(int capacity)
    	{
		assert(capacity);
		_capacity=capacity;
		_hit_count=0;
		_miss_count=0;
		cache_list=new List<Key,T>();
	}
	
	typedef typename std::unordered_map<Key,cacheItem<Key,T>*>::const_iterator key_iterator;
	std::unordered_map<Key,cacheItem<Key,T>*> key_mapping;


    void incrementHitCount(){_hit_count++;}
    void decrementHitCount(){_hit_count--;}
    void incrementMissCount(){_miss_count++;}
    void decrementMissCount(){_miss_count--;}



    void  set(const Key& key, const T& value)
    {
		std::unique_lock<std::shared_timed_mutex> lock(_cache_mutex);

		key_iterator itr=key_mapping.find(key);
		if(itr != key_mapping.end())
		{   
            incrementHitCount();
			cacheItem<Key,T>* temp=itr->second;
			temp->value=value;
			onKeyAccess(temp);
			key_mapping[key]=temp;
			return;
		}
		else
		{
            incrementMissCount();
			cacheItem<Key,T>* node=new cacheItem(key,value);
			key_mapping[key]=node;
			if(cache_list->size()>=Cache<Key,T>::capacity())
			{
				cacheItem<Key,T>* candidate=getCandidateCacheItem();
				if(!candidate)
					{
						std::cout<<"Error no candidate for eviction found";
						exit(-1);
					}
				cache_list->deleteNode(candidate);
				Key k=candidate->key;
				key_mapping.erase(k);
				delete candidate;
				cache_list->decrementSize();
			}
			addCacheItem(node);
		}
	}



	bool get(const Key& key,T& value){

		std::shared_lock<std::shared_timed_mutex> lock(_cache_mutex);

		key_iterator itr=key_mapping.find(key);
		if(itr==key_mapping.end()){
            incrementMissCount();
			return false;
		}
        incrementHitCount();
		cacheItem<Key,T>* temp=itr->second;
		value=temp->value;
		onKeyAccess(temp);
		return true;
	}

    
	void remove(const Key& key){

		std::unique_lock<std::shared_timed_mutex> lock(_cache_mutex);

		key_iterator itr=key_mapping.find(key);
		if(itr==key_mapping.end())
			{   incrementMissCount();
                return ;
            }
        incrementHitCount();
		cacheItem<Key,T>* temp=itr->second;
		cache_list->deleteNode(temp);
		key_mapping.erase(key);
		delete temp;
		cache_list->decrementSize();
	}

//--------------------------------------------------------------------------------------------------------------------
// Implement the virtual functions in derived class as per the eviction policy
	virtual void  onKeyAccess(cacheItem<Key,T>* node) = 0;
	virtual void  addCacheItem(cacheItem<Key,T>* node) = 0;
	virtual cacheItem<Key,T>*  getCandidateCacheItem() = 0;
//--------------------------------------------------------------------------------------------------------------------
    
	bool contains(const Key& key) const
    { return key_mapping.find(key)!=key_mapping.end(); }


    void clear()
    {
		key_mapping.clear();
		cache_list->clear_list();
        _miss_count=0;
        _hit_count=0;
	}
	int hit_count()		const noexcept { return _hit_count; }
	int miss_count()	const noexcept { return _miss_count; }
	int capacity()		const noexcept { return _capacity; }
};
#endif
