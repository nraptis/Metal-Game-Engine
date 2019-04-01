//
//  CameraMenu.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "CameraMenu.hpp"
#include "PGMainCanvas.hpp"
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
    
    mSliderDummyRot1 = new UISlider();
    mSliderDummyRot1->SetTarget(&mCamera->mTarget.mX);
    mSliderDummyRot1->SetRange(0.0f, 360.0f);
    mSliderDummyRot1->SetText("MROT1:");
    mPanelTarget->AddSection(mSliderDummyRot1);
    
    mSliderDummyRot2 = new UISlider();
    mSliderDummyRot2->SetTarget(&mCamera->mTarget.mX);
    mSliderDummyRot2->SetRange(0.0f, 360.0f);
    mSliderDummyRot2->SetText("MROT2:");
    mPanelTarget->AddSection(mSliderDummyRot2);
    
    
    /*
    mSliderTargetX = new UISlider();
    mSliderTargetX->SetValue(&mCamera->mTarget.mX);
    mSliderTargetX->SetRange(-2.0f, 2.0f);
    mSliderTargetX->SetText("X:");
    mPanelTarget->AddSection(mSliderTargetX);
    
    mSliderTargetY = new UISlider();
    mSliderTargetY->SetValue(&mCamera->mTarget.mY);
    mSliderTargetY->SetRange(-2.0f, 2.0f);
    mSliderTargetY->SetText("Y:");
    mPanelTarget->AddSection(mSliderTargetY);
    
    mSliderTargetZ = new UISlider();
    mSliderTargetZ->SetValue(&mCamera->mTarget.mZ);
    mSliderTargetZ->SetRange(-2.0f, 2.0f);
    mSliderTargetZ->SetText("Z:");
    mPanelTarget->AddSection(mSliderTargetZ);
    */
    
    mPanelTarget->Collapse();
    
    
    mPanelDummy = new ToolMenuPanel();
    mPanelDummy->SetTitle("Reference Model");
    
    mSliderDummyX = new UISlider();
    mSliderDummyX->SetText("Mod-X:");
    mSliderDummyX->SetRange(-12.0f, 12.0f);
    mPanelDummy->AddSection(mSliderDummyX);
    
    mSliderDummyY = new UISlider();
    mSliderDummyY->SetText("Mod-Y:");
    mSliderDummyY->SetRange(-12.0f, 12.0f);
    mPanelDummy->AddSection(mSliderDummyY);
    
    mSliderDummyZ = new UISlider();
    mSliderDummyZ->SetText("Mod-Z:");
    mSliderDummyZ->SetRange(-10.0f, 10.0f);
    mPanelDummy->AddSection(mSliderDummyZ);
    
    mPanelDummy->Collapse();
    
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
