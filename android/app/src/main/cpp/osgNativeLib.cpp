
/*
This file is part of OpenSceneGraph cross-platform guide:
  https://github.com/OGStudio/openscenegraph-cross-platform-guide

Copyright (C) 2017 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

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

