//
//  OpenGLView.m
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//

#import "OpenGLView.h"
#import "Scene.hpp"

@implementation OpenGLView

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
