//
//  SimpleSpotLightMenu.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "SimpleSpotLightMenu.hpp"

//
//  PhongSimpleSpotLightMenu.cpp
//  MacMetal
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "LightConfigurationScene.hpp"
#include "SimpleSpotLightMenu.hpp"
#include "SpotLightSimpleConfiguration.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"

SimpleSpotLightMenu::SimpleSpotLightMenu(SpotLightSimpleConfiguration *pConfiguration) : ToolMenu() {
    mName = "SimpleSpotLightMenu";
    
    mConfig = pConfiguration;
    
    SetScrollMode(true);
    
    
    mSpotlightPanel = new ToolMenuPanel();
    mSpotlightPanel->SetTitle("Spotlight");
    AddSection(mSpotlightPanel);
    
    mStepperSpotlightX = new UIStepper();
    mStepperSpotlightX->SetTarget(&pConfiguration->mSpotlightX);
    mStepperSpotlightX->SetText("X:");
    mSpotlightPanel->AddSection(mStepperSpotlightX);
    
    mStepperSpotlightY = new UIStepper();
    mStepperSpotlightY->SetTarget(&pConfiguration->mSpotlightY);
    mStepperSpotlightY->SetText("Y:");
    mSpotlightPanel->AddSection(mStepperSpotlightY);
    
    mStepperSpotlightZ = new UIStepper();
    mStepperSpotlightZ->SetTarget(&pConfiguration->mSpotlightZ);
    mStepperSpotlightZ->SetText("Z:");
    mSpotlightPanel->AddSection(mStepperSpotlightZ);
    
    
    //mSpecularPanel = new ToolMenuPanel();
    //mSpecularPanel->SetTitle("Specular");
    //AddSection(mSpecularPanel);
    
    mSliderSpecularShininess = new UISlider();
    mSliderSpecularShininess->SetValue(&pConfiguration->mUniform.mLight.mShininess);
    mSliderSpecularShininess->SetRange(0.0f, 40.0f);
    mSliderSpecularShininess->SetText("Shininess:");
    AddSection(mSliderSpecularShininess);

    
    
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
    mSliderIntensityAmbient->SetRange(0.0f, 2.0f);
    mSliderIntensityAmbient->SetText("Ambient:");
    mIntensityPanel->AddSection(mSliderIntensityAmbient);
    
    mSliderIntensityDiffuse = new UISlider();
    mSliderIntensityDiffuse->SetValue(&pConfiguration->mUniform.mLight.mDiffuseIntensity);
    mSliderIntensityDiffuse->SetRange(0.0f, 2.0f);
    mSliderIntensityDiffuse->SetText("Diffuse:");
    mIntensityPanel->AddSection(mSliderIntensityDiffuse);
    
    mSliderIntensitySpecular = new UISlider();
    mSliderIntensitySpecular->SetValue(&pConfiguration->mUniform.mLight.mSpecularIntensity);
    mSliderIntensitySpecular->SetRange(0.0f, 10.0f);
    mSliderIntensitySpecular->SetText("Specular:");
    mIntensityPanel->AddSection(mSliderIntensitySpecular);
    
    mIntensityPanel->Collapse();
    
    DeactivateCloseButton();
    
    RefreshTestMode();
}

SimpleSpotLightMenu::~SimpleSpotLightMenu() {
    
}

void SimpleSpotLightMenu::Layout() {
    ToolMenu::Layout();
    
}


void SimpleSpotLightMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void SimpleSpotLightMenu::RefreshTestMode() {
    
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





