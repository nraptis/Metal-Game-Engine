//
//  DiffuseLightMenu.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/25/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "DiffuseLightMenu.hpp"


//
//  PhongDiffuseLightMenu.cpp
//  MacMetal
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "LightConfigurationScene.hpp"
#include "DiffuseLightMenu.hpp"
#include "DiffuseConfiguration.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"

DiffuseLightMenu::DiffuseLightMenu(DiffuseConfiguration *pConfiguration) : ToolMenu() {
    mName = "DiffuseLightMenu";
    
    mDiffuse = pConfiguration;
    
    SetScrollMode(true);
    

    
    mDirectionPanel = new ToolMenuPanel();
    mDirectionPanel->SetTitle("Directions");
    AddSection(mDirectionPanel);
    
    mSliderDirectionRotationPrimary = new UISlider();
    mSliderDirectionRotationPrimary->SetValue(&pConfiguration->mDirectionRotationPrimary);
    mSliderDirectionRotationPrimary->SetRange(0.0f, 360.0f);
    mSliderDirectionRotationPrimary->SetText("Dir-R1:");
    mDirectionPanel->AddSection(mSliderDirectionRotationPrimary);
    
    
    mSliderDirectionRotationSecondary = new UISlider();
    mSliderDirectionRotationSecondary->SetValue(&pConfiguration->mDirectionRotationSecondary);
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
    mSliderColorR->SetValue(&pConfiguration->mUniform.mLight.mRed);
    mSliderColorR->SetRange(0.0f, 1.0f);
    mSliderColorR->SetText("Red:");
    mColorPanel->AddSection(mSliderColorR);
    
    mSliderColorG = new UISlider();
    mSliderColorG->SetValue(&pConfiguration->mUniform.mLight.mGreen);
    mSliderColorG->SetRange(0.0f, 1.0f);
    mSliderColorG->SetText("Green:");
    mColorPanel->AddSection(mSliderColorG);
    
    mSliderColorB = new UISlider();
    mSliderColorB->SetValue(&pConfiguration->mUniform.mLight.mBlue);
    mSliderColorB->SetRange(0.0f, 1.0f);
    mSliderColorB->SetText("Blue:");
    mColorPanel->AddSection(mSliderColorB);
    
    mColorPanel->Collapse();
    
    
    
    
    
    
    mIntensityPanel = new ToolMenuPanel();
    mIntensityPanel->SetTitle("Intensity");
    AddSection(mIntensityPanel);
    
    mSliderIntensityAmbient = new UISlider();
    mSliderIntensityAmbient->SetValue(&pConfiguration->mUniform.mLight.mAmbientIntensity);
    mSliderIntensityAmbient->SetRange(0.0f, 1.0f);
    mSliderIntensityAmbient->SetText("Ambient:");
    mIntensityPanel->AddSection(mSliderIntensityAmbient);
    
    mSliderIntensityDiffuse = new UISlider();
    mSliderIntensityDiffuse->SetValue(&pConfiguration->mUniform.mLight.mDiffuseIntensity);
    mSliderIntensityDiffuse->SetRange(0.0f, 1.0f);
    mSliderIntensityDiffuse->SetText("Diffuse:");
    mIntensityPanel->AddSection(mSliderIntensityDiffuse);
    
    
    DeactivateCloseButton();
    
    RefreshTestMode();
}

DiffuseLightMenu::~DiffuseLightMenu() {
    
}

void DiffuseLightMenu::Layout() {
    ToolMenu::Layout();
    
}


void DiffuseLightMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void DiffuseLightMenu::RefreshTestMode() {
    
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





