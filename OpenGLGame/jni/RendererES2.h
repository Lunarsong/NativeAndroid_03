/*
 * RendererES2.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Nishry
 */

#ifndef RENDERERES2_H_
#define RENDERERES2_H_

#include <EGL/egl.h>

class RendererES2
{
public:
	enum ContextState
	{
		Initialised = 0,
		Invalid,
		Restored,

		RenderStateCount
	};

	RendererES2();
	~RendererES2();

	ContextState OnContextCreated();
	void SetViewport( int iWidth, int iHeight );

	void ClearScreen( float fRed, float fGreen, float fBlue, float fAlpha = 0.0f, bool bClearDepth = true );

private:
	EGLContext m_EglContext;
};

#endif /* RENDERERES2_H_ */
