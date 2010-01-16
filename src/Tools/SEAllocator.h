
#ifndef SEAllocator_H
#define SEAllocator_H

#include <iostream>

template <class T>
class SEAllocator
{
public:
  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;
  typedef T*        pointer;
  typedef const T*  const_pointer;
  typedef T&        reference;
  typedef const T&  const_reference;
  typedef T         value_type;

  SEAllocator() {}
  SEAllocator(const SEAllocator&) {}



  pointer   allocate(size_type n, const void * = 0) {
              T* t = (T*) malloc(n * sizeof(T));
              //std::cout
              //<< "  used SEAllocator to allocate   at address "
              //<< t << " (+)" << std::endl;
              return t;
            }
  
  void      deallocate(void* p, size_type) {
              if (p) {
                free(p);
                //std::cout
                //<< "  used SEAllocator to deallocate at address "
                //<< p << " (-)" << 
                //std::endl;
              } 
            }

  pointer           address(reference x) const { return &x; }
  const_pointer     address(const_reference x) const { return &x; }
  SEAllocator<T>&  operator=(const SEAllocator&) { return *this; }
  
  void              construct(pointer p, const T& val) 
                    { 
						new ((T*) p) T(val); 
  }
  void              destroy(pointer p) { p->~T(); }
  

  size_type         max_size() const { return size_t(-1); }

  template <class U>
  struct rebind { typedef SEAllocator<U> other; };

  template <class U>
  SEAllocator(const SEAllocator<U>&) {}

  template <class U>
  SEAllocator& operator=(const SEAllocator<U>&) { return *this; }
};

//basic_string.h:213: error: no match for 'operator==' in '__alloc1 == __alloc2

//operators ( ==, != ) added to resolve iPhone compiler error:
template<typename _T1, typename _T2>
inline bool
operator==(const SEAllocator<_T1>&, const SEAllocator<_T2>&)
{ return true; }

template<typename _T1, typename _T2>
inline bool
operator!=(const SEAllocator<_T1>&, const SEAllocator<_T2>&)
{ return false; }


#endif SEAllocator_H