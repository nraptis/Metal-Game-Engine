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
    
    void                                    Draw3DPropeller();
    void                                    Draw3DBillboard();
    
    
    float                                   mSpinSpeed;
    
    FModelDataPacked                        *mPropellerModel;
    FSprite                                 *mPropellerSprite;
    
    
    
    //FModelDataPacked                        *mPropellerModel;
    //FSpriteSequence                         *mPropellerSprite;
    
    float                                   mVelX;
    float                                   mVelY;
    
    
    
    //mTestSequence1.LoadOBJSequence("butterfly_body_", 0, 19);
    //mTestSequence2.LoadOBJSequence("butterfly_wings_", 0, 19);
    //mTestSequenceMap.Load("butterfly_map");
    
    float                                   mTestFrame;
    
    
    
    
};

#endif /* Turtle_hpp */
