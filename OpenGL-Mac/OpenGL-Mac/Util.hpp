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

GLuint TextureFromFile(const char *path);
GLuint CreateDisplayList(std::function<void()>foo);

#endif /* Util_hpp */
