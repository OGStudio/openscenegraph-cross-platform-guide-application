
#include "main.h"

#include <jni.h>
#include <string>

// Shortcuts for JNI functions.
#define OSG_JNI(FUNC_NAME) \
    JNIEXPORT void JNICALL Java_org_opengamestudio_osgapp_osgNativeLib_ ## FUNC_NAME
#define OSG_JNI_ARG \
    JNIEnv *env, jobject /* this */

// Mouse (pointer) speed multiplier.
const float MOUSE_MOTION_FACTOR = 0.01;

// Create application instance.
Application app;

extern "C" {

// Initialization.
OSG_JNI(init)(OSG_JNI_ARG, jint width, jint height)
{
    app.setupWindow(width, height);
}

// Rendering.
OSG_JNI(step)(OSG_JNI_ARG)
{
    app.frame();
}

// Resources.
OSG_JNI(loadModel)(OSG_JNI_ARG, jstring path)
{
    const char *cpath = env->GetStringUTFChars(path, JNI_FALSE);
    app.loadScene(cpath);
    env->ReleaseStringUTFChars(path, cpath);
}

// Input.
OSG_JNI(moveMouse)(OSG_JNI_ARG, jfloat x, jfloat y)
{
    app.moveMouse(x * MOUSE_MOTION_FACTOR, y * MOUSE_MOTION_FACTOR);
}

OSG_JNI(pressMouse)(OSG_JNI_ARG, jboolean down, jfloat x, jfloat y)
{
    app.pressMouse(down == JNI_TRUE, x * MOUSE_MOTION_FACTOR, y * MOUSE_MOTION_FACTOR);
}

} // extern "C"

