//
//  Transform3D.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Transform3D.hpp"

Transform3D::Transform3D() {
    
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    
    mScale = 1.0f;
    
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    mScaleZ = 1.0f;
    
    mRotation2D = 0.0f;
    
    mSpin = 0.0f;
    
    mRotationX = 0.0f;
    mRotationZ = 0.0f;
}

Transform3D::~Transform3D() {
    
}

