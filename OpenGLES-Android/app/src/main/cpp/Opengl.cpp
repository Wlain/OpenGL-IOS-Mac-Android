//
// Created by william on 2020-02-25.
//
#include "Base.h"
#include "Scene.h"

AAssetManager *sAssertManager = nullptr;
extern "C" JNIEXPORT void JNICALL
Java_com_example_opengles_1android_Native_initAssertManager(
        JNIEnv *env,
        jclass /* this */,
        jobject assetManager) {
    sAssertManager = AAssetManager_fromJava(env, assetManager);
}

extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_1android_Native_onSurfaceCreated(
        JNIEnv *env,
        jclass /* this */) {
    Initialize();
}


extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_1android_Native_onSurfaceChanged(
        JNIEnv *env,
        jclass /* this */,
        jfloat width,
        jfloat height) {
    SetViewPortSize(width, height);
}

extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_1android_Native_onDrawFrame(
        JNIEnv *env,
        jclass /* this */) {
    Draw();
}

