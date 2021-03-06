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
#include "FreeLife.hpp"
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
#include "GameOverlayEffects.hpp"
#include "GameOverlayInterface.hpp"
#include "WindSpeedSimulator.hpp"


#define GAME_WIDTH 768
#define GAME_HEIGHT 1280


#define GAME_PLAYBACK_XXX_SLOW 0
#define GAME_PLAYBACK_XX_SLOW 1
#define GAME_PLAYBACK_X_SLOW 2
#define GAME_PLAYBACK_SLOW 3
#define GAME_PLAYBACK_NORMAL 4
#define GAME_PLAYBACK_FAST 5
#define GAME_PLAYBACK_X_FAST 6
#define GAME_PLAYBACK_XX_FAST 7
#define GAME_PLAYBACK_XXX_FAST 8




class Game : public FCanvas {
public:
    Game();
    virtual ~Game();
    
    virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight) override;
    
    virtual void                                LayoutTransform() override;
    virtual void                                Layout() override;
    virtual void                                Update() override;
    void                                        UpdateMainLoop();
    
    
    virtual void                                Draw() override;
    
    void                                        Draw3D();
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    
    void                                        Clear();
    
    bool                                        IsWaveClearForSpawn();
    bool                                        IsScreenClearForSpawn(bool pIncludePerms);
    bool                                        IsAnyObjectFloatingAway();
    int                                         mRecentFloatingAwayTick;
    
    // Note: This is intended to be used for preliminary check (FROM EDITOR)...
    //When computing actual progress count, there will need to be
    //foreknowledge about which replacements will occur. For example,
    //a "free life" in editor does not count towards progress, but if a replacement occurs,
    //then total progress cannot include the object (balloon replaced by free life, as an example)
    bool                                        DoesObjectTypeCountTowardsProgressCount(int pObjectType);
    
    bool                                        DoesObjectTypeCountTowardsProgress(int pObjectType);
    
    bool                                        DoesObjectTypeRequireClearing(int pObjectType);
    
    
    void                                        Convert2DTransformTo3D(Transform2D *p2D, Transform3D *p3D);
    
    FVec3                                       Convert2DCoordsTo3D(float pX, float pY);
    float                                       Convert2DXTo3D(float pX);
    float                                       Convert2DYTo3D(float pY);
    
    FVec2                                       Convert3DCoordsTo2D(float pX, float pY);
    float                                       Convert3DXTo2D(float pX);
    float                                       Convert3DYTo2D(float pY);
    
    void                                        DisposeObject(GameObject *pObject);
    void                                        DisposeObjectFromLevelData(GameObject *pObject);
    
    //Mainly used by editor to "flush" screen before re-spawn...
    void                                        DisposeAllObjects();
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    ////
    ////             These are "events" which occur in certain object's life cycles...
    ////
    void                                        FlyOffEscape(GameObject *pObject);
    
    //Generally these are only going to be bricks to start..?
    void                                        KnockDown(GameObject *pObject);
    
    
    void                                        StuckDartBeginFadeOut(Dart *pDart);
    void                                        StuckDartFinishFadeOut(Dart *pDart);
    
    void                                        DartCollideWithBalloon(Dart *pDart, Balloon *pBalloon);
    void                                        DartCollideWithBrickhead(Dart *pDart, BrickHead *pBrickHead);
    void                                        DartCollideWithTurtle(Dart *pDart, Turtle *pTurtle);
    void                                        DartCollideWithFreeLife(Dart *pDart, FreeLife *pFreeLife);
    
    void                                        PopBalloon(Balloon *pBalloon);
    
    void                                        TurtleDidLoseBalloon(Turtle *pTurtle);
    
    ////
    ////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void                                        DartMovingInterpolationTurtles(Dart *pDart, float pPercent, bool pEnd);
    void                                        DartMovingInterpolationBrickHeads(Dart *pDart, float pPercent, bool pEnd);
    void                                        DartMovingInterpolationBalloons(Dart *pDart, float pPercent, bool pEnd);
    void                                        DartMovingInterpolationFreeLives(Dart *pDart, float pPercent, bool pEnd);
    
    
    bool                                        ShouldSpawnFreeLife();
    void                                        NotifyDidSpawnFreeLife();
    
    
    
    GameInfoOverlay                             *mTestOverlay;
    
    
    float                                       mRenderShiftX;
    float                                       mRenderShiftY;
    
    LevelData                                   *mLevelData;
    //GameLevelController                         *mLevelController;
    
    
    GameRenderer                                *mRenderer;
    FloatingCamera                              *mCamera;
    
    WindSpeedSimulator                          mWind;
    
    float                                       mGravity;
    
    FObjectList                                 mDartList;
    FObjectList                                 mBalloonList;
    FObjectList                                 mFreeLifeList;
    FObjectList                                 mBrickHeadList;
    FObjectList                                 mTurtleList;
    FObjectList                                 mBombList;
    
    
    Dart                                        *mCurrentDart;
    int                                         mCurrentDartRespawnTimer;
    
    void                                        ResetDartTouch();
    void                                        ReleaseDart();
    
    
    bool                                        mTrajectoryExists;
    float                                       mTrajectoryReleaseDirX;
    float                                       mTrajectoryReleaseDirY;
    float                                       mTrajectoryReleaseVelocity;
    FPointList                                  mTrajectoryList;
    
    
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
    
    int                                         mProgressCount;
    int                                         mProgress;
    
    int                                         mPoppedCount;
    int                                         mThrownCount;
    int                                         mThrownHitCount;
    int                                         mThrownMissedCount;
    
    int                                         mEscapedCount;
    
    int                                         mPopSoundDelay;
    
    
    
    
};

extern Game *gGame;

#endif

