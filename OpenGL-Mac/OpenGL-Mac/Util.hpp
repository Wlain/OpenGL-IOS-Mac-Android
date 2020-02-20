//
//  Util.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

#include "Base.h"

/**
 根据图片文件创建纹理

 @param path 图片文件路径
 @return 纹理ID
 */
GLuint TextureFromFile(const char *path);

/**
 创建显示列表

 @param foo draw方法指针
 @return 显示列表
 */
GLuint CreateDisplayList(std::function<void()>foo);

#endif /* Util_hpp */
