//
//  ifDynamicArray.h
//  iFighter
//
//  Created by System Administrator on 5/7/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

//#import <Foundation/Foundation.h>
//#import "Box2D.h"
#import "b2BlockAllocator.h"

//аналог класса vector
template< typename T , int SA=10, int NA=10 >
class ifDynamicArray 
{
	const static size_t startAlloc = sizeof(T)*SA;
	const static size_t nextAlloc  = sizeof(T)*NA;
	
	size_t  m_elementCount;
	size_t  m_arraySize;
	T*		m_array;
	b2BlockAllocator* m_allocator;
	
public:
	
	ifDynamicArray()
	{
	}
	
	ifDynamicArray( b2BlockAllocator* _allocator )
	{
		Init(_allocator);
	}
	
	~ifDynamicArray()
	{
		m_allocator->Free(m_array, m_arraySize);
	}
	
	void Init(b2BlockAllocator* _allocator)
	{
		m_allocator = _allocator;
		m_arraySize = startAlloc;
		//printf("alloc size =  %d",startAlloc);
		
		m_elementCount = 0;
		
		if( _allocator )
			m_array = (T*) m_allocator->Allocate(m_arraySize);
	}
	
	void Realloc( size_t newSize )
	{
		b2Assert( m_allocator );
		
		T* buffer = (T*) m_allocator->Allocate(newSize);
		memset(buffer, 0, newSize);
		memcpy(buffer, m_array, m_arraySize );
		
		m_allocator->Free(m_array, m_arraySize);
		m_array = buffer;
		
		m_arraySize = newSize;
		
		printf("realloc = %d\r\n",newSize);
	}
	
	void Add(T obj)
	{
		if( m_elementCount == m_arraySize/sizeof(T))
			Realloc(m_arraySize + nextAlloc);
		
		m_array[m_elementCount] = obj;
		++m_elementCount;
	}
	
	void Remove(T obj)
	{
		int i=0;
		for( ; i<m_elementCount; ++i )
			if( m_array[i] == obj )
				break;
		
		if(i == m_elementCount)
			return;
		
		for( int g = i; g<m_elementCount-1; ++g )
			m_array[g]=m_array[g+1];
		
		m_elementCount--;
	}
	
	void RemoveAt(NSUInteger i)
	{
		if( m_elementCount == 0 || i >= m_elementCount )
			return;
		
		for( int g = i; g<m_elementCount-1; ++g )
			m_array[g]=m_array[g+1];
		
		m_elementCount--;
	}
	
	int GetIndex(T obj)
	{
		for( int i=0 ; i<m_elementCount; ++i )
			if( m_array[i] == obj )
				return i;
		
		return -1;
	}
	
	void Clear()
	{
		memset( m_array, 0, m_arraySize );
		m_elementCount = 0;
	}
	
	size_t Count()
	{
		return m_elementCount;
	}
	
	T& operator[] (int i)
	{
		return m_array[i];
	}
};
