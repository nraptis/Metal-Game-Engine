//
//  PhongPhongLightMenu.cpp
//  MacMetal
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "LightConfigurationScene.hpp"
#include "PhongLightMenu.hpp"
#include "PhongConfiguration.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"

PhongLightMenu::PhongLightMenu(PhongConfiguration *pConfiguration) : ToolMenu() {
    mName = "PhongLightMenu";
    
    mPhong = pConfiguration;
    
    SetScrollMode(true);
    
    mSpecularPanel = new ToolMenuPanel();
    mSpecularPanel->SetTitle("Specular");
    AddSection(mSpecularPanel);
    
    mSliderSpecularShininess = new UISlider();
    mSliderSpecularShininess->SetTarget(&pConfiguration->mUniform.mLight.mShininess);
    mSliderSpecularShininess->SetRange(0.0f, 128.0f);
    mSliderSpecularShininess->SetText("Shininess:");
    mSpecularPanel->AddSection(mSliderSpecularShininess);
    
    
    mDirectionPanel = new ToolMenuPanel();
    mDirectionPanel->SetTitle("Directions");
    AddSection(mDirectionPanel);
    
    mSliderDirectionRotationPrimary = new UISlider();
    mSliderDirectionRotationPrimary->SetTarget(&pConfiguration->mDirectionRotationPrimary);
    mSliderDirectionRotationPrimary->SetRange(0.0f, 360.0f);
    mSliderDirectionRotationPrimary->SetText("Dir-R1:");
    mDirectionPanel->AddSection(mSliderDirectionRotationPrimary);
    
    
    mSliderDirectionRotationSecondary = new UISlider();
    mSliderDirectionRotationSecondary->SetTarget(&pConfiguration->mDirectionRotationSecondary);
    mSliderDirectionRotationSecondary->SetRange(0.0f, 360.0f);
    mSliderDirectionRotationSecondary->SetText("Dir-R2:");
    mDirectionPanel->AddSection(mSliderDirectionRotationSecondary);
    
    
    /*
    
    ToolMenuPanel                           *;
    UISlider                                *;
    UISlider                                *;
    
    */
    
    mColorPanel = new ToolMenuPanel();
    mColorPanel->SetTitle("Color");
    AddSection(mColorPanel);
    
    mSliderColorR = new UISlider();
    mSliderColorR->SetTarget(&pConfiguration->mUniform.mLight.mRed);
    mSliderColorR->SetRange(0.0f, 1.0f);
    mSliderColorR->SetText("Red:");
    mColorPanel->AddSection(mSliderColorR);
    
    mSliderColorG = new UISlider();
    mSliderColorG->SetTarget(&pConfiguration->mUniform.mLight.mGreen);
    mSliderColorG->SetRange(0.0f, 1.0f);
    mSliderColorG->SetText("Green:");
    mColorPanel->AddSection(mSliderColorG);
    
    mSliderColorB = new UISlider();
    mSliderColorB->SetTarget(&pConfiguration->mUniform.mLight.mBlue);
    mSliderColorB->SetRange(0.0f, 1.0f);
    mSliderColorB->SetText("Blue:");
    mColorPanel->AddSection(mSliderColorB);
    
    mColorPanel->Collapse();

    
    
    
    
    
    mIntensityPanel = new ToolMenuPanel();
    mIntensityPanel->SetTitle("Intensity");
    AddSection(mIntensityPanel);
    
    mSliderIntensityAmbient = new UISlider();
    mSliderIntensityAmbient->SetTarget(&pConfiguration->mUniform.mLight.mAmbientIntensity);
    mSliderIntensityAmbient->SetRange(0.0f, 1.0f);
    mSliderIntensityAmbient->SetText("Ambient:");
    mIntensityPanel->AddSection(mSliderIntensityAmbient);
    
    mSliderIntensityDiffuse = new UISlider();
    mSliderIntensityDiffuse->SetTarget(&pConfiguration->mUniform.mLight.mDiffuseIntensity);
    mSliderIntensityDiffuse->SetRange(0.0f, 1.0f);
    mSliderIntensityDiffuse->SetText("Diffuse:");
    mIntensityPanel->AddSection(mSliderIntensityDiffuse);
    
    mSliderIntensitySpecular = new UISlider();
    mSliderIntensitySpecular->SetTarget(&pConfiguration->mUniform.mLight.mSpecularIntensity);
    mSliderIntensitySpecular->SetRange(0.0f, 5.0f);
    mSliderIntensitySpecular->SetText("Specular:");
    mIntensityPanel->AddSection(mSliderIntensitySpecular);
    
    mIntensityPanel->Collapse();
    
    DeactivateCloseButton();
    
    RefreshTestMode();
}

PhongLightMenu::~PhongLightMenu() {
    
}

void PhongLightMenu::Layout() {
    ToolMenu::Layout();
    
}


void PhongLightMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void PhongLightMenu::RefreshTestMode() {
    
    /*
     if (gArena->mTestMode == TEST_MODE_NONE) {
     mMarkerDrawingPanel->Activate();
     mMarkerDrawingPanel->Expand();
     } else {
     mMarkerDrawingPanel->Deactivate();
     }
     
     if (gArena->mTestMode == TEST_MODE_UNIT_GROUP_CREATE) {
     mUnitGroupDragCreationPanel->Activate();
     mUnitGroupDragCreationPanel->Expand();
     } else {
     mUnitGroupDragCreationPanel->Deactivate();
     }
     
     if (gArena->mTestMode == TEST_MODE_UNIT_GROUP_SELECT) {
     
     }
     
     if (gArena->mTestMode == TEST_MODE_ITEM_CREATE) {
     
     }
     
     if (gArena->mTestMode == TEST_MODE_ITEM_SELECT) {
     
     }
     
     if (gArena->mTestMode == TEST_MODE_UNIT_SPAWN) {
     mUnitGroupSingleCreationPanel->Activate();
     mUnitGroupSingleCreationPanel->Expand();
     } else {
     mUnitGroupSingleCreationPanel->Deactivate();
     }
     */
}





