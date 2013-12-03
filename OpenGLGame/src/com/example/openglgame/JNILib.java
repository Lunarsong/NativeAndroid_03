package com.example.openglgame;

public class JNILib 
{
    static 
    {
        System.loadLibrary( "Engine" );
    }

    public static native void OnInit();
    public static native void OnResize( int iWidth, int iHeight );
    public static native void OnFrame();
    public static native void OnShutdown();
    
    public static native void OnTouch( int iPointerID, float fPosX, float fPosY, int iAction );
    
    public static native void OnPause();
    public static native void OnResume();
}

