//
//  Transform2D.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Transform2D.hpp"

Transform2D::Transform2D() {
    
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    mOffsetZ = 0.0f;
    
    mScale = 1.0f;
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    
    mOffsetScale = 1.0f;
    
    mRotation = 0.0f;
    mOffsetRotation = 0.0f;
    
}

Transform2D::~Transform2D() {
    
}








