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

