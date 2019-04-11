//
//  Balloon.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/14/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef Balloon_hpp
#define Balloon_hpp

#include "FSprite.hpp"
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
    
    float                                   mVelX;
    float                                   mVelY;
    
    bool                                    mTagged;
};



#endif /* Balloon_hpp */
