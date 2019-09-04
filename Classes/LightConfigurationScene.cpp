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
    
    mType = 2;
    
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
    mCameraMenu->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 320.0f), gDeviceHeight - (gSafeAreaInsetBottom + 280.0f), 320.0f, 280.0f);
    mCameraMenu->SetTitle("Cameras");
    mCameraMenu->mSliderDummyX->SetTarget(&mDummyObjectX);
    mCameraMenu->mSliderDummyY->SetTarget(&mDummyObjectY);
    mCameraMenu->mSliderDummyZ->SetTarget(&mDummyObjectZ);
    
    mCameraMenu->mSliderDummyRot1->SetTarget(&mDummyRot1);
    mCameraMenu->mSliderDummyRot2->SetTarget(&mDummyRot2);
    
    AddChild(mCameraMenu);
    
    
    mPhongLightMenu = NULL;
    
    
    if (mType == 0) {
    mDiffuseLightMenu = new DiffuseLightMenu(&mDiffuse);
    if (gDeviceWidth > 600) {
        mDiffuseLightMenu->SetFrame(20.0f, aPaddingTop, 500.0f, gDeviceHeight * 0.75f);
    } else {
        mDiffuseLightMenu->SetFrame(20.0f, aPaddingTop, gDeviceWidth * 0.8f, gDeviceHeight * 0.75f);
    }
    mDiffuseLightMenu->SetTitle("DIffuse Light");
    AddChild(mDiffuseLightMenu);
    } else if (mType == 1) {
        mPhongLightMenu = new PhongLightMenu(&mPhong);
        if (gDeviceWidth > 600) {
            mPhongLightMenu->SetFrame(20.0f, aPaddingTop, 500.0f, gDeviceHeight * 0.75f);
        } else {
            mPhongLightMenu->SetFrame(20.0f, aPaddingTop, gDeviceWidth * 0.8f, gDeviceHeight * 0.75f);
        }
        mPhongLightMenu->SetTitle("Phong Light");
        AddChild(mPhongLightMenu);
    } else if (mType == 2) {
        mPhongLightMenu = new PhongLightMenu(&mPhong);
        if (gDeviceWidth > 600) {
            mPhongLightMenu->SetFrame(20.0f, aPaddingTop, 500.0f, gDeviceHeight * 0.75f);
        } else {
            mPhongLightMenu->SetFrame(20.0f, aPaddingTop, gDeviceWidth * 0.8f, gDeviceHeight * 0.75f);
        }
        mPhongLightMenu->SetTitle("Phong Light");
        AddChild(mPhongLightMenu);
    } else if (mType == 3) {
        mSpotlightMenu = new SimpleSpotLightMenu(&mSpotlight);
        if (gDeviceWidth > 600) {
            mSpotlightMenu->SetFrame(20.0f, aPaddingTop, 500.0f, gDeviceHeight * 0.75f);
        } else {
            mSpotlightMenu->SetFrame(20.0f, aPaddingTop, gDeviceWidth * 0.8f, gDeviceHeight * 0.75f);
        }
        mSpotlightMenu->SetTitle("Spotlight");
        AddChild(mSpotlightMenu);
    }
    
    /*
    
    */
    
    /*
    
    */
    
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
    
    if (mType == 0) {
        mDiffuse.Compute();
    } else if (mType == 1) {
        mPhong.Compute();
    } else if (mType == 2) {
        mPhong.Compute();
    } else if (mType == 3) {
        mSpotlight.Compute();
    }
    
   
    
    
    
    
    mDisableLight = gRand.GetBool();
    mDisableLight = false;
    
    
    float aAbsoluteCenterX = gAppBase->mWindowMain.mRoot.mX + gAppBase->mWindowMain.mRoot.mWidth2;
    float aAbsoluteCenterY = gAppBase->mWindowMain.mRoot.mY + gAppBase->mWindowMain.mRoot.mHeight2;
    mCamera.mCenterOffset = FVec2(gDeviceWidth2 - aAbsoluteCenterX, gDeviceHeight2 - aAbsoluteCenterY);
    
    
    
    
    
    Graphics::DepthEnable();
    Graphics::CullFacesSetDisabled();
    
    //Graphics::DepthClear();
    
    
    FModelDataPacked *aDart = &(gWadModels.mDartRegular[0]);
    FModelDataPacked *aBalloon = &(gApp->mBalloon);
    
    
    FModelDataPacked *aGround = &(gApp->mGround);
    
    
    
    static float mScrapScaleSin = 0.0f;
    mScrapScaleSin += 1.0f;
    if (mScrapScaleSin >= 360.0f) {
        mScrapScaleSin -= 360.0f;
    }
    
    float aScale = 0.65f + (Sin(mScrapScaleSin) + 1.0f) * 0.5f * 1.0f;
    
    
    FMatrix aProjection = mCamera.GetProjection();
    Graphics::SetColor();
    
    FMatrix aModelView;
    aModelView.RotateX(90.0f);
    
    FMatrix aNormal;
    FMatrix aModelViewHome;
    
    //
    /*
    mCenterOffset
    //
    float aProjectionShiftX = mCamera.mDistance / aScreenCenterOffsetX;
    float aProjectionShiftY = mCamera.mDistance / aScreenCenterOffsetY;
    //
    aProjection.Translate(aProjectionShiftX, aProjectionShiftY);
    */
    
    aModelView.Translate(-3.0f, 0.0f);
    aModelView.Scale(aScale);
    
    
    aNormal.SetNormalMatrix(aModelView);
    aModelViewHome.Set(aModelView);
    aModelViewHome.ResetTranslation();
    
    Graphics::MatrixProjectionSet(aProjection);
    Graphics::MatrixModelViewSet(aModelView);
    mPhong.mUniform.mProjection.Set(aProjection);
    mPhong.mUniform.mModelView.Set(aModelView);
    mPhong.mUniform.mNormal.Set(aNormal);
    mDiffuse.mUniform.mProjection.Set(aProjection);
    mDiffuse.mUniform.mModelView.Set(aModelView);
    mDiffuse.mUniform.mNormal.Set(aNormal);
    mSpotlight.mUniform.mProjection.Set(aProjection);
    mSpotlight.mUniform.mModelView.Set(aModelView);
    mSpotlight.mUniform.mNormal.Set(aNormal);
    
    
    
    FModelDataPacked *aTree = &(gApp->mPalmLeaves);
    FModelDataPacked *aTrunk = &(gApp->mPalmTrunk);
    
    if (mDisableLight) {
        Graphics::PipelineStateSetModelIndexedAlphaBlending();
    } else {
        
        if (mType == 0) {
            Graphics::PipelineStateSetModelIndexedLightedDiffuseAlphaBlending();
        } else if (mType == 1) {
            Graphics::PipelineStateSetModelIndexedLightedPhongAlphaBlending();
        } else if (mType == 2) {
            Graphics::PipelineStateSetModelIndexedLightedPhongOverlayAlphaBlending();
        } else if (mType == 3) {
            //Graphics::PipelineStateSetModelIndexedLightedSimpleSpotlightNoBlending();
            
        }
    }
    
    float aAlpha = 1.0f;
    mPhong.mUniform.mColor.mAlpha = aAlpha;
    mPhong.mUniform.mColor.mAlpha = aAlpha;
    
    
    
    if (mDisableLight) {
        Graphics::UniformBind();
    } else {
        if (mType == 0) { Graphics::UniformBind(&mDiffuse.mUniform);
        } else if (mType == 1) { Graphics::UniformBind(&mPhong.mUniform);
        } else if (mType == 2) { Graphics::UniformBind(&mPhong.mUniform);
        } else if (mType == 3) { }
    }
    Graphics::DrawTrianglesIndexedWithPackedBuffers(aTrunk->mBuffer, 0, aTrunk->mIndex, aTrunk->mIndexCount, gApp->mPalmTrunkMap.mTexture);
    
    
    if (mDisableLight) {
        Graphics::UniformBind();
    } else {
        if (mType == 0) { Graphics::UniformBind(&mDiffuse.mUniform);
        } else if (mType == 1) { Graphics::UniformBind(&mPhong.mUniform);
        } else if (mType == 2) { Graphics::UniformBind(&mPhong.mUniform);
        } else if (mType == 3) { }
    }
    Graphics::DrawTrianglesIndexedWithPackedBuffers(aTree->mBuffer, 0, aTree->mIndex, aTree->mIndexCount, gApp->mPalmLeavesMap.mTexture);

    
    static float mBalloonRot = 0.0f;
    mBalloonRot += 1.0f;
    if (mBalloonRot >= 360.0f) { mBalloonRot -= 360.0f; }
    
    
    float aExtraRot = 0.0f;
    
    int aBalloonIndex = 0;
    
    /*
    for (float aX=-4.0f;aX<=4.0f;aX+=1.0f) {
        for (float aY=-4.0f;aY<=4.0f;aY+=1.0f) {
            
            aModelView.Reset();
            aModelView.Translate(aX * 5.0f, aY * 7.0f);
            aModelView.RotateX(90);
            aModelView.RotateZ(mBalloonRot + aExtraRot);
            aModelView.Scale(aScale);
            
            aNormal.SetNormalMatrix(aModelView);
            aModelViewHome.Set(aModelView);
            aModelViewHome.ResetTranslation();
            
            
            Graphics::MatrixProjectionSet(aProjection);
            Graphics::MatrixModelViewSet(aModelView);
            mPhong.mUniform.mProjection.Set(aProjection);
            mPhong.mUniform.mModelView.Set(aModelView);
            mPhong.mUniform.mNormal.Set(aNormal);
            
            
            mDiffuse.mUniform.mProjection.Set(aProjection);
            mDiffuse.mUniform.mModelView.Set(aModelView);
            mDiffuse.mUniform.mNormal.Set(aNormal);
            mSpotlight.mUniform.mProjection.Set(aProjection);
            mSpotlight.mUniform.mModelView.Set(aModelView);
            mSpotlight.mUniform.mNormal.Set(aNormal);
            
            
            if (mDisableLight) {
                Graphics::UniformBind();
            } else {
                
                if (mType == 0) {
                    Graphics::UniformBind(&mDiffuse.mUniform);
                } else if (mType == 1) {
                    Graphics::UniformBind(&mPhong.mUniform);
                } else if (mType == 2) {
                    Graphics::UniformBind(&mPhong.mUniform);
                } else if (mType == 3) {
                    
                }
                
                //
            }
            Graphics::DrawTrianglesIndexedWithPackedBuffers(aBalloon->mBuffer, 0, aBalloon->mIndex, aBalloon->mIndexCount, gApp->mBalloonMap[aBalloonIndex].mTexture);
            
            
            aBalloonIndex += 1;
            if (aBalloonIndex == 5) { aBalloonIndex = 0; }
            
            aExtraRot += 5.0f;
        }
    }
    */
    
    
    Graphics::DepthDisable();


    
    Graphics::PipelineStateSetShape3DNoBlending();
    Graphics::MatrixModelViewReset();
    
    float aDirX = 0.0f;
    float aDirY = 0.0f;
    float aDirZ = 0.0f;
    
    aDirX = mPhong.mUniform.mLight.mDirX;
    aDirY = mPhong.mUniform.mLight.mDirY;
    aDirZ = mPhong.mUniform.mLight.mDirZ;
    
    Graphics::SetColor(1.0f, 0.0f, 0.25f, 1.0f);
    Graphics::DrawBox(0.0f, 0.0f, 0.0f, aDirX * 8.0f, aDirY * 8.0f, aDirZ * 8.0f, 0.5f);
    

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

    Graphics::SetColor(0.5f, 0.25f, 0.125f, 0.65f);
    Graphics::DrawLine(0.0f, 0.0, mWidth, mHeight);
    Graphics::DrawLine(0.0f, mWidth, 0.0f, mHeight);
    */
    
    
}


void LightConfigurationScene::TouchDown(float pX, float pY, void *pData) {
    
    mCamera.Print();
    mPhong.Print();
    
    //mSpotlight.Print();
    
    
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

