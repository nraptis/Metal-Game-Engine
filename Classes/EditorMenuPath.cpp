//
//  EditorMenuPathMain.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPath.hpp"
#include "EditorMenuPath.hpp"
#include "GamePathEditor.hpp"
#include "FApp.hpp"

EditorMenuPath::EditorMenuPath(GamePathEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPath";
    
    mEditor = pEditor;
    
    
    SetTitle("Path Tools");
    SetScrollMode(true);
    
    
    mPathControls = new ToolMenuPanel();
    mPathControls->SetTitle("Main Primary Enhance");
    AddSection(mPathControls);
    
    mRowControls1 = new ToolMenuSectionRow();
    mPathControls->AddSection(mRowControls1);
    
    
    mButtonPrintPath = new UIButton();
    mButtonPrintPath->SetText("Print Path");
    mRowControls1->AddButton(mButtonPrintPath);
    
    mButtonSavePath = new UIButton();
    mButtonSavePath->SetText("Save Path");
    mRowControls1->AddButton(mButtonSavePath);
    
    mButtonLoadPath = new UIButton();
    mButtonLoadPath->SetText("Load Path");
    mRowControls1->AddButton(mButtonLoadPath);
    
    
    mEditorPanel = new ToolMenuPanel();
    mEditorPanel->SetTitle("Edit Paths");
    AddSection(mEditorPanel);
    
    
    mSegmentMode = new UISegment();
    mSegmentMode->SetSegmentCount(4);
    mSegmentMode->SetTitles("A", "B", "C", "D");
    mSegmentMode->SetTarget(&mEditor->mPathMode);
    mEditorPanel->AddSection(mSegmentMode);
    
    
    
    mRowVisuals = new ToolMenuSectionRow();
    mEditorPanel->AddSection(mRowVisuals);
    
    
    mCheckBoxSmooth = new UICheckBox();
    mCheckBoxSmooth->SetText("Smoothing");
    mRowVisuals->AddCheckBox(mCheckBoxSmooth);
    
    
    mCheckBoxPreview = new UICheckBox();
    mCheckBoxPreview->SetText("Preview");
    mRowVisuals->AddCheckBox(mCheckBoxPreview);
    
    mRowAlignment = new ToolMenuSectionRow();
    mEditorPanel->AddSection(mRowAlignment);
    
    mLabelA1 = new UILabel();
    mLabelA1->SetText("Alignment 1:");
    mRowAlignment->AddLabel(mLabelA1);
    
    mAlignmentPicker1 = new UIAlignmentPicker();
    mRowAlignment->AddAlignmentPicker(mAlignmentPicker1);
    
    
    mLabelA2 = new UILabel();
    mLabelA2->SetText("A 2:");
    mRowAlignment->AddLabel(mLabelA2);
    
    mAlignmentPicker2 = new UIAlignmentPicker();
    mRowAlignment->AddAlignmentPicker(mAlignmentPicker2);
    
    

    /*
    ToolMenuSectionRow                      *mSectionVisuals;
    UICheckBox                              *mCheckBoxSmooth;
    UICheckBox                              *mCheckBoxPreview;
    
    
    UIButton                                *mButtonEditPaths;
    UIAlignmentPicker                       *;
    UIAlignmentPicker                       *;
    
    */
    
    DeactivateCloseButton();
}

EditorMenuPath::~EditorMenuPath() {
    
}

void EditorMenuPath::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuPath::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        if (pSender == mButtonPrintPath) {
            //mEditor->OpenPathEditor();
            
        }
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}
