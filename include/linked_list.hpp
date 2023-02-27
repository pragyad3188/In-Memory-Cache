#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "cache_item.hpp"
#include<cassert>


template<typename Key,typename T>
class List
{
    int _size;
	cacheItem<Key,T>* head;
	cacheItem<Key,T>* tail;	
	
public:
    List<Key,T>()
    {
		_size=0;
		head=new cacheItem<Key,T>();
		tail=new cacheItem<Key,T>();
		head->next=tail;
		tail->prev=head;
	}
	
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
		if(delNext!=NULL)
		delNext->prev=delPrev;
		
		if(delPrev!=NULL)
		delPrev->next=delNext;
	}

	void incrementSize(){_size++;}
	void decrementSize(){_size--;}

    void clear_list()
    {
		cacheItem<Key,T>* temp=head->next;
		cacheItem<Key,T>* temp2;
		while(temp!=tail)
		{
			temp2=temp;
			temp=temp->next;
			delete temp2;
		}
		head->next=tail;
		tail->prev=head;
        _size=0;
	}
	int size()			const  { return _size; }
   	bool empty()		const  { return _size==0; }

	void printlist()	const
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
