//
// Created by william on 2020-02-25.
//
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

AAssetManager *sAssertManager = nullptr;
extern "C" JNIEXPORT void JNICALL
Java_com_example_opengles_android_Native_initAssertManager(
        JNIEnv *env,
        jobject /* this */,
        jobject assetManager) {
    sAssertManager = AAssetManager_fromJava(env, assetManager);
}

extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_android_Native_onSurfaceCreated(
        JNIEnv *env,
        jobject /* this */) {
    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
}


extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_android_Native_onSurfaceChanged(
        JNIEnv *env,
        jobject /* this */,
        jfloat width,
        jfloat height) {
    glViewport(0.0f, 0.0f, width, height);
}

extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_android_Native_onDrawFrame(
        JNIEnv *env,
        jobject /* this */) {
    glClear(GL_COLOR_BUFFER_BIT);
}