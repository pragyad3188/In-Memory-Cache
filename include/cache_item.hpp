#ifndef CACHE_ITEM_H
#define CACHE_ITEM_H
#include<iostream>
template<typename Key,typename T>
struct cacheItem
	{
		Key key;
		T value;
		cacheItem * next;
		cacheItem * prev;
		
		cacheItem()
        {
	        next=NULL;
	        prev=NULL;
        }	
		cacheItem(Key _key,T _value)
        {
            key=_key;
	        value=_value;
	        next=NULL;
	        prev=NULL;
        }
		void print()
		{
			std::cout<<"Key: "<<key<<" Value: "<<value<<"\n";
		}
	};

#endif