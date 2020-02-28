//
//  OpenGLView.m
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//

#import "OpenGLView.h"
#import "Scene.hpp"
#include "stb_image.h"
#include "Utils.hpp"

#define STB_IMAGE_IMPLEMENTATION

GLuint TextureFromFile(const char *path, bool flipVertical) {
    NSString *filename = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:path] ofType:nil];
    GLuint textureID = 0;
    glGenTextures(1, &textureID);
    
    int width, height, channels_in_file;
    stbi_set_flip_vertically_on_load(flipVertical);
    GLubyte *data = stbi_load(filename.UTF8String, &width, &height, &channels_in_file, 0);
    if (data != nullptr) {
        GLenum format = 0;
        if (channels_in_file == 1) {
            format = GL_RED;
        } else if (channels_in_file == 3) {
            format = GL_RGB;
        } else if (channels_in_file == 4) {
            format = GL_RGBA;
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path:" << path << std::endl;
    }
    return textureID;
}

GLubyte * LoadFileContent(const char *filePath, int &filesize) {
    unsigned char *fileContent = nullptr;
    filesize = 0;
    NSString *filename = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filePath] ofType:nil];
    NSData *data = [NSData dataWithContentsOfFile:filename];
    unsigned long dataSize = [data length];
    if (dataSize > 0) {
        fileContent = new GLubyte[dataSize + 1];
        memset(fileContent, 0, dataSize + 1);
        memcpy(fileContent, [data bytes], dataSize);
        fileContent[dataSize] = '\0';
    }
    return fileContent;
}


float GetFrameTime(){
    return 1.0f/60.0f;
}


@interface OpenGLView()
// 存储鼠标原始点
@property(nonatomic, assign) CGPoint orignPosition;
@property(nonatomic, assign) CGPoint lastPosition;
@property(nonatomic, assign) BOOL rotateView;

@end


@implementation OpenGLView

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)keyDown:(NSEvent *)event {
    // 对应的是大写字母
    OnKeyDown([event.characters UTF8String][0] - 32);
}

- (void)keyUp:(NSEvent *)event {
    // 对应的是大写字母
    OnKeyUp([event.characters UTF8String][0] - 32);
}

- (void)rightMouseDown:(NSEvent *)event {
    CGEventRef tempEvent = CGEventCreate(NULL);
    self.orignPosition = CGEventGetLocation(tempEvent);
    CFRelease(tempEvent);
    self.rotateView = YES;
    self.lastPosition = self.orignPosition;
    
}

- (void)rightMouseUp:(NSEvent *)event {
    self.rotateView = NO;
    CGDisplayMoveCursorToPoint(kCGDirectMainDisplay, self.orignPosition);
}

- (void)rightMouseDragged:(NSEvent *)event {
    CGEventRef tempEvent = CGEventCreate(NULL);
    CGPoint point = CGEventGetLocation(tempEvent);
    CFRelease(tempEvent);
    if (self.rotateView) {
        OnMouseMove(point.y - self.lastPosition.x, point.y - self.lastPosition.y);
        self.lastPosition = point;
    }
}

- (void)prepareOpenGL {
    [super prepareOpenGL];
    Initialize();
    [NSTimer scheduledTimerWithTimeInterval:1.0/60.0 target:self selector:@selector(renderOneFrame) userInfo:nil repeats:YES];
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    Draw();
    glFlush();
    // Drawing code here.
}

- (void)renderOneFrame {
    // 帧率60
    [self setNeedsDisplay:YES];
}


@end
