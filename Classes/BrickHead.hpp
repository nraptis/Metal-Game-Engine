//
//  BrickHead.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/4/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef BrickHead_hpp
#define BrickHead_hpp

#include "FSprite.hpp"
#include "FModelDataPacked.hpp"
#include "GameObject.hpp"

class Dart;
class BrickHead : public GameObject {
public:
    BrickHead();
    virtual ~BrickHead();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    
    virtual bool                            WillCollide(float pStartX, float pStartY, float pEndX, float pEndY);
    
    
    float                                   mSpinSpeed;
    
    
    float                                   mSwivel;
    float                                   mSwivelSpeed;
    
    bool                                    mStuck;
    
    Dart                                    *mStuckDart;
    float                                   mStuckDartStartDartRotation;
    float                                   mStuckDartStartBrickHeadRotation;
    float                                   mStuckDartStartXDiff;
    float                                   mStuckDartStartYDiff;
    
    FModelDataPacked                        *mAccessoryModel;
    FSprite                                 *mAccessorySprite;
    
    float                                   mVelX;
    float                                   mVelY;
    
    FVec2                                   mCornerPoint1;
    FVec2                                   mCornerPoint2;
    FVec2                                   mCornerPoint3;
    FVec2                                   mCornerPoint4;
    
    
    float                                   mHitOscSin;
    float                                   mHitOscSpinRot;
    float                                   mHitStartX;
    float                                   mHitStartY;
    int                                     mHitDelay;
    
    
    
};

#endif /* BrickHead_hpp */
