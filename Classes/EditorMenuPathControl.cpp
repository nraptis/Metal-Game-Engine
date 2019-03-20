//
//  EditorMenuPathControl.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPathControl.hpp"
#include "EditorMenuPathControl.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuPathControl::EditorMenuPathControl(GamePathEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPathControl";
    
    mEditor = pEditor;
    
    
    SetTitle("Path Control");
    SetScrollMode(true);
    
    
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonCloseEditor = new UIButton();
    mButtonCloseEditor->SetText("Close Editor");
    mRowMain1->AddButton(mButtonCloseEditor);
    
    
    mButtonResetPath = new UIButton();
    mButtonResetPath->SetText("Reset Path");
    mRowMain1->AddButton(mButtonResetPath);
    
    
    
    
    
    mPathControls = new ToolMenuPanel();
    mPathControls->SetTitle("Main Primary Enhance");
    AddSection(mPathControls);
    
    mRowControls1 = new ToolMenuSectionRow();
    mPathControls->AddSection(mRowControls1);
    
    mButtonSavePath = new UIButton();
    mButtonSavePath->SetText("Save Path");
    mRowControls1->AddButton(mButtonSavePath);
    
    mButtonPrintPath = new UIButton();
    mButtonPrintPath->SetText("Print Path");
    mRowControls1->AddButton(mButtonPrintPath);
    
    mRowControls2 = new ToolMenuSectionRow();
    mPathControls->AddSection(mRowControls2);
    
    mButtonLoadPath = new UIButton();
    mButtonLoadPath->SetText("Load Path");
    mRowControls2->AddButton(mButtonLoadPath);
    
    
    
    
    
    DeactivateCloseButton();
}

EditorMenuPathControl::~EditorMenuPathControl() {
    
}

void EditorMenuPathControl::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuPathControl::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        if (pSender == mButtonCloseEditor) {
            mEditor->Close();
        }
        if (pSender == mButtonResetPath) {
            mEditor->PathReset();
        }
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}
