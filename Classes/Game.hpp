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
#include "GameLevelController.hpp"
#include "FloatingCamera.hpp"
#include "Dart.hpp"
#include "Balloon.hpp"
#include "Bomb.hpp"
#include "Turtle.hpp"
#include "BrickHead.hpp"
#include "Level.hpp"
#include "LevelData.hpp"
#include "LevelPath.hpp"
#include "Transform2D.hpp"
#include "Transform3D.hpp"
#include "GameInfoOverlay.hpp"
#include "HangingThread.hpp"
#include "GameOverlay.hpp"

#define GAME_WIDTH 768
#define GAME_HEIGHT 1280

class Game : public FCanvas {
public:
    Game();
    virtual ~Game();
    
    virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight) override;
    
    virtual void                                LayoutTransform() override;
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
    
    bool                                        IsWaveClearForSpawn();
    bool                                        IsScreenClearForSpawn(bool pIncludePerms);
    
    void                                        Convert2DTransformTo3D(Transform2D *p2D, Transform3D *p3D);
    
    FVec3                                       Convert2DCoordsTo3D(float pX, float pY);
    float                                       Convert2DXTo3D(float pX);
    float                                       Convert2DYTo3D(float pY);
    
    FVec2                                       Convert3DCoordsTo2D(float pX, float pY);
    float                                       Convert3DXTo2D(float pX);
    float                                       Convert3DYTo2D(float pY);
    
    void                                        DisposeObject(GameObject *pObject);
    
    void                                        DisposeObjectFromLevelData(GameObject *pObject);
    
    void                                        FlyOffEscape(GameObject *pObject);
    void                                        DartFlyOffScreen(Dart *pDart);
    
    void                                        StuckDartBeginFadeOut(Dart *pDart);
    void                                        StuckDartFinishFadeOut(Dart *pDart);
    
    void                                        DartCollideWithBalloon(Dart *pDart, Balloon *pBalloon);
    void                                        DartCollideWithBrickhead(Dart *pDart, BrickHead *pBrickHead);
    void                                        DartMovingInterpolation(Dart *pDart, float pPercent, bool pEnd);
    
    //Mainly used by editor to "flush" screen before re-spawn...
    void                                        DisposeAllObjects();
    
    GameInfoOverlay                             *mTestOverlay;
    
    
    float                                       mRenderShiftX;
    float                                       mRenderShiftY;
    
    LevelData                                   *mLevelData;
    GameLevelController                         *mLevelController;
    
    GameRenderer                                *mRenderer;
    FloatingCamera                              *mCamera;
    
    float                                       mGravity;
    
    FObjectList                                 mDartList;
    FObjectList                                 mBalloonList;
    FObjectList                                 mBrickHeadList;
    FObjectList                                 mBombList;
    FObjectList                                 mTurtleList;
    
    Dart                                        *mCurrentDart;
    int                                         mCurrentDartRespawnTimer;
    
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
    
    float                                       mPlayAreaTop;
    float                                       mPlayAreaRight;
    float                                       mPlayAreaBottom;
    float                                       mPlayAreaLeft;
    
    float                                       mGameAreaTop;
    float                                       mGameAreaRight;
    float                                       mGameAreaBottom;
    float                                       mGameAreaLeft;
    
    //
    // This is the region where collisions are permitted...
    //
    float                                       mHitZoneTop;
    float                                       mHitZoneRight;
    float                                       mHitZoneBottom;
    float                                       mHitZoneLeft;
    
    float                                       mSpawnZoneTop;
    float                                       mSpawnZoneRight;
    float                                       mSpawnZoneBottom;
    float                                       mSpawnZoneLeft;
    
    float                                       mPeekZoneTop;
    float                                       mPeekZoneRight;
    float                                       mPeekZoneLeft;
    
    float                                       mQuarterZoneTop;
    float                                       mQuarterZoneRight;
    float                                       mQuarterZoneLeft;
    float                                       mQuarterZoneBottom;
    
    float                                       mExitZoneTop;
    float                                       mExitZoneRight;
    float                                       mExitZoneLeft;
    
    //
    // Once darts, items, etc get into this area, they
    // are automatically killed. "Out of bounds"
    //
    float                                       mKillZoneTop;
    float                                       mKillZoneRight;
    float                                       mKillZoneBottom;
    float                                       mKillZoneLeft;
    bool                                        IsGameObjectOutsideKillZone(GameObject *pObject);
    
    void                                        Load();
    void                                        LoadEditorTest();
    
    LevelSection                                mTestSection;
    
    bool                                        mSlowMo;
    int                                         mSlowMoTimer;
    
    
    int                                         mScore;
    
    int                                         mLives;
    int                                         mLivesMax;
    
    int                                         mPoppedCount;
    int                                         mThrownCount;
    int                                         mThrownHitCount;
    int                                         mThrownMissedCount;
    
    int                                         mEscapedCount;
    
    float                                       mTestBalloonRotX;
    float                                       mTestBalloonRotY;
    float                                       mTestBalloonRotZ;
    
    
    float                                       mWind;
    float                                       mWindSin;
    
    int                                         mPopSoundDelay;
    
    
};

extern Game *gGame;

#endif

