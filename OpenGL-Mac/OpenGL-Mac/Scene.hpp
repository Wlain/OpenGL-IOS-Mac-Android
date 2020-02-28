//
//  Scene.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Base.h"


/**
 初始化
 */
void Initialize();

/**
 绘制
 */
void Draw();


/**
 键盘按下
 
 @param code 键盘对应的ASCII值
 */
void OnKeyDown(char code);


/**
 键盘弹起
 
 @param code 键盘对应的ASCII值
 */
void OnKeyUp(char code);


/**
 鼠标移动时间
 
 @param deltaX 鼠标X轴偏移的距离
 @param deltaY 鼠标Y轴偏移的距离
 */
void OnMouseMove(float deltaX, float deltaY);


#endif /* Scene_hpp */
