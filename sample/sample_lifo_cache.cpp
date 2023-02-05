#include <iostream>
#include <string>
#include "in_memory_cache.h"

using namespace std;
int main()
{

	cout<<"\n\nTESTING LIFO CACHE\n\n";
	
	LifoCache<int,string>* c=new LifoCache<int,string>(2);
	cout<<"Capacity:- "<<c->capacity()<<"\n";
	cout<<"Size:- "<<c->size()<<"\n";
	c->printlist();
	c->set(1,"a");
	c->printlist();
	cout<<"Size:- "<<c->size()<<"\n";
	c->set(2,"b");
	c->printlist();
	cout<<"Size:- "<<c->size()<<"\n";

	string response;
	if(c->get(1,response))
		cout<<"Value of key a in cache: "<<response<<endl;
	else
	cout<<"Key: a  Not present"<<endl;
	c->printlist();
	c->set(3,"c");
	c->printlist();

	if(c->get(3,response))
		cout<<"Value of key b in cache: "<<response<<endl;
	else
	cout<<"Key b Not present"<<endl;
	c->remove(3);
	c->printlist();
	cout<<"Capacity: "<<c->capacity()<<"\n";

}
