//
//  HangingThreadTestMenu.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "HangingThreadTestMenu.hpp"



//
//  HangingThreadTestMenu.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "HangingThreadTestMenu.hpp"
#include "FApp.hpp"
#include "Game.hpp"

HangingThreadTestMenu::HangingThreadTestMenu(Game *pGame) : ToolMenu() {
    mName = "HangingThreadTestMenu";
    
    SetScrollMode(true);
    
    
    //ToolMenuPanel                           *;
    //UISlider                                *;
    //UISlider                                *mSliderTestAxisY;
    //UISlider                                *mSliderTestAxisZ;
    
    
    mPanelTestAxis = new ToolMenuPanel();
    mPanelTestAxis->SetTitle("<--->");
    AddSection(mPanelTestAxis);
    //
    //
    mSliderTestAxisX = new UISlider();
    mSliderTestAxisX->SetText("R-X");
    //mSliderTestAxisX->SetTarget(&pGame->mTestBalloonRotX);
    //mSliderViewRotationPrimary->SetRange(-180.0f, 360.0f);
    mSliderTestAxisX->SetRange(-60.0f, 60.0f);
    mPanelTestAxis->AddSection(mSliderTestAxisX);
    
    mSliderTestAxisY = new UISlider();
    mSliderTestAxisY->SetText("R-Z");
    //mSliderTestAxisY->SetTarget(&pGame->mTestBalloonRotZ);
    //mSliderTestAxisY->SetTarget(&pGame->mHangingThreatTestAxisEndOffsetY);
    mSliderTestAxisY->SetRange(-60.0f, 60.0f);
    mPanelTestAxis->AddSection(mSliderTestAxisY);
    
    
    
    DeactivateCloseButton();
}

HangingThreadTestMenu::~HangingThreadTestMenu() {
    
}

void HangingThreadTestMenu::Layout() {
    ToolMenu::Layout();
    
}


void HangingThreadTestMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void HangingThreadTestMenu::RefreshTestMode() {
    
}

















