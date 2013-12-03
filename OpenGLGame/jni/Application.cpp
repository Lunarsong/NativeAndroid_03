/*
 * Application.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: Nishry
 */

#include <time.h>
#include <assert.h>
#include "Application.h"

Application* Application::s_pApplication = NULL;

Application::Application()
{
	s_pApplication = this;

	m_bPaused = false;

	// Set the current time
	timespec timeNow;
	clock_gettime( CLOCK_MONOTONIC, &timeNow );
	m_Time = timeNow.tv_sec * 1000000000ull + timeNow.tv_nsec;

	// Create the renderer
	m_pRenderer = new RendererES2();
}

Application::~Application()
{
	s_pApplication = NULL;

	if ( m_pRenderer )
	{
		delete m_pRenderer;
	}
}

Application& Application::Get()
{
	assert( s_pApplication && "Application not created!" );
	return *s_pApplication;
}

void Application::OnContextCreated()
{
	if ( m_pRenderer->OnContextCreated() == RendererES2::Restored )
	{
		// The surface was re-created which means all
		// of the OpenGL resources were deleted.
		// You will need to recreate your resources here
		// This means textures, buffers, shader programs, etc...

	}
}

void Application::OnWindowResize( int iWidth, int iHeight )
{
	// Our window changed its size

	// Set the new viewport
	m_pRenderer->SetViewport( iWidth, iHeight );

	// Fix UI, camera, etc...

}

void Application::Step()
{
	// Get an accurate delta time
	timespec timeNow;
	clock_gettime( CLOCK_MONOTONIC, &timeNow );
	uint64_t uNowNano = timeNow.tv_sec * 1000000000ull + timeNow.tv_nsec;

	float fDeltaSeconds = float( uNowNano - m_Time ) * 0.000000001f; // 1 second = 1,000,000,000 nanoseconds
	m_Time = uNowNano;

	if ( !m_bPaused )
	{
		// Update logic
		OnUpdate( fDeltaSeconds );

		// Draw
		OnDraw();
	}
}

void Application::OnUpdate( const float fDeltaSeconds )
{
	// Do game logic here
}

void Application::OnDraw()
{
	m_pRenderer->ClearScreen( 1.0f, 0.0f, 0.0f, 0.0f, true );
}

void Application::OnPause()
{
	m_bPaused = true;
}

void Application::OnResume()
{
	m_bPaused = false;
}

void Application::OnTouch( int iPointerID, float fPosX, float fPosY, int iAction )
{
	// Input! Let's do something...
}
