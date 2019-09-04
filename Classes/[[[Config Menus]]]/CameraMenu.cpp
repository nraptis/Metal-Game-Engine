//
//  CameraMenu.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "CameraMenu.hpp"
#include "FApp.hpp"

CameraMenu::CameraMenu(FloatingCamera *pCamera) : ToolMenu() {
    mName = "CameraMenu";
    mCamera = pCamera;
    
    SetScrollMode(true);
    //
    //
    /*
    mSliderAspectFOV = new UISlider();
    mSliderAspectFOV->SetText("FOV:");
    mSliderAspectFOV->SetValue(&mCamera->mFOV);
    mSliderAspectFOV->SetRange(0.075, M_PI);
    AddSection(mSliderAspectFOV);
    */
    //
    //
    mPanelView = new ToolMenuPanel();
    mPanelView->SetTitle("<--->");
    AddSection(mPanelView);
    //
    //
    mSliderViewRotationPrimary = new UISlider();
    mSliderViewRotationPrimary->SetText("R-1");
    mSliderViewRotationPrimary->SetTarget(&mCamera->mRotationPrimary);
    //mSliderViewRotationPrimary->SetRange(-180.0f, 360.0f);
    mSliderViewRotationPrimary->SetRange(0.0f, 360.0f);
    mPanelView->AddSection(mSliderViewRotationPrimary);
    //
    //
    mSliderViewRotationSecondary = new UISlider();
    mSliderViewRotationSecondary->SetText("R-1");
    mSliderViewRotationSecondary->SetTarget(&mCamera->mRotationSecondary);
    mSliderViewRotationSecondary->SetRange(-80.0f, 80.0f);
    mPanelView->AddSection(mSliderViewRotationSecondary);
    //
    //
    mSliderViewDistance = new UISlider();
    mSliderViewDistance->SetText("Distance");
    mSliderViewDistance->SetTarget(&mCamera->mDistance);
    mSliderViewDistance->SetRange(1.0f, 40.0f);
    mPanelView->AddSection(mSliderViewDistance);
    
    
    mPanelTarget = new ToolMenuPanel();
    mPanelTarget->SetTitle("Target");
    AddSection(mPanelTarget);
    
    
    
    mSliderTargetX = new UISlider();
    mSliderTargetX->SetTarget(&mCamera->mTarget.mX);
    mSliderTargetX->SetRange(-40.0f, 40.0f);
    mSliderTargetX->SetText("TX:");
    mPanelTarget->AddSection(mSliderTargetX);
    
    mSliderTargetY = new UISlider();
    mSliderTargetY->SetTarget(&mCamera->mTarget.mY);
    mSliderTargetY->SetRange(-40.0f, 40.0f);
    mSliderTargetY->SetText("TY:");
    mPanelTarget->AddSection(mSliderTargetY);
    
    mSliderTargetZ = new UISlider();
    mSliderTargetZ->SetTarget(&mCamera->mTarget.mZ);
    mSliderTargetZ->SetRange(-40.0f, 40.0f);
    mSliderTargetZ->SetText("TZ:");
    mPanelTarget->AddSection(mSliderTargetZ);
    
    mPanelTarget->Collapse();
    
    
    
    
    
    DeactivateCloseButton();
}

CameraMenu::~CameraMenu() {
    
}

void CameraMenu::Layout() {
    ToolMenu::Layout();
    
}


void CameraMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void CameraMenu::RefreshTestMode() {
    
}
