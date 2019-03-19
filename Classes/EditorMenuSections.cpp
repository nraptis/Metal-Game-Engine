//
//  EditorMenuSections.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuSections.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuSections.hpp"
#include "PhongConfiguration.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuSections::EditorMenuSections(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuSections";
    
    mEditor = pEditor;
    
    
    SetTitle("Section Editor");
    SetScrollMode(true);
    
    
    
    
    
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonNewSection = new UIButton();
    mButtonNewSection->SetText("New Section");
    mRowMain1->AddButton(mButtonNewSection);
    
    mButtonSaveSection = new UIButton();
    mButtonSaveSection->SetText("Save..");
    mRowMain1->AddButton(mButtonSaveSection);
    
    mButtonLoadSection = new UIButton();
    mButtonLoadSection->SetText("Load..");
    mRowMain1->AddButton(mButtonLoadSection);
    
    mRowMain2 = new ToolMenuSectionRow();
    AddSection(mRowMain2);
    

    mPathPanel = new ToolMenuPanel();
    mPathPanel->SetTitle("Path Editor");
    AddSection(mPathPanel);
    
    mRowPath1 = new ToolMenuSectionRow();
    mPathPanel->AddSection(mRowPath1);
    
    
    mButtonEditPaths = new UIButton();
    mButtonEditPaths->SetText("Edit Paths");
    mRowPath1->AddButton(mButtonEditPaths);
    
    mButtonSelectNextPath = new UIButton();
    mButtonSelectNextPath->SetText("Next Paths");
    mRowPath1->AddButton(mButtonSelectNextPath);
    
    mButtonSelectPreviousPath = new UIButton();
    mButtonSelectPreviousPath->SetText("Prev Paths");
    mRowPath1->AddButton(mButtonSelectPreviousPath);
    
    
    mRowPath2 = new ToolMenuSectionRow();
    mPathPanel->AddSection(mRowPath2);
    
    
    /*
    mSpecularPanel = new ToolMenuPanel();
    mSpecularPanel->SetTitle("Specular");
    AddSection(mSpecularPanel);
    
    mSliderSpecularShininess = new UISlider();
    mSliderSpecularShininess->SetRange(0.0f, 40.0f);
    mSliderSpecularShininess->SetText("Shininess:");
    mSpecularPanel->AddSection(mSliderSpecularShininess);
    
    
    mSliderSpecularEyeRotationPrimary = new UISlider();
    
    mSliderSpecularEyeRotationPrimary->SetRange(0.0f, 360.0f);
    mSliderSpecularEyeRotationPrimary->SetText("Eye-R1:");
    mSpecularPanel->AddSection(mSliderSpecularEyeRotationPrimary);
    
    mSliderSpecularEyeRotationSecondary = new UISlider();
    
    mSliderSpecularEyeRotationSecondary->SetRange(0.0f, 360.0f);
    mSliderSpecularEyeRotationSecondary->SetText("Eye-R2:");
    mSpecularPanel->AddSection(mSliderSpecularEyeRotationSecondary);
    
    
    
    
    mDirectionPanel = new ToolMenuPanel();
    mDirectionPanel->SetTitle("Directions");
    AddSection(mDirectionPanel);
    
    mSliderDirectionRotationPrimary = new UISlider();
    
    mSliderDirectionRotationPrimary->SetRange(0.0f, 360.0f);
    mSliderDirectionRotationPrimary->SetText("Dir-R1:");
    mDirectionPanel->AddSection(mSliderDirectionRotationPrimary);
    
    
    mSliderDirectionRotationSecondary = new UISlider();
    
    mSliderDirectionRotationSecondary->SetRange(0.0f, 360.0f);
    mSliderDirectionRotationSecondary->SetText("Dir-R2:");
    mDirectionPanel->AddSection(mSliderDirectionRotationSecondary);
    
*/
    
    
    /*
    
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
    
    mSliderIntensitySpecular = new UISlider();
    mSliderIntensitySpecular->SetValue(&pConfiguration->mUniform.mLight.mSpecularIntensity);
    mSliderIntensitySpecular->SetRange(0.0f, 1.0f);
    mSliderIntensitySpecular->SetText("Specular:");
    mIntensityPanel->AddSection(mSliderIntensitySpecular);
    
    mIntensityPanel->Collapse();
     
    */
    
    DeactivateCloseButton();
}

EditorMenuSections::~EditorMenuSections() {
    
}

void EditorMenuSections::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuSections::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        if (pSender == mButtonEditPaths) {
            mEditor->OpenPathEditor();
        }
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}
