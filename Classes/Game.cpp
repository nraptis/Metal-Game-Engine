//
//  Game.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "core_includes.h"
#include "Game.hpp"
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
    
    mLevelController = new GameLevelController(this);
    mLevelData = NULL;
    
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
    
    mScore = 0;
    
    mLivesMax = 5;
    mLives = mLivesMax;
    
    mPoppedCount = 0;
    
    mThrownHitCount = 0;
    mThrownMissedCount = 0;
    
    mThrownCount = 0;
    mEscapedCount = 0;
    
    mSlowMo = false;
    mSlowMoTimer = 0;
    
    mPopSoundDelay = 0;
    
    mWind = 0.0f;
    mWindSin = 0.0f;
    
    mTestBalloonRotX = 0.0f;
    mTestBalloonRotY = 0.0f;
    mTestBalloonRotZ = 0.0f;
    
}

Game::~Game() {
    if (gGame == this) {
        gGame = NULL;
    }
    if (mCurrentDart) {
        delete mCurrentDart;
        mCurrentDart = NULL;
    }
    mDartList.Free();
    mBalloonList.Free();
    mBrickHeadList.Free();
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
    
    float aKillZonePaddingTop = ((float)GAME_HEIGHT) * 3.0f;
    float aKillZonePaddingBottom = ((float)GAME_HEIGHT) * 0.5f;
    float aKillZonePaddingSides = ((float)GAME_WIDTH) * 0.75f + 200.0f;
    mKillZoneTop = -aKillZonePaddingTop;
    mKillZoneRight = mWidth + aKillZonePaddingSides;
    mKillZoneBottom = mHeight + aKillZonePaddingBottom;
    mKillZoneLeft = -aKillZonePaddingSides;
}

void Game::Layout() {
    
    //TODO: This is only for build mode.
    
    
    
}

void Game::Update() {
    
    bool aShowOverlay = true;
#ifdef EDITOR_MODE
    if (gEditor == NULL) {
        aShowOverlay = false;
    }
#endif
    
    if (gRand.Get(40) == 22) {
        mScore += gRand.Get(1, 100);
    }
    
    if (gRand.Get(80) == 22) {
        mScore += gRand.Get(80, 999);
    }
    
    if (gRand.Get(200) == 50) {
        mScore += gRand.Get(1000, 4999);
    }
    
    
    
    if (mPopSoundDelay > 0) { mPopSoundDelay--; }
    
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
    
    mLevelController->Update();
    
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
    
    
    //TODO: Remove
    for (int i=0;i<mBalloonList.mObjectList.mCount;i++) {
        Balloon *aBalloon = (Balloon *)mBalloonList.mObjectList.mData[i];
        aBalloon->mTransform.mRotation = mTestBalloonRotZ;
        aBalloon->mTilt = mTestBalloonRotX;
    }
    
    mBalloonList.Update();
    mDartList.Update();
    mBrickHeadList.Update();
    mBombList.Update();
    mTurtleList.Update();
    
    
    
    
    //New thing, the dart now moves small increments and tries to collide.
    
    for (int i=0;i<mDartList.mObjectList.mCount;i++) {
        Dart *aDart = (Dart *)mDartList.mObjectList.mData[i];
        
        if (aDart->mIdle == false && aDart->mKill == 0 && aDart->mStuck == false) {
            
            for (float aPercent=0.0f;aPercent<1.0f;aPercent+=0.05f) {
                if (aDart->mStuck == false) {
                    DartMovingInterpolation(aDart, aPercent, false);
                }
            }
            
            if (aDart->mStuck == false) {
                DartMovingInterpolation(aDart, 1.0, true);
            }
            
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
        
        FVec3 aDartPos = Convert2DCoordsTo3D(mDartSpawnX + mDartPullX, mDartSpawnY + mDartPullY);
        
        mCurrentDart->mTransform.mX = mDartSpawnX + mDartPullX;
        mCurrentDart->mTransform.mY = mDartSpawnY + mDartPullY;
        
        mCurrentDart->mTransform.mRotation = mDartPullRotation;
        
        
        /*
         FVec3 aDartPos = Convert2DCoordsTo3D(mDartSpawnX + mDartPullX, mDartSpawnY + mDartPullY);
         mCurrentDart->SetPos(aDartPos);
         float aSceneDirX = Convert2DXTo3D(mDartSpawnX + mDartPullX) - Convert2DXTo3D(mDartSpawnX);
         float aSceneDirY = Convert2DYTo3D(mDartSpawnY + mDartPullY) - Convert2DYTo3D(mDartSpawnY);
         float aScenePullLength = aSceneDirX * aSceneDirX + aSceneDirY * aSceneDirY;
         if (aScenePullLength > SQRT_EPSILON) {
         mCurrentDart->mRotation2D = FaceTarget(aSceneDirX, aSceneDirY);
         } else {
         mCurrentDart->mTransform. mRotation2D = mDartPullRotation;
         }
         */
    }
    
    
    mWindSin += 2.0f;
    if (mWindSin >= 360.0f) { mWindSin -= 360.0f; }
    
    mWind = Sin(mWindSin);
    
    
    
}

void Game::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor();
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 1.0f, 0.25f, 0.25f);
    Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 2000.0f);
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
    mDartList.Draw();
    
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
    
}

void Game::DartMovingInterpolation(Dart *pDart, float pPercent, bool pEnd) {
    
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
    
    FVec2 aTip = pDart->GetTipPoint();
    pDart->mTipX = aTip.mX;
    pDart->mTipY = aTip.mY;
    
    for (int n=0;n<mBalloonList.mObjectList.mCount;n++) {
        Balloon *aBalloon = (Balloon *)mBalloonList.mObjectList.mData[n];
        if (aBalloon->mKill == 0) {
            if (aBalloon->WillCollide(pDart->mPrevTipX, pDart->mPrevTipY, pDart->mTipX, pDart->mTipY)) {
                DartCollideWithBalloon(pDart, aBalloon);
            }
        }
    }
    
    for (int n=0;n<mBrickHeadList.mObjectList.mCount;n++) {
        BrickHead *aBrickHead = (BrickHead *)mBrickHeadList.mObjectList.mData[n];
        if (aBrickHead->mKill == 0) {
            if (aBrickHead->WillCollide(pDart->mPrevTipX, pDart->mPrevTipY, pDart->mTipX, pDart->mTipY)) {
                //aDart->mHitCount++;
                //aBalloon->Kill();
                //mPoppedCount++;
                
                DartCollideWithBrickhead(pDart, aBrickHead);
                
            }
        }
    }
}


void Game::Draw3D() {
    if (mRenderer) {
        mRenderer->Draw3D();
    }
}

void Game::TouchDown(float pX, float pY, void *pData) {
    
    if (gTouch.mTouchCount >= 3) {
        printf("Hack: Killing all balloons..!");
        
        EnumList(GameObject, aObject, gGame->mBalloonList.mObjectList) {
            aObject->Kill();
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
    
}

void Game::KeyUp(int pKey) {
    
}

void Game::Notify(void *pSender, const char *pNotification) {
    
}

bool Game::IsWaveClearForSpawn() {
    EnumList (Balloon, aBalloon, mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0 && aBalloon->mWave != NULL) {
            return false;
        }
    }
    return true;
}


bool Game::IsScreenClearForSpawn(bool pIncludePerms) {
    
    //TODO: We need to know if the PERMS are clear too...
    
    int aPermCount = 0;
    int aWaveCount = 0;
    
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
    
    if (pIncludePerms) {
        if (aPermCount > 0 || aWaveCount > 0) { return false; }
    } else {
        if (aWaveCount > 0) { return false; }
    }
    
    return true;
}

void Game::Convert2DTransformTo3D(Transform2D *p2D, Transform3D *p3D) {
    
    if (p2D == NULL) return;
    if (p3D == NULL) return;
    
    p3D->mX = Convert2DXTo3D(p2D->mX + p2D->mOffsetX);
    p3D->mY = Convert2DYTo3D(p2D->mY + p2D->mOffsetY);
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
    
    if (pObject != NULL) {
        pObject->Kill();
    }
    
    if (pObject->mGameObjectType == GAME_OBJECT_TYPE_DART) {
        EnumList (BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
            EnumList(StuckDart, aStuck, aBrickHead->mStuckDartList) {
                if (aStuck->mDart == pObject) {
                    aStuck->mDart = NULL;
                }
            }
        }
    }
    
    //TODO: Pass dispose along to all sections, waves, etc
    if (mLevelData != NULL) {
        mLevelData->DisposeObject(pObject);
    }
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
    
    EnumList (BrickHead, aBrickHead, mBrickHeadList.mObjectList) {
        DisposeObject(aBrickHead);
    }
}

void Game::FlyOffEscape(GameObject *pObject) {
    if (pObject != NULL) {
        printf("Miss Object... [%s][%x]\n", pObject->TypeString().c(), pObject);
        
        DisposeObject(pObject);
        mEscapedCount++;
        pObject->Kill();
    }
}

void Game::DartFlyOffScreen(Dart *pDart) {
    if (pDart != NULL) {
        printf("Miss Dart... [%s][%x]\n", pDart->TypeString().c(), pDart);
        
        DisposeObject(pDart);
        if (pDart->mHitCount <= 0) {
            mThrownMissedCount++;
        } else {
            mThrownHitCount++;
        }
        pDart->Kill();
    }
}

void Game::StuckDartBeginFadeOut(Dart *pDart) {
    
    if (pDart != NULL) {
        
        int aCount = 6 + gRand.Get(4);
        
        float aOffsetRotation = gRand.GetRotation();
        
        for (int i=0;i<aCount;i++) {
            
            float aRotation = aOffsetRotation + ((float)i) / ((float)aCount) * 360.0f + gRand.GetFloat(-10.0f, 10.0f);
            
            float aDirX = Sin(aRotation);
            float aDirY = -Cos(aRotation);
            float aSpeed = gRand.GetFloat(0.65f, 1.25f);
            float aShift = gRand.GetFloat(3.0f, 7.0f);
            
            EffectDartFadeStar *aStar = new EffectDartFadeStar();
            FVec2 aPos = FCanvas::Convert(pDart->mTransform.mX, pDart->mTransform.mY, this, gGameOverlay);
            aStar->SetPos(aPos.mX + aDirX * aShift, aPos.mY + aDirY * aShift);
            aStar->SetSpeed(aDirX * aSpeed, aDirY * aSpeed);
            aStar->SetAccel(0.970f);
            aStar->SetScale(0.325f, -0.001f);
            aStar->SetRotation(gRand.GetRotation(), gRand.GetFloat(-8.0f, 8.0f), 0.985f);
            
            gGameOverlay->mEffectListDartFadeStar.Add(aStar);
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

void Game::DartCollideWithBalloon(Dart *pDart, Balloon *pBalloon) {
    
    if (pDart != NULL) {
        pDart->mHitCount++;
    }
    
    if (pBalloon != NULL) {
        pBalloon->Kill();
        
        if (mPopSoundDelay == 0) {
            mPopSoundDelay = 4;
            
            gApp->mSoundBalloonPop.Play();
        }
        
        EffectBalloonBurst *aBurst = new EffectBalloonBurst();
        FVec2 aPos = FCanvas::Convert(pBalloon->mTransform.mX, pBalloon->mTransform.mY, this, gGameOverlay);
        aBurst->SetPos(aPos.mX, aPos.mY);
        gGameOverlay->mEffectListBalloonBursts.Add(aBurst);
    }
    
    mPoppedCount++;
    
    
}

void Game::DartCollideWithBrickhead(Dart *pDart, BrickHead *pBrickHead) {
    if (pDart != NULL) {
        
        pDart->mHitCount++;
        
        pDart->mStuck = true;
        
        if (pBrickHead != NULL) {
            
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

void Game::ReleaseDart() {
    
    if (mCurrentDart) {
        
        //How much kapow do we give this dart?
        float aReleaseFactor = 0.0f;
        
        float aDiffX = -mDartPullX;
        float aDiffY = -mDartPullY;
        
        float aPullLength = aDiffX * aDiffX + aDiffY * aDiffY;
        if (aPullLength > SQRT_EPSILON) {
            
            mThrownCount++;
            
            mDartList.Add(mCurrentDart);
            
            aPullLength = (float)(sqrtf(aPullLength));
            
            aDiffX /= aPullLength;
            aDiffY /= aPullLength;
            
            aReleaseFactor = (aPullLength - mDartPullbackRangeMin) / (mDartPullbackRangeMax - mDartPullbackRangeMin);
            aReleaseFactor *= 1.10f;
            if (aReleaseFactor < 0.0f) aReleaseFactor = 0.0f;
            if (aReleaseFactor > 1.0f) aReleaseFactor = 1.0f;
            
            aReleaseFactor = FAnimation::EaseInCirc(aReleaseFactor) * 0.5f + aReleaseFactor * 0.5f;
            
            float aReleaseVelocity = mDartReleaseVelocityMin + (mDartReleaseVelocityMax - mDartReleaseVelocityMin) * aReleaseFactor;
            mCurrentDart->Fling(aDiffX * aReleaseVelocity, aDiffY * aReleaseVelocity);
            
            gApp->mSoundDartRelease.Play();
            gApp->mSoundDartPullback.Stop();
            
        } else {
            Log("Fizzle? This should never trigger...\n");
            delete mCurrentDart;
        }
        
        mCurrentDart = NULL;
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


void Game::Load() {
    
    Log("Game::Load()\n");
    
    //TODO: Remove...
    //return;
    
    Level aLevel;
    //aLevel.AddSection("test_section_01");
    
    //aLevel.AddSection("test_section_03");
    //aLevel.AddSection("test_section_02");
    
    /*
    aLevel.SetAliveTimer(6500);
    aLevel.AddSection("test_section_perm_only_all_brickheads_landings");
    aLevel.AddSection("test_section_perm_only_all_brickheads_landings");
    aLevel.AddSection("test_section_perm_only_all_brickheads");
    aLevel.AddSection("test_section_perm_only_all_brickheads");
    aLevel.AddSection("test_section_perm_only_all_brickheads");
    */
    
    aLevel.SetAliveTimer(2400);
    aLevel.AddSection("test_section_perm_only_all_brickheads");
    
    aLevel.SetKillTimer(1200);
    aLevel.AddSection("test_section_perm_only_all_balloons_all_tracers");
    
    aLevel.SetAliveTimer(800);
    aLevel.AddSection("test_section_perm_only_all_balloons");
    
    aLevel.AddSection("test_section_perm_only_all_balloons");
    
    
    //aLevel.SetKillTimer(100);
    //aLevel.AddSection("test_section_perm_only_all_brickheads_landings");
    
    //aLevel.SetKillTimer(100);
    //aLevel.AddSection("test_section_perm_only_all_balloons_all_tracers");
    
    //aLevel.SetAliveTimer(100);
    //aLevel.AddSection("test_section_perm_only_all_balloons");
    
    //aLevel.SetKillTimer(100);
    //aLevel.AddSection("test_section_perm_only_all_brickheads");
    
    //aLevel.SetKillTimer(100);
    //aLevel.AddSection("test_section_perm_only_all_balloons_all_tracers");
    
    //test_section_three_complex_waves_staggered_only_tracers.json
    //
    //
    //test_section_perm_only_all_balloons_all_tracers.json
    //test_section_perm_only_all_balloons.json
    //test_section_perm_only_all_brickheads.json
    //test_section_perm_only_one_balloon.json
    //test_section_perm_only_3_scattered_balloons.json
    //test_section_perm_only_all_balloons_path_tracer_and_formation.json
    //
    //
    
    /*
    aLevel.SetAliveTimer(500);
    aLevel.AddSection("test_section_perm_only_all_brickheads");
    
    aLevel.SetKillTimer(500);
    aLevel.AddSection("test_section_perm_only_all_balloons");
    
    
    aLevel.SetKillTimer(400);
    aLevel.AddSection("test_section_perm_only_all_balloons_all_tracers");
    
    aLevel.ResetAll();
    aLevel.AddSection("test_section_three_complex_waves_staggered_only_tracers");
    
    aLevel.AddSection("test_section_perm_only_all_balloons");
    */
    
    //test_section_three_complex_waves_staggered_only_tracers.json
    //test_section_one_complex_wave.json
    //test_section_one_simple_wave.json
    //test_section_perm_only_all_balloons_all_tracers.json
    //test_section_perm_only_all_balloons.json
    //test_section_perm_only_all_brickheads.json
    //test_section_three_simple_waves_simultaneous.json
    //test_section_three_simple_waves_staggered.json
    
    //test_section_one_complex_wave
    //test_section_one_simple_wave
    //test_section_perm_only_all_balloons
    //test_section_perm_only_all_brickheads
    //test_section_three_simple_waves_simultaneous
    //test_section_three_simple_waves_staggered
    //test_section_perm_only_all_balloons_all_tracers
    //test_section_three_complex_waves_staggered_only_tracers
    
    //aLevel.AddSection("test_section_04");
    LevelData *aData = aLevel.Build();
    mLevelData = aData;
    mLevelController->Setup(mLevelData);
    
    /*
    LevelSection *aSection = NULL;
    LevelWave *aWave = NULL;
    
    LevelData *aLevel = new LevelData();
    
    //Create level section (1 of 2) (A)
    aSection = new LevelSection();
    aSection->Load("section_learn_the_game.json");
    aLevel->AddSection(aSection);
    
    aSection->mDelay = 0;
    
     mLevelData = aLevel;
     mLevelController->Setup(mLevelData);
    */
}

void Game::LoadEditorTest() {
    
    LevelSection *aSection = NULL;
    LevelData *aLevel = new LevelData();
    
    aSection = new LevelSection();
    aSection->Load("editor_test_section.json");
    aLevel->AddSection(aSection);
    
    aSection->mDelay = 0;
    
    mLevelData = aLevel;
    mLevelController->Setup(mLevelData);
}
