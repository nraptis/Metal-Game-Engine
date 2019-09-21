//
//  GameObject.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "GFXApp.hpp"
#include "FObject.hpp"
#include "FModelDataPacked.hpp"
#include "FModelDataPackedSequence.hpp"
#include "FSprite.hpp"
#include "FSpriteSequence.h"
#include "FUniforms.hpp"
#include "FAnimation.hpp"
#include "Transform2D.hpp"
#include "Transform3D.hpp"

#define GAME_OBJECT_TYPE_UNKNOWN -1
#define GAME_OBJECT_TYPE_BALLOON 0
#define GAME_OBJECT_TYPE_BRICKHEAD 1
#define GAME_OBJECT_TYPE_BOMB 2
#define GAME_OBJECT_TYPE_TURTLE 3

#define GAME_OBJECT_TYPE_FREE_LIFE 7

#define GAME_OBJECT_TYPE_DART 1000

class LevelWave;
class LevelWaveSpawn;
class LevelPermSpawn;
class GameObject : public FObject {
public:
    GameObject();
    virtual ~GameObject();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    virtual void                            Kill();
    
    FString                                 TypeString();
    
    //Basically, an object / dart moves from (startX, startY) to (endX, endY)
    virtual bool                            WillCollide(float pStartX, float pStartY, float pEndX, float pEndY);
    float                                   mEllipseRadiusH;
    float                                   mEllipseRadiusV;
    
    //Where did we come from?
    bool                                    mDidOriginateOnWave;
    bool                                    mDidOriginateAsPermanent;
    
    bool                                    IsRequiredToClearForSectionCompletion();
    
    //Essentially, the objects will "disperse" as a cluster, and pMagnitude will be 1.0 for
    //the furthest object away from the centroid of all the objects in the cluster.........
    
    virtual void                            Disperse(float pDirX, float pDirY, float pMagnitude);
    
    virtual void                            FloatAway(float pDirX, float pDirY, float pMagnitude);
    
    bool                                    mFloatAway;
    float                                   mFloatAwaySpeedX;
    float                                   mFloatAwaySpeedY;
    
    
    LevelWave                               *mWave;
    
    FModelDataPacked                        *mModel;
    FSprite                                 *mSprite;
    
    //Each "Game Object" gets its own model view matrix,
    //which will automatically set the uniform's model
    //view matrix to the game object's MVM...
    FMatrix                                 mModelView;
    FMatrix                                 mNormal;
    
    //Rule for how "Game Objects" control a uniform...
    //1.) They MAY NOT modify the projection matrix.
    //2.) They may entirely replace the model view matrix...
    //3.) The native draw functionality will ALWAYS bind
    //    the uniform before a draw, which means... DO NOT
    //    use the built in Graphics::MatrixModelViewSet, etc...
    FUniforms                               *mUniform;
    
    //These will be the actual coordinates...
    //void                                    SetPos(FVec3 pPos) { mX = pPos.mX; mY = pPos.mY; mZ = pPos.mZ; }
    //void                                    SetPos(FVec2 pPos) { mX = pPos.mX; mY = pPos.mY; mZ = 0.0f; }
    
    FColor                                  mColor;
    
    Transform2D                             mTransform;
    Transform3D                             mTransform3D;
    
    int                                     mGameObjectType;
    
    LevelWaveSpawn                          *mWaveSpawn;
    LevelPermSpawn                          *mPermSpawn;
};

#endif /* GameObject_hpp */
