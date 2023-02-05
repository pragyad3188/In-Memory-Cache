#ifndef BASE_CACHE_H
#define BASE_CACHE_H

#include<unordered_map>
#include "cache_item.hpp"
#include<cassert>


template<typename Key,typename T>
class Cache
{
	int _capacity;
	mutable int _size;
	mutable int _hit_count;
	mutable int _miss_count;
	cacheItem<Key,T>* head;
	cacheItem<Key,T>* tail;

protected:
	
	Cache<Key,T>(int capacity)
    	{
		assert(capacity);

		_capacity=capacity;
		_hit_count=0;
		_miss_count=0;
		_size=0;
		head=new cacheItem<Key,T>();
		tail=new cacheItem<Key,T>();
		head->next=tail;
		tail->prev=head;

	}
	
	typedef typename std::unordered_map<Key,cacheItem<Key,T>*>::const_iterator key_iterator;
	std::unordered_map<Key,cacheItem<Key,T>*> key_mapping;
	void push_front(cacheItem<Key,T>* &node)
    	{
		cacheItem<Key,T>* temp=head->next;
		head->next = node;
		node->next = temp;
		node->prev = head;
		temp->prev = node;
	}
	void push_back(cacheItem<Key,T>* &node)
    	{
		cacheItem<Key,T>* temp=tail->prev;
		tail->prev = node;
		node->next = tail;
		node->prev = temp;
		temp->next = node;
	}
	
	cacheItem<Key,T>* pop_front()
    	{
		if(_size==0)
			return nullptr;
		cacheItem<Key,T>* temp=head->next;
		head->next=temp->next;
		temp->next->prev=head;
		temp->next=NULL;
		temp->prev=NULL;
		return temp;
	}

	cacheItem<Key,T>* pop_back()
    	{
		if(_size==0)
			return nullptr;
		cacheItem<Key,T>* temp=tail->prev;
		tail->prev=temp->prev;
		temp->prev->next=tail;
		temp->next=NULL;
		temp->prev=NULL;
		return temp;
	}


	void deleteNode(cacheItem<Key,T>* &node)
    	{
		if(node==head || node==tail)
			return;
		cacheItem<Key,T>* delNext=node->next;
		cacheItem<Key,T>* delPrev=node->prev;
		delNext->prev=delPrev;
		delPrev->next=delNext;
	}

	void incrementSize(){_size++;}
	void decrementSize(){_size--;}
    void incrementHitCount(){_hit_count++;}
    void decrementHitCount(){_hit_count--;}
    void incrementMissCount(){_miss_count++;}
    void decrementMissCount(){_miss_count--;}


//--------------------------------------------------------------------------------------------------------------------
// Implement the virtual functions in derived class as per the eviction policy
    
    virtual void  set(const Key& key, const T& value) = 0;
	virtual bool get(const Key& key,T& value) = 0;
	virtual void remove(const Key& key)=0;
	bool contains(const Key& key) const
    { return key_mapping.find(key)!=key_mapping.end(); }

//--------------------------------------------------------------------------------------------------------------------
    
    void clear()
    {
		key_mapping.clear();
		cacheItem<Key,T>* temp=head->next;
		cacheItem<Key,T>* temp2;
		while(temp!=tail)
		{
			temp2=temp;
			temp=temp->next;
			delete temp2;
		}
        _size=0;
        _miss_count=0;
        _hit_count=0;
	}
	int hit_count()		const noexcept { return _hit_count; }
	int miss_count()	const noexcept { return _miss_count; }
	int capacity()		const noexcept { return _capacity; }
	int size()			const noexcept { return _size; }
   	bool empty()		const noexcept { return _size==0; }

	void printlist()	const noexcept
    {
		cacheItem<Key,T>* temp=head->next;
		std::cout<<"\nPrinting Cache\n";
		while(temp!=tail)
		{
			std::cout<<"Key:"<<temp->key<<"     Value:"<<temp->value<<std::endl;
			temp=temp->next;
		}
		std::cout<<"\n\n";
	}
};
#endif
