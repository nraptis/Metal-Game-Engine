//
//  GameObject.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameObject.hpp"
#include "Game.hpp"
#include "LevelWave.hpp"
#include "LevelWaveSpawn.hpp"
#include "LevelPermSpawn.hpp"

GameObject::GameObject() {
    mWave = NULL;
    mUniform = NULL;
    mModel = NULL;
    mSprite = NULL;
    
    mWaveSpawn = NULL;
    mPermSpawn = NULL;
    
    
    mDidOriginateOnWave = false;
    mDidOriginateAsPermanent = false;
    
    mGameObjectType = GAME_OBJECT_TYPE_UNKNOWN;
    
    mFloatAway = false;
    mFloatAwaySpeedX = 0.0f;
    mFloatAwaySpeedY = 0.0f;
    
    mEllipseRadiusH = 34.0f;
    mEllipseRadiusV = 52.0f;
}

GameObject::~GameObject() {
    if (mWaveSpawn != NULL) {
        mWaveSpawn->DisposeObject(this);
        mWaveSpawn = NULL;
    }
    if (mPermSpawn != NULL) {
        mPermSpawn->DisposeObject(this);
    }
}

void GameObject::Update() {
    if (mFloatAway == true) {
        mTransform.mX += mFloatAwaySpeedX;
        mTransform.mY += mFloatAwaySpeedY;
        mFloatAwaySpeedX *= 0.972f;
        mFloatAwaySpeedY -= 0.042f;
        mFloatAwaySpeedY *= 0.987f;
        if (gGame != NULL) {
            if (mTransform.mY <= gGame->mSpawnZoneTop) {
                gGame->DisposeObject(this);
            }
        }
    }
}

void GameObject::Draw() {
    
    
    /*
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor();
    if (mDidOriginateOnWave) {
        gApp->mSysFontBold.Center("W", mTransform.mX, mTransform.mY);
    }
    
    if (mDidOriginateAsPermanent) {
        gApp->mSysFontBold.Center("P", mTransform.mX, mTransform.mY);
    }
    
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    if (mEllipseRadiusH > SQRT_EPSILON && mEllipseRadiusV > SQRT_EPSILON) {
        
        
        Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.65f);
        
        FVec2 aEllC = FVec2(mTransform.mX, mTransform.mY);
        FVec2 aP2H = FVec2(mTransform.mX + mEllipseRadiusH, mTransform.mY);
        aP2H = PivotPoint(aP2H, mTransform.mRotation, aEllC);
        
        FVec2 aP2V = FVec2(mTransform.mX, mTransform.mY - mEllipseRadiusV);
        aP2V = PivotPoint(aP2V, mTransform.mRotation, aEllC);
        
        
        Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.75f);
        Graphics::DrawLine(mTransform.mX, mTransform.mY, aP2H.mX, aP2H.mY, 2.0f);
        
        Graphics::SetColor(0.75f, 1.0f, 0.25f, 0.75f);
        Graphics::DrawLine(mTransform.mX, mTransform.mY, aP2V.mX, aP2V.mY, 2.0f);
        
    }
    */
    
    
}

void GameObject::Draw3D() {
    
    if (mModel != NULL && mSprite != NULL) {
        
        if (mUniform != NULL) {
            gGame->Convert2DTransformTo3D(&mTransform, &mTransform3D);
            
            mModelView.Reset();
            
            //We start by translation...?
            mModelView.Translate(mTransform3D.mX, mTransform3D.mY, mTransform3D.mZ);
            
            //All of our models are exported with X 90 degrees wrong...
            mModelView.RotateX(-90.0f);
            mModelView.RotateY(180.0f);
            
            //mModelView.RotateZ(180.0f);
            
            mModelView.RotateX(mTransform3D.mRotationX);
            mModelView.RotateZ(mTransform3D.mRotationZ);
            
            //Now we do a 2-D rotation...
            
            mModelView.RotateY(-mTransform3D.mRotation2D);
            
            //Now we spin around the Y axis...
            mModelView.RotateZ(mTransform3D.mSpin);
            
            //Now we scale down...
            mModelView.Scale(mTransform3D.mScaleX * mTransform3D.mScale, mTransform3D.mScaleY * mTransform3D.mScale, mTransform3D.mScaleZ * mTransform3D.mScale);
            
            mNormal.SetNormalMatrix(mModelView);
            
            
            //Assign the model view to the uniform...
            mUniform->mModelView.Set(mModelView);
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_DIFFUSE) {
                FUniformsLightDiffuse *aUniform = (FUniformsLightDiffuse *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_PHONG) {
                FUniformsLightPhong *aUniform = (FUniformsLightPhong *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            if (mUniform->GetType() == UNIFORM_TYPE_LIGHT_SIMPLE_SPOTLIGHT) {
                FUniformsLightSimpleSpotlight *aUniform = (FUniformsLightSimpleSpotlight *)(mUniform);
                aUniform->mNormal.Set(mNormal);
            }
            
            
            //aNormal.SetNormalMatrix(aModelView);
            
            
            mUniform->mColor.mRed = mColor.mRed;
            mUniform->mColor.mGreen = mColor.mGreen;
            mUniform->mColor.mBlue = mColor.mBlue;
            mUniform->mColor.mAlpha = mColor.mAlpha;
            
            //Then bind the uniform...
            Graphics::UniformBind(mUniform);
        }
        
        Graphics::DrawTrianglesIndexedWithPackedBuffers(mModel->mBuffer, 0, mModel->mIndex, mModel->mIndexCount, mSprite->mTexture);
        
    }
}

void GameObject::Kill() {
    FObject::Kill();
}

FString GameObject::TypeString() {
    
    if (mGameObjectType == GAME_OBJECT_TYPE_BALLOON) { return FString("balloon"); }
    if (mGameObjectType == GAME_OBJECT_TYPE_BRICKHEAD) { return FString("brickhead"); }
    if (mGameObjectType == GAME_OBJECT_TYPE_BOMB) { return FString("bomb"); }
    if (mGameObjectType == GAME_OBJECT_TYPE_TURTLE) { return FString("turtle"); }
    
    if (mGameObjectType == GAME_OBJECT_TYPE_DART) { return FString("dart"); }
    
    return FString("unknown");
}

bool GameObject::IsRequiredToClearForSectionCompletion() {
    
    if (mGameObjectType == GAME_OBJECT_TYPE_BALLOON) { return true; }
    if (mGameObjectType == GAME_OBJECT_TYPE_TURTLE) { return true; }
    
    return false;
}

bool GameObject::WillCollide(float pStartX, float pStartY, float pEndX, float pEndY) {
    float aDirX = pEndX - pStartX;
    float aDirY = pEndY - pStartY;
    float aLength = aDirX * aDirX + aDirY * aDirY;
    if (aLength > 0.25f) {
        aLength = sqrtf(aLength);
        aDirX /= aLength;
        aDirY /= aLength;
        int aStepCount = (int)(aLength / 2) + 4;
        if (aStepCount > 100) {
            aStepCount = 100;
            Log("Object moving too fast?\nLOL!\n");
        }
        for (int i=0;i<aStepCount;i++) {
            float aPercent = ((float)i) / ((float)(aStepCount - 1));
            float aX = pStartX + aDirX * aPercent * aLength;
            float aY = pStartY + aDirY * aPercent * aLength;
            if (EllipseContainsPoint(aX, aY, mTransform.mX, mTransform.mY, mEllipseRadiusH, mEllipseRadiusV, mTransform.mRotation)) {
                return true;
            }
        }
        return false;
    } else {
        return EllipseContainsPoint(pStartX, pStartY, mTransform.mX, mTransform.mY, mEllipseRadiusH, mEllipseRadiusV, mTransform.mRotation);
    }
}

void GameObject::FloatAway(float pDirX, float pDirY, float pMagnitude) {
    mFloatAway = true;
    mFloatAwaySpeedX = pDirX * pMagnitude * 4.0f;
    mFloatAwaySpeedY = pDirY * pMagnitude * 4.0f;
}

void GameObject::Disperse(float pDirX, float pDirY, float pMagnitude) {
    FloatAway(pDirX, pDirY, pMagnitude);
}
