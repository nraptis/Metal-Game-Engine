//
//  EditorMenuSpawn.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuSpawn.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuSpawn.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuSpawn::EditorMenuSpawn(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuSpawn";
    
    mEditor = pEditor;
    
    SetTitle("Miiioooo Mennuu");
    SetScrollMode(true);
}

EditorMenuSpawn::~EditorMenuSpawn() {
    if (gEditor->mMenuSpawn == this) {
        gEditor->mMenuSpawn = NULL;
    }
}

void EditorMenuSpawn::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuSpawn::Notify(void *pSender, const char *pNotification) {
    
    if (FString("slider_update") == pNotification) {
        
    }
    
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
    
    if (FString(pNotification) == "stepper") {
        UIStepper *aStepper = (UIStepper *)pSender;
    }
}

void EditorMenuSpawn::Update() {
    
}
