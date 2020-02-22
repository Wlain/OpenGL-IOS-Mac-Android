//
//  Utils.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include "Base.h"

/**
 根据图片文件创建纹理

 @param path 图片文件路径
 @return 纹理ID
 */
GLuint TextureFromFile(const char *path, bool flipVertical);

/**
 创建显示列表

 @param foo draw方法指针
 @return 显示列表
 */
GLuint CreateDisplayList(std::function<void()>foo);


/**
 加载文件内容

 @param filePath 文件路径
 @param filesize 文件size
 @return 文件内容
 */

GLubyte * LoadFileContent(const char *filePath, int &filesize);

/**
 获取帧间隔时间

 @return 帧间隔时间
 */
float GetFrameTime();

#endif /* Utils_hpp */
