//
// Created by william on 2020-02-25.
//
#include "Base.h"
#include "Scene.h"
#include "Utils.h"

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

