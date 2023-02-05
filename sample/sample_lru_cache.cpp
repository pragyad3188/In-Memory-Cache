#include <iostream>
#include <string>
#include "in_memory_cache.h"

using namespace std;
int main()
{

	cout<<"TESTING LRU CACHE 1\n\n";
	LruCache<string,int>* c=new LruCache<string,int>(2);
	cout<<"Capacity:- "<<c->capacity()<<"\n";
	cout<<"Size:- "<<c->size()<<"\n";
	c->printlist();
	c->set("a",1);
	c->printlist();
	cout<<"Size:- "<<c->size()<<"\n";
	c->set("b",2);
	c->printlist();
	cout<<"Size:- "<<c->size()<<"\n";

	int response;
	if(c->get("a",response))
		cout<<"Value of key a in cache: "<<response<<endl;
	else
	cout<<"Key: a  Not present"<<endl;
	c->printlist();
	c->set("c",3);
	c->printlist();

	if(c->get("b",response))
		cout<<"Value of key b in cache: "<<response<<endl;
	else
	cout<<"Key b Not present"<<endl;
	c->remove("c");
	c->printlist();
	cout<<"Capacity: "<<c->capacity()<<"\n";


	cout<<"\n\nTESTING LRU CACHE 2\n\n";
	LruCache<string,string>* d=new LruCache<string,string>(2);
	cout<<"Capacity: "<<d->capacity()<<"\n";
	cout<<"Size:- "<<d->size()<<"\n";
	d->printlist();
	d->set("a","1");
	d->printlist();
	cout<<"Size:- "<<d->size()<<"\n";
	d->set("b","2");
	d->printlist();
	cout<<"Size:- "<<d->size()<<"\n";
	string res;
	if(d->get("a",res))
	{
		cout<<"Value of key a returned: "<<res<<endl;
	}
	else
		cout<<"Key:-a not found\n";
	d->printlist();
	d->set("c","3");
	d->printlist();

	if(d->get("b",res)){
		cout<<"Value of key returned: "<<res<<endl;
	}
	else
		cout<<"Key not found\n";
	
	d->remove("c");
	d->printlist();
	cout<<"Capacity:- "<<d->capacity()<<"\n";
}
