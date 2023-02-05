#include <iostream>
#include <string>
#include "in_memory_cache.h"

using namespace std;
int main()
{
	cout<<"\n\nTESTING FIFO CACHE\n\n";
	FifoCache<int,int>* c=new FifoCache<int,int>(2);
	cout<<"Capacity:- "<<c->capacity()<<"\n";
	cout<<"Size:- "<<c->size()<<"\n";
	c->printlist();
	c->set(1,1);
	c->printlist();
	cout<<"Size:- "<<c->size()<<"\n";
	c->set(2,2);
	c->printlist();
	cout<<"Size:- "<<c->size()<<"\n";

	int response;
	if(c->get(2,response))
		cout<<"Value of key 2 in cache: "<<response<<endl;
	else
	cout<<"Key: 2  Not present"<<endl;
	c->printlist();
	c->set(3,3);
	c->printlist();

	if(c->get(1,response))
		cout<<"Value of key 1 in cache: "<<response<<endl;
	else
	cout<<"Key 1 Not present"<<endl;
	c->remove(3);
	c->printlist();
	cout<<"Capacity: "<<c->capacity()<<"\n";
}
