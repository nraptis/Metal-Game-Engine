//
//  GameRenderer.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/26/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameRenderer.hpp"
#include "Game.hpp"
#include "GameEditor.hpp"


GameRenderer::GameRenderer(Game *pGame, FloatingCamera *pCamera) {
    mGame = pGame;
    mCamera = pCamera;
    //
    mDart = &gApp->mDart;
    
    mLightDirRotationPrimaryBase = 50.0f;
    mLightDirRotationSecondaryBase = 218.0f;
    
    mLightAmbientBase = 0.30f;
    mLightDiffuseBase = 0.70f;
    mLightSpecularBase = 1.60f;
    
    mLightRedBase = 1.000000;
    mLightGreenBase = 1.000000;
    mLightBlueBase = 1.000000;
    mLightDirX = 0.364717;
    mLightDirY = -0.758964;
    mLightDirZ = 0.539402;
    
    mDartSpin = 0.0f;
    
    //FUniformsLightPhong                 mUniformPhong;
    //FUniformsLightDiffuse        mUniformDiffuse;
    //FUniformsLightAmbient               mUniformAmbient;
    
    
    /*
    mDirectionRotationPrimary = 51.593315;
    mDirectionRotationSecondary = 218.292572;
    *** BEGIN FUniformsLightPhong ***
    mLight.mAmbientIntensity = 0.308003;
    mLight.mDiffuseIntensity = 0.679439;
    mLight.mSpecularIntensity = 1.558217;
    mLight.mRed = 1.000000;
    mLight.mGreen = 1.000000;
    mLight.mBlue = 1.000000;
    mLight.mDirX = -0.615030;
    mLight.mDirY = 0.619677;
    mLight.mDirZ = -0.487584;
    mLight.mShininess = 69.073463;
    ******* For Uni **********
    mUniform.mLight.mAmbientIntensity = 0.308003;
    mUniform.mLight.mDiffuseIntensity = 0.679439;
    mUniform.mLight.mSpecularIntensity = 1.558217;
    mUniform.mLight.mRed = 1.000000;
    mUniform.mLight.mGreen = 1.000000;
    mUniform.mLight.mBlue = 1.000000;
    mUniform.mLight.mDirX = -0.615030;
    mUniform.mLight.mDirY = 0.619677;
    mUniform.mLight.mDirZ = -0.487584;
    mUniform.mLight.mShininess = 69.073463;
    */
    
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
    
    
    //Graphics::PipelineStateSetShape3DAlphaBlending();
    
    
    FMatrix aProjection = mCamera->GetProjection();
    Graphics::MatrixProjectionSet(aProjection);
    Graphics::MatrixModelViewReset();
    
    //Graphics::DepthDisable();
    //Graphics::CullFacesSetFront();
    Graphics::PipelineStateSetShapeNodeNoBlending();
    Graphics::SetColor();
    
    EnumList (Balloon, aBalloon, mGame->mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0) {
            aBalloon->Draw3DThread();
        }
    }
    //Graphics::DepthEnable();
    
    
    Graphics::PipelineStateSetModelIndexedLightedPhongNoBlending();
    EnumList (Dart, aDart, mGame->mDartList.mObjectList) {
        if (aDart->mKill == 0) {
            aDart->Draw3D();
        }
    }
    
    Graphics::PipelineStateSetModelIndexedLightedPhongNoBlending();
    EnumList (Balloon, aBalloon, mGame->mBalloonList.mObjectList) {
        if (aBalloon->mKill == 0) {
            aBalloon->Draw3D();
        }
    }
    
    EnumList (BrickHead, aBrickHead, mGame->mBrickHeadList.mObjectList) {
        if (aBrickHead->mKill == 0) {
            aBrickHead->Draw3D();
        }
    }
    
    EnumList (Bomb, aBomb, mGame->mBombList.mObjectList) {
        if (aBomb->mKill == 0) {
            aBomb->Draw3D();
        }
    }
    
    EnumList (Turtle, aTurtle, mGame->mTurtleList.mObjectList) {
        if (aTurtle->mKill == 0) {
            aTurtle->Draw3D();
        }
    }
    
    if (mGame->mCurrentDart) {
        mGame->mCurrentDart->Draw3D();
    }
    
#ifdef EDITOR_MODE
    if (gEditor != NULL) {
        if (gEditor->mEditorShowReferenced) {
            for (int i=0;i<gEditor->mEditorWave.mPath.mNodeList.mCount;i++) {
                GameObject *aObject = (GameObject *)gEditor->mEditorObjectList.Fetch(i);
                if (aObject != NULL) {
                    aObject->Draw3D();
                }
            }
        }
    }
#endif
    
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
    mUniformPhongBalloon.mLight.mAmbientIntensity = aLightAmbient;
    mUniformPhongBalloon.mLight.mDiffuseIntensity = aLightDiffuse;
    mUniformPhongBalloon.mLight.mSpecularIntensity = aLightSpecular;
    mUniformPhongBalloon.mLight.mShininess = 70.0f;
    mUniformPhongBalloon.mColor = FColor(1.0f, 1.0f, 1.0f, 1.0f);
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
