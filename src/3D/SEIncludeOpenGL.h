
#if (TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE)

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#else

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#endif