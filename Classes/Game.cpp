//
//  Game.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "core_includes.h"
#include "Game.hpp"
#include "GameContainer.hpp"
#include "FAnimation.hpp"
#include "StuckDart.hpp"

#include "EffectDartFadeStar.hpp"
#include "EffectBalloonBurst.hpp"

#ifdef EDITOR_MODE
#include "GameEditor.hpp"
#endif


Game *gGame = NULL;

Game::Game() {
    
    mName = "[Game]";
    
    gGame = this;
    
    mTestOverlay = NULL;
    
    mRenderShiftX = 0.0f;
    mRenderShiftY = 0.0f;
    
    SetWidth(GAME_WIDTH);
    SetHeight(GAME_HEIGHT);
    SetTransformAnchor(0.5f, 0.5f);
    
    //mLevelController = new GameLevelController(this);
    mLevelData = NULL;
    
    mProgressCount = 0;
    mProgress = 0;
    
    
    mCamera = new FloatingCamera();
    
    mCamera->mAspect = ((float)GAME_WIDTH) / ((float)GAME_HEIGHT);
    
    mRenderer = new GameRenderer(this, mCamera);
    
    mDartSpawnX = gDeviceWidth2;
    mDartSpawnY = gDeviceHeight2;
    
    mDartReleaseVelocityMin = 12.0f;
    mDartReleaseVelocityMax = 42.0f;
    
    mGravity = 0.24f;
    
    mPlayAreaTop = 0.0f;
    mPlayAreaRight = 0.0f;
    mPlayAreaBottom = 0.0f;
    mPlayAreaLeft = 0.0f;
    
    mGameAreaTop = 0.0f;
    mGameAreaRight = 0.0f;
    mGameAreaBottom = 0.0f;
    mGameAreaLeft = 0.0f;
    
    mHitZoneTop = 0.0f;
    mHitZoneRight = 0.0f;
    mHitZoneBottom = 0.0f;
    mHitZoneLeft = 0.0f;
    
    mSpawnZoneTop = 0.0f;
    mSpawnZoneRight = 0.0f;
    mSpawnZoneBottom = 0.0f;
    mSpawnZoneLeft = 0.0f;
    
    mPeekZoneTop = 0.0f;
    mPeekZoneRight = 0.0f;
    mPeekZoneLeft = 0.0f;
    
    mExitZoneTop = 0.0f;
    mExitZoneRight = 0.0f;
    mExitZoneLeft = 0.0f;
    
    mQuarterZoneTop = 0.0f;
    mQuarterZoneRight = 0.0f;
    mQuarterZoneLeft = 0.0f;
    mQuarterZoneBottom = 0.0f;
    
    mKillZoneTop = 0.0f;
    mKillZoneRight = 0.0f;
    mKillZoneBottom = 0.0f;
    mKillZoneLeft = 0.0f;
    
    mCurrentDart = new Dart();
    mCurrentDartRespawnTimer = 0;
    
    mDartPullbackRangeMin = 4.0f;
    mDartPullbackRangeMax = 160.0f;
    mDartTargetPullX = 0.0f;
    mDartTargetPullY = 0.0f;
    mDartPullX = 0.0f;
    mDartPullY = 0.0f;
    mDartTargetPullRotation = 0.0f;
    mDartPullRotation = 0.0f;
    mDartResetStartPullX = 0.0f;
    mDartResetStartPullY = 0.0f;
    mDartResetStartRotation = 0.0f;
    mDartTouch = NULL;
    mDartTouchStartX = 0.0f;
    mDartTouchStartY = 0.0f;
    mIsDartBeingPulled = false;
    mDartResetAnimation = false;
    mDartResetAnimationTick = 0;
    mDartResetAnimationTime = 200;
    
    mTrajectoryExists = false;
    mTrajectoryReleaseDirX = 0.0f;
    mTrajectoryReleaseDirY = 0.0f;
    mTrajectoryReleaseVelocity = 0.0f;
    //mTrajectoryList
    
    mRecentFloatingAwayTick = 0;
    
    mScore = 0;
    
    mLivesMax = 5;
    mLives = mLivesMax;
    //TODO: Remove mLives = 3;
    mLives = 4;
    
    mPoppedCount = 0;
    
    mThrownHitCount = 0;
    mThrownMissedCount = 0;
    
    mThrownCount = 0;
    mEscapedCount = 0;
    
    mSlowMo = false;
    mSlowMoTimer = 0;
    
    mPopSoundDelay = 0;
}

Game::~Game() {
    if (gGame == this) {
        gGame = NULL;
    }
    
    if (mCamera != NULL) {
        delete mCamera;
        mCamera = NULL;
    }
    
    if (mRenderer != NULL) {
        delete mRenderer;
        mRenderer = NULL;
    }
    
    if (mLevelData != NULL) {
        delete mLevelData;
        mLevelData = NULL;
    }
    
    mProgressCount = 0;
    mProgress = 0;
    
    
    Clear();
    
    mDartList.Free();
    mBalloonList.Free();
    mFreeLifeList.Free();
    mBrickHeadList.Free();
    mTurtleList.Free();
    mBombList.Free();
}



void Game::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    FCanvas::SetFrame(pX, pY, pWidth, pHeight);
    
}

void Game::LayoutTransform() {
    
    if (mCamera) {
        mCamera->mAspect = gDeviceWidth / gDeviceHeight;
        
    }
    
    mDartTouch = NULL;
    
    //We re-compute the center of our game window...
    float aAbsoluteCenterX = gAppBase->mWindowMain.mRoot.mX + gAppBase->mWindowMain.mRoot.mWidth2;
    float aAbsoluteCenterY = gAppBase->mWindowMain.mRoot.mY + gAppBase->mWindowMain.mRoot.mHeight2;
    mCamera->mCenterOffset = FVec2(gDeviceWidth2 - aAbsoluteCenterX, gDeviceHeight2 - aAbsoluteCenterY);
    
    float aGameWidth = mWidth - (gSafeAreaInsetLeft + gSafeAreaInsetRight);
    float aGameHeight = mHeight - (gSafeAreaInsetTop + gSafeAreaInsetBottom);
    
    mDartSpawnX = (int)(gSafeAreaInsetLeft + (aGameWidth / 2.0f) + 0.5f);
    
    float aSpawnShiftY = aGameHeight / 4.0f;
    if (aSpawnShiftY < 70.0f) aSpawnShiftY = 70.0f;
    if (aSpawnShiftY > 240.0f) aSpawnShiftY = 240.0f;
    
    mDartPullbackGrabRangeSquared = aSpawnShiftY * 0.35f;
    if (mDartPullbackGrabRangeSquared < 60.0f) {
        mDartPullbackGrabRangeSquared = 60.0f;
    }
    mDartPullbackGrabRangeSquared = mDartPullbackGrabRangeSquared * mDartPullbackGrabRangeSquared;
    
    mDartSpawnY = (mHeight - gSafeAreaInsetBottom) - aSpawnShiftY;
    
    mDartPullbackRangeMin = aSpawnShiftY * 0.125f;
    if (mDartPullbackRangeMin < 12.0f) { mDartPullbackRangeMin = 12.0f; }
    if (mDartPullbackRangeMin > 28.0f) { mDartPullbackRangeMin = 28.0f; }
    
    mDartPullbackRangeMax = aSpawnShiftY;
    
    float aScreenMinDimension = mWidth;
    if (mHeight < aScreenMinDimension) { aScreenMinDimension = mHeight; }
    
    float aScreenMaxDimension = mWidth;
    if (mHeight > aScreenMaxDimension) { aScreenMaxDimension = mHeight; }
    
    mCamera->mDistance = 20.0f;
    
    for (int aCalibrationLoops=0;aCalibrationLoops<2048;aCalibrationLoops++) {
        
        // The algebra for this conversion does not
        // seem to work out, se we calibrate the camera
        // by easing towards the best distance...
        
        float aTestSceneLeft = Convert2DXTo3D(0.0f);
        float aTestSceneRight = Convert2DXTo3D(mWidth);
        //float aExpectedWidth = 34.0f;
        float aExpectedWidth = 40.0f;
        
        float aActualWidth = (aTestSceneRight - aTestSceneLeft);
        if (aActualWidth < aExpectedWidth) {
            mCamera->mDistance += 0.05f;
        } else {
            mCamera->mDistance -= 0.05f;
        }
    }
    
    //Keep in mind, the hit zone we are expanding based on screen size...
    float aHitZonePaddingH = 12.0f;
    float aHitZonePaddingV = 60.0f;
    
    mHitZoneTop = Convert2DYTo3D(-aHitZonePaddingV);
    mHitZoneRight = Convert2DXTo3D(mWidth + aHitZonePaddingH);
    mHitZoneBottom = Convert2DYTo3D(mHeight + aHitZonePaddingV);
    mHitZoneLeft = Convert2DXTo3D(-aHitZonePaddingH);
    
    
    mGameAreaTop = 0.0f;
    mGameAreaRight = mWidth;
    mGameAreaBottom = mHeight;
    mGameAreaLeft = 0.0f;
    
    
    float aPlayAreaPadding = mWidth;
    if (mHeight < mWidth) aPlayAreaPadding = mHeight;
    
    aPlayAreaPadding = aPlayAreaPadding * 0.065f;
    //Log("aPlayAreaPadding = %f\n", aPlayAreaPadding);
    
    if (aPlayAreaPadding < 24.0f) {
        aPlayAreaPadding = 24.0f;
    }
    
    mPlayAreaTop = gSafeAreaInsetTop + aPlayAreaPadding;
    mPlayAreaRight = (mWidth - gSafeAreaInsetRight) - aPlayAreaPadding;
    mPlayAreaBottom = mDartSpawnY - aPlayAreaPadding;
    mPlayAreaLeft = gSafeAreaInsetLeft + aPlayAreaPadding;
    
    float aSpawnZonePadding = 100.0f;
    mSpawnZoneTop = -aSpawnZonePadding;
    mSpawnZoneRight = mWidth + aSpawnZonePadding;
    mSpawnZoneBottom = mHeight;
    mSpawnZoneLeft = -aSpawnZonePadding;
    
    float aPeekZonePaddingTop = 88.0f;
    float aPeekZonePaddingSides = 60.0f;
    mPeekZoneTop = aPeekZonePaddingTop;
    mPeekZoneRight = mWidth - aPeekZonePaddingSides;
    mPeekZoneLeft = aPeekZonePaddingSides;
    
    float aQuarterZoneHeight = mPlayAreaBottom;
    mQuarterZoneTop = aQuarterZoneHeight / 4.0f;
    mQuarterZoneRight = mWidth - mWidth / 4.0f;
    mQuarterZoneLeft = mWidth / 4.0f;
    mQuarterZoneBottom = mPlayAreaBottom - aQuarterZoneHeight / 4.0f;
    
    float aExitZonePaddingTop = aPeekZonePaddingTop + 100.0f;
    float aExitZonePaddingSides = aPeekZonePaddingSides + 100.0f;
    mExitZoneTop = -aExitZonePaddingTop;
    mExitZoneRight = mWidth + aExitZonePaddingSides;
    mExitZoneLeft = -aExitZonePaddingSides;
    
    float aKillZonePaddingTop = ((float)GAME_HEIGHT) * 2.0f;
    float aKillZonePaddingBottom = ((float)GAME_HEIGHT) * 0.25f;
    float aKillZonePaddingSides = ((float)GAME_WIDTH) * 0.25f + 200.0f;
    mKillZoneTop = -aKillZonePaddingTop;
    mKillZoneRight = mWidth + aKillZonePaddingSides;
    mKillZoneBottom = mHeight + aKillZonePaddingBottom;
    mKillZoneLeft = -aKillZonePaddingSides;
    
    if (mRenderer) {
        mRenderer->ScreenBoundaryRefresh();
    }
    
    //ScreenBoundaryRefresh()
}

void Game::Layout() {
    
    //TODO: This is only for build mode.
    
    
    if (mRenderer) {
        //mRenderer->ScreenBoundaryRefresh();
        
    }
}

void Game::Update() {
    
}

void Game::UpdateMainLoop() {
    
    bool aShowOverlay = true;
#ifdef EDITOR_MODE
    if (gEditor == NULL) {
        aShowOverlay = false;
    }
#endif
    
    
    if (mPopSoundDelay > 0) { mPopSoundDelay--; }
    if (mRecentFloatingAwayTick > 0) { mRecentFloatingAwayTick--; }
    
    if (aShowOverlay) {
        if (mTestOverlay == NULL) {
            
            mTestOverlay = new GameInfoOverlay();
            AddChild(mTestOverlay);
            
        }
        
    }
    
    if (mTestOverlay != NULL) {
        mTestOverlay->SetFrame(0.0f, 0.0f, mWidth, mHeight);
    }
    
    
    if (mSlowMo == true) {
        
        ++mSlowMoTimer;
        if (mSlowMoTimer < 5) {
            return;
        } else {
            mSlowMoTimer = 0;
        }
    }
    
    if (mLevelData != NULL) {
        mLevelData->Update();
    }
    
    if (mDartResetAnimation) {
        mDartResetAnimationTick += 1;
        if (mDartResetAnimationTick >= mDartResetAnimationTime) {
            ResetDartTouch();
        } else {
            float aAnimationPercent = ((float)mDartResetAnimationTick) / ((float)mDartResetAnimationTime);
            float aSnapbackPercent = FAnimation::EaseOutBack(aAnimationPercent, 0.25f);
            aSnapbackPercent = 1.0f - aSnapbackPercent;
            
            mDartPullX = mDartResetStartPullX * aSnapbackPercent;
            mDartPullY = mDartResetStartPullY * aSnapbackPercent;
            
            float aRotationPercent = FAnimation::EaseOutBack(aAnimationPercent, 0.25f);
            mDartPullRotation = mDartResetStartRotation + mDartResetRotationLength * aRotationPercent;
        }
    }
    
    EnumList (FreeLife, aFreeLife, mFreeLifeList.mObjectList) {
        if (aFreeLife->mKill == 0) {
            if (aFreeLife->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList(Balloon, aBalloon, mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0) {
            if (aBalloon->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList(Turtle, aTurtle, mTurtleList.mObjectList) {
        if (aTurtle->mKill == 0) {
            if (aTurtle->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList(BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
        if (aBrickHead->mKill == 0) {
            if (aBrickHead->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList(Bomb, aBomb, mBombList.mObjectList) {
        if (aBomb->mKill == 0) {
            if (aBomb->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    if (mCurrentDart) {
        mCurrentDart->Update();
    } else {
        if (--mCurrentDartRespawnTimer <= 0) {
            mCurrentDartRespawnTimer = 0;
            mCurrentDart = new Dart();
            
            mCurrentDart->mTransform.mX = mDartSpawnX;
            mCurrentDart->mTransform.mY = mDartSpawnY;
            
            mCurrentDart->SpawnAnimation();
        }
    }
    
    mDartList.Update();
    mBalloonList.Update();
    mFreeLifeList.Update();
    mBrickHeadList.Update();
    mBombList.Update();
    mTurtleList.Update();
    
    //New thing, the dart now moves small increments and tries to collide.
    for (int i=0;i<mDartList.mObjectList.mCount;i++) {
        Dart *aDart = (Dart *)mDartList.mObjectList.mData[i];
        
        for (float aPercent=0.0f;aPercent<1.0f;aPercent+=0.025f) {
            if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
                DartMovingInterpolationTurtles(aDart, aPercent, false);
            }
        }
        if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
            DartMovingInterpolationTurtles(aDart, 1.0, true);
        }
        
        
        for (float aPercent=0.0f;aPercent<1.0f;aPercent+=0.025f) {
            if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
                DartMovingInterpolationBrickHeads(aDart, aPercent, false);
            }
        }
        if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
            DartMovingInterpolationBrickHeads(aDart, 1.0, true);
        }
        
        
        for (float aPercent=0.0f;aPercent<1.0f;aPercent+=0.025f) {
            if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
                DartMovingInterpolationBalloons(aDart, aPercent, false);
            }
        }
        if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
            DartMovingInterpolationBalloons(aDart, 1.0, true);
        }
        
        
        for (float aPercent=0.0f;aPercent<1.0f;aPercent+=0.025f) {
            if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
                DartMovingInterpolationFreeLives(aDart, aPercent, false);
            }
        }
        if ((aDart->mIdle == false) && (aDart->mKill == 0) && (aDart->mStuck == false) && (aDart->mKnockedDown == false)) {
            DartMovingInterpolationFreeLives(aDart, 1.0, true);
        }
    }
    
    if (mDartTouch != NULL && mDartResetAnimation == false) {
        float aDiffX = mDartTargetPullX - mDartPullX;
        float aDiffY = mDartTargetPullY - mDartPullY;
        float aLength = aDiffX * aDiffX + aDiffY * aDiffY;
        float aLengthFactor = 0.175f;
        if (aLength > SQRT_EPSILON) {
            aLength = sqrtf(aLength);
            aDiffX /= aLength;
            aDiffY /= aLength;
            float aMoveDist = aLength / 7.0f + 3.5f;
            if (aMoveDist >= aLength) {
                mDartPullX = mDartTargetPullX;
                mDartPullY = mDartTargetPullY;
            } else {
                mDartPullX += aDiffX * aMoveDist;
                mDartPullY += aDiffY * aMoveDist;
            }
            aLengthFactor = aLength / (mDartPullbackRangeMin * 2.0f);
            if (aLengthFactor > 1.5f) {
                aLengthFactor = 1.5f;
            }
            
        } else {
            mDartPullX = mDartTargetPullX;
            mDartPullY = mDartTargetPullY;
        }
        
        float aAngleDiff = DistanceBetweenAngles(mDartPullRotation, mDartTargetPullRotation);
        if (aAngleDiff > 2.0f) {
            mDartPullRotation += 1.0f;
        }
        if (aAngleDiff < -2.0f) {
            mDartPullRotation -= 1.0f;
        }
        aAngleDiff = DistanceBetweenAngles(mDartPullRotation, mDartTargetPullRotation);
        mDartPullRotation += aAngleDiff * 0.32f * aLengthFactor;
    }
    
    //So... to correct perspective distortion for rotation, we need to convert
    //our pull vector into "scene" coords, and adjust the rotation accordingly...
    
    if (mCurrentDart) {
        //FVec3 aDartPos = Convert2DCoordsTo3D(mDartSpawnX + mDartPullX, mDartSpawnY + mDartPullY);
        mCurrentDart->mTransform.mX = mDartSpawnX + mDartPullX;
        mCurrentDart->mTransform.mY = mDartSpawnY + mDartPullY;
        mCurrentDart->mTransform.mRotation = mDartPullRotation;
    }
    
    
    mTrajectoryExists = false;
    
    if ((mCurrentDart != NULL) && (mIsDartBeingPulled == true)) {
        
        //How much kapow do we give this dart?
        float aReleaseFactor = 0.0f;
        
        mTrajectoryReleaseDirX = -mDartPullX;
        mTrajectoryReleaseDirY = -mDartPullY;
        
        float aPullLength = mTrajectoryReleaseDirX * mTrajectoryReleaseDirX + mTrajectoryReleaseDirY * mTrajectoryReleaseDirY;
        if (aPullLength > SQRT_EPSILON) {
            mTrajectoryExists = true;
            
            aPullLength = (float)(sqrtf(aPullLength));
            
            mTrajectoryReleaseDirX /= aPullLength;
            mTrajectoryReleaseDirY /= aPullLength;
            
            aReleaseFactor = (aPullLength - mDartPullbackRangeMin) / (mDartPullbackRangeMax - mDartPullbackRangeMin);
            aReleaseFactor *= 1.10f;
            if (aReleaseFactor < 0.0f) aReleaseFactor = 0.0f;
            if (aReleaseFactor > 1.0f) aReleaseFactor = 1.0f;
            
            aReleaseFactor = FAnimation::EaseInCirc(aReleaseFactor) * 0.5f + aReleaseFactor * 0.5f;
            
            mTrajectoryReleaseVelocity = mDartReleaseVelocityMin + (mDartReleaseVelocityMax - mDartReleaseVelocityMin) * aReleaseFactor;
            
            float aTrajectoryX = mCurrentDart->mTransform.mX;
            float aTrajectoryY = mCurrentDart->mTransform.mY;
            
            float aTrajectoryVelocityX = mTrajectoryReleaseDirX * mTrajectoryReleaseVelocity;
            float aTrajectoryVelocityY = mTrajectoryReleaseDirY * mTrajectoryReleaseVelocity;
            
            float aTrajectoryTargetRotation = FaceTarget(-aTrajectoryVelocityX, -aTrajectoryVelocityY);
            float aTrajectoryRotation = aTrajectoryTargetRotation;
            
            float aAngleDiff = 0.0f;
            
            float aTipX = 0.0f;
            float aTipY = 0.0f;
            
            mCurrentDart->GetTipPoint(aTrajectoryX, aTrajectoryY, 1.0f, aTrajectoryRotation, aTipX, aTipY);
            
            bool aLoop = true;
            
            mTrajectoryList.Reset();
            while (aLoop == true) {
                mTrajectoryList.Add(aTipX, aTipY);
                aTrajectoryVelocityY += mGravity;
                
                if (fabsf(aTrajectoryVelocityX) > 0.001f || fabsf(aTrajectoryVelocityY) > 0.001f) {
                    aTrajectoryTargetRotation = FaceTarget(-aTrajectoryVelocityX, -aTrajectoryVelocityY);
                }
                
                aAngleDiff = DistanceBetweenAngles(aTrajectoryRotation, aTrajectoryTargetRotation);
                if (aAngleDiff > 2.0f) { aTrajectoryRotation += 1.0f; }
                if (aAngleDiff < -2.0f) { aTrajectoryRotation -= 1.0f; }
                aAngleDiff = DistanceBetweenAngles(aTrajectoryRotation, aTrajectoryTargetRotation);
                aTrajectoryRotation += aAngleDiff * 0.035f;
                aTrajectoryX += aTrajectoryVelocityX;
                aTrajectoryY += aTrajectoryVelocityY;
                
                mCurrentDart->GetTipPoint(aTrajectoryX, aTrajectoryY, 1.0f, aTrajectoryRotation, aTipX, aTipY);
                
                if ((aTrajectoryX < mKillZoneLeft) || (aTrajectoryX > mKillZoneRight) || (aTrajectoryY < mKillZoneTop) || (aTrajectoryY > mKillZoneBottom)) {
                    break;
                }
            }
        }
    }
    
    if (mDartList.mObjectList.mCount == 0 && mTrajectoryList.mCount > 0 && mIsDartBeingPulled == false) {
        mTrajectoryList.RemoveAll();
    }
    
    mWind.Update();
}

void Game::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor();
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor(0.125f, 0.5f, 0.35f, 0.075f);
    Graphics::SetColor(0.825f, 0.5f, 0.35f, 0.25f);
    
    Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 20.0f);
    Graphics::SetColor();

    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor();
    
    /*
     Graphics::PipelineStateSetShape2DAlphaBlending();
     Graphics::SetColor(0.66f, 0.25f, 0.25f, 0.66f);
     Graphics::DrawPoint(mDartSpawnX, mDartSpawnY, 8.0f);
     Graphics::DrawLine(mDartSpawnX, mDartSpawnY, mDartSpawnX + mDartPullX, mDartSpawnY + mDartPullY);
     for (float aAngle = 0.0f;aAngle < 360.0f; aAngle += 6.0f) {
     Graphics::SetColor(0.75f + (aAngle / 360.0f) * 0.25f, (aAngle / 360.0f) * 0.25f, 0.65f, 0.32f);
     FVec2 aDir = AngleToVector(aAngle);
     Graphics::DrawLine(mDartSpawnX, mDartSpawnY, mDartSpawnX + aDir.mX * sqrtf(mDartPullbackGrabRangeSquared), mDartSpawnY + aDir.mY * sqrtf(mDartPullbackGrabRangeSquared));
     }
     */
    
    
    mBrickHeadList.Draw();
    mBalloonList.Draw();
    mFreeLifeList.Draw();
    mDartList.Draw();
    mTurtleList.Draw();
    mBombList.Draw();
    
    if (mCurrentDart) {
        mCurrentDart->Draw();
    }
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor();
    //
    
    /*
     FSprite *aDart = &(gApp->mRay[3]);
     if (mIsDartBeingPulled) Graphics::SetColor(1.0f, 0.5f, 0.5f, 1.0f);
     aDart->Draw(mDartSpawnX + mDartPullX, mDartSpawnY + mDartPullY,
     1.5f, mDartPullRotation + 180.0f);
     */
    
    
    /*
     float aIndicatorCenterX = mDartSpawnX - mWidth * 0.1f;
     float aIndicatorCenterY = mDartSpawnY;
     
     float aIndicatorWidth = 30.0f;
     float aIndicatorHeight = 100.0f;
     
     float aIndicatorX = aIndicatorCenterX - (aIndicatorWidth / 2.0f);
     float aIndicatorY = aIndicatorCenterY - (aIndicatorHeight / 2.0f);
     
     Graphics::PipelineStateSetShape2DNoBlending();
     
     Graphics::SetColor(0.66f, 0.66f, 0.66f, 0.35f);
     Graphics::DrawRect(aIndicatorX - 2.0f, aIndicatorY - 2.0f, aIndicatorWidth + 4.0f, aIndicatorHeight + 4.0f);
     
     if (mIsDartBeingPulled) {
     Graphics::SetColor(0.045f, 0.045f, 0.0626f, 0.45f);
     } else {
     Graphics::SetColor(0.045f, 0.045f, 0.1226f, 0.45f);
     }
     Graphics::DrawRect(aIndicatorX, aIndicatorY, aIndicatorWidth, aIndicatorHeight);
     
     float aPullLength = mDartPullX * mDartPullX + mDartPullY * mDartPullY;
     float aPullPercent = 0.0f;
     if (aPullLength > SQRT_EPSILON) {
     aPullLength = (float)(sqrtf(aPullLength));
     aPullPercent = (aPullLength - mDartPullbackRangeMin) / (mDartPullbackRangeMax - mDartPullbackRangeMin);
     }
     aPullPercent *= 1.10f;
     if (aPullPercent > 1.0f) aPullPercent = 1.0f;
     if (aPullPercent < 0.0f) aPullPercent = 0.0f;
     aPullPercent = FAnimation::EaseInCirc(aPullPercent) * 0.5f + aPullPercent * 0.5f;
     
     if (mIsDartBeingPulled) {
     Graphics::SetColor(1.0f, 0.35f, 0.25f, 0.525f);
     float aPowerBarHeight = aPullPercent * aIndicatorHeight;
     float aPowerBarY = (aIndicatorY + aIndicatorHeight) - aPowerBarHeight;
     Graphics::DrawRect(aIndicatorX, aPowerBarY, aIndicatorWidth, aPowerBarHeight);
     } else {
     
     }
     */
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    if (gApp->mDarkMode) {
        Graphics::SetColor(1.0f, 1.0f, 1.0f);
    } else {
        Graphics::SetColor(1.0f, 1.0f, 0.20f);
    }
    
    
    for (int i=0;i<mTrajectoryList.mCount;i++) {
        float aX = mTrajectoryList.mX[i];
        float aY = mTrajectoryList.mY[i];
        Graphics::DrawPoint(aX, aY, 3.0f);
    }
}

void Game::Draw3D() {
    if (mRenderer) {
        mRenderer->Draw3D();
    }
}




void Game::TouchDown(float pX, float pY, void *pData) {
    
    if ((gGameContainer != NULL) && (gGameContainer->mPaused == true)) {
        TouchFlush();
        return;
    }
    
    if (gTouch.mTouchCount >= 3) {
        Log("Hack: Killing all balloons..!");
        
        FList aList;
        EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
            aList.Add(aObject);
        }
        
        EnumList(GameObject, aObject, gGame->mFreeLifeList.mObjectList) {
            aList.Add(aObject);
        }
        EnumList(GameObject, aObject, aList) {
            DisposeObject(aObject);
        }
    }
    
    if (mDartTouch) {
        ResetDartTouch();
        return;
    }
    
    if (mDartTouch == NULL && mDartResetAnimation == false && mCurrentDart != NULL) {
        float aDistanceSquared = DistanceSquared(pX, pY, mDartSpawnX, mDartSpawnY);
        if (aDistanceSquared <= mDartPullbackGrabRangeSquared) {
            mDartTouch = pData;
            mDartTouchStartX = mDartSpawnX;
            mDartTouchStartY = mDartSpawnY;
            mDartTargetPullX = 0.0f;
            mDartTargetPullY = 0.0f;
            mDartPullX = 0.0f;
            mDartPullY = 0.0f;
            mDartTargetPullRotation = 0.0f;
            mDartPullRotation = 0.0f;
            mIsDartBeingPulled = false;
            mCurrentDart->SpawnAnimationForceComplete();
        }
    }
}

void Game::TouchMove(float pX, float pY, void *pData) {
    
    if ((gGameContainer != NULL) && (gGameContainer->mPaused == true)) {
        TouchFlush();
        return;
    }
    
    if (mDartTouch == pData && mDartTouch != NULL) {
        float aDiffX = pX - mDartTouchStartX;
        float aDiffY = pY - mDartTouchStartY;
        float aDistanceSquared = aDiffX * aDiffX + aDiffY * aDiffY;
        if (aDistanceSquared > (mDartPullbackRangeMin * mDartPullbackRangeMin)) {
            
            if (mIsDartBeingPulled == false) {
                mIsDartBeingPulled = true;
                gApp->mSoundDartPullback.Play();
            }
            
            float aLength = aDiffX * aDiffX + aDiffY * aDiffY;
            if (aLength > SQRT_EPSILON) {
                aLength = sqrtf(aLength);
                if (aLength > mDartPullbackRangeMax) {
                    aDiffX /= aLength;
                    aDiffY /= aLength;
                    aDiffX *= mDartPullbackRangeMax;
                    aDiffY *= mDartPullbackRangeMax;
                }
            }
            mDartTargetPullX = aDiffX;
            mDartTargetPullY = aDiffY;
            mDartTargetPullRotation = FaceTarget(aDiffX, aDiffY);
            //mDartTargetPullRotation = -90.0f;
            
            
        } else {
            mIsDartBeingPulled = false;
            mDartTargetPullX = 0.0f;
            mDartTargetPullY = 0.0f;
            mDartTargetPullRotation = 0.0f;
        }
    }
}

void Game::TouchUp(float pX, float pY, void *pData) {
    
    if ((gGameContainer != NULL) && (gGameContainer->mPaused == true)) {
        TouchFlush();
        return;
    }
    
    if (mDartTouch) {
        if (mIsDartBeingPulled) {
            ReleaseDart();
        } else {
            ResetDartTouch();
        }
    }
}

void Game::TouchFlush() {
    ResetDartTouch();
}

void Game::KeyDown(int pKey) {
    
#ifdef EDITOR_MODE
    if (gEditor != NULL) {
        return;
    }
#endif
    
    
    if (gKeyDownCtrl) {
        if (pKey == __KEY__R) {
            DisposeAllObjects();
            if (mLevelData != NULL) {
                delete mLevelData;
                mLevelData = NULL;
            }
#ifndef EDITOR_MODE
            Load();
#else
            LoadEditorTest();
#endif
        }
        
        if (pKey == __KEY__W) {
            
            EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            
        }
        
        if (pKey == __KEY__P) {
            
            EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            
            
        }
        
        if (pKey == __KEY__K) {
            
            EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
                DisposeObject(aObject);
            }
            EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
                DisposeObject(aObject);
            }
            
        }
        
    }
    
    if (gKeyDownShift) {
        
        if (pKey == __KEY__W) {
            
            EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mDartList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mBrickHeadList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mTurtleList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mBombList.mObjectList) {
                if (aObject->mDidOriginateOnWave == true) { DisposeObject(aObject); }
            }
            
        }
        
        if (pKey == __KEY__P) {
            
            EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mDartList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mBrickHeadList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mTurtleList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            EnumList(GameObject, aObject, gGame->mBombList.mObjectList) {
                if (aObject->mDidOriginateAsPermanent == true) { DisposeObject(aObject); }
            }
            
        }
        
        if (pKey == __KEY__K) {
            
            EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
                DisposeObject(aObject);
            }
            EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
                DisposeObject(aObject);
            }
            EnumList(GameObject, aObject, gGame->mDartList.mObjectList) {
                DisposeObject(aObject);
            }
            EnumList(GameObject, aObject, gGame->mBrickHeadList.mObjectList) {
                DisposeObject(aObject);
            }
            EnumList(GameObject, aObject, gGame->mTurtleList.mObjectList) {
                DisposeObject(aObject);
            }
            EnumList(GameObject, aObject, gGame->mBombList.mObjectList) {
                DisposeObject(aObject);
            }
            
        }
        
    }
    
    if (pKey == __KEY__L) {
        if (gKeyDownCtrl) {
            mLives++;
            if (gInterfaceOverlay != NULL) { gInterfaceOverlay->NotifyLivesChanged(); }
        }
    }
    
    
    if (pKey == __KEY__D) {
        
        EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
            KnockDown(aObject);
        }
        EnumList(FreeLife, aObject, gGame->mFreeLifeList.mObjectList) {
            KnockDown(aObject);
        }
        EnumList(GameObject, aObject, gGame->mDartList.mObjectList) {
            KnockDown(aObject);
        }
        EnumList(GameObject, aObject, gGame->mBrickHeadList.mObjectList) {
            KnockDown(aObject);
        }
        EnumList(GameObject, aObject, gGame->mTurtleList.mObjectList) {
            KnockDown(aObject);
        }
        EnumList(GameObject, aObject, gGame->mBombList.mObjectList) {
            KnockDown(aObject);
        }
        
    }
    
}

void Game::KeyUp(int pKey) {
    
}

void Game::Notify(void *pSender, const char *pNotification) {
    
}






void Game::Clear() {
    
    if (mCurrentDart) {
        delete mCurrentDart;
        mCurrentDart = NULL;
    }
    
    DisposeAllObjects();
    
    mTrajectoryList.Reset();
    
    if (mLevelData != NULL) {
        delete mLevelData;
        mLevelData = NULL;
    }
    
    mProgressCount = 0;
    mProgress = 0;
    
}

void Game::DartMovingInterpolationFreeLives(Dart *pDart, float pPercent, bool pEnd) {
    
    if (pEnd) {
        pDart->mTransform.mX = pDart->mUpdateInterpEndX;
        pDart->mTransform.mY = pDart->mUpdateInterpEndY;
        pDart->mTransform.mRotation = pDart->mUpdateInterpEndRotation;
    } else {
        pDart->mTransform.mX = pDart->mUpdateInterpStartX
        + (pDart->mUpdateInterpEndX - pDart->mUpdateInterpStartX) * pPercent;
        pDart->mTransform.mY = pDart->mUpdateInterpStartY
        + (pDart->mUpdateInterpEndY - pDart->mUpdateInterpStartY) * pPercent;
        pDart->mTransform.mRotation = pDart->mUpdateInterpStartRotation
        + (pDart->mUpdateInterpEndRotation - pDart->mUpdateInterpStartRotation) * pPercent;
    }
    
    pDart->GetTipPoint(pDart->mTipX, pDart->mTipY);
    
    for (int n=0;n<mFreeLifeList.mObjectList.mCount;n++) {
        FreeLife *aFreeLife = (FreeLife *)mFreeLifeList.mObjectList.mData[n];
        if (aFreeLife->mKill == 0) {
            if (aFreeLife->WillCollide(pDart->mPrevTipX, pDart->mPrevTipY, pDart->mTipX, pDart->mTipY)) {
                DartCollideWithFreeLife(pDart, aFreeLife);
            }
        }
    }
}

void Game::DartMovingInterpolationBalloons(Dart *pDart, float pPercent, bool pEnd) {
    
    if (pEnd) {
        pDart->mTransform.mX = pDart->mUpdateInterpEndX;
        pDart->mTransform.mY = pDart->mUpdateInterpEndY;
        pDart->mTransform.mRotation = pDart->mUpdateInterpEndRotation;
    } else {
        pDart->mTransform.mX = pDart->mUpdateInterpStartX
        + (pDart->mUpdateInterpEndX - pDart->mUpdateInterpStartX) * pPercent;
        pDart->mTransform.mY = pDart->mUpdateInterpStartY
        + (pDart->mUpdateInterpEndY - pDart->mUpdateInterpStartY) * pPercent;
        pDart->mTransform.mRotation = pDart->mUpdateInterpStartRotation
        + (pDart->mUpdateInterpEndRotation - pDart->mUpdateInterpStartRotation) * pPercent;
    }
    
    pDart->GetTipPoint(pDart->mTipX, pDart->mTipY);
    
    for (int n=0;n<mBalloonList.mObjectList.mCount;n++) {
        Balloon *aBalloon = (Balloon *)mBalloonList.mObjectList.mData[n];
        if (aBalloon->mKill == 0) {
            if (aBalloon->WillCollide(pDart->mPrevTipX, pDart->mPrevTipY, pDart->mTipX, pDart->mTipY)) {
                DartCollideWithBalloon(pDart, aBalloon);
            }
        }
    }
}

void Game::DartMovingInterpolationBrickHeads(Dart *pDart, float pPercent, bool pEnd) {
    
    if (pEnd) {
        pDart->mTransform.mX = pDart->mUpdateInterpEndX;
        pDart->mTransform.mY = pDart->mUpdateInterpEndY;
        pDart->mTransform.mRotation = pDart->mUpdateInterpEndRotation;
        
    } else {
        pDart->mTransform.mX = pDart->mUpdateInterpStartX
        + (pDart->mUpdateInterpEndX - pDart->mUpdateInterpStartX) * pPercent;
        pDart->mTransform.mY = pDart->mUpdateInterpStartY
        + (pDart->mUpdateInterpEndY - pDart->mUpdateInterpStartY) * pPercent;
        pDart->mTransform.mRotation = pDart->mUpdateInterpStartRotation
        + (pDart->mUpdateInterpEndRotation - pDart->mUpdateInterpStartRotation) * pPercent;
    }
    
    pDart->GetTipPoint(pDart->mTipX, pDart->mTipY);
    
    for (int n=0;n<mBrickHeadList.mObjectList.mCount;n++) {
        BrickHead *aBrickHead = (BrickHead *)mBrickHeadList.mObjectList.mData[n];
        if ((aBrickHead->mKill == 0) && (aBrickHead->mKnockedDown == false)) {
            if (aBrickHead->WillCollide(pDart->mPrevTipX, pDart->mPrevTipY, pDart->mTipX, pDart->mTipY)) {
                DartCollideWithBrickhead(pDart, aBrickHead);
            }
        }
    }
}

void Game::DartMovingInterpolationTurtles(Dart *pDart, float pPercent, bool pEnd) {
    
    if (pEnd) {
        pDart->mTransform.mX = pDart->mUpdateInterpEndX;
        pDart->mTransform.mY = pDart->mUpdateInterpEndY;
        pDart->mTransform.mRotation = pDart->mUpdateInterpEndRotation;
    } else {
        pDart->mTransform.mX = pDart->mUpdateInterpStartX
        + (pDart->mUpdateInterpEndX - pDart->mUpdateInterpStartX) * pPercent;
        pDart->mTransform.mY = pDart->mUpdateInterpStartY
        + (pDart->mUpdateInterpEndY - pDart->mUpdateInterpStartY) * pPercent;
        pDart->mTransform.mRotation = pDart->mUpdateInterpStartRotation
        + (pDart->mUpdateInterpEndRotation - pDart->mUpdateInterpStartRotation) * pPercent;
    }
    
    pDart->GetTipPoint(pDart->mTipX, pDart->mTipY);
    
    for (int n=0;n<mTurtleList.mObjectList.mCount;n++) {
        Turtle *aTurtle = (Turtle *)mTurtleList.mObjectList.mData[n];
        if ((aTurtle->mKill == 0) && (aTurtle->mKnockedDown == false)) {
            if (aTurtle->WillCollide(pDart->mPrevTipX, pDart->mPrevTipY, pDart->mTipX, pDart->mTipY)) {
                DartCollideWithTurtle(pDart, aTurtle);
            }
        }
    }
}

bool Game::ShouldSpawnFreeLife() {
#ifdef EDITOR_MODE
    
    if (gEditor != NULL) {
        return false;
    } else {
        return gRand.Get(6) == 2;
    }
    
#endif
    return gRand.Get(20) == 8;
}

void Game::NotifyDidSpawnFreeLife() {
    //printf("We spawned FL...\n");
    
}

bool Game::IsWaveClearForSpawn() {
    
    EnumList (FreeLife, aFreeLife, mFreeLifeList.mObjectList) {
        if ((aFreeLife->mKill == 0) && (aFreeLife->mDidOriginateOnWave == true)) {
            return false;
        }
    }
    EnumList (Balloon, aBalloon, mBalloonList.mObjectList) {
        if ((aBalloon->mKill == 0) && (aBalloon->mDidOriginateOnWave == true)) {
            return false;
        }
    }
    EnumList (Turtle, aTurtle, mTurtleList.mObjectList) {
        if ((aTurtle->mKill == 0) && (aTurtle->mDidOriginateOnWave == true) && (aTurtle->mKnockedDown == false) && (aTurtle->mBalloon != NULL)) {
            return false;
        }
    }
    EnumList (BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
        if ((aBrickHead->mKill == 0) && (aBrickHead->mKnockedDown == false) && (aBrickHead->mDidOriginateOnWave == true)) {
            return false;
        }
    }
    EnumList (Bomb, aBomb, mBombList.mObjectList) {
        if ((aBomb->mKill == 0) && (aBomb->mDidOriginateOnWave == true)) {
            return false;
        }
    }
    
    if (IsAnyObjectFloatingAway() == true) {
        return false;
    }
    
    return true;
}


bool Game::IsScreenClearForSpawn(bool pIncludePerms) {
    
    int aPermCount = 0;
    int aWaveCount = 0;
    
    EnumList (FreeLife, aFreeLife, mFreeLifeList.mObjectList) {
        if (aFreeLife->mKill == 0) {
            if (aFreeLife->mDidOriginateAsPermanent == true) {
                ++aPermCount;
            }
            if (aFreeLife->mDidOriginateOnWave == true) {
                ++aWaveCount;
            }
        }
    }
    
    EnumList (Balloon, aBalloon, mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0) {
            if (aBalloon->mDidOriginateAsPermanent == true) {
                ++aPermCount;
            }
            if (aBalloon->mDidOriginateOnWave == true) {
                ++aWaveCount;
            }
        }
    }
    
    EnumList (Turtle, aTurtle, mTurtleList.mObjectList) {
        if ((aTurtle->mKill == 0) && (aTurtle->mKnockedDown == false) && (aTurtle->mBalloon != NULL)) {
            if (aTurtle->mDidOriginateAsPermanent == true) {
                ++aPermCount;
            }
            if (aTurtle->mDidOriginateOnWave == true) {
                ++aWaveCount;
            }
        }
    }
    
    EnumList (BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
        
        //TODO: What was the reason for "mDidOriginateOnWave" here?
        if ((aBrickHead->mKill == 0) && (aBrickHead->mKnockedDown == false)) {
        //if ((aBrickHead->mKill == 0) && (aBrickHead->mKnockedDown == false) && (aBrickHead->mDidOriginateOnWave == true)) {
            if (aBrickHead->mDidOriginateAsPermanent == true) {
                ++aPermCount;
            }
            if (aBrickHead->mDidOriginateOnWave == true) {
                ++aWaveCount;
            }
        }
    }
    EnumList (Bomb, aBomb, mBombList.mObjectList) {
        if ((aBomb->mKill == 0) && (aBomb->mDidOriginateOnWave == true)) {
            if (aBomb->mDidOriginateAsPermanent == true) {
                ++aPermCount;
            }
            if (aBomb->mDidOriginateOnWave == true) {
                ++aWaveCount;
            }
        }
    }
    
    if (pIncludePerms) {
        if (aPermCount > 0 || aWaveCount > 0) { return false; }
    } else {
        if (aWaveCount > 0) { return false; }
    }
    
    if (IsAnyObjectFloatingAway() == true) {
        return false;
    }
    
    return true;
}

void Game::Convert2DTransformTo3D(Transform2D *p2D, Transform3D *p3D) {
    
    if (p2D == NULL) return;
    if (p3D == NULL) return;
    
    p3D->mX = Convert2DXTo3D(p2D->mX + p2D->mOffsetX + p2D->mShiftX);
    p3D->mY = Convert2DYTo3D(p2D->mY + p2D->mOffsetY + p2D->mShiftY);
    //p3D->mZ = ???
    
    p3D->mScale = p2D->mScale * p2D->mOffsetScale;
    p3D->mScaleX = p2D->mScaleX;
    p3D->mScaleY = p2D->mScaleY;
    p3D->mScaleZ = p2D->mScaleZ;
    //p3D->mScaleZ = ???;
    
    p3D->mRotation2D = p2D->mRotation + p2D->mOffsetRotation;
}

FVec3 Game::Convert2DCoordsTo3D(float pX, float pY) {
    FVec3 aResult;
    aResult.mX = Convert2DXTo3D(pX);
    aResult.mY = Convert2DYTo3D(pY);
    aResult.mZ = 0.0f;
    return aResult;
}

float Game::Convert2DXTo3D(float pX) {
    return (mTransformAbsolute.mScale * (pX - mWidth2 + mRenderShiftX) / gDeviceWidth2) * mCamera->mDistance * mCamera->mAspect;
}

float Game::Convert2DYTo3D(float pY) {
    return (mTransformAbsolute.mScale * (pY - mHeight2 + mRenderShiftY) / gDeviceHeight2) * mCamera->mDistance;
}

FVec2 Game::Convert3DCoordsTo2D(float pX, float pY) {
    FVec2 aResult;
    aResult.mX = Convert3DXTo2D(pX);
    aResult.mY = Convert3DYTo2D(pY);
    return aResult;
}

float Game::Convert3DXTo2D(float pX) {
    return (pX * gDeviceWidth2) / (mTransformAbsolute.mScale * mCamera->mDistance * mCamera->mAspect) + mWidth2 - mRenderShiftX;
}

float Game::Convert3DYTo2D(float pY) {
    return ((pY * gDeviceHeight2) / (mTransformAbsolute.mScale * mCamera->mDistance)) + mHeight2 - mRenderShiftY;
}

void Game::DisposeObject(GameObject *pObject) {
    
    if (pObject == NULL) {
        return;
    }
    
    
    if (pObject->mKill != 0) {
        
        //TODO: For IN-GAME, we shouldn't see this.
        //If we do, there is a logical error...
        //printf("Already Killed %x\n", pObject);
        return;
    }
    
#ifndef EDITOR_MODE
    //printf("Disposing: (%s) %x\n", pObject->TypeString().c() , pObject);
#endif
    
    if (DoesObjectTypeCountTowardsProgress(pObject->mGameObjectType)) {
        mProgress++;
    }
        
    
    pObject->Kill();
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_TURTLE) {
        Turtle *aTurtle = ((Turtle *)pObject);
        Balloon *aBalloon = aTurtle->mBalloon;
        if ((aTurtle->mKnockedDown == false) && (aBalloon != NULL)) {
            aTurtle->mBalloon = NULL;
            FlyOffEscape(aBalloon);
        }
    }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_BRICKHEAD) {
        BrickHead *aBrickHead = ((BrickHead *)pObject);
        EnumList(StuckDart, aStuck, aBrickHead->mStuckDartList) {
            if (aStuck->mDart != NULL) {
                Dart *aDart = aStuck->mDart;
                aStuck->mDart = NULL;
                DisposeObject(aDart);
            }
        }
    }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_BALLOON) {
        Balloon *aBalloon = ((Balloon *)pObject);
        EnumList(Turtle, aTurtle, mTurtleList.mObjectList) {
            if (aTurtle->mBalloon == aBalloon) {
                aTurtle->mBalloon = NULL;
                
                if (aTurtle->mKnockedDown == false) {
                    //printf("WE ARE FORCE-KNOCKING DOWN TURTLE [%lld] for auto-die balloon\n", aTurtle);
                    aTurtle->KnockDown();
                }
            }
        }
    }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_FREE_LIFE) {
        FreeLife *aFreeLife = ((FreeLife *)pObject);
        EnumList(Turtle, aTurtle, mTurtleList.mObjectList) {
            if (aTurtle->mBalloon == aFreeLife) {
                aTurtle->mBalloon = NULL;
                
                if (aTurtle->mKnockedDown == false) {
                    
                    //printf("WE ARE FORCE-KNOCKING DOWN TURTLE [%lld] for auto-die free-life\n", aTurtle);
                    aTurtle->KnockDown();
                }
            }
        }
    }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_DART) {
        Dart *aDart = (Dart *)pObject;
        EnumList (BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
            EnumList(StuckDart, aStuck, aBrickHead->mStuckDartList) {
                if (aStuck->mDart == aDart) {
                    aStuck->mDart = NULL;
                }
            }
        }
        
        if (aDart->mHitCount <= 0) {
            mThrownMissedCount++;
        } else {
            mThrownHitCount++;
        }
    } else {
        if (mLevelData != NULL) {
            mLevelData->DisposeObject(pObject);
        }
    }
    
#ifdef EDITOR_MODE
    if (gEditor != NULL) {
        gEditor->mEditorSection.DisposeObject(pObject);
        //gEditor->mEditorWave.DisposeObject(pObject);
        
    }
#endif
    
}

void Game::DisposeObjectFromLevelData(GameObject *pObject) {
    if (mLevelData != NULL) {
        mLevelData->DisposeObject(pObject);
    }
}


void Game::DisposeAllObjects() {
    EnumList (Dart, aDart, mDartList.mObjectList) {
        DisposeObject(aDart);
    }
    EnumList (Balloon, aBalloon, mBalloonList.mObjectList) {
        DisposeObject(aBalloon);
    }
    EnumList (FreeLife, aFreeLife, mFreeLifeList.mObjectList) {
        DisposeObject(aFreeLife);
    }
    EnumList (BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
        DisposeObject(aBrickHead);
    }
    EnumList (Turtle, aTurtle, mTurtleList.mObjectList) {
        DisposeObject(aTurtle);
    }
    EnumList (Bomb, aBomb, mBombList.mObjectList) {
        DisposeObject(aBomb);
    }
}

void Game::FlyOffEscape(GameObject *pObject) {
    
    //TODO: When turtle escapes, we need to lose balloon life...
    
    if (pObject == NULL) { return; }
    
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_TURTLE) {
        Turtle *aTurtle = ((Turtle *)pObject);
        Balloon *aBalloon = aTurtle->mBalloon;
        if ((aTurtle->mKnockedDown == false) && (aBalloon != NULL)) {
            aTurtle->mBalloon = NULL;
            FlyOffEscape(aBalloon);
        }
    }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_BALLOON) {
        mLives--;
        if (mLives <= 0) {
            mLives = 0;
        }
    }
    
    DisposeObject(pObject);
}

//Generally these are only going to be bricks to start..?
void Game::KnockDown(GameObject *pObject) {
    
    if (pObject == NULL) { return; }
    if (pObject->mKill > 0) { return; }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_BRICKHEAD) {
        BrickHead *aBrickHead = ((BrickHead *)pObject);
        if (aBrickHead->mKnockedDown == false) {
            aBrickHead->KnockDown();
        }
    }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_TURTLE) {
        Turtle *aTurtle = ((Turtle *)pObject);
        
        if (aTurtle->mBalloon != NULL && aTurtle->mBalloon->mKill == 0) {
            PopBalloon(aTurtle->mBalloon);
        }
        
        if (aTurtle->mKnockedDown == false) {
            aTurtle->KnockDown();
        }
    }
    
    
}

void Game::StuckDartBeginFadeOut(Dart *pDart) {
    
    if (pDart != NULL && gEffectsOverlay != NULL) {
        int aCount = 6 + gRand.Get(4);
        float aOffsetRotation = gRand.GetRotation();
        
        for (int i=0;i<aCount;i++) {
            
            float aRotation = aOffsetRotation + ((float)i) / ((float)aCount) * 360.0f + gRand.GetFloat(-10.0f, 10.0f);
            
            float aDirX = Sin(aRotation);
            float aDirY = -Cos(aRotation);
            float aSpeed = gRand.GetFloat(0.65f, 1.25f);
            float aShift = gRand.GetFloat(3.0f, 7.0f);
            
            EffectDartFadeStar *aStar = new EffectDartFadeStar();
            FVec2 aPos = FCanvas::Convert(pDart->mTransform.mX, pDart->mTransform.mY, this, gEffectsOverlay);
            aStar->SetPos(aPos.mX + aDirX * aShift, aPos.mY + aDirY * aShift);
            aStar->SetSpeed(aDirX * aSpeed, aDirY * aSpeed);
            aStar->SetAccel(0.970f);
            aStar->SetScale(0.325f, -0.001f);
            aStar->SetRotation(gRand.GetRotation(), gRand.GetFloat(-8.0f, 8.0f), 0.985f);
            gEffectsOverlay->mEffectListDartFadeStar.Add(aStar);
        }
    }
}

void Game::StuckDartFinishFadeOut(Dart *pDart) {
    
    /*
    if (pDart != NULL) {
        
        int aCount = 4 + gRand.Get(3);
        
        for (int i=0;i<aCount;i++) {
            
            float aRotation = gRand.GetRotation();
            
            float aDirX = Sin(aRotation);
            float aDirY = -Cos(aRotation);
            float aSpeed = gRand.GetFloat(0.65f, 1.25f);
            
            EffectDartFadeStar *aStar = new EffectDartFadeStar();
            FVec2 aPos = FCanvas::Convert(pDart->mTransform.mX, pDart->mTransform.mY, this, gGameOverlay);
            aStar->SetPos(aPos.mX + gRand.GetFloat(-5.0f, 5.0f), aPos.mY + gRand.GetFloat(-5.0f, 5.0f));
            
            aStar->SetSpeed(aDirX * aSpeed, aDirY * aSpeed);
            aStar->SetAccel(0.935f);
            aStar->SetScale(0.25f, -0.001f);
            
            gGameOverlay->mEffectListDartFadeStar.Add(aStar);
            
        }
    }
    */
    
}

void Game::PopBalloon(Balloon *pBalloon) {
    
    if (pBalloon != NULL) {
        
        if (mPopSoundDelay == 0) {
            mPopSoundDelay = 2;
            gApp->mSoundBalloonPop.Play();
        }
        
        if (gEffectsOverlay != NULL) {
            gEffectsOverlay->GenerateBalloonPopAnimation(pBalloon);
        }
        
        //Important: The turtle loses the balloon before the balloon is disposed...
        EnumList(Turtle, aTurtle, mTurtleList.mObjectList) {
            if ((aTurtle->mKill == 0) && (aTurtle->mBalloon == pBalloon)) {
                TurtleDidLoseBalloon(aTurtle);
            }
        }
        
        DisposeObject(pBalloon);
        
        mPoppedCount++;
    }
    
    
}

void Game::DartCollideWithBalloon(Dart *pDart, Balloon *pBalloon) {
    
    if (pDart != NULL) {
        pDart->mHitCount++;
    }
    
    PopBalloon(pBalloon);
    
}

void Game::DartCollideWithFreeLife(Dart *pDart, FreeLife *pFreeLife) {
    if (pDart != NULL) {
        pDart->mHitCount++;
    }
    
    if (pFreeLife != NULL) {
        
        if (mPopSoundDelay == 0) {
            mPopSoundDelay = 2;
            gApp->mSoundBalloonPop.Play();
        }
        
        if (gEffectsOverlay != NULL) {
            gEffectsOverlay->GenerateFreeLifePopAnimation(pFreeLife);
        }
        
        //Important: The turtle loses the balloon before the balloon is disposed...
        EnumList(Turtle, aTurtle, mTurtleList.mObjectList) {
            if ((aTurtle->mKill == 0) && (aTurtle->mBalloon == pFreeLife)) {
                TurtleDidLoseBalloon(aTurtle);
            }
        }
        
        DisposeObject(pFreeLife);
        
    }
    mPoppedCount++;
}

void Game::DartCollideWithBrickhead(Dart *pDart, BrickHead *pBrickHead) {
    if (pDart != NULL) {
        
        pDart->mStuck = true;
        
        if (pBrickHead != NULL) {
            
            gApp->mSoundHitTurtle.Play();
            
            StuckDart *aStuck = new StuckDart();
            aStuck->mDart = pDart;
            aStuck->mStartDartRotation = pDart->mTransform.mRotation;
            aStuck->mStartReferenceRotation = (pBrickHead->mTransform.mRotation + pBrickHead->mTransform.mOffsetRotation);
            
            //
            //We don't factor in the dart's offset because that is independent of
            //the collider object. The dart's new position will be dependent on the collider...
            //
            
            float aDeltaX = (pDart->mTransform.mX) - (pBrickHead->mTransform.mX + pBrickHead->mTransform.mOffsetX);
            float aDeltaY = (pDart->mTransform.mY) - (pBrickHead->mTransform.mY + pBrickHead->mTransform.mOffsetY);
            
            aStuck->mStartXDiff = aDeltaX;
            aStuck->mStartYDiff = aDeltaY;
            
            pBrickHead->mStuckDartList.Add(aStuck);
            
            pBrickHead->Rumble(pDart->mTransform.mRotation);
        }
    }
}

void Game::DartCollideWithTurtle(Dart *pDart, Turtle *pTurtle) {
    if (pDart != NULL) {
        pDart->KnockDown();
        if (pTurtle != NULL) {
            pTurtle->Impact(pDart->mTransform.mRotation);
            gApp->mSoundHitBrickhead.Play();
        }
    }
}

void Game::TurtleDidLoseBalloon(Turtle *pTurtle) {
    if (pTurtle != NULL) {
        pTurtle->mBalloon = NULL;
        pTurtle->KnockDown();
    }
    
}

void Game::ReleaseDart() {
    
    
    //mDartTrajectoryList
    
    if (mCurrentDart != NULL) {
        if (mTrajectoryExists == true) {
            mThrownCount++;
            
            mCurrentDart->Fling(mTrajectoryReleaseDirX * mTrajectoryReleaseVelocity, mTrajectoryReleaseDirY * mTrajectoryReleaseVelocity);
            mDartList.Add(mCurrentDart);
            mCurrentDart = NULL;
            
            gApp->mSoundDartRelease.Play();
            gApp->mSoundDartPullback.Stop();
        }
        
        mDartTouch = NULL;
        ResetDartTouch();
        
        mCurrentDartRespawnTimer = 8;
    }
}

void Game::ResetDartTouch() {
    
    if (mDartTouch != NULL) {
        
        mDartTouch = NULL;
        mIsDartBeingPulled = false;
        
        mDartResetAnimation = true;
        mDartResetAnimationTick = 0;
        
        mDartResetStartPullX = mDartPullX;
        mDartResetStartPullY = mDartPullY;
        mDartResetStartRotation = mDartPullRotation;
        
        mDartResetRotationLength = DistanceBetweenAngles(mDartResetStartRotation, 0.0f);
        
        float aFactorRotation = fabsf(mDartResetRotationLength) / 120.0f;
        if (aFactorRotation > 1.0f) { aFactorRotation = 1.0f; }
        
        float aPullLength = Distance(0.0f, 0.0f, mDartPullX, mDartPullY);
        
        float aFactorDistance = aPullLength / ((mDartPullbackRangeMin + mDartPullbackRangeMax) * 0.425f);
        if (aFactorDistance > 1.0f) { aFactorDistance = 1.0f; }
        
        float aAnimationFactor = aFactorRotation;
        if (aFactorDistance > aFactorRotation) aAnimationFactor = aFactorDistance;
        
        float aTime = 5.0f + aAnimationFactor * 40.0f;
        
        mDartResetAnimationTime = (int)(aTime + 0.5f);
        
    } else {
        mDartTouch = NULL;
        mIsDartBeingPulled = false;
        mDartResetAnimation = false;
        mDartResetAnimationTick = 0;
        mDartPullX = 0.0f;
        mDartPullY = 0.0f;
        mDartPullRotation = 0.0f;
        mDartTargetPullRotation = 0.0f;
        mDartTargetPullX = 0.0f;
        mDartTargetPullY = 0.0f;
    }
}

bool Game::IsGameObjectOutsideKillZone(GameObject *pObject) {
    if (pObject != NULL) {
         if (pObject->mTransform.mX < mKillZoneLeft) { return true; }
         if (pObject->mTransform.mX > mKillZoneRight) { return true; }
         if (pObject->mTransform.mY < mKillZoneTop) { return true; }
         if (pObject->mTransform.mY > mKillZoneBottom) { return true; }
    }
    return false;
}

bool Game::IsAnyObjectFloatingAway() {
    
    EnumList (FreeLife, aFreeLife, mFreeLifeList.mObjectList) {
        if (aFreeLife->mKill == 0) {
            if (aFreeLife->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList (Balloon, aBalloon, mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0) {
            if (aBalloon->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList (Turtle, aTurtle, mTurtleList.mObjectList) {
        if ((aTurtle->mKill == 0) && (aTurtle->mKnockedDown == false) && (aTurtle->mBalloon != NULL)) {
            if (aTurtle->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList (BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
        if ((aBrickHead->mKill == 0) && (aBrickHead->mKnockedDown == false)) {
            if (aBrickHead->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    EnumList (Bomb, aBomb, mBombList.mObjectList) {
        if (aBomb->mKill == 0) {
            if (aBomb->mFloatAway == true) {
                mRecentFloatingAwayTick = 4;
            }
        }
    }
    
    return (mRecentFloatingAwayTick > 0);
}

bool Game::DoesObjectTypeCountTowardsProgressCount(int pObjectType) {
    
    if (pObjectType == GAME_OBJECT_TYPE_BALLOON) { return true; }
    if (pObjectType == GAME_OBJECT_TYPE_TURTLE) { return true; }
    
    return false;
}

bool Game::DoesObjectTypeCountTowardsProgress(int pObjectType) {
    
    if (pObjectType == GAME_OBJECT_TYPE_BALLOON) { return true; }
    if (pObjectType == GAME_OBJECT_TYPE_FREE_LIFE) { return true; }
    
    return false;
}


bool Game::DoesObjectTypeRequireClearing(int pObjectType) {
    
    if (pObjectType == GAME_OBJECT_TYPE_BALLOON) { return true; }
    if (pObjectType == GAME_OBJECT_TYPE_TURTLE) { return true; }
    if (pObjectType == GAME_OBJECT_TYPE_FREE_LIFE) { return true; }
    
    return false;
}

void Game::Load() {
    
    Clear();
    
    Log("Game::Load()\n");
    
    //TODO: Remove...
    //return;
    
    Level aLevel;
    
    /*
    
    section_2_turtles_2_bricks_2_balloon_3_waves_turtles_brickcircle_star
    section_2_turtles_2_bricks_2_waves_1_center_balloon
    test_section_2_brickhead_waves_with_and_without_balloons
    test_section_2_tracers_slowslow_speed_all_4_types
    test_section_all_bricks_2_perms
    test_section_all_bricks_2_waves
    test_section_one_perm_4_turtles
    test_section_one_wave_4_turtles
     test_section_one_wave_16_turtles
    
    */
    
    //aLevel.SetKillTimer(5000);
    //aLevel.SetAliveTimer(5000);
    
    aLevel.AddSection("section_easymed_2_perms_2_bricks_blocking_1_turtle_both_sides_3_waves_med_tri_2_singles_med_square.json");
    aLevel.AddSection("section_medium_2_perms_2_bricks_2_turtles_4_waves_staggered_mixed_turtles_bricks_medium_circle_2_singles_1_turtle_brick.json");
    aLevel.AddSection("section_medium_3_waves_simultaneous_large_hexahon_two_ring_tracer_with_bricks_2_small_osc_circles_brick_in_center.json");
    aLevel.AddSection("section_medium_2_perms_circle_8_4_bricks_rot_oscillations_1_wave_circle_8_4_bricks_rotating.json");
    //aLevel.AddSection("section_easy_1_wave_15_single_balloons_back_n_forth.json");
    //aLevel.AddSection("section_easy_1_wave_15_single_balloons_back_n_forth_chamfer.json");
    //aLevel.AddSection("section_learning_start.json");
    //aLevel.AddSection("section_learning_2_waves_lineshot_all_balloons.json");
    
    
    
    //aLevel.AddSection("section_medium_2_perms_2_bricks_2_turtles_4_waves_staggered_mixed_turtles_bricks_medium_circle_2_singles_1_turtle_brick.json");
    //aLevel.AddSection("section_easymed_2_perms_2_bricks_blocking_1_turtle_both_sides_3_waves_med_tri_2_singles_med_square.json");
    
    
    //aLevel.AddSection("section_learning_start");
    
    //aLevel.AddSection("test_section_04");
    mLevelData = aLevel.Build();
    mProgressCount = mLevelData->GetProgressCount();
    mProgress = 0;
    
}

void Game::LoadEditorTest() {
    Clear();
    
    LevelSection *aSection = NULL;
    LevelData *aLevel = new LevelData();
    
    aSection = new LevelSection();
    aSection->Load("editor_test_section.json");
    aLevel->AddSection(aSection);
    
    aSection->mDelay = 0;
    
    mLevelData = aLevel;
    mProgressCount = mLevelData->GetProgressCount();
    mProgress = 0;
}
