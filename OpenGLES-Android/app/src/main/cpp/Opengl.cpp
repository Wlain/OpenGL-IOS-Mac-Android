//
// Created by william on 2020-02-25.
//
#include "Common/Base.h"
#include "GL/Scene.h"
#include "Common/Utils.h"
#include <sys/time.h>

AAssetManager *sAssertManager = nullptr;
unsigned char* LoadFileContent(const char *filePath, int &fileSize) {
    unsigned char *fileContent = nullptr;
    fileSize = 0;
    AAsset *asset = AAssetManager_open(sAssertManager, filePath, AASSET_MODE_UNKNOWN);
    if (asset == nullptr) {
        return nullptr;
    }
    fileSize = AAsset_getLength(asset);
    fileContent = new unsigned char[fileSize];
    AAsset_read(asset, fileContent, fileSize);
    fileContent[fileSize] = '\0';
    AAsset_close(asset);
    return fileContent;
}

float GetFrameTime() {
    static double lastTime = 0;
    static double currentTime = 0;
    struct timeval t;
    gettimeofday(&t, NULL);
    currentTime = t.tv_sec + t.tv_usec * 1e-6;;
    double frameTime = lastTime == 0 ? 0 : currentTime - lastTime;
    lastTime = currentTime;
    return frameTime;
}

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

