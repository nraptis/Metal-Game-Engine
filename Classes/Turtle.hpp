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

class Turtle : public GameObject {
public:
    Turtle();
    virtual ~Turtle();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    
    void                                    Draw3DPropeller();
    void                                    Draw3DBillboard();
    
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
    
    
    
    
    //FModelDataPacked                        *mPropellerModel;
    //FSpriteSequence                         *mPropellerSprite;
    
    float                                   mVelX;
    float                                   mVelY;
    
    
    
    float                                   mBillboardFrame;
    
    
    
};

#endif /* Turtle_hpp */
