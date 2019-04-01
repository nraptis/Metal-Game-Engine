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
    
    
    
    
    
    
    DeactivateCloseButton();
}

EditorMenuFormationUtilities::~EditorMenuFormationUtilities() {
    
}

void EditorMenuFormationUtilities::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuFormationUtilities::Notify(void *pSender, const char *pNotification) {
    
    if (pSender == mButtonCloseEditor) {
        mEditor->Close();
    }
    
    if (pSender == mButtonResetFormation) {
        
    }
}

void EditorMenuFormationUtilities::Update() {
    
}
