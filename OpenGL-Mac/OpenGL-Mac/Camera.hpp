//
//  Camera.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/21.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Vector3f.hpp"

class Camera {
public:
    Camera();
    ~Camera();
    Vector3f mEyePosition; // mTargetPosition
    Vector3f mTargetPosition;
    Vector3f mUp;
    bool mIsMoveLeft;
    bool mIsMoveRight;
    bool mIsMoveForward;
    bool mIDMoveBack;
    // 设置当前摄像机的姿态
    void Update(float deltaTime);
};

#endif /* Camera_hpp */
