/*
 * RendererES2.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: Nishry
 */

#include "RendererES2.h"
#include <GLES3/gl3.h>

RendererES2::RendererES2()
{
	m_EglContext = NULL;
}

RendererES2::~RendererES2()
{

}

RendererES2::ContextState RendererES2::OnContextCreated()
{
	RendererES2::ContextState eState = Initialised;;

	EGLContext eglContext = eglGetCurrentContext();
	if ( m_EglContext != NULL && m_EglContext != eglContext )
	{
		// You will need to recreate your resources here
		// This means textures, buffers, shader programs, etc...
		eState = RendererES2::Restored;
	}

	else
	{
		eState = RendererES2::Initialised;
	}

	m_EglContext = eglContext;

	return eState;
}

void RendererES2::SetViewport( int iWidth, int iHeight )
{
	glViewport( 0, 0, iWidth, iHeight );
}

void RendererES2::ClearScreen( float fRed, float fGreen, float fBlue, float fAlpha /*= 0.0f*/, bool bClearDepth /*= true*/ )
{
	GLbitfield mask = ( bClearDepth ) ? ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) : GL_COLOR_BUFFER_BIT;
	glClearColor( fRed, fGreen, fBlue, fAlpha );
	glClear( mask );
}
