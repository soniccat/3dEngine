
#ifndef NULL
#define NULL 0
#endif

#define SEAssert(a,str) if(!(a)){ printf(str);printf("\n");assert(false); }
#define SEGLAssert if( glGetError() != 0 ) { printf("OpenGL error %d", glGetError()); assert(false); }
#define TRACE( a ) { printf(a); printf("\n"); }

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#define BREAKPOINTPLACE {int i=0;++i;}


#define PATH_DELIMETER '/'
#define EPATH_MAX_LENGHT 256+1
typedef char sechar;

typedef unsigned int uint;
typedef basic_string<sechar, char_traits<sechar> , SEAllocator<sechar> > SEString;
typedef shared_ptr<SEString> SEStringPtr;
typedef vector<SEString,SEAllocator<SEString>> SEStringArray;

typedef shared_array<SEString> SEStringNativeArray;
