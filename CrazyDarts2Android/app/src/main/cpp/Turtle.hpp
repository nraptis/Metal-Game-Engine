//
//  Turtle.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Turtle_hpp
#define Turtle_hpp

#include "FSprite.hpp"
#include "FModelDataPacked.hpp"
#include "GameObject.hpp"

class Turtle : public GameObject {
public:
    Turtle();
    virtual ~Turtle();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    
    float                                   mSpinSpeed;
    
    FModelDataPacked                        *mAccessoryModel;
    FSprite                                 *mAccessorySprite;
    
    float                                   mVelX;
    float                                   mVelY;
};

#endif /* Turtle_hpp */
