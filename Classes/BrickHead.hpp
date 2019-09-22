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
#include "StuckDart.hpp"

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
    
    //bool                                    mStuck;
    
    //List of StuckDart objects...
    FList                                   mStuckDartList;
    FList                                   mStuckDartDeleteList;
    
    
    
    void                                    Rumble(float pRotation);
    bool                                    mIsRumbling;
    int                                     mRumbleTime;
    int                                     mRumbleTimer;
    int                                     mRumbleDampenTime;
    float                                   mRumbleDirX;
    float                                   mRumbleDirY;
    float                                   mRumbleBounceMagnitude;
    float                                   mRumbleBounceSin;
    float                                   mRumbleColorSin;
    
    
    
    void                                    KnockDown();
    bool                                    mKnockedDown; //When  we are knocked down, we no longer operate as a blocker.
    float                                   mKnockedDownColorSin;
    float                                   mKnockedDownRotationSpeed1;
    float                                   mKnockedDownRotationSpeed2;
    float                                   mKnockedDownFallSpeed;
    
    
    //Dart                                    *mStuckDart;
    //float                                   mStuckDartStartDartRotation;
    //float                                   mStuckDartStartBrickHeadRotation;
    //float                                   mStuckDartStartXDiff;
    //float                                   mStuckDartStartYDiff;
    
    
    
    
    FModelDataPacked                        *mAccessoryModel;
    FSprite                                 *mAccessorySprite;
    
    float                                   mVelX;
    float                                   mVelY;
    
    FVec2                                   mCornerPoint1;
    FVec2                                   mCornerPoint2;
    FVec2                                   mCornerPoint3;
    FVec2                                   mCornerPoint4;
    
    
    float                                   mWanderingSinX;
    float                                   mWanderingSinY;
    
    
    float                                   mWanderingOsc;
    
    float                                   mWanderingMagX;
    float                                   mWanderingMagY;
    
    
    
};

#endif /* BrickHead_hpp */
