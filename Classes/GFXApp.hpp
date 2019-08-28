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
#include "WadGlobalConfiguration.hpp"
#include "FUniforms.hpp"
#include "FJSON.hpp"

#include "AssetWadGameInterface.hpp"
#include "AssetWadGameEffects.hpp"

#define EDITOR_MODE 1
#undef EDITOR_MODE


#ifdef EDITOR_MODE
class GameEditor;
#endif

class Util_ScreenFrame;
class LightConfigurationScene;
class LevelSelectorScreen;
class LightMenu;
class CameraMenu;
class SoundConfigMenu;
class AssetConfigMenu;
class GameContainer;
class WorldConfigScene;

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
    
    void                                    EditorTestSwitchToGame();
    void                                    EditorTestSwitchToEditor();
    
    int                                     mEditorSwitchType;
    int                                     mEditorSwitchTimer;
    
#endif

    
    void                                    EnqueueWadReload(int pTime);
    bool                                    mWadReloadIsEnqueued;
    bool                                    mWadReloadOnNextDraw;
    void                                    ExecuteWadReload();
    int                                     mWadReloadTimer;
    
    
    
    //AssetWadGameInterface                   mWadGameInterface;
    //AssetWadGameEffects                     mWadGameEffects;
    
    
    //effect_twinkle_additive_white_large.png
    //effect_twinkle_additive_white_small.png
    
    
    FloatingCamera                          mCamera;
    
    CameraMenu                              *mCameraMenu;
    
    SoundConfigMenu                         *mSoundMenu;
    AssetConfigMenu                         *mAssetMenu;
    
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
    FSprite                                 mDartMap[4];
    
    FModelDataPacked                        mBalloon;
    FSprite                                 mBalloonMap[5];
    
    FModelDataPacked                        mBrickhead;
    FSprite                                 mBrickheadMap;
    
    FModelDataPacked                        mBrickheadCage;
    FSprite                                 mBrickheadCageMap;
    
    FModelDataPacked                        mSpiralPineStump;
    FSprite                                 mSpiralPineStumpMap;
    
    FModelDataPacked                        mSpiralPineTree;
    FSprite                                 mSpiralPineTreeMap;
    
    FModelDataPacked                        mMonolith;
    FSprite                                 mMonolithMap;
    
    FSprite                                 mCircle256;
    FSprite                                 mCircle512;
    
    FSprite                                 mGameAreaMarker;
    
    
    FSound                                  mSoundBalloonPop;
    FSound                                  mSoundDartPullback;
    FSound                                  mSoundDartRelease;
    
    FSound                                  mSoundHitBrickhead;
    FSound                                  mSoundHitTurtle;
    
    FSound                                  mSoundFreeLife;
    
    FSound                                  mSoundSparkle1;
    FSound                                  mSoundSparkle2;
    
    FSound                                  mSoundXylophone;
    
    
    LevelSelectorScreen                     *mLevelSelect;
    LightConfigurationScene                 *mLightScene;
    WorldConfigScene                        *mWorldScene;
    Util_ScreenFrame                        *mScreenTool;
    
    
    int                                     mLoadGame;
    
    
};

extern GFXApp *gApp;

extern AssetWadGameInterface gWadGameInterface;
extern AssetWadGameEffects gWadGameEffects;


#endif /* GFXApp_hpp */
