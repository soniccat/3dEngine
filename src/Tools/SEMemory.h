
#ifndef SESharedAllocator_H
#define SESharedAllocator_H

#include "SEAllocator.h"

template<typename T>
T* SENewObject()
{
	return new T;

	//void* mem = malloc(sizeof(T));
	//return new(mem)T;
}

template<typename T, typename ARG1>
T* SENewObject( ARG1 arg1)
{
	return new T(arg1);

	//void* mem = malloc(sizeof(T));
	//return new(mem)T(arg1);
}

template<typename T, typename ARG1, typename ARG2>
T* SENewObject( ARG1 arg1, ARG2 arg2)
{
	return new T(arg1, arg2);

	//void* mem = malloc(sizeof(T));
	//return new(mem)T(arg1, arg2);
}

template<typename T, typename ARG1, typename ARG2, typename ARG3>
T* SENewObject( ARG1 arg1, ARG2 arg2, ARG3 arg3)
{
	return new T(arg1, arg2, arg3);

	//void* mem = malloc(sizeof(T));
	//return new(mem)T(arg1, arg2, arg3);
}

template<typename T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
T* SENewObject( ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
{
	return new T(arg1, arg2, arg3, arg4);

	//void* mem = malloc(sizeof(T));
	//return new(mem)T(arg1, arg2, arg3, arg4);
}

template<typename T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
T* SENewObject( ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
{
	return new T(arg1, arg2, arg3, arg4, arg5);

	//void* mem = malloc(sizeof(T));
	//return new(mem)T(arg1, arg2, arg3, arg4, arg5);
}

template<typename T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
T* SENewObject( ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6)
{
	return new T(arg1, arg2, arg3, arg4, arg5, arg6);

	//void* mem = malloc(sizeof(T));
	//return new(mem)T(arg1, arg2, arg3, arg4, arg5, arg6);
}

template<typename T>
T* SENewArray( size_t itemCount )
{
	return new T[itemCount];

	//T* arr = (T*)calloc( itemCount, sizeof(T) );
	//return new(arr) T[itemCount];
}


template<typename T>
void SEDeleteObject(T* p)
{
	delete p;
}

template<typename T>
void SEDeleteArray(T* p)
{
	delete[] p;
}



/*
class SESharedAllocator
{
	static SESharedAllocatorPtr mAllocator;

	SESharedAllocator(void);

public:
	~SESharedAllocator(void);

	static SESharedAllocatorPtr allocator();

	template<typename T>
	static T* NewObject(  )
	{
		void* mem = SESharedAllocator::allocator()->
	}

	template<typename T, typename A>
	static T* NewObject( A arg );
};

*/

#endif SESharedAllocator_H