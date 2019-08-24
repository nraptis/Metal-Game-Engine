//
//  Bomb.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Bomb_hpp
#define Bomb_hpp

#include "FSprite.hpp"
#include "FModelDataPacked.hpp"
#include "GameObject.hpp"

class Bomb : public GameObject {
public:
    Bomb();
    virtual ~Bomb();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    
    float                                   mSpinSpeed;
    
    FModelDataPacked                        *mAccessoryModel;
    FSprite                                 *mAccessorySprite;
    
    float                                   mVelX;
    float                                   mVelY;
};

#endif /* Bomb_hpp */
