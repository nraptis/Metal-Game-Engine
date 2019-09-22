//
//  StatsMenu.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "StatsMenu.hpp"

//
//  StatsMenu.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "StatsMenu.hpp"
#include "FApp.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"
#include "GameEditor.hpp"
#include "GameContainer.hpp"

StatsMenu::StatsMenu() : ToolMenu() {
    mName = "StatsMenu";
    
    
    //UILabel                                 *mLabelPercent;
    
    
    
    
    SetTitle("Stats");
    SetScrollMode(true);

    
    mRowProgress = new ToolMenuSectionRow();
    AddSection(mRowProgress);

    
    mLabelProgress = new UILabel();
    mLabelProgress->SetText("Freeze");
    mRowProgress->AddLabel(mLabelProgress);
    
    mLabelPercent = new UILabel();
    mLabelPercent->SetText("Freeze");
    mRowProgress->AddLabel(mLabelPercent);
    
    
    
    
    
    DeactivateCloseButton();
}

StatsMenu::~StatsMenu() {
    
}

void StatsMenu::Layout() {
    ToolMenu::Layout();
    
}

void StatsMenu::Update() {

    
    
    int aProgress = 0;
    int aProgressCount = 1;
    float aProgressPercent = 0.0f;
    
    if (gGame != NULL) {
        
        aProgressCount = gGame->mProgressCount;
        aProgress = gGame->mProgress;
        
        if (aProgressCount > 0) {
            aProgressPercent = (((float)aProgress) / ((float)aProgressCount)) * 100.0f;
        }
    }
    
    if (mLabelProgress != NULL) {
        
        FString aProgressText = FString("P: ") + FString(aProgress) + FString("/") + FString(aProgressCount);
        
        mLabelProgress->SetText(aProgressText.c());
    }
    
    if (mLabelPercent != NULL) {
        FString aPercentText = FString(aProgressPercent, 2) + FString("%%");
        mLabelPercent->SetText(aPercentText.c());
    }
    
}

void StatsMenu::Notify(void *pSender, const char *pNotification) {
    

}

