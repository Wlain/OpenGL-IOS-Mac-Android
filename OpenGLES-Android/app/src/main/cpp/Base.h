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


#define MATH_TOLERANCE              2e-37f
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_PI                     3.14159265

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error;error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}


#endif //BASE_H
