//
//  EditorMenuFormation.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormation.hpp"
#include "GameFormationEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuFormation::EditorMenuFormation(GameFormationEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuFormation";
    
    mEditor = pEditor;
    
    SetTitle("Formation Builder");
    SetScrollMode(true);
    
    mPanelMain = new ToolMenuPanel();
    mPanelMain->SetTitle("Control");
    AddSection(mPanelMain);
    
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonSaveFormation = new UIButton();
    mButtonSaveFormation->SetText("Save...");
    mRowMain1->AddButton(mButtonSaveFormation);
    
    mButtonLoadFormation = new UIButton();
    mButtonLoadFormation->SetText("Load...");
    mRowMain1->AddButton(mButtonLoadFormation);
    
    mButtonPrintFormation = new UIButton();
    mButtonPrintFormation->SetText("Print");
    mRowMain1->AddButton(mButtonPrintFormation);
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(3);
    mSegmentMode->SetTitles("Add Point", "Move Point", "Select Point");
    mSegmentMode->SetTarget(&mEditor->mFormationMode);
    mPanelMain->AddSection(mSegmentMode);
    
    
    mSliderRotation = new UISlider();
    mSliderRotation->SetText("Rotate:");
    if (mEditor) {
        mSliderRotation->SetTarget(&(mEditor->mFormation.mRotation));
    }
    mSliderRotation->SetRange(0.0f, 360.0f);
    mPanelMain->AddSection(mSliderRotation);
    
    
    
    
    mPanelNodes = new ToolMenuPanel();
    mPanelNodes->SetTitle("Nodes");
    AddSection(mPanelNodes);
    
    
    mRowNodes1 = new ToolMenuSectionRow();
    mPanelNodes->AddSection(mRowNodes1);
    
    mButtonDeleteNode = new UIButton();
    mButtonDeleteNode->SetText("Delete Node");
    mRowNodes1->AddButton(mButtonDeleteNode);
    
    
    
    DeactivateCloseButton();
}

EditorMenuFormation::~EditorMenuFormation() {
    
}

void EditorMenuFormation::Layout() {
    ToolMenu::Layout();
    
}

void EditorMenuFormation::Update() {
    ToolMenu::Update();
    
    /*
    if (mCheckBoxSmooth) {
        bool aUnlink = true;
        if (mEditor->mWave != NULL) {
            aUnlink = false;
            mCheckBoxSmooth->SetTarget(&(mEditor->mWave->mPath.mSmooth));
        }
        if (aUnlink) {
            mCheckBoxSmooth->SetTarget(NULL);
        }
    }
    */
    
}
//

void EditorMenuFormation::Notify(void *pSender, const char *pNotification) {
    
    if (mEditor == NULL) { return; }
    
    if (pSender == mButtonDeleteNode) { mEditor->DeleteNode(); }
    if (pSender == mButtonPrintFormation) { mEditor->Print(); }
    if (pSender == mButtonSaveFormation) { mEditor->Save(); }
    if (pSender == mButtonLoadFormation) { mEditor->Load(); }
    if (pSender == mSliderRotation) { mEditor->Refresh(); }
}
