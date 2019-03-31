//
//  Game.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "core_includes.h"
#include "Game.hpp"
#include "FAnimation.h"

Game *gGame = NULL;

Game::Game() {
    
    mName = "[Game]";
    
    gGame = this;
    
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
        //
        // The algebra for this conversion does not
        // seem to work out, se we calibrate the camera
        // by easing towards the best distance...
        //
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
    
    float aKillZonePaddingTop = gDeviceHeight * 0.75f;
    float aKillZonePaddingBottom = gDeviceHeight * 0.5f;
    float aKillZonePaddingSides = gDeviceWidth * 0.5f + 200.0f;
    mKillZoneTop = aKillZonePaddingTop;
    mKillZoneRight = mWidth + aKillZonePaddingSides;
    mKillZoneBottom = mHeight + aKillZonePaddingBottom;
    mKillZoneLeft = -aKillZonePaddingSides;
    
    
    
    
    
    
    
    
    //Gravity shoul be a percent of the total height of the play area...
    
    
    
    
    //float aVelocityFactor = aGameAreaMaxDimension / aScreenMaxDimension;
    
    //Takes ONE second to fly across screen...
    //float aMaxVelocity2D = aScreenMaxDimension * (1.90f / 100.0f);
    //float aMinVelocity2D = aScreenMaxDimension * (0.38f / 100.0f);
    //float aGravity2D = aScreenMaxDimension * (0.012 / 100.0f);
    
    //Log("Gravity = %.3f\n", mGravity);
}

void Game::Layout() {
    
}

void Game::Update() {
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
    
    mBalloonList.Update();
    mDartList.Update();
    
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
    mLevelController->Update();
}

void Game::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor();
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor();
    
    
    //Graphics::SetColor(1.0f, 1.0f, 0.25f, 0.25f);
    //Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 1.0f);
    //Graphics::SetColor();
    
    
    //gApp->mGameAreaMarker.Draw(0.0f, 0.0f);
    
    
    
    /*
    gApp->mChaosEgg1X.Draw(mWidth2 / 2.0f + 20.0f, 200.0f, 1.5f, 0.0f);
    gApp->mChaosEgg2X.Draw(mWidth2 + mWidth2 / 2.0f, 200.0f, 1.5f, 0.0f);
    gApp->mChaosEgg3X.Draw(mWidth2 / 2.0f + 20.0f, 380.0f, 1.5f, 0.0f);
    gApp->mChaosEgg4X.Draw(mWidth2 + mWidth2 / 2.0f, 380.0f, 1.5f, 0.0f);
    */
    

    
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
    
    
    mBalloonList.Draw();
    mDartList.Draw();
    
    if (mCurrentDart) {
        mCurrentDart->Draw();
    }
    
    //
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

void Game::Draw3D() {
    
    
    if (mRenderer) {
        mRenderer->Draw3D();
    }
    
    Graphics::ClipDisable();
    Graphics::DepthDisable();
}

void Game::TouchDown(float pX, float pY, void *pData) {
    
    if (gRand.GetBool()) {
        gApp->mSound1.Play();
    } else {
        gApp->mSound2.Play();
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
            mIsDartBeingPulled = true;
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


bool Game::IsScreenClearForSpawn() {
    EnumList (Balloon, aBalloon, mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0) {
            return false;
        }
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

void Game::ReleaseDart() {
    
    if (mCurrentDart) {
        
        //How much kapow do we give this dart?
        float aReleaseFactor = 0.0f;
        
        float aDiffX = -mDartPullX;
        float aDiffY = -mDartPullY;
        
        float aPullLength = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if (aPullLength > SQRT_EPSILON) {
            
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
            
        } else {
            Log("Fizzle? This should never trigger...\n");
            delete mCurrentDart;
        }
        
        
        /*
        float aSceneDirX = Convert2DXTo3D(mDartSpawnX) - Convert2DXTo3D(mDartSpawnX + mDartPullX);
        float aSceneDirY = Convert2DYTo3D(mDartSpawnY) - Convert2DYTo3D(mDartSpawnY + mDartPullY);
        
        float aPullLength = aDiffX * aDiffX + aDiffY * aDiffY;
        float aScenePullLength = aSceneDirX * aSceneDirX + aSceneDirY * aSceneDirY;
        
        if (aPullLength > SQRT_EPSILON && aScenePullLength > SQRT_EPSILON) {
            
            mDartList.Add(mCurrentDart);
            
            aPullLength = (float)(sqrtf(aPullLength));
            aScenePullLength = (float)(sqrtf(aScenePullLength));
            
            aDiffX /= aPullLength;
            aDiffY /= aPullLength;
            
            aSceneDirX /= aScenePullLength;
            aSceneDirY /= aScenePullLength;
            
            aReleaseFactor = (aPullLength - mDartPullbackRangeMin) / (mDartPullbackRangeMax - mDartPullbackRangeMin);
            if (aReleaseFactor < 0.0f) aReleaseFactor = 0.0f;
            if (aReleaseFactor > 1.0f) aReleaseFactor = 1.0f;
            
            aReleaseFactor = FAnimation::EaseInCirc(aReleaseFactor) * 0.5f + aReleaseFactor * 0.5f;
            
            //Log("Release Factor: %f\n", aReleaseFactor);
            
            float aReleaseVelocity = mDartReleaseVelocityMin + (mDartReleaseVelocityMax - mDartReleaseVelocityMin) * aReleaseFactor;
            
            mCurrentDart->Fling(aSceneDirX * aReleaseVelocity, aSceneDirY * aReleaseVelocity);
            
        } else {
            Log("Fizzle? This should never trigger...\n");
            delete mCurrentDart;
        }
        */
        
        mCurrentDart = NULL;
        mDartTouch = NULL;
        ResetDartTouch();
        
        mCurrentDartRespawnTimer = 8;
        
    }
    
    //ResetDartTouch();
    
    
    
}

void Game::ResetDartTouch() {
    
    if (mDartTouch != NULL) {//} && mIsDartBeingPulled == true) {
        
        mDartTouch = NULL;
        mIsDartBeingPulled = false;
        
        mDartResetAnimation = true;
        mDartResetAnimationTick = 0;
        
        mDartResetStartPullX = mDartPullX;
        mDartResetStartPullY = mDartPullY;
        mDartResetStartRotation = mDartPullRotation;
        
        mDartResetRotationLength = DistanceBetweenAngles(mDartResetStartRotation, 0.0f);
        
        float aFactorRotation = fabsf(mDartResetRotationLength) / 120.0f;
        if (aFactorRotation > 1.0f) {
            aFactorRotation = 1.0f;
        }
        
        float aPullLength = Distance(0.0f, 0.0f, mDartPullX, mDartPullY);
        
        float aFactorDistance = aPullLength / ((mDartPullbackRangeMin + mDartPullbackRangeMax) * 0.425f);
        if (aFactorDistance > 1.0f) {
            aFactorDistance = 1.0f;
        }
        
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
        /*
        if (pObject->mX < mKillZoneLeft) { return true; }
        if (pObject->mX > mKillZoneRight) { return true; }
        if (pObject->mY < mKillZoneTop) { return true; }
        if (pObject->mY > mKillZoneBottom) { return true; }
        */
    }
    return false;
}


void Game::Load() {
    
    Log("Game::Load()\n");
    
    LevelSection *aSection = NULL;
    LevelWave *aWave = NULL;
    
    LevelData *aLevel = new LevelData();
    
    //Create level section (1 of 2) (A)
    aSection = new LevelSection();
    aLevel->AddSection(aSection);
    
    //  A does not animate in.
    //  A does not animate out.
    
    //  Greate spawn wave group (1 of 2).
    //      Wave 1: one balloon flies in from the left.
    aWave = new LevelWave();
    aSection->AddWave(aWave);
    //      Wave 2: one balloon flies across from the right.
    aWave = new LevelWave();
    aSection->AddWave(aWave);
    
    
    //  Greate spawn wave (2 of 2).
    //      Wave 1: Group of 4 balloons flies down from the top...
    
    //
    
    //Create level section (2 of 2) (B)
    
    //  B animates in from the left.
    
    //  B has 2 "blockers"
    //      Blocker 1 is at (X: 25%, Y: 25%)
    //      Blocker 2 is at (X: 75%, Y: 25%)
    
    //  Greate spawn wave group (1 of 2).
    //      Wave 1: one balloon flies across from the left.
    //      Wave 2: one balloon flies across from the right.
    
    //  Greate spawn wave (2 of 2).
    //      Wave 1: Group of 2 balloons flies in from the left...
    //      Wave 2: Group of 2 balloons flies in from the right...
    
    
    
    
    
    
    
    
    mLevelData = aLevel;
    mLevelController->Setup(mLevelData);
    
}




