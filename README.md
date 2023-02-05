# In-Memory Cache
The module provides a very lightweight fast in memory caching library as a template which can be used efficiently with applications to cache data and speed up the process of retreival of data. The caching library is written in C++ and is compaible with modern C++ processors. The cache behaves like a doubly linked list which provides for very fast and lightweight operations like retireival and insertion of data in constant time. Appropriate data structures like hash map has been used to enable optimal operations to the cache.


Initally the module has support for few eviction strategies followed by the cache like Least Recently Used(LRU), First  In First Out(FIFO) and Last in First Out(LIFO).
One of the most important features of this library is easy extensibility of the code to add new features and eviction policies. There is a header file named "base_cache.hpp" in the include folder that is an abstract class. It serves as a gateway to interact with the cache as a list and provides the users with several tools to implement their own eviction policy.

The basic operations performed by all types of cache include:- 
- set(Key,Value) :- This functionality sets a Value corresponsing to a key in the cache for fast retreival
- bool get(Key,&Value):- This functionality checks for the existence of a key in the cache and gets its value if found
- remove(Key):- This functionality removes a key from the cache
- bool contains(Key):- This functionality checks for the existence of a key in the hashmap 

To implement a new eviction policy,one must inherit the abstract **class Cache** which contains pure virtual functions like get(),set(),remove()
Any other policy written must be thoroughly tested with the help of uni tests. We have used GoogleTest 's gtest library to write unit tests for our library. For sample tests and more details about unit tests check the "test" folder.

One of the major requirements of the library was thread safety which has been acheived with the help of mutex and shared mutexes which allow only **"only one write,multiple concurrent reads"**. While implementing a new eviction policy it is important to make sure the program remains thread safe.

Sample implementation in a third party file can be found in the "sample" folder.


