//
// Created by william on 2020-02-26.
//

#ifndef Base_h
#define Base_h

#include <jni.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "gl3stub.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include "glm.hpp"
#include "ext.hpp"
#include "android_debug.h"

// 安全释放文件
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if (x) delete (x); (x) = NULL; }    //定义安全释放函数
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) { if (x) delete [] (x); (x) = NULL; }    //定义安全释放函数
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL;}
#endif

// GL_CHECK
#define GL_CHECK() \
{ \
GLenum glError = glGetError(); \
if (glError != GL_NO_ERROR) {\
LOGI("glGetError() = %i (0x%.8x) in filename = %s, line  = %i\n", glError, glError, __FILE__ , __LINE__); \
} \
}

static void printGlString(const char* name, GLenum s) {
    const char* v = (const char*)glGetString(s);
    LOGI("GL %s: %s\n", name, v);
}



#define MATH_TOLERANCE              2e-37f
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_PI                     3.14159265


#endif //BASE_H
