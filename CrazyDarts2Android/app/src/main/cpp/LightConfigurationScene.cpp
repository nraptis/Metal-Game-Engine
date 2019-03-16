//
//  LightConfigurationScene.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "LightConfigurationScene.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"

LightConfigurationScene *gLightScene = NULL;

LightConfigurationScene::LightConfigurationScene() {
    gLightScene = this;
    
    mClipDisabled = true;
    
    mCenterX = gAppWidth2;
    mCenterY = gAppHeight2;
    
    
    mDummyObjectX = 0.0f;
    mDummyObjectY = 0.0f;
    mDummyObjectZ = 0.0f;
    
    mDummyRot1 = 0.0f;
    mDummyRot2 = 0.0f;
    
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    float aPaddingTop = 80.0f;
    float aPaddingBottom = 20.0f;
    float aMenuGroupHeight = (gDeviceHeight - (aPaddingTop + aPaddingBottom));
    
    //mLightMenu = new LightMenu();
    //mLightMenu->SetFrame(20.0f, aPaddingTop, 260.0f, aMenuGroupHeight / 2.0f);
    //mLightMenu->SetTitle("Lights");
    //AddChild(mLightMenu);
    
    mCameraMenu = new CameraMenu(&mCamera);
    mCameraMenu->SetFrame(20.0f, aPaddingTop + aMenuGroupHeight / 2.0f, min(600.0f, gDeviceWidth * 0.8f), aMenuGroupHeight / 2.0f);
    mCameraMenu->SetTitle("Cameras");
    mCameraMenu->mSliderDummyX->SetValue(&mDummyObjectX);
    mCameraMenu->mSliderDummyY->SetValue(&mDummyObjectY);
    mCameraMenu->mSliderDummyZ->SetValue(&mDummyObjectZ);
    
    mCameraMenu->mSliderDummyRot1->SetValue(&mDummyRot1);
    mCameraMenu->mSliderDummyRot2->SetValue(&mDummyRot2);
    
    AddChild(mCameraMenu);
    
    
    mPhongLightMenu = new PhongLightMenu(&mPhong);
    if (gDeviceWidth > 600) {
        mPhongLightMenu->SetFrame(20.0f, aPaddingTop, 500.0f, aMenuGroupHeight / 2.0f);
    } else {
        mPhongLightMenu->SetFrame(20.0f, aPaddingTop, gDeviceWidth * 0.8f, aMenuGroupHeight / 2.0f);
    }
    mPhongLightMenu->SetTitle("Phong Light");
    AddChild(mPhongLightMenu);
}

LightConfigurationScene::~LightConfigurationScene() {
    
}

void LightConfigurationScene::Layout()  {
    
}

void LightConfigurationScene::Update() {
    
    float aScreenCenterOffsetX = mCenterX - mWidth2;
    float aScreenCenterOffsetY = mCenterY - mHeight2;
    
    mDummyObjectX = (aScreenCenterOffsetX / gDeviceWidth2) * mCamera.mDistance * mCamera.mAspect;
    mDummyObjectY = (aScreenCenterOffsetY / gDeviceHeight2) * mCamera.mDistance;
    
    
    
    //m[8] = pOffsetX / gDeviceWidth2;
    //m[9] = -pOffsetY / gDeviceHeight2;
    

}

void LightConfigurationScene::Draw3D() {
    
    Graphics::ClipDisable();
    
    mPhong.Compute();
    
    
    mDisableLight = gRand.GetBool();
    mDisableLight = false;
    
    
    float aAbsoluteCenterX = gAppBase->mWindowMain.mRoot.mX + gAppBase->mWindowMain.mRoot.mWidth2;
    float aAbsoluteCenterY = gAppBase->mWindowMain.mRoot.mY + gAppBase->mWindowMain.mRoot.mHeight2;
    mCamera.mCenterOffset = FVec2(gDeviceWidth2 - aAbsoluteCenterX, gDeviceHeight2 - aAbsoluteCenterY);
    
    
    
    
    
    Graphics::DepthEnable();
    Graphics::CullFacesSetDisabled();
    
    //Graphics::DepthClear();
    
    
    FModelDataPacked *aDart = &(gApp->mDart);
    FModelDataPacked *aGround = &(gApp->mGround);
    
    
    
    
    FMatrix aProjection = mCamera.GetProjection();
    Graphics::SetColor();
    
    FMatrix aModelView;
    aModelView.RotateX(90.0f);
    //
    /*
    mCenterOffset
    //
    float aProjectionShiftX = mCamera.mDistance / aScreenCenterOffsetX;
    float aProjectionShiftY = mCamera.mDistance / aScreenCenterOffsetY;
    //
    aProjection.Translate(aProjectionShiftX, aProjectionShiftY);
    */
    
    Graphics::MatrixProjectionSet(aProjection);
    Graphics::MatrixModelViewSet(aModelView);
    mPhong.mUniform.mProjection.Set(aProjection);
    mPhong.mUniform.mModelView.Set(aModelView);
    
    FModelDataPacked *aBalloon = &(gApp->mBalloon);
    FModelDataPacked *aTree = &(gApp->mPalmLeaves);
    FModelDataPacked *aTrunk = &(gApp->mPalmTrunk);
    
    if (mDisableLight) {
        Graphics::PipelineStateSetModelIndexedAlphaBlending();
    } else {
        Graphics::PipelineStateSetModelIndexedLightedPhongNoBlending();
    }
    //
    
    Graphics::SetColor();
    
    Graphics::UniformBind(&mPhong.mUniform);
    //Graphics::DrawTrianglesIndexedFromPackedBuffers(aTrunk->mBufferVertex, aTrunk->mBufferVertexOffset, aTrunk->mBufferIndex, aTrunk->mBufferIndexOffset, aTrunk->mIndexCount, gApp->mPalmTrunkMap.mTexture);
    
    if (mDisableLight) {
        Graphics::UniformBind();
    } else {
        Graphics::UniformBind(&mPhong.mUniform);
    }
    //Graphics::DrawTrianglesIndexedFromPackedBuffers(aTree->mBufferVertex, aTree->mBufferVertexOffset, aTree->mBufferIndex, aTree->mBufferIndexOffset, aTree->mIndexCount, gApp->mPalmLeavesMap.mTexture);
    
    aModelView.Reset();
    aModelView.Translate(mDummyObjectX, mDummyObjectY, mDummyObjectZ);
    aModelView.Scale(2.0f);
    
    aModelView.RotateX(90.0f);
    
    aModelView.RotateX(mDummyRot1);
    aModelView.RotateY(mDummyRot2);
    
    //aModelView.Translate(5.0f, 1.0f, -1.0f);
    
    
    Graphics::MatrixModelViewSet(aModelView);
    mPhong.mUniform.mModelView.Set(aModelView);
    
    if (mDisableLight) {
        Graphics::UniformBind();
    } else {
        Graphics::UniformBind(&mPhong.mUniform);
    }
    
    //Graphics::DrawTrianglesIndexedFromPackedBuffers(aBalloon->mBufferVertex, aBalloon->mBufferVertexOffset, aBalloon->mBufferIndex, aBalloon->mBufferIndexOffset, aBalloon->mIndexCount, gApp->mBalloonMap[3].mTexture);
    //Graphics::DrawTrianglesIndexedFromPackedBuffers(aDart->mBufferVertex, aDart->mBufferVertexOffset, aDart->mBufferIndex, aDart->mBufferIndexOffset, aDart->mIndexCount, gApp->mDartMap.mTexture);
    
    
    
    
    
    aModelView.Reset();
    aModelView.Translate(-mDummyObjectX, mDummyObjectY, mDummyObjectZ);
    aModelView.Scale(0.5f);
    
    aModelView.RotateX(90.0f);
    
    aModelView.RotateX(mDummyRot1);
    aModelView.RotateY(mDummyRot2);
    
    Graphics::MatrixModelViewSet(aModelView);
    mPhong.mUniform.mModelView.Set(aModelView);
    
    if (mDisableLight) {
        Graphics::UniformBind();
    } else {
        Graphics::UniformBind(&mPhong.mUniform);
    }
    
    //Graphics::DrawTrianglesIndexedFromPackedBuffers(aDart->mBufferVertex, aDart->mBufferVertexOffset, aDart->mBufferIndex, aDart->mBufferIndexOffset, aDart->mIndexCount, gApp->mDartMap.mTexture);
    
    aModelView.Reset();
    Graphics::MatrixModelViewSet(aModelView);
    mPhong.mUniform.mModelView.Set(aModelView);
    Graphics::PipelineStateSetShape3DAlphaBlending();
    
    /*
     aModelView.Reset();
     Graphics::MatrixModelViewSet(aModelView);
     mPhong.mUniform.mModelView.Set(aModelView);
     Graphics::PipelineStateSetShape3DAlphaBlending();
    
    float aDirSize = 5.0f;
    Graphics::SetColor(0.45f, 0.4f, 0.95f, 0.85f);
    Graphics::DrawBox(0.0f, 0.0f, 0.0f, mPhong.mUniform.mLight.mDirX * aDirSize, mPhong.mUniform.mLight.mDirY * aDirSize, mPhong.mUniform.mLight.mDirZ * aDirSize, 0.275f);
    */
    
    
    /*
    float aEyeSize = 10.0f;
    Graphics::SetColor(0.25f, 0.90f, 0.125f, 0.5f);
    Graphics::DrawBox(0.0f, 0.0f, 0.0f, mPhong.mUniform.mLight.mEyeDirX * aEyeSize, mPhong.mUniform.mLight.mEyeDirY * aEyeSize, mPhong.mUniform.mLight.mEyeDirZ * aEyeSize, 0.4f);
    */
    
    
    Graphics::DepthDisable();
}

void LightConfigurationScene::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    /*
    Graphics::SetColor(0.66f, 0.90f, 0.95f, 1.0f);
    Graphics::DrawPoint(mCenterX, mCenterY, 12.0f);
    Graphics::SetColor(0.25f, 0.75f, 0.25f, 1.0f);
    Graphics::DrawPoint(mCenterX, mCenterY, 8.0f);
    //
    Graphics::SetColor(0.0f, 0.66f, 0.66f, 0.66f);
    Graphics::DrawLine(mWidth2, mHeight2, mCenterX, mCenterY, 2.0f);
    */
    //
    
}


void LightConfigurationScene::TouchDown(float pX, float pY, void *pData) {
    
    mCamera.Print();
    mPhong.Print();
    
    
    mCenterX = pX;
    mCenterY = pY;
    
    
}

void LightConfigurationScene::TouchMove(float pX, float pY, void *pData) {
    
    mCenterX = pX;
    mCenterY = pY;
    
}

void LightConfigurationScene::TouchUp(float pX, float pY, void *pData) {

}

void LightConfigurationScene::TouchFlush() {

}

void LightConfigurationScene::KeyDown(int pKey) {

}

void LightConfigurationScene::KeyUp(int pKey) {
    
}

void LightConfigurationScene::Notify(void *pSender, const char *pNotification)  {
    
}

