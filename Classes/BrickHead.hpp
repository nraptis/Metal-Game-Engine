//
//  BrickHead.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/4/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef BrickHead_hpp
#define BrickHead_hpp

#include "FSprite.h"
#include "FModelDataPacked.hpp"
#include "GameObject.hpp"

class BrickHead : public GameObject {
public:
    BrickHead();
    virtual ~BrickHead();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    
    float                                   mSpinSpeed;
    
    float                                   mVelX;
    float                                   mVelY;
};

#endif /* BrickHead_hpp */
