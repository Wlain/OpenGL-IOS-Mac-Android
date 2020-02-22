//
//  ViewController.m
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#import "ViewController.h"
#include "Scene.hpp"

GLubyte* LoadFileContent(const char *filePath, int &filesize) {
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


@interface ViewController ()
@property(nonatomic, strong) EAGLContext *context;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (self.context == nil) {
        self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    }
    if (self.context == nil) {
        NSLog(@"Failed to create OpenGLES context");
    }
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    // 初始化深度缓冲区为24bit
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:self.context];
    Init();
    CGRect rect = [[UIScreen mainScreen] bounds];
    SetViewPort(rect.size.width, rect.size.height);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    Draw();
}


@end
