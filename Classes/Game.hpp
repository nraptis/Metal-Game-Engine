//
//  Game.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "GFXApp.hpp"
#include "GameRenderer.hpp"
#include "FloatingCamera.hpp"
#include "Dart.hpp"
#include "Balloon.hpp"

#define GAME_WIDTH 768
#define GAME_HEIGHT 1280

class Game : public FCanvas {
public:
    Game();
    virtual ~Game();
    
    virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight) override;
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    void                                        Draw3D();
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    FVec3                                       ConvertScreenCoordsToScene(float pX, float pY);
    float                                       ConvertScreenXToScene(float pX);
    float                                       ConvertScreenYToScene(float pY);
    
    
    FVec2                                       ConvertSceneCoordsToScreen(float pX, float pY);
    float                                       ConvertSceneXToScreen(float pX);
    float                                       ConvertSceneYToScreen(float pY);
    
    
    
    GameRenderer                                *mRenderer;
    FloatingCamera                              *mCamera;
    
    float                                       mGravity;
    
    FObjectList                                 mDartList;
    FObjectList                                 mBalloonList;
    
    Dart                                        *mCurrentDart;
    int                                         mCurrentDartRespawnTimer;
    
    FList                                       mDemoDartList;
    
    void                                        ResetDartTouch();
    void                                        ReleaseDart();
    
    
    
    float                                       mDartReleaseVelocityMin;
    float                                       mDartReleaseVelocityMax;
    bool                                        mDartResetAnimation;
    int                                         mDartResetAnimationTick;
    int                                         mDartResetAnimationTime;
    float                                       mDartResetStartPullX;
    float                                       mDartResetStartPullY;
    float                                       mDartResetStartRotation;
    float                                       mDartResetRotationLength;
    // The location (in 2-D where the dart spawns...)
    float                                       mDartSpawnX;
    float                                       mDartSpawnY;
    float                                       mDartPullbackRangeMin;
    float                                       mDartPullbackRangeMax;
    float                                       mDartPullbackGrabRangeSquared;
    float                                       mDartTargetPullX;
    float                                       mDartTargetPullY;
    float                                       mDartPullX;
    float                                       mDartPullY;
    float                                       mDartTargetPullRotation;
    float                                       mDartPullRotation;
    
    bool                                        mIsDartBeingPulled;
    void                                        *mDartTouch;
    float                                       mDartTouchStartX;
    float                                       mDartTouchStartY;
    
    /////////////////////////////////////////////
    
    float                                       mPlayAreaTop;
    float                                       mPlayAreaRight;
    float                                       mPlayAreaBottom;
    float                                       mPlayAreaLeft;
    
    
    float                                       mGameAreaTop;
    float                                       mGameAreaRight;
    float                                       mGameAreaBottom;
    float                                       mGameAreaLeft;
    
    // This is the region where collisions are permitted...
    float                                       mHitZoneTop;
    float                                       mHitZoneRight;
    float                                       mHitZoneBottom;
    float                                       mHitZoneLeft;
    
    //
    float                                       mSpawnZoneTop;
    float                                       mSpawnZoneRight;
    float                                       mSpawnZoneBottom;
    float                                       mSpawnZoneLeft;
    
    
    // Once darts, items, etc get into this area, they
    // are automatically killed. "Out of bounds"
    float                                       mKillZoneTop;
    float                                       mKillZoneRight;
    float                                       mKillZoneBottom;
    float                                       mKillZoneLeft;
    bool                                        IsGameObjectOutsideKillZone(GameObject *pObject);
    
    
    
    
    
};

extern Game *gGame;

#endif

