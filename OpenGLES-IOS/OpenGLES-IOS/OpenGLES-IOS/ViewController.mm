//
//  ViewController.m
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#import "ViewController.h"
#import "Scene.hpp"
#import "Base.h"


const GLchar* LoadFileContent(const char *filePath, int &filesize) {
    assert(filePath);
    char *fileContent = nullptr;
    filesize = 0;
    NSString *filename = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filePath] ofType:nil];
    NSData *data = [NSData dataWithContentsOfFile:filename];
    unsigned long dataSize = [data length];
    if (dataSize > 0) {
        fileContent = new GLchar[dataSize + 1];
        memset(fileContent, 0, dataSize + 1);
        memcpy(fileContent, [data bytes], dataSize);
        fileContent[dataSize] = '\0';
    }
    return fileContent;
}

GLfloat GetFrameTime() {
    static double lastTime = 0;
    static double currentTime = 0;
    struct timeval t;
    gettimeofday(&t, NULL);
    currentTime = t.tv_sec + t.tv_usec * 1e-6;;
    double frameTime = lastTime == 0 ? 0 : currentTime - lastTime;
    lastTime = currentTime;
    return frameTime;
}

GLuint GetTextureFromFile(const char *path, bool flipVertical) {
    GLuint textureID = 0;
    NSString *fileName = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:path] ofType:nil];
    // 1.将 UiImgae 转换成 CGImageRef
    UIImage *image = [UIImage imageNamed:fileName];
    CGImageRef imageRef = [image CGImage];
    if (imageRef == nil) {
        NSLog(@"Failed to load Image %@", fileName);
        return textureID;
    }
    // 2.读取图片的宽高
    unsigned long width = CGImageGetWidth(imageRef);
    unsigned long height = CGImageGetHeight(imageRef);
    // 3.申请内存创建图片
    GLubyte *imageData = (GLubyte *)malloc(width * height * 4 * sizeof(GLubyte));
    memset(imageData, 0, width * height * 4 * sizeof(GLubyte));
    // 获取图片的rect
    CGRect rect = CGRectMake(0, 0, width, height);
    // 获取图片的颜色空间
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    // 4.创建上下文
    CGContextRef context = CGBitmapContextCreate(imageData, width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);
    // 5.将图片翻转过来(图片默认是倒置的)
    if (flipVertical) {
        CGContextTranslateCTM(context, 0, height);
        CGContextScaleCTM(context, 1.0f, -1.0f);
    }
    // 6.对图片进行重新绘制，得到一张新的解压缩后的位图
    // 绘制前清屏
    CGContextClearRect(context, rect);
    CGContextDrawImage(context, rect, imageRef);
    CGContextRelease(context);
    // 7.绑定纹理ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // 8.将内存的2D纹理数据载入GPU显存
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    // 9.设置纹理属性
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    // 10.释放资源
    SAFE_FREE(imageData);
    return textureID;
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
    Initialize();
    CGRect rect = [[UIScreen mainScreen] bounds];
    SetViewPort(rect.size.width, rect.size.height);
}

- (void)dealloc
{
    Finalize();
    if ([EAGLContext currentContext] == self.context)
    {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    Draw();
}


@end
