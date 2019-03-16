//
//  Balloon.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/14/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef Balloon_hpp
#define Balloon_hpp

#include "FSprite.h"
#include "FModelDataPacked.hpp"
#include "GameObject.hpp"

class Balloon : public GameObject {
public:
    Balloon();
    virtual ~Balloon();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    
    float                                   mSpinSpeed;
    
    int                                     mDeathTimer;
    int                                     mTimer;
    
    float                                   mVelX;
    float                                   mVelY;
};



#endif /* Balloon_hpp */
