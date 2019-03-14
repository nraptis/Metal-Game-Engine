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
    
    void                                    Draw3D();
    void                                    Draw2D();
    
    FloatingCamera                          mCamera;
    
    CameraMenu                              *mCameraMenu;
    
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
    
    bool                                    mLayoutGame;
    
};

extern GFXApp *gApp;

#endif /* GFXApp_hpp */
