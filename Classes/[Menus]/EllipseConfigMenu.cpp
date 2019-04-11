//
//  EllipseConfigMenu.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/9/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EllipseConfigMenu.hpp"
#include "WorldConfigScene.hpp"

//
//  EllipseConfigMenu.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "EllipseConfigMenu.hpp"
#include "FApp.hpp"

EllipseConfigMenu::EllipseConfigMenu(WorldConfigScene *pScene) : ToolMenu() {
    mName = "EllipseConfigMenu";
    
    mScene = pScene;
    
    SetTitle("Ellipse");
    SetScrollMode(true);
    
    mPanelDummy = new ToolMenuPanel();
    mPanelDummy->SetTitle("<--->");
    AddSection(mPanelDummy);
    //
    //
    mSliderAxisH = new UISlider();
    mSliderAxisH->SetText("H-Axis");
    mSliderAxisH->SetTarget(&mScene->mEllipseAxisH);
    mSliderAxisH->SetRange(0.0f, 300.0f);
    mPanelDummy->AddSection(mSliderAxisH);
    
    mSliderAxisV = new UISlider();
    mSliderAxisV->SetText("V-Axis");
    mSliderAxisV->SetTarget(&mScene->mEllipseAxisV);
    mSliderAxisV->SetRange(0.0f, 300.0f);
    mPanelDummy->AddSection(mSliderAxisV);
    
    mSliderRotation = new UISlider();
    mSliderRotation->SetText("E-Rot");
    mSliderRotation->SetTarget(&mScene->mEllipseRotation);
    mSliderRotation->SetRange(0.0f, 300.0f);
    mPanelDummy->AddSection(mSliderRotation);
    
    
    
    DeactivateCloseButton();
}

EllipseConfigMenu::~EllipseConfigMenu() {
    
}

void EllipseConfigMenu::Layout() {
    ToolMenu::Layout();
    
}


void EllipseConfigMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void EllipseConfigMenu::RefreshTestMode() {
    
}
