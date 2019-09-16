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
#include "AssetWadModels.hpp"

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
class SoundConfigMenu;
class AssetConfigMenu;
class GameContainer;
class MainMenu;
class Transition;
class GFXAppNotificationHelper;


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
    
    
    GFXAppNotificationHelper                *mNotificationHelper;
    
    FCanvas                                 *mCurrentCanvas;
    
    GameContainer                           *mGameContainer;
    MainMenu                                *mMainMenu;
    
    Transition                              *mTransition;
    FCanvas                                 *mTransitionPreviousCanvas;
    
    int                                     mTransitionTarget;
    int                                     mTransitionCooldown;
    
    
    bool                                    TransitionAllowed();
    
    //For any transition, this will spawn the transition, and queue out the old current VC..
    void                                    TransitionPrepare();
    
    void                                    TransitionToGame();
    void                                    TransitionToMainMenu();
    
    
    
    void                                    NotifyTransitionSwap();
    void                                    NotifyTransitionComplete();
    
    
#ifdef EDITOR_MODE
    GameEditor                              *mEditor;
    
    void                                    EditorTestSwitchToGame();
    void                                    EditorTestSwitchToGameInternal();
    
    void                                    EditorTestSwitchToEditor();
    void                                    EditorTestSwitchToEditorInternal();
    
    
    
    
    int                                     mEditorTestSwitchToGameEnqueue;
    int                                     mEditorTestSwitchToEditorEnqueue;
    
    
    
    
#endif
    
    void                                    EnqueueWadReload(int pTime);
    void                                    DequeueWadReload();
    
    bool                                    mWadReloadIsEnqueued;
    bool                                    mWadReloadOnNextDraw;
    void                                    ExecuteWadReload();
    int                                     mWadReloadTimer;
    
    void                                    ReevaluateScreenResolution();
    
    FloatingCamera                          mCamera;
    
    CameraMenu                              *mCameraMenu;
    
    SoundConfigMenu                         *mSoundMenu;
    AssetConfigMenu                         *mAssetMenu;
    
    
    FModelDataPacked                        mGround;
    FSprite                                 mGroundMixedMap;
    FSprite                                 mGroundGreenMap;
    
    FModelDataPacked                        mPalmTrunk;
    FSprite                                 mPalmTrunkMap;
    
    FModelDataPacked                        mPalmLeaves;
    FSprite                                 mPalmLeavesMap;
    
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
    
    //FModelDataPacked                        mBF;
    //FSprite                                 mBFMap;
    
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
};

extern GFXApp *gApp;

extern AssetWadGameInterface gWadGameInterface;
extern AssetWadGameEffects gWadGameEffects;
extern AssetWadModels gWadModels;


#endif /* GFXApp_hpp */
