//
//  GameTestRunningMainMenu.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "GameTestRunningMainMenu.hpp"
#include "LightConfigurationScene.hpp"
#include "GameTestRunningMainMenu.hpp"
#include "PhongConfiguration.hpp"
#include "FApp.hpp"

GameTestRunningMainMenu::GameTestRunningMainMenu(Game *pGame) : ToolMenu() {
    mName = "GameTestRunningMainMenu";
    
    SetScrollMode(true);
    
    mMainPanel = new ToolMenuPanel();
    mMainPanel->SetTitle("Main Flow");
    AddSection(mMainPanel);
    
    mRowMain1 = new ToolMenuSectionRow();
    mMainPanel->AddSection(mRowMain1);
    
    mRowMain2 = new ToolMenuSectionRow();
    mMainPanel->AddSection(mRowMain2);
    
    mRowMain3 = new ToolMenuSectionRow();
    mMainPanel->AddSection(mRowMain3);
    
    mButtonRestart = new UIButton();
    mButtonRestart->SetText("Restart");
    mRowMain1->AddButton(mButtonRestart);
    
    mButtonPause = new UIButton();
    mButtonPause->SetText("Pause");
    mRowMain1->AddButton(mButtonPause);
    
    DeactivateCloseButton();
    
}

GameTestRunningMainMenu::~GameTestRunningMainMenu() {
    
}

void GameTestRunningMainMenu::Layout() {
    ToolMenu::Layout();
    
}


void GameTestRunningMainMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}
