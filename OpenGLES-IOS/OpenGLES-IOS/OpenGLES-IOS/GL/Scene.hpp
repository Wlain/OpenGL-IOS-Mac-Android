//
//  Scene.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp
#include "Base.h"

///
//  Macros
//
#ifdef WIN32
#define ESSCENE_API  __cdecl
#define ESCALLBACK  __cdecl
#else
#define ESSCENE_API
#define ESCALLBACK
#endif

typedef struct ESContext ESContest;
struct ESContext {
    void   *platformData;
    void   *userData;
    // Window width
    GLint  width;
    // Widow height
    GLuint height;
    // Callbacks
    void (ESCALLBACK *initFunc)(ESContext *);
    void (ESCALLBACK *resizeFunc)(ESContext *);
    void (ESCALLBACK *drawFunc)(ESContext *);
    void (ESCALLBACK *keyFunc)(ESContext *, unsigned char, int, int);
    void (ESCALLBACK *updateFunc)(ESContext *, float deltaTime);
    void (ESCALLBACK *finalizeFunc)(ESContext *);
};


/// 创建一个窗口
/// @param esContext 平台上下文
/// @param title 窗口名
/// @param width 窗口的宽
/// @param height 窗口的高
GLboolean ESSCENE_API esCreateWindow(ESContext *esContext, const char *title, GLint width, GLuint height);


/// 注册一个init方法的回调
/// @param esContext 平台上下文
/// @param initFunc draw回调函数地址
void ESSCENE_API esResigerInitFunc(ESContext *esContext, void(ESCALLBACK *initFunc)(ESContext *));

/// 注册一个resize方法的回调
/// @param esContext 平台上下文
/// @param resizeFunc draw回调函数地址
void ESSCENE_API esSetViewPortFuncResizeFunc(ESContext *esContext, void(ESCALLBACK *resizeFunc)(ESContext *));

/// 注册一个draw方法的回调
/// @param esContext 平台上下文
/// @param drawFunc draw回调函数地址
void ESSCENE_API esResigerDrawFunc(ESContext *esContext, void(ESCALLBACK *drawFunc)(ESContext *));

/// 注册一个update方法的回调
/// @param esContext 平台上下文
/// @param updateFunc update回调函数地址
void ESSCENE_API esResigerUpdateFunc(ESContext *esContext, void(ESCALLBACK *updateFunc)(ESContext *, float deltaTime));


/// 注册一个键盘输入处理方法的回调
/// @param esContext 平台上下文
/// @param keyFunc key回调函数地址
void ESSCENE_API esResigerKeyFunc(ESContext *esContext, void(ESCALLBACK *keyFunc)(ESContext *,unsigned char, int, int));


/// 注册一个shutdown方法的回调
/// @param esContext 平台上下文
/// @param finalizeFunc shutdown回调函数地址
void ESSCENE_API esRegisterFinalizeFunc( ESContext *esContext, void(ESCALLBACK *finalizeFunc)(ESContext *));


/// 平台日志打印
/// @param formatStr 日志的格式
void ESSCENE_API esLogMessage(const char *formatStr, ...);

void Initialize(ESContext *esContext);
void Resize(ESContext *esContext, GLint width, GLint height);
void Draw(ESContext *esContext);
void Key(ESContext *esContext);
void Update(ESContext *esContext, GLfloat deltaTime);
void Finalize(ESContext *esContext);


#endif /* Scene_hpp */
