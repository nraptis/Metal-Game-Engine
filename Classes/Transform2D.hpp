//
//  Transform2D.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Transform2D_hpp
#define Transform2D_hpp

class Transform2D {
public:
    
    Transform2D();
    ~Transform2D();
    
    float                                   mX;
    float                                   mY;
    float                                   mZ;
    
    float                                   mOffsetX;
    float                                   mOffsetY;
    float                                   mOffsetZ;
    
    float                                   mScale;
    float                                   mScaleX;
    float                                   mScaleY;
    float                                   mScaleZ; //Pass through...
    
    float                                   mOffsetScale;
    
    float                                   mRotation;
    float                                   mOffsetRotation;
    
    //These help us translate into 3-D 
    
};

#endif
