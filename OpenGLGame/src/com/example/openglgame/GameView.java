package com.example.openglgame;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.example.openglgame.JNILib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

public class GameView extends GLSurfaceView 
{
	private static class Renderer implements GLSurfaceView.Renderer 
    {
        public void onDrawFrame( GL10 gl ) 
        {
        	JNILib.OnFrame();
        }

        public void onSurfaceChanged( GL10 gl, int iWidth, int iHeight ) 
        {
        	JNILib.OnResize( iWidth, iHeight );
        }

        public void onSurfaceCreated( GL10 gl, EGLConfig config ) 
        {
        	JNILib.OnInit();
        }
    }
	
    public GameView( Context context ) 
    {
        super( context );
        
        // Pick an EGLConfig with RGBA8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 2.0 or later backwards-compatible versions.
        setEGLConfigChooser( 8, 8, 8, 8, 16, 0 );
        setEGLContextClientVersion( 2 );
        setRenderer( new Renderer() );
    }
    
    public void onDestroy()
    {	
    	// Send the event to the renderer thread
    	queueEvent( new Runnable() 
    	{
            @Override
            public void run() 
            {
            	JNILib.OnShutdown();
            }
        });
    }

    public void onResume()
    {
    	super.onResume();
    	
    	// Send the event to the renderer thread
    	queueEvent( new Runnable() 
    	{
            @Override
            public void run() 
            {
            	JNILib.OnResume();
            }
        });
    }
    
    public void onPause()
    {
    	// Send the event to the renderer thread
    	queueEvent( new Runnable() 
    	{
            @Override
            public void run() 
            {
            	JNILib.OnPause();
            }
        });
    	
    	super.onPause();
    }
    
    @Override
    public boolean onTouchEvent( MotionEvent event ) 
    {
    	// Implement Runnable for MotionEvent parameter
    	class MotionEventRunnable implements Runnable
    	{
    		private MotionEvent mEvent;
    		public MotionEventRunnable( MotionEvent event ) { mEvent = event; }
    		
			@Override
			public void run() 
			{
				// Get the number of pointers to iterate
				int iNumPointers = mEvent.getPointerCount();
		    	for ( int i = 0; i < iNumPointers; ++i )
		    	{
		    		// Get the pointer ID and index
		    		int iPointerID = mEvent.getPointerId( i );
		    		int iPointerIndex = mEvent.findPointerIndex( iPointerID );
		    		
		    		// Get the xy position and action
		    		float x = mEvent.getX( iPointerIndex );
		            float y = mEvent.getY( iPointerIndex );
		            
		            int iAction = mEvent.getActionMasked();
		            
		            // Send to C++
		            JNILib.OnTouch( iPointerID, x, y, iAction );
		    	}				
			}
    	}
    	
    	// Send the event to the renderer thread
    	queueEvent( new MotionEventRunnable( event ) );
    	
    	return true;
    }
}
