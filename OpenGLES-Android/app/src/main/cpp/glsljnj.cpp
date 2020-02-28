//
// Created by william on 2020-02-25.
//
#include "Common/Base.h"
#include "GL/Scene.h"
#include "Common/Utils.h"
#include <sys/time.h>
#include "stb_image.h"

AAssetManager *sAssertManager = nullptr;
unsigned char* LoadFileContent(const char *filePath, int &fileSize) {
    assert(filePath);
    unsigned char *fileContent = nullptr;
    fileSize = 0;
    AAsset *asset = AAssetManager_open(sAssertManager, filePath, AASSET_MODE_UNKNOWN);
    if (asset == nullptr) {
        assert(false);
        return nullptr;
    }
    fileSize = AAsset_getLength(asset);
    fileContent = new unsigned char[fileSize];
    AAsset_read(asset, fileContent, fileSize);
    fileContent[fileSize] = '\0';
    AAsset_close(asset);
    return fileContent;
}

GLuint CreateTextureFromFile(const char *filePath, bool flipVertical) {
    GLuint texture = 0;
    assert(filePath);
    int width, height, channelsInFile;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (texture == GL_INVALID_VALUE) {
        assert(false);
        return texture;
    }
    int fileSize = 0;
    unsigned char *textureContent = LoadFileContent(filePath, fileSize);
    stbi_set_flip_vertically_on_load(flipVertical);
    unsigned char *data = stbi_load_from_memory(textureContent, fileSize, &width, &height, &channelsInFile, 0);
    SAFE_DELETE_ARRAY(textureContent);
    if (data != nullptr) {
        GLenum format = 0;
        if (channelsInFile == 1) {
            format = GL_RED_BITS;
        } else if (channelsInFile == 3) {
            format = GL_RGB;
        } else if (channelsInFile == 4) {
            format = GL_RGBA;
        }
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    } else {
        assert(false);
        return texture;
    }
    return texture;
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

