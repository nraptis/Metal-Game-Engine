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
    UISlider                                *mSliderTestAxisY;
    UISlider                                *mSliderTestAxisZ;
    
    
    mPanelTestAxis = new ToolMenuPanel();
    mPanelTestAxis->SetTitle("<--->");
    AddSection(mPanelTestAxis);
    //
    //
    mSliderTestAxisX = new UISlider();
    mSliderTestAxisX->SetText("E-X");
    mSliderTestAxisX->SetTarget(&pGame->mHangingThreatTestAxisEndOffsetX);
    //mSliderViewRotationPrimary->SetRange(-180.0f, 360.0f);
    mSliderTestAxisX->SetRange(-20.0f, 20.0f);
    mPanelTestAxis->AddSection(mSliderTestAxisX);
    
    mSliderTestAxisY = new UISlider();
    mSliderTestAxisY->SetText("E-Y");
    mSliderTestAxisY->SetTarget(&pGame->mHangingThreatTestAxisEndOffsetY);
    mSliderTestAxisY->SetRange(-50.0f, 0.0f);
    mPanelTestAxis->AddSection(mSliderTestAxisY);
    
    mSliderTestAxisZ = new UISlider();
    mSliderTestAxisZ->SetText("E-Z");
    mSliderTestAxisZ->SetTarget(&pGame->mHangingThreatTestAxisEndOffsetZ);
    mSliderTestAxisZ->SetRange(-20.0f, 20.0f);
    mPanelTestAxis->AddSection(mSliderTestAxisZ);
    
    
    
    
    
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

















