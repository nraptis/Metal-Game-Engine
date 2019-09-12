//
//  Turtle.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Turtle.hpp"
#include "Game.hpp"

Turtle::Turtle() {
    
    mGameObjectType = GAME_OBJECT_TYPE_TURTLE;
    
    mBalloon = NULL;
    mDidSpawnBalloon = false;
    
    mModel = &(gWadModels.mTurtle);
    mSprite = &(gWadModels.mTurtleMap);
    
    //mModel = &(gWadModels.mTurtlePropeller);
    //mSprite = &(gWadModels.mTurtlePropellerMap);
    
    
    mPropellerModel = &(gWadModels.mTurtlePropeller);
    mPropellerSprite = &(gWadModels.mTurtlePropellerMap);
    mPropellerSpin = gRand.Rot();
    mPropellerSpeed = gRand.GetFloat(7.0f, 9.0f);
    
    
    mPropellerBillboardSequence = &(gWadModels.mTurtlePropellerBillboardSequence);
    mPropellerBillboardSequenceMap = &(gWadModels.mTurtlePropellerBillboardMapSequence);
    
    mPropellerBillboardFrame1 = gRand.GetFloat(gWadModels.mTurtlePropellerBillboardSequence.GetMaxFrame());
    mPropellerBillboardFrame2 = gRand.GetFloat(gWadModels.mTurtlePropellerBillboardSequence.GetMaxFrame());
    mPropellerBillboardFrame3 = gRand.GetFloat(gWadModels.mTurtlePropellerBillboardSequence.GetMaxFrame());
    
    mPropellerBillboardSpin1 = gRand.Rot();
    mPropellerBillboardSpin2 = gRand.Rot();
    mPropellerBillboardSpin3 = gRand.Rot();
    
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    mKnockedDown = false;
    mKnockedDownColorSin = 0.0f;
    mKnockedDownRotationSpeed1 = 0.0f;
    mKnockedDownRotationSpeed2 = 0.0f;
    mKnockedDownFallSpeed = 0.0f;
    
    
    
    
    mIsRumbling = false;
    mRumbleTime = 80;
    mRumbleDampenTime = mRumbleTime - 30;
    mRumbleTimer = 0;
    mRumbleColorSin = 0.0f;
    mRumbleDirX = 0.0f;
    mRumbleDirY = -1.0f;
    mRumbleBounceMagnitude = 5.0f;
    mRumbleBounceSin = 0.0f;
    
    
    
    mTransform.mOffsetY = 1.0f;
    mTransform.mOffsetScale = 0.65f;
    
    mBillboardFrame = 0.0f;
    
    mTransform.mShiftX = 0.0f;
    mTransform.mShiftY = 52.0f;
    
    mBalloonOscillationSin = gRand.GetRotation();
    mBalloonOscillationSinSpeed = gRand.GetFloat(1.4f, 1.8f, true);
    
    
    BuildEdgePointListBase();
}

Turtle::~Turtle() {
    
}

void Turtle::Update() {
    
    GameObject::Update();
    
    //mTransform3D.mRotationX += 2.0f;
    //if (mTransform3D.mRotationX >= 360.0f) { mTransform3D.mRotationX -= 360.0f; }
    
    
    
    if (mKnockedDown == true) {
        
        
        
        mKnockedDownColorSin += 12.0f;
        if (mKnockedDownColorSin >= 360.0f) { mKnockedDownColorSin -= 360.0f; }
        
        if (mTransform.mScale > 0.8f) {
            mTransform.mScale *= 0.985f;
            if (mTransform.mScale <= 0.8f) { mTransform.mScale = 0.8f; }
        }
        
        mTransform3D.mRotationX += mKnockedDownRotationSpeed1;
        if (mTransform3D.mRotationX >= 360.0f) { mTransform3D.mRotationX -= 360.0f; }
        
        
        mTransform3D.mRotationZ += mKnockedDownRotationSpeed2;
        if (mTransform3D.mRotationZ >= 360.0f) { mTransform3D.mRotationZ -= 360.0f; }
        
        
        mKnockedDownRotationSpeed1 *= 0.994f;
        mKnockedDownRotationSpeed2 *= 0.994f;
        
        //mTransform.mRotation += DistanceBetweenAngles(mTransform.mRotation, 180.0f) * 0.02125f;
        mTransform.mY += mKnockedDownFallSpeed;
        mKnockedDownFallSpeed += gGame->mGravity;
        
        
        
        float aColorSin = Sin(mKnockedDownColorSin);
        float aColorPercent = (aColorSin + 1.0f) * 0.5f; //Goes from 0 to 1...
        mColor.mRed = 0.8f - (aColorPercent * 0.45f);
        mColor.mGreen = 0.8f - (aColorPercent * 0.65f);
        mColor.mBlue = 0.8f - (aColorPercent * 0.65f);
    }
    
    if ((mDidSpawnBalloon == false) && (mBalloon == NULL)) {//} && (mKill == 0)) {
        mDidSpawnBalloon = true;
        mBalloon = new Balloon();
        mBalloon->mShouldSpawnThread = false;
        gGame->mBalloonList.Add(mBalloon);
    }
    
    if (mBalloon != NULL) {
        mBalloonOscillationSin += mBalloonOscillationSinSpeed;
        if (mBalloonOscillationSin >= 360.0f) { mBalloonOscillationSin -= 360.0f; }
        if (mBalloonOscillationSin  < 0.0f  ) { mBalloonOscillationSin += 360.0f; }
        
        mBalloon->mTransform.mX = mTransform.mX;
        mBalloon->mTransform.mY = mTransform.mY + Sin(mBalloonOscillationSin) * 1.65f;
    }
    
    mPropellerSpin += mPropellerSpeed + gRand.GetFloat(2.0f, 2.5f);
    if (mPropellerSpin >= 360.0f) { mPropellerSpin -= 360.0f; }
    
    if ((mPropellerBillboardSequence != NULL) && (mPropellerBillboardSequence->GetMaxFrame() > 1.0f)) {
        
        mPropellerBillboardFrame1 += 0.6f + gRand.F(0.125, 0.25);
        if (mPropellerBillboardFrame1 >= mPropellerBillboardSequence->GetMaxFrame()) {
            mPropellerBillboardFrame1 -= mPropellerBillboardSequence->GetMaxFrame();
        }
        
        mPropellerBillboardFrame2 -= 0.8f + gRand.F(0.125, 0.25);
        if (mPropellerBillboardFrame1 <= 0.0f) {
            mPropellerBillboardFrame1 += mPropellerBillboardSequence->GetMaxFrame();
        }
        
        mPropellerBillboardFrame3 += 0.9f + gRand.F(0.15, 0.325);
        if (mPropellerBillboardFrame3 >= mPropellerBillboardSequence->GetMaxFrame()) {
            mPropellerBillboardFrame3 -= mPropellerBillboardSequence->GetMaxFrame();
        }
        
        mPropellerBillboardSpin1 += 5.0f + gRand.GetFloat(3.0f);
        if (mPropellerBillboardSpin1 >= 360.0f) { mPropellerBillboardSpin1 -= 360.0f; }
        
        mPropellerBillboardSpin2 -= 5.0f + gRand.GetFloat(3.0f);
        if (mPropellerBillboardSpin2 <= 0.0f) { mPropellerBillboardSpin2 += 360.0f; }
        
        mPropellerBillboardSpin3 += 8.0f + gRand.GetFloat(4.0f);
        if (mPropellerBillboardSpin3 >= 360.0f) { mPropellerBillboardSpin3 -= 360.0f; }
        
    }
    
    if (gWadModels.mTurtlePropellerBillboardMapSequence.mList.mCount > 0) {
        mBillboardFrame += 0.5f;
        if (mBillboardFrame >= gWadModels.mTurtlePropellerBillboardMapSequence.GetMaxFrame()) {
            mBillboardFrame -= gWadModels.mTurtlePropellerBillboardMapSequence.GetMaxFrame();
        }
    }
    
    if (mIsRumbling) {
        
        mRumbleTimer++;
        if (mRumbleTimer >= mRumbleTime) {
            mIsRumbling = false;
        }
        
        float aDampenPercent = 0.0f;
        if (mRumbleTimer > mRumbleDampenTime) {
            int aAdjustedTimer = mRumbleTimer - mRumbleDampenTime;
            int aDampenSpan = mRumbleTime - mRumbleDampenTime;
            aDampenPercent = ((float)aAdjustedTimer) / ((float)aDampenSpan);
        }
        
        mRumbleColorSin += 11.0f;
        if (mRumbleColorSin >= 360.0f) {
            mRumbleColorSin -= 360.0f;
        }
        
        mRumbleBounceSin += 13.0f;
        if (mRumbleBounceSin >= 360.0f) {
            mRumbleBounceSin -= 360.0f;
        }
        
        float aColorSin = Sin(mRumbleColorSin);
        float aColorPercent = (aColorSin + 1.0f) * 0.5f; //Goes from 0 to 1...
        
        mColor.mRed = 1.0f - (aColorPercent * 0.65f) * (1.0f - aDampenPercent);
        mColor.mGreen = 1.0f - (aColorPercent * 0.65f) * (1.0f - aDampenPercent);
        mColor.mBlue = 1.0f - (aColorPercent * 0.65f) * (1.0f - aDampenPercent);
        
        mRumbleBounceMagnitude = 3.0f * (1.0f - aDampenPercent);
        float aMag = Cos(mRumbleBounceSin) * mRumbleBounceMagnitude;
        mTransform.mOffsetX = mRumbleDirX * aMag;
        mTransform.mOffsetY = mRumbleDirY * aMag;
        
        mTransform3D.mRotationX = aColorPercent * 6.0f;
        
    } else {
        
        if (mKnockedDown == false) {
            mColor.mRed = 1.0f;
            mColor.mGreen = 1.0f;
            mColor.mBlue = 1.0f;
            
            mTransform3D.mRotationX = 0.0f;
        }
        
        mTransform.mOffsetX = 0.0f;
        mTransform.mOffsetY = 0.0f;
    }
    BuildEdgePointList();
}

void Turtle::Draw() {
    
    GameObject::Draw();
    
    /*
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.85f);
    
    Graphics::DrawPoint(mTransform.mX, mTransform.mY, 10.0f);
    
    
    Graphics::SetColor(1.0f, 0.0f, 0.25f, 0.5f);
    mEdgePointList2D.DrawEdges(2.0f);
    */
}

void Turtle::Draw3DPropeller() {
    
    if (mPropellerModel != NULL && mPropellerSprite != NULL) {
        
        if (mUniform != NULL) {
            
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateZ(mPropellerSpin);
            mPropellerMatrixNormal.SetNormalMatrix(mPropellerMatrixModelView);
            
            //Assign the model view to the uniform...
            mUniform->mModelView.Set(mPropellerMatrixModelView);
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_DIFFUSE) {
                FUniformsLightDiffuse *aUniform = (FUniformsLightDiffuse *)(mUniform);
                aUniform->mNormal.Set(mPropellerMatrixNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_PHONG) {
                FUniformsLightPhong *aUniform = (FUniformsLightPhong *)(mUniform);
                aUniform->mNormal.Set(mPropellerMatrixNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_SIMPLE_SPOTLIGHT) {
                FUniformsLightSimpleSpotlight *aUniform = (FUniformsLightSimpleSpotlight *)(mUniform);
                aUniform->mNormal.Set(mPropellerMatrixNormal);
            }
            
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            Graphics::UniformBind(mUniform);
        }
        
        Graphics::DrawTrianglesIndexedWithPackedBuffers(mPropellerModel->mBuffer, 0, mPropellerModel->mIndex, mPropellerModel->mIndexCount, mPropellerSprite->mTexture);
    }
}

void Turtle::Draw3DBillboard() {
    
    if (mPropellerBillboardSequence != NULL && mPropellerBillboardSequenceMap != NULL) {
        FModelDataPacked *aModel = mPropellerBillboardSequence->GetModel(mPropellerBillboardFrame1);
        FSprite *aSprite = mPropellerBillboardSequenceMap->GetSprite(mPropellerBillboardFrame1);
        if ((mUniform != NULL) && (aModel != NULL) && (aSprite != NULL)) {
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateZ(mPropellerBillboardSpin1);
            Graphics::MatrixModelViewSet(mPropellerMatrixModelView);
            Graphics::UniformBind();
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel->mBuffer, 0, mPropellerBillboardSequence->mIndex, mPropellerBillboardSequence->mIndexCount, aSprite->mTexture);
        }
        
        aModel = mPropellerBillboardSequence->GetModel(mPropellerBillboardFrame2);
        aSprite = mPropellerBillboardSequenceMap->GetSprite(mPropellerBillboardFrame2);
        if ((mUniform != NULL) && (aModel != NULL) && (aSprite != NULL)) {
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateX(-3.0f);
            mPropellerMatrixModelView.RotateZ(mPropellerBillboardSpin2);
            Graphics::MatrixModelViewSet(mPropellerMatrixModelView);
            Graphics::UniformBind();
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel->mBuffer, 0, mPropellerBillboardSequence->mIndex, mPropellerBillboardSequence->mIndexCount, aSprite->mTexture);
        }
        
        aModel = mPropellerBillboardSequence->GetModel(mPropellerBillboardFrame3);
        aSprite = mPropellerBillboardSequenceMap->GetSprite(mPropellerBillboardFrame3);
        if ((mUniform != NULL) && (aModel != NULL) && (aSprite != NULL)) {
            mPropellerMatrixModelView.Set(mModelView);
            mPropellerMatrixModelView.RotateX(3.0f);
            mPropellerMatrixModelView.RotateZ(mPropellerBillboardSpin3);
            Graphics::MatrixModelViewSet(mPropellerMatrixModelView);
            Graphics::UniformBind();
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aModel->mBuffer, 0, mPropellerBillboardSequence->mIndex, mPropellerBillboardSequence->mIndexCount, aSprite->mTexture);
        }
    }
}

void Turtle::KnockDown() {
    if (gGame != NULL) {
        //This becomes removed from whichever group it was in...
        gGame->DisposeObjectFromLevelData(this);
    }
    
    mKnockedDown = true;
    mModel = &(gWadModels.mTurtleDamaged);
    mSprite = &(gWadModels.mTurtleDamagedMap);
    
    
    mKnockedDownColorSin = 0.0f;
    mKnockedDownRotationSpeed1 = gRand.GetFloat(3.0f, 4.5f, true);
    mKnockedDownRotationSpeed2 = gRand.GetFloat(1.5f, 1.75f, true);
    mKnockedDownFallSpeed = 0.0f;
    
    
}

bool Turtle::WillCollide(float pStartX, float pStartY, float pEndX, float pEndY) {
    float aMidX = (pStartX + pEndX) * 0.5f;
    float aMidY = (pStartY + pEndY) * 0.5f;
    if (mEdgePointList2D.ContainsPoint(pStartX, pStartY)) { return true; }
    if (mEdgePointList2D.ContainsPoint(aMidX, aMidY)) { return true; }
    if (mEdgePointList2D.ContainsPoint(pEndX, pEndY)) { return true; }
    return false;
}

void Turtle::BuildEdgePointListBase() {
    mEdgePointList3DBase.RemoveAll();
    
    float aOutlineStartY = -1.40f;
    float aOutlineArcWidth = 1.48f;
    float aOutlineLipHeight = 0.85f;
    float aOutlineArcCenterX = 0.0f;
    float aOutlineArcCenterY = aOutlineStartY + aOutlineLipHeight;
    float aOutlineArcVerticalCompressionFactor = 0.825f;
    
    float aY = aOutlineStartY;
    float aX = -aOutlineArcWidth;
    
    int aLipPointCount = 2;
    for (int aLipIndex=0;aLipIndex<aLipPointCount;aLipIndex++) {
        float aPercent = ((float)aLipIndex) / ((float)aLipPointCount);
        aY = aOutlineStartY + aOutlineLipHeight * aPercent;
        mEdgePointList3DBase.Add(aX, aY);
    }
    
    int aArcPointCount = 12;
    for (int i=0;i<aArcPointCount;i++) {
        float aPercent = ((float)i) / ((float)(aArcPointCount - 1));
        float aRotation = 270.0f - 180.0f * aPercent;
        float aDirX = Sin(aRotation);
        float aDirY = -Cos(aRotation);
        aX = aOutlineArcCenterX + aDirX * aOutlineArcWidth;
        aY = aOutlineArcCenterY + aDirY * aOutlineArcWidth * aOutlineArcVerticalCompressionFactor;
        mEdgePointList3DBase.Add(aX, aY);
    }
    
    aX = aOutlineArcWidth;
    for (int aLipIndex=0;aLipIndex<aLipPointCount;aLipIndex++) {
        float aPercent = ((float)(aLipIndex + 1)) / ((float)aLipPointCount);
        aY = (aOutlineStartY + aOutlineLipHeight) - aOutlineLipHeight * aPercent;
        mEdgePointList3DBase.Add(aX, aY);
    }
}

void Turtle::BuildEdgePointList() {
    
    
    gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
    
    mEdgePointList3D.RemoveAll();
    for (int i=0;i<mEdgePointList3DBase.mCount;i++) {
        mEdgePointList3D.Add(mEdgePointList3DBase.mX[i] + mTransform3D.mX, mEdgePointList3DBase.mY[i] + mTransform3D.mY);
    }
    
    mEdgePointList2D.RemoveAll();
    
    float aX = 0.0f;
    float aY = 0.0f;
    for (int i=0;i<mEdgePointList3D.mCount;i++) {
        
        aX = mEdgePointList3D.mX[i];
        aY = mEdgePointList3D.mY[i];
        
        aX = gGame->Convert3DXTo2D(aX);
        aY = gGame->Convert3DYTo2D(aY);
        
        mEdgePointList2D.Add(aX, aY);
    }
}


void Turtle::Impact(float pImpactRotation) {
    
    mIsRumbling = true;
    
    mRumbleTimer = 0;
    
    mRumbleColorSin = 0.0f;
    
    mRumbleDirX = Sin(pImpactRotation);
    mRumbleDirY = -Cos(pImpactRotation);
    
    mRumbleBounceMagnitude = 7.0f;
    mRumbleBounceSin = 0.0f;
}




