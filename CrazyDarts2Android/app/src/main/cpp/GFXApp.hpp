//
//  GFXApp.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/29/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef GFXApp_hpp
#define GFXApp_hpp

#include "FApp.hpp"
#include "FModelData.h"
#include "FModelDataPacked.hpp"
#include "UIRoundedRect.hpp"
#include "FloatingCamera.hpp"
#include "FUniforms.hpp"
#include "FJSON.hpp"

#define EDITOR_MODE 1
//#undef EDITOR_MODE

#ifdef EDITOR_MODE
class GameEditor;
#endif

class Util_ScreenFrame;
class LightConfigurationScene;
class LevelSelectorScreen;
class LightMenu;
class CameraMenu;

class GameContainer;

class GFXApp : public FApp {
public:
    GFXApp();
    virtual ~GFXApp();
    
    virtual void                            Update() override;
    virtual void                            Draw() override;
    
    virtual void                            Load() override;
    virtual void                            LoadComplete() override;
    
    virtual void                            SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) override;
    virtual void                            SetDeviceSize(int pWidth, int pHeight) override;
    
    virtual void                            MouseWheel(int pDirection) override;
    virtual void                            KeyDown(int pKey) override;
    virtual void                            KeyUp(int pKey) override;
    
    virtual void                            TouchDown(float pX, float pY, void *pData) override;
    virtual void                            TouchMove(float pX, float pY, void *pData) override;
    virtual void                            TouchUp(float pX, float pY, void *pData) override;
    virtual void                            TouchFlush() override;
    
    GameContainer                           *mGameContainer;
    
#ifdef EDITOR_MODE
    GameEditor                              *mEditor;
#endif
    
    
    void                                    Draw3D();
    void                                    Draw2D();
    
    FloatingCamera                          mCamera;
    
    CameraMenu                              *mCameraMenu;
    
    FModelData                              mSnail;
    FSprite                                 mSnailMap;
    
    FModelDataPacked                        mRocket;
    FSprite                                 mRocketMap;
    
    
    FModelDataPacked                        mGround;
    FSprite                                 mGroundMixedMap;
    FSprite                                 mGroundGreenMap;
    
    FModelDataPacked                        mPalmTrunk;
    FSprite                                 mPalmTrunkMap;
    
    FModelDataPacked                        mPalmLeaves;
    FSprite                                 mPalmLeavesMap;
    
    FModelDataPacked                        mDart;
    FSprite                                 mDartMap;
    
    FModelDataPacked                        mBalloon;
    FSprite                                 mBalloonMap[5];
    
    FModelDataPacked                        mSpiralPineStump;
    FSprite                                 mSpiralPineStumpMap;
    
    FModelDataPacked                        mSpiralPineTree;
    FSprite                                 mSpiralPineTreeMap;
    
    FModelDataPacked                        mMonolith;
    FSprite                                 mMonolithMap;
    
    FSprite                                 mChaosEgg1X;
    FSprite                                 mChaosEgg2X;
    FSprite                                 mChaosEgg3X;
    FSprite                                 mChaosEgg4X;
    
    FSprite                                 mRay[4];
    
    
    FSprite                                 mGameAreaMarker;
    
    
    FSound                                  mSound1;
    FSound                                  mSound2;
    
    LevelSelectorScreen                     *mLevelSelect;
    LightConfigurationScene                 *mLightScene;
    Util_ScreenFrame                        *mScreenTool;
    
    
    UIRoundedRect                           mTestRR;
    
    
    FUniformsLightAmbient                   mUniAmb;
    FUniformsLightAmbientDiffuse            mUniDiff;
    FUniformsLightPhong                     mUniPhong;
    
    
    
    int                                     mLoadGame;
    
    void                                    *mTestTouch1;
    void                                    *mTestTouch2;
    
    float                                   mTestX1;
    float                                   mTestY1;
    
    float                                   mTestX2;
    float                                   mTestY2;
    
    float                                   mTestSin1;
    float                                   mTestSin2;
    
    
    float                                   mAmbientRoll1;
    float                                   mAmbientRoll2;
    
    
    
};

extern GFXApp *gApp;

#endif /* GFXApp_hpp */
