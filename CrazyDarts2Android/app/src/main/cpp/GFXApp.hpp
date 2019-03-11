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


class ScreenTracker {
    
public:
    ScreenTracker() {
        float mX=0.0f;
        float mY=0.0f;
        float mSpeed=1.0f;
        int mDir=1;
    }
    
    void Update() {
        if (mDir == -1) {
            mX -= mSpeed;
            if (mX <= 0.0f) {
                mX =0.0f;
                mDir = 1;
            }
        } else {
            mX += mSpeed;
            if (mX >= gDeviceWidth) {
                mX = gDeviceWidth;
                mDir = -1;
            }
        }
        
    }
    
    float mX;
    float mY;
    float mSpeed;
    int mDir;
    
    
    
    
};



class Util_ScreenFrame;
class LightConfigurationScene;
class LevelSelectorScreen;
class LightMenu;
class CameraMenu;

class Game;

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
    
    Game                                    *mGame;
    
    void                                    Draw3D();
    void                                    Draw2D();
    
    ScreenTracker                           mTracker[4];
    
    FloatingCamera                          mCamera;
    
    CameraMenu                              *mCameraMenu;
    

    FSprite                                 mGroundMixedMap;
    FSprite                                 mGroundGreenMap;
    


    FSprite                                 mDartMap;
    

    FSprite                                 mBalloonMap[5];

    FSprite                                 mSpiralPineStumpMap;

    FSprite                                 mSpiralPineTreeMap;

    FSprite                                 mMonolithMap;
    
    FSprite                                 mChaosEgg1X;
    FSprite                                 mChaosEgg2X;
    FSprite                                 mChaosEgg3X;
    FSprite                                 mChaosEgg4X;
    
    FSprite                                 mRay[4];

    FSound                                  mSound1;
    FSound                                  mSound2;


    LevelSelectorScreen                     *mLevelSelect;
    LightConfigurationScene                 *mLightScene;
    Util_ScreenFrame                        *mScreenTool;
    
};

extern GFXApp *gApp;

#endif /* GFXApp_hpp */
