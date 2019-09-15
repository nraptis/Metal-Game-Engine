//
//  EditorMenuGameTestUtils.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuGameTestUtils.hpp"
#include "Game.hpp"
#include "GameContainer.hpp"

EditorMenuGameTestUtils::EditorMenuGameTestUtils() : ToolMenu() {
    
    mName = "EditorMenuGameTestUtils";
    SetTitle("Utilities");
    
    SetScrollMode(true);
    
    DeactivateCloseButton();

    Collapse();
}

EditorMenuGameTestUtils::~EditorMenuGameTestUtils() {
    if (gGameContainer != NULL) {
        if (gGameContainer->mEditorMenuUtils == this) {
            gGameContainer->mEditorMenuUtils = NULL;
        }
    }
}

void EditorMenuGameTestUtils::Layout() {
    ToolMenu::Layout();
    
}

void EditorMenuGameTestUtils::Notify(void *pSender, const char *pNotification) {
    
    if (gGame == NULL) { return; }
    if (gGameContainer == NULL) { return; }
    
}

void EditorMenuGameTestUtils::Update() {

    if (gGame == NULL) { return; }
    if (gGameContainer == NULL) { return; }
    
    
    
}
