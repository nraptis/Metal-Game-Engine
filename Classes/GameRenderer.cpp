//
//  GameRenderer.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameRenderer.hpp"
#include "Game.hpp"

GameRenderer::GameRenderer(Game *pGame, FloatingCamera *pCamera) {
    mGame = pGame;
    mCamera = pCamera;
    //
    mDart = &gApp->mDart;
    
    mLightDirRotationPrimaryBase = 34.064598;
    mLightDirRotationSecondaryBase = 49.372952;
    
    mLightAmbientBase = 0.35f;
    mLightDiffuseBase = 0.65f;
    mLightSpecularBase = 0.75f;
    
    mLightRedBase = 1.000000;
    mLightGreenBase = 1.000000;
    mLightBlueBase = 1.000000;
    mLightDirX = 0.364717;
    mLightDirY = -0.758964;
    mLightDirZ = 0.539402;
    
    mDartSpin = 0.0f;
    
    //FUniformsLightPhong                 mUniformPhong;
    //FUniformsLightAmbientDiffuse        mUniformDiffuse;
    //FUniformsLightAmbient               mUniformAmbient;
    
}

GameRenderer::~GameRenderer() {
    
}

void GameRenderer::Draw3D() {
    
    DumpLightsToUniforms();
    
    Graphics::SetColor();
    Graphics::DepthEnable();
    Graphics::CullFacesSetDisabled();
    Graphics::PipelineStateSetModelIndexedLightedPhongNoBlending();
    
    mDartSpin += 0.66f;
    if (mDartSpin >= 360.0f) {
        mDartSpin -= 360.0f;
    }
    
    /*
    for (float aX = -mCamera->mDistance;aX <= mCamera->mDistance;aX += 1.25f) {
        for (float aY = -mCamera->mDistance;aY <= mCamera->mDistance;aY += 3.0f) {
            FMatrix aProjection = mCamera->GetProjection();
            Graphics::SetColor();
            
            FMatrix aModelView;
            
            aModelView.Translate(aX, aY);
            aModelView.Scale(0.66f);
            aModelView.RotateX(90.0f);
            aModelView.RotateZ(mDartSpin);
            
            
            Graphics::UniformBind();
            
            
            mUniformPhong.mModelView.Set(aModelView);
            Graphics::UniformBind(&mUniformPhong);
            
            Graphics::DrawTrianglesIndexedFromPackedBuffers(mDart->mBufferVertex, mDart->mBufferVertexOffset, mDart->mBufferIndex, mDart->mBufferIndexOffset, mDart->mIndexCount, gApp->mDartMap.mTexture);
        }
    }
    */
    
    
    
    //mUniformPhong.mModelView.Set(aModelView);
    //Graphics::UniformBind(&mUniformPhong);
    
    
    Graphics::PipelineStateSetModelIndexedLightedPhongNoBlending();
    
    EnumList (Dart, aDart, mGame->mDartList.mObjectList) {
        if (aDart->mKill == 0) {
            aDart->Draw3D();
        }
    }
    
    Graphics::PipelineStateSetModelIndexedLightedPhongAlphaBlending();
    
    EnumList (Balloon, aBalloon, mGame->mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0) {
            aBalloon->Draw3D();
        }
    }
    
    if (mGame->mCurrentDart) {
        mGame->mCurrentDart->Draw3D();
    }
    
    Graphics::DepthDisable();
    Graphics::CullFacesSetBack();
    
}


void GameRenderer::DumpLightsToUniforms() {
    
    FMatrix aProjection = mCamera->GetProjection();
    
    float aLightDirRotationPrimary = mLightDirRotationPrimaryBase;
    float aLightDirRotationSecondary = mLightDirRotationSecondaryBase;
    
    FVec3 aDir = FVec3(0.0f, 0.0f, 1.0f);
    aDir = Rotate3D(aDir, FVec3(1.0f, 0.0f, 0.0f), aLightDirRotationSecondary);
    aDir = Rotate3D(aDir, FVec3(0.0f, 1.0f, 0.0f), aLightDirRotationPrimary);
    
    mLightDirX = aDir.mX;
    mLightDirY = aDir.mY;
    mLightDirZ = aDir.mZ;
    
    float aLightAmbient = mLightAmbientBase;
    float aLightDiffuse = mLightDiffuseBase;
    float aLightSpecular = mLightSpecularBase;

    float aLightRed = mLightRedBase;
    float aLightGreen = mLightGreenBase;
    float aLightBlue = mLightBlueBase;
    
    mUniformPhong.mLight.mRed = aLightRed;
    mUniformPhong.mLight.mGreen = aLightGreen;
    mUniformPhong.mLight.mBlue = aLightBlue;
    mUniformPhong.mLight.mDirX = mLightDirX;
    mUniformPhong.mLight.mDirY = mLightDirY;
    mUniformPhong.mLight.mDirZ = mLightDirZ;
    mUniformPhong.mLight.mAmbientIntensity = aLightAmbient;
    mUniformPhong.mLight.mDiffuseIntensity = aLightDiffuse;
    mUniformPhong.mLight.mSpecularIntensity = aLightSpecular;
    mUniformPhong.mColor = FColor(1.0f, 1.0f, 1.0f, 1.0f);
    mUniformPhong.mProjection.Set(aProjection);
    
    
    mUniformPhongBalloon.mLight.mRed = aLightRed;
    mUniformPhongBalloon.mLight.mGreen = aLightGreen;
    mUniformPhongBalloon.mLight.mBlue = aLightBlue;
    mUniformPhongBalloon.mLight.mDirX = mLightDirX;
    mUniformPhongBalloon.mLight.mDirY = mLightDirY;
    mUniformPhongBalloon.mLight.mDirZ = mLightDirZ;
    mUniformPhongBalloon.mLight.mAmbientIntensity = 0.5f;
    mUniformPhongBalloon.mLight.mDiffuseIntensity = aLightDiffuse;
    mUniformPhongBalloon.mLight.mSpecularIntensity = 50.0f;
    mUniformPhongBalloon.mLight.mShininess = 90.0f;
    mUniformPhongBalloon.mColor = FColor(1.0f, 1.0f, 1.0f, 0.05);
    mUniformPhongBalloon.mProjection.Set(aProjection);
    
    mUniformDiffuse.mLight.mRed = aLightRed;
    mUniformDiffuse.mLight.mGreen = aLightGreen;
    mUniformDiffuse.mLight.mBlue = aLightBlue;
    mUniformDiffuse.mLight.mDirX = mLightDirX;
    mUniformDiffuse.mLight.mDirY = mLightDirY;
    mUniformDiffuse.mLight.mDirZ = mLightDirZ;
    mUniformDiffuse.mLight.mAmbientIntensity = aLightAmbient;
    mUniformDiffuse.mLight.mDiffuseIntensity = aLightDiffuse;
    mUniformDiffuse.mColor = FColor(1.0f, 1.0f, 1.0f, 1.0f);
    mUniformDiffuse.mProjection.Set(aProjection);
    
    
}
