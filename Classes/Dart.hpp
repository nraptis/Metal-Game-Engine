//
//  Dart.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Dart_hpp
#define Dart_hpp

#include "GameObject.hpp"

class Dart : public GameObject {
public:
    Dart();
    virtual ~Dart();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    
    void                                    SpawnAnimation();
    void                                    SpawnAnimationForceComplete();
    
    int                                     mStyleIndex;
    
    
    bool                                    mSpawnAnimation;
    
    int                                     mSpawnAnimationDelay;
    
    int                                     mSpawnAnimationTime;
    int                                     mSpawnAnimationTimer;
    
    FVec2                                   GetTipPoint();
    
    float                                   mPrevTipX;
    float                                   mPrevTipY;
    
    float                                   mTipX;
    float                                   mTipY;
    
    float                                   mSpinSpeed;
    
    int                                     mDeathTimer;
    int                                     mTimer;
    
    float                                   mTargetRotation;
    
    float                                   mVelX;
    float                                   mVelY;
    
    int                                     mHitCount;
    
    //While we are "idle" we have not yet been released
    //and are sitting at the lower center of the screen...
    bool                                    mIdle;
    
    bool                                    mStuck;
    
    virtual void                            Fling(float pVelocityX, float pVelocityY);
    
    float                                   mUpdateInterpStartX;
    float                                   mUpdateInterpStartY;
    float                                   mUpdateInterpStartRotation;
    
    float                                   mUpdateInterpEndX;
    float                                   mUpdateInterpEndY;
    float                                   mUpdateInterpEndRotation;
    
    float                                   mStoredTipX;
    float                                   mStoredTipY;
    
    float                                   mStoredPrevTipX;
    float                                   mStoredPrevTipY;
    
    
};

#endif
