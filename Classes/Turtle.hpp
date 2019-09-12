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
#include "GameObject.hpp"
#include "FPointList.hpp"

class Balloon;
class Turtle : public GameObject {
public:
    Turtle();
    virtual ~Turtle();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    
    void                                    Draw3DPropeller();
    void                                    Draw3DBillboard();
    
    virtual bool                            WillCollide(float pStartX, float pStartY, float pEndX, float pEndY);
    
    void                                    KnockDown();
    bool                                    mKnockedDown; //When  we are knocked down, we no longer operate as a blocker.
    float                                   mKnockedDownColorSin;
    float                                   mKnockedDownRotationSpeed1;
    float                                   mKnockedDownRotationSpeed2;
    float                                   mKnockedDownFallSpeed;
    
    
    
    void                                    Impact(float pImpactRotation);
    bool                                    mIsRumbling;
    int                                     mRumbleTime;
    int                                     mRumbleTimer;
    int                                     mRumbleDampenTime;
    float                                   mRumbleDirX;
    float                                   mRumbleDirY;
    float                                   mRumbleBounceMagnitude;
    float                                   mRumbleBounceSin;
    float                                   mRumbleColorSin;
    
    
    FMatrix                                 mPropellerMatrixModelView;
    FMatrix                                 mPropellerMatrixNormal;
    
    FModelDataPacked                        *mPropellerModel;
    FSprite                                 *mPropellerSprite;
    float                                   mPropellerSpin;
    float                                   mPropellerSpeed;
    
    FModelDataPackedSequence                *mPropellerBillboardSequence;
    FSpriteSequence                         *mPropellerBillboardSequenceMap;
    float                                   mPropellerBillboardFrame1;
    float                                   mPropellerBillboardFrame2;
    float                                   mPropellerBillboardFrame3;
    float                                   mPropellerBillboardSpin1;
    float                                   mPropellerBillboardSpin2;
    float                                   mPropellerBillboardSpin3;
    
    float                                   mBillboardFrame;
    
    Balloon                                 *mBalloon;
    bool                                    mDidSpawnBalloon;
    
    float                                   mBalloonOscillationSin;
    float                                   mBalloonOscillationSinSpeed;
    
    void                                    BuildEdgePointListBase();
    void                                    BuildEdgePointList();
    
    FPointList                              mEdgePointList3DBase;
    FPointList                              mEdgePointList3D;
    FPointList                              mEdgePointList2D;
    
};

#endif /* Turtle_hpp */
