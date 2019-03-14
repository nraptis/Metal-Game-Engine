//
//  Transform3D.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Transform3D_hpp
#define Transform3D_hpp

class Transform3D {
public:
    Transform3D();
    ~Transform3D();
    
    float                                   mX;
    float                                   mY;
    float                                   mZ;
    
    float                                   mScale;
    float                                   mScaleX;
    float                                   mScaleY;
    float                                   mScaleZ;
    
    
    
    //Rotation about Y axis (spinning around merry-go-round)
    float                                   mSpin;
    
    //Rotation about Z axis (2-D normal rotation).
    float                                   mRotation2D;
    
    
    float                                   mRotationX;
    float                                   mRotationZ;
    
};

#endif /* Transform3D_hpp */
