//
//  EditorMenuFormationUtilities.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormationUtilities.hpp"
#include "GameFormationEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuFormationUtilities::EditorMenuFormationUtilities(GameFormationEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuFormationUtilities";
    
    mEditor = pEditor;
    
    
    SetTitle("Formation Utils");
    SetScrollMode(true);
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonCloseEditor = new UIButton();
    mButtonCloseEditor->SetText("Close Editor");
    mRowMain1->AddButton(mButtonCloseEditor);
    
    
    mButtonResetFormation = new UIButton();
    mButtonResetFormation->SetText("Reset");
    mRowMain1->AddButton(mButtonResetFormation);
    
    
    
    
    mPanelTracers = new ToolMenuPanel();
    mPanelTracers->SetTitle("Tracers");
    AddSection(mPanelTracers);
    
    mRowTracers1 = new ToolMenuSectionRow();
    mPanelTracers->AddSection(mRowTracers1);
    
    
    mCheckBoxTracersEnabled = new UICheckBox();
    mCheckBoxTracersEnabled->SetText("Tracers Enabled");
    mCheckBoxTracersEnabled->SetTarget(&mEditor->mTracerEnabled);
    mRowTracers1->AddCheckBox(mCheckBoxTracersEnabled);
    
    mButtonDeleteTracer = new UIButton();
    mButtonDeleteTracer->SetText("Delete Tracer");
    mRowTracers1->AddButton(mButtonDeleteTracer);
    
    
    mSegmentTracersMode = new UISegment();
    mSegmentTracersMode->SetSegmentCount(3);
    mSegmentTracersMode->SetTitles("Add Point", "Move Point", "Select Point");
    mSegmentTracersMode->SetTarget(&mEditor->mTracerMode);
    mPanelTracers->AddSection(mSegmentTracersMode);
    
    
    DeactivateCloseButton();
}

EditorMenuFormationUtilities::~EditorMenuFormationUtilities() {
    
}

void EditorMenuFormationUtilities::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuFormationUtilities::Notify(void *pSender, const char *pNotification) {
    
    if (pSender == mButtonCloseEditor) { mEditor->Close(); }
    
    if (pSender == mButtonResetFormation) { mEditor->Clear(); }
    
    if (pSender == mButtonResetFormation) {
        
    }
}

void EditorMenuFormationUtilities::Update() {
    
}
