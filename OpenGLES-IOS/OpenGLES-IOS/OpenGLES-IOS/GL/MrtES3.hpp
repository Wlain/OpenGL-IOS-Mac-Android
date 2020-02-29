//
//  MrtES3.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/29.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef MrtES3_hpp
#define MrtES3_hpp
#include "RendererES3.hpp"

class MrtES3 : public RendererES3 {
public:
    MrtES3();
    virtual ~MrtES3();
    virtual void Initialize();
    virtual void Draw();
    void DrawGeometry();
    // Initialize the framebuffer object and MRTs
    GLboolean InitFbo();
    // Copy MRT output buffers to screen
    void BlitTextures();
    void Resize(int width, int height);
private:
    GLuint mFbo;
    GLint mWidth;
    GLint mHeight;
    // Texture size
    GLsizei mTextureWidth;
    GLsizei mTextureHeight;
    // Texture handle
    GLuint mColorTexId[4];

};

#endif /* MrtES3_hpp */
