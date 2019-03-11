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
    
    gGame = this;
    
    
    
    
    SetWidth(GAME_WIDTH);
    SetHeight(GAME_HEIGHT);
    SetTransformAnchor(0.5f, 0.5f);
    
    mCamera = new FloatingCamera();
    mRenderer = new GameRenderer(this, mCamera);
    
    mDartSpawnX = gDeviceWidth2;
    mDartSpawnY = gDeviceHeight2;
    
    mGravity = 0.01f;
    
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

void Game::Layout() {
    
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
        float aTestSceneLeft = ConvertScreenXToScene(0.0f);
        float aTestSceneRight = ConvertScreenXToScene(mWidth);
        float aExpectedWidth = 34.0f;
        float aActualWidth = (aTestSceneRight - aTestSceneLeft);
        if (aActualWidth < aExpectedWidth) {
            mCamera->mDistance += 0.05f;
        } else {
            mCamera->mDistance -= 0.05f;
        }
    }
    
    //mHitZoneRight = ConvertScreenXToScene(mWidth + aHitZonePaddingH);
    //mHitZoneBottom = ConvertScreenYToScene(mHeight + aHitZonePaddingV);
    //mHitZoneLeft = ConvertScreenXToScene(-aHitZonePaddingH);
    
    mCamera->mDistance = mCamera->mDistance;
    Log("mCamera->mDistance = %f\n", mCamera->mDistance);
    
    
    
    
    
    
    
    
    //Keep in mind, the hit zone we are expanding based on screen size...
    float aHitZonePaddingH = 12.0f;
    float aHitZonePaddingV = 60.0f;
    
    mHitZoneTop = ConvertScreenYToScene(-aHitZonePaddingV);
    mHitZoneRight = ConvertScreenXToScene(mWidth + aHitZonePaddingH);
    mHitZoneBottom = ConvertScreenYToScene(mHeight + aHitZonePaddingV);
    mHitZoneLeft = ConvertScreenXToScene(-aHitZonePaddingH);
    
    
    mGameAreaTop = ConvertScreenYToScene(0.0f);
    mGameAreaRight = ConvertScreenXToScene(mWidth);
    mGameAreaBottom = ConvertScreenYToScene(mHeight);
    mGameAreaLeft = ConvertScreenXToScene(0.0f);
    
    float aGameAreaWidth = mGameAreaRight - mGameAreaLeft;
    float aGameAreaHeight = mGameAreaBottom - mGameAreaTop;
    float aGameAreaMinDimension = aGameAreaWidth;
    if (aGameAreaHeight < aGameAreaMinDimension) { aGameAreaMinDimension = aGameAreaHeight; }
    float aGameAreaMaxDimension = aGameAreaWidth;
    if (aGameAreaHeight > aGameAreaMaxDimension) { aGameAreaMaxDimension = aGameAreaHeight; }
    
    
    
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
    
    mPlayAreaTop = ConvertScreenYToScene(mPlayAreaTop);
    mPlayAreaRight = ConvertScreenXToScene(mPlayAreaRight);
    mPlayAreaBottom = ConvertScreenYToScene(mPlayAreaBottom);
    mPlayAreaLeft = ConvertScreenXToScene(mPlayAreaLeft);
    
    
    float aSpawnZonePadding = 80.0f;
    
    mSpawnZoneTop = ConvertScreenYToScene(-aSpawnZonePadding);
    mSpawnZoneRight = ConvertScreenXToScene(mWidth + aSpawnZonePadding);
    mSpawnZoneBottom = mPlayAreaBottom;
    mSpawnZoneLeft = ConvertScreenXToScene(-aSpawnZonePadding);
    
    float aKillZonePaddingTop = gDeviceHeight * 0.75f;
    float aKillZonePaddingBottom = gDeviceHeight * 0.5f;
    float aKillZonePaddingSides = gDeviceWidth * 0.5f + 200.0f;
    
    mKillZoneTop = ConvertScreenYToScene(-aKillZonePaddingTop);
    mKillZoneRight = ConvertScreenXToScene(mWidth + aKillZonePaddingSides);
    mKillZoneBottom = ConvertScreenYToScene(mHeight + aKillZonePaddingBottom);
    mKillZoneLeft = ConvertScreenXToScene(-aKillZonePaddingSides);
    
    
    
    

    
    
    
    //Gravity shoul be a percent of the total height of the play area...
    
    
    
    
    float aVelocityFactor = aGameAreaMaxDimension / aScreenMaxDimension;
    
    //Takes ONE second to fly across screen...
    float aMaxVelocity2D = aScreenMaxDimension * (1.90f / 100.0f);
    float aMinVelocity2D = aScreenMaxDimension * (0.38f / 100.0f);
    float aGravity2D = aScreenMaxDimension * (0.012 / 100.0f);
    
    mDartReleaseVelocityMin = aMinVelocity2D * aVelocityFactor;
    mDartReleaseVelocityMax = aMaxVelocity2D * aVelocityFactor;
    
    mGravity = aGravity2D * aVelocityFactor;
    
    
    //Log("Gravity = %.3f\n", mGravity);
    
    
    mBalloonList.Free();
    for (float xp = 0.125f;xp<=0.975f;xp+= 0.15f) {
     
        for (float yp = 0.125f;yp<=0.975f;yp+= 0.15f) {
            
            Balloon *aBalloon = new Balloon();
            
            aBalloon->mX = mGameAreaLeft + (mGameAreaRight - mGameAreaLeft) * xp;
            aBalloon->mY = mGameAreaTop + (mGameAreaBottom - mGameAreaTop) * yp;
            
            FVec2 aPos1 = ConvertSceneCoordsToScreen(aBalloon->mX, aBalloon->mY);
            FVec2 aPos2 = ConvertSceneCoordsToScreen(mCurrentDart->mX, mCurrentDart->mY);
            
            if (Distance(aPos1, aPos2) < 150.0f) {
                delete aBalloon;
            } else {
                mBalloonList.Add(aBalloon);
            }
            
            
            
        }
    }
    
    
    if (mDemoDartList.mCount <= 0) {
        for (int i=0;i<14;i++) {
            Dart *aDart = new Dart();
            mDemoDartList.Add(aDart);
        }
    }
    
    int aDartIndex = 0;
    for (int i=0;i<7;i++) {
        Dart *aDart1 = (Dart *)(mDemoDartList[aDartIndex++]);
        Dart *aDart2 = (Dart *)(mDemoDartList[aDartIndex++]);
        
        float aPercent = ((float)i) / ((float)6);
        
        aDart1->mColor.mRed = aPercent;
        aDart2->mColor.mRed = aPercent;
        
        
        aDart1->mX = 2.5f * ((float)(i + 1));
        aDart2->mX = -2.5f * ((float)(i + 1));
        
        
    }
    
    
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
            FVec3 aDartPos = ConvertScreenCoordsToScene(mDartSpawnX, mDartSpawnY);
            mCurrentDart->SetPos(aDartPos);
            mCurrentDart->SpawnAnimation();
        }
    }
    
    mBalloonList.Update();
    
    EnumList(Balloon, aBalloon, mBalloonList.mObjectList) {
        //Log("Balloon[%x]\n", aBalloon);
        
    }
    
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
        FVec3 aDartPos = ConvertScreenCoordsToScene(mDartSpawnX + mDartPullX, mDartSpawnY + mDartPullY);
        mCurrentDart->SetPos(aDartPos);
        float aSceneDirX = ConvertScreenXToScene(mDartSpawnX + mDartPullX) - ConvertScreenXToScene(mDartSpawnX);
        float aSceneDirY = ConvertScreenYToScene(mDartSpawnY + mDartPullY) - ConvertScreenYToScene(mDartSpawnY);
        float aScenePullLength = aSceneDirX * aSceneDirX + aSceneDirY * aSceneDirY;
        if (aScenePullLength > SQRT_EPSILON) {
            mCurrentDart->mRotation2D = FaceTarget(aSceneDirX, aSceneDirY);
        } else {
            mCurrentDart->mRotation2D = mDartPullRotation;
        }
    }
}

void Game::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor();
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor();
    
    gApp->mGameAreaMarker.Draw(0.0f, 0.0f);
    
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
    
    
}

void Game::Draw3D() {
    
    
    if (mRenderer) {
        mRenderer->Draw3D();
    }
    
    Graphics::ClipDisable();
    
    Graphics::PipelineStateSetShape3DAlphaBlending();
    Graphics::DepthDisable();
    
    if (false) {
        FMatrix aProjection = mCamera->GetProjection();
        FMatrix aModelView;
        Graphics::MatrixProjectionSet(aProjection);
        Graphics::MatrixModelViewReset();
        
        Graphics::SetColor(0.75f, 0.75f, 1.0f, 0.5f);
        Graphics::UniformBind();
        Graphics::DrawQuad(mKillZoneLeft, mKillZoneTop, 0.0f, mKillZoneRight, mKillZoneTop, 0.0f,
                           mKillZoneLeft, mKillZoneBottom, 0.0f, mKillZoneRight, mKillZoneBottom, 0.0f);
        
        Graphics::SetColor(1.0f, 0.125f, 0.25f, 0.125f);
        Graphics::UniformBind();
        Graphics::DrawQuad(mGameAreaLeft, mGameAreaTop, 0.0f, mGameAreaRight, mGameAreaTop, 0.0f,
                           mGameAreaLeft, mGameAreaBottom, 0.0f, mGameAreaRight, mGameAreaBottom, 0.0f);
        
        Graphics::SetColor(0.125f, 0.85f, 0.075f, 0.15f);
        Graphics::UniformBind();
        Graphics::DrawQuad(mPlayAreaLeft, mPlayAreaTop, 0.0f, mPlayAreaRight, mPlayAreaTop, 0.0f,
                           mPlayAreaLeft, mPlayAreaBottom, 0.0f, mPlayAreaRight, mPlayAreaBottom, 0.0f);
        
        Graphics::SetColor(0.77f, 0.77f, 0.77f, 0.5f);
        Graphics::UniformBind();
        Graphics::DrawQuad(mHitZoneLeft, mHitZoneTop, 0.0f, mHitZoneRight, mHitZoneTop, 0.0f,
                           mHitZoneLeft, mHitZoneBottom, 0.0f, mHitZoneRight, mHitZoneBottom, 0.0f);
        
        Graphics::SetColor(0.55f, 0.08f, 0.08f, 0.5f);
        Graphics::UniformBind();
        Graphics::DrawQuad(mSpawnZoneLeft, mSpawnZoneTop, 0.0f, mSpawnZoneRight, mSpawnZoneTop, 0.0f,
                           mSpawnZoneLeft, mSpawnZoneBottom, 0.0f, mSpawnZoneRight, mSpawnZoneBottom, 0.0f);
    }
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

FVec3 Game::ConvertScreenCoordsToScene(float pX, float pY) {
    FVec3 aResult;
    aResult.mX = ConvertScreenXToScene(pX);
    aResult.mY = ConvertScreenYToScene(pY);
    aResult.mZ = 0.0f;
    return aResult;
}

float Game::ConvertScreenXToScene(float pX) {
    return (mTransformAbsolute.mScale * (pX - mWidth2) / gDeviceWidth2) * mCamera->mDistance * mCamera->mAspect;
}

float Game::ConvertScreenYToScene(float pY) {
    return (mTransformAbsolute.mScale * (pY - mHeight2) / gDeviceHeight2) * mCamera->mDistance;
}


FVec2 Game::ConvertSceneCoordsToScreen(float pX, float pY) {
    FVec2 aResult;
    aResult.mX = ConvertSceneXToScreen(pX);
    aResult.mY = ConvertSceneYToScreen(pY);
    return aResult;
}

float Game::ConvertSceneXToScreen(float pX) {
    return (pX * gDeviceWidth2) / (mTransformAbsolute.mScale * mCamera->mDistance * mCamera->mAspect) + mWidth2;
}

float Game::ConvertSceneYToScreen(float pY) {
    return ((pY * gDeviceHeight2) / (mTransformAbsolute.mScale * mCamera->mDistance)) + mHeight2;
    
    //return ((pY - mHeight2) / gDeviceHeight2) * mCamera->mDistance;
}

void Game::ReleaseDart() {
    
    if (mCurrentDart) {
        
        //Dart *aDart = mCurrentDart;
        
        
        //mCurrentDart = NULL;
        
        
        
        
        
        //How much kapow do we give this dart?
        float aReleaseFactor = 0.0f;
        
        float aDiffX = -mDartPullX;
        float aDiffY = -mDartPullY;
        
        float aSceneDirX = ConvertScreenXToScene(mDartSpawnX) - ConvertScreenXToScene(mDartSpawnX + mDartPullX);
        float aSceneDirY = ConvertScreenYToScene(mDartSpawnY) - ConvertScreenYToScene(mDartSpawnY + mDartPullY);
        
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
        
        mCurrentDart = NULL;
        mDartTouch = NULL;
        ResetDartTouch();
        
        mCurrentDartRespawnTimer = 6 + gRand.Get(3);
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
        
        Log("Animation Factors Rot[%f] Dist[%f]\n", aFactorRotation, aFactorDistance);
        
        float aAnimationFactor = aFactorRotation;
        if (aFactorDistance > aFactorRotation) aAnimationFactor = aFactorDistance;
        
        float aTime = 5.0f + aAnimationFactor * 40.0f;
        
        
        
        
        mDartResetAnimationTime = (int)(aTime + 0.5f);
        
        Log("mDartResetStartRotation = %f..\nmDartResetRotationLength = %f\n", mDartResetStartRotation, mDartResetRotationLength);
        
    } else {
        Log("Dart => No Pull\n");
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
        if (pObject->mX < mKillZoneLeft) { return true; }
        if (pObject->mX > mKillZoneRight) { return true; }
        if (pObject->mY < mKillZoneTop) { return true; }
        if (pObject->mY > mKillZoneBottom) { return true; }
    }
    return false;
}
