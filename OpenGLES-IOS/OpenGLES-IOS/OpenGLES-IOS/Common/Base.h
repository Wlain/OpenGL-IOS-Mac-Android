//
//  Base.h
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Base_h
#define Base_h
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "glm.hpp"
#include "ext.hpp"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <map>
#include <cassert>
#include <sys/time.h>

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

#define MATH_TOLERANCE              2e-37f
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_PI                     3.14159265


#endif /* Base_h */
