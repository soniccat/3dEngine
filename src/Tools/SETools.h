
#include "SECamera.h"


bool streq(const sechar *s1, const sechar *s2);

void SELoadDefaultOpenGLSettings();

btVector3 getRayTo( const SECameraPtr camera, float glutScreenWidth, float glutScreenHeight, int x,int y);
