
#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEIncludeOpenGL.h"

bool streq(const sechar *s1, const sechar *s2)
{
	for (;;) 
	{
		if( *(s1++)!=*(s2++) )
			return 0;
		
		if( *s1 == 0 && *s2 == 0 )
			return 1;
		
		if( *s1 == 0 || *s2 == 0 )
			return 0;
	}
}

void SELoadDefaultOpenGLSettings()
{
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_TEXTURE_2D);

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
}