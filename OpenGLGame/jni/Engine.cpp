#include "Engine.h"

extern "C"
{
    JNIEXPORT void JNICALL Native_OnInit( JNIEnv* env, jobject obj );
    JNIEXPORT void JNICALL Native_OnShutdown( JNIEnv* env, jobject obj );
    JNIEXPORT void JNICALL Native_OnResize( JNIEnv* env, jobject obj, jint iWidth, jint iHeight );
    JNIEXPORT void JNICALL Native_OnFrame( JNIEnv* env, jobject obj );
    JNIEXPORT void JNICALL Native_OnTouch( JNIEnv* env, jobject obj, int iPointerID, float fPosX, float fPosY, int iAction );

    JNIEXPORT void JNICALL Native_OnPause( JNIEnv* env, jobject obj );
    JNIEXPORT void JNICALL Native_OnResume( JNIEnv* env, jobject obj );
};

static Application* s_pApplication = NULL;

JNIEXPORT void JNICALL Native_OnInit( JNIEnv* env, jobject obj )
{
	LOGV( "Init called." );
	if ( !s_pApplication )
	{
		s_pApplication = new Application();
	}

	s_pApplication->OnContextCreated();
}

JNIEXPORT void JNICALL Native_OnShutdown( JNIEnv* env, jobject obj )
{
	if ( s_pApplication )
	{
		delete s_pApplication;
		s_pApplication = NULL;
	}
}

JNIEXPORT void JNICALL Native_OnResize( JNIEnv* env, jobject obj, jint iWidth, jint iHeight )
{
	s_pApplication->OnWindowResize( iWidth, iHeight );
}

JNIEXPORT void JNICALL Native_OnFrame( JNIEnv* env, jobject obj )
{
	s_pApplication->Step();
}

JNIEXPORT void JNICALL Native_OnTouch( JNIEnv* env, jobject obj, int iPointerID, float fPosX, float fPosY, int iAction )
{
	LOGV( "Touch: %i, x: %f y:, %f action:, %i.", iPointerID, fPosX, fPosY, iAction );
	if ( s_pApplication )
	{
		s_pApplication->OnTouch( iPointerID, fPosX, fPosY, iAction );
	}
}

JNIEXPORT void JNICALL Native_OnPause( JNIEnv* env, jobject obj )
{
	if ( s_pApplication )
	{
		s_pApplication->OnPause();
	}
}

JNIEXPORT void JNICALL Native_OnResume( JNIEnv* env, jobject obj )
{
	if ( s_pApplication )
	{
		s_pApplication->OnResume();
	}
}

static const JNINativeMethod g_NativeMethods[] =
{

    { "OnInit", "()V", (void*)Native_OnInit },
    { "OnShutdown", "()V", (void*)Native_OnShutdown },
    { "OnResize", "(II)V", (void*)Native_OnResize },
    { "OnFrame", "()V", (void*)Native_OnFrame },
    { "OnTouch", "(IFFI)V", (void*)Native_OnTouch },
    { "OnPause", "()V", (void*)Native_OnPause },
    { "OnResume", "()V", (void*)Native_OnResume },
};

#define NELEM( x ) ( (int) ( sizeof(x) / sizeof( (x) [0] ) ) )
jint JNI_OnLoad( JavaVM* pJavaVM, void* pReserved )
{
    JNIEnv* pEnv;
    if ( pJavaVM->GetEnv(reinterpret_cast<void**>( &pEnv ), JNI_VERSION_1_6) != JNI_OK )
    {
        return -1;
    }

    // Get jclass with pEnv->FindClass.
    // Register methods with pEnv->RegisterNatives.
    jclass javaLibClass = pEnv->FindClass( "com/example/openglgame/JNILib" );
    pEnv->RegisterNatives( javaLibClass, g_NativeMethods, NELEM( g_NativeMethods ) );

    LOGV( "Engine library successfully loaded." );

    return JNI_VERSION_1_6;
}
