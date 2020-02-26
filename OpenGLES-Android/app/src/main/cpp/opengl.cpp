//
// Created by william on 2020-02-25.
//
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm.hpp>
#include <ext.hpp>
#include <stb_image.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

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
    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
}


extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_1android_Native_onSurfaceChanged(
        JNIEnv *env,
        jclass /* this */,
        jfloat width,
        jfloat height) {
    glViewport(0.0f, 0.0f, width, height);
    glm::mat4 modelMatrix;
}

extern  "C" JNIEXPORT void JNICALL
Java_com_example_opengles_1android_Native_onDrawFrame(
        JNIEnv *env,
        jclass /* this */) {
    glClear(GL_COLOR_BUFFER_BIT);
}