
#ifndef SETools_H
#define SETools_H

#include "SETools.h"
#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEIncludeOpenGL.h"



//function check the strings for equal
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

btVector3 getRayTo( const SECameraPtr camera, float glutScreenWidth, float glutScreenHeight, int x,int y)
{
	/*
	if (m_ortho)
	{
		btScalar aspect;
		btVector3 extents;
		if (m_glutScreenWidth > m_glutScreenHeight) 
		{
			aspect = m_glutScreenWidth / (btScalar)m_glutScreenHeight;
			extents.setValue(aspect * 1.0f, 1.0f,0);
		} else 
		{
			aspect = m_glutScreenHeight / (btScalar)m_glutScreenWidth;
			extents.setValue(1.0f, aspect*1.f,0);
		}
		
		extents *= m_cameraDistance;
		btVector3 lower = m_cameraTargetPosition - extents;
		btVector3 upper = m_cameraTargetPosition + extents;

		btScalar u = x / btScalar(m_glutScreenWidth);
		btScalar v = (m_glutScreenHeight - y) / btScalar(m_glutScreenHeight);
		
		btVector3	p(0,0,0);
		p.setValue((1.0f - u) * lower.getX() + u * upper.getX(),(1.0f - v) * lower.getY() + v * upper.getY(),m_cameraTargetPosition.getZ());
		return p;
	}*/

	float top = 1.f;
	float bottom = -1.f;
	float nearPlane = 1.f;
	float tanFov = (top-bottom)*0.5f / nearPlane;
	float fov = 2.0 * atanf (tanFov);

	btVector3 rayFrom = camera->position();
	btVector3 rayForward = (camera->seePoint()-camera->position());
	rayForward.normalize();
	float farPlane = 10000.f;
	rayForward*= farPlane;

	btVector3 rightOffset;
	btVector3 vertical = camera->upVector();

	btVector3 hor;
	hor = rayForward.cross(vertical);
	hor.normalize();
	vertical = hor.cross(rayForward);
	vertical.normalize();

	float tanfov = tanf(0.5f*fov);


	hor *= 2.f * farPlane * tanfov;
	vertical *= 2.f * farPlane * tanfov;

	btScalar aspect;
	
	if (glutScreenWidth > glutScreenHeight) 
	{
		aspect = glutScreenWidth / (btScalar)glutScreenHeight;
		
		hor*=aspect;
	} else 
	{
		aspect = glutScreenHeight / (btScalar)glutScreenWidth;
		vertical*=aspect;
	}


	btVector3 rayToCenter = rayFrom + rayForward;
	btVector3 dHor = hor * 1.f/float(glutScreenWidth);
	btVector3 dVert = vertical * 1.f/float(glutScreenHeight);


	btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * vertical;
	rayTo += x * dHor;
	rayTo -= y * dVert;
	return rayTo;
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


#endif SETools_H