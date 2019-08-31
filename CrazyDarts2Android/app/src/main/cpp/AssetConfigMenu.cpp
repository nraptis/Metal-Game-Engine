//
//  AssetConfigMenu.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetConfigMenu.hpp"
#include "FApp.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"
#include "WadGlobalConfiguration.hpp"


AssetConfigMenu::AssetConfigMenu() : ToolMenu() {
    mName = "AssetConfigMenu";
    
    
    SetTitle("Asset Testboard");
    SetScrollMode(true);
    //
    //
    
    
    
    mPanelScaling = new ToolMenuPanel();
    mPanelScaling->SetTitle("Scaling");
    AddSection(mPanelScaling);
    
    
    
    
    
    mSegmentRetinaScale = new UISegment();
    mSegmentRetinaScale->SetSegmentCount(5);
    mSegmentRetinaScale->SetTitles("R@1X", "R@1X", "R@2X", "R@3X", "R@4X");
    mSegmentRetinaScale->SetTarget(&gWadConfiguration.mAssetScale);
    mPanelScaling->AddSection(mSegmentRetinaScale);
    
    mSegmentSpriteScale = new UISegment();
    mSegmentSpriteScale->SetSegmentCount(5);
    mSegmentSpriteScale->SetTitles("S-0X", "S-1X", "S-2X", "S-3X", "S-4X");
    mSegmentSpriteScale->SetTarget(&gWadConfiguration.mSpriteScale);
    mPanelScaling->AddSection(mSegmentSpriteScale);
    
    
    mRowScaling1 = new ToolMenuSectionRow();
    mPanelScaling->AddSection(mRowScaling1);
    
    
    
    mCheckBoxAutoScale = new UICheckBox();
    mCheckBoxAutoScale->SetText("Auto-S:");
    mCheckBoxAutoScale->SetTarget(&gWadConfiguration.mAutoScale);
    mRowScaling1->AddCheckBox(mCheckBoxAutoScale);
    
    //mRowScaling2 = new ToolMenuSectionRow();
    //mPanelScaling->AddSection(mRowScaling2);
    
    //mRowScaling3 = new ToolMenuSectionRow();
    //mPanelScaling->AddSection(mRowScaling3);
    
    
    
    
    
    mPanelLoading = new ToolMenuPanel();
    mPanelLoading->SetTitle("Loading");
    AddSection(mPanelLoading);
    
    
    mRowLoading1 = new ToolMenuSectionRow();
    mPanelLoading->AddSection(mRowLoading1);
    
    
    mButtonReload = new UIButton();
    mButtonReload->SetText("Reload");
    mRowLoading1->AddButton(mButtonReload);
    
    
    mButtonUnload = new UIButton();
    mButtonUnload->SetText("Unload");
    mRowLoading1->AddButton(mButtonUnload);
    
    DeactivateCloseButton();
}

AssetConfigMenu::~AssetConfigMenu() {
    
}

void AssetConfigMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
        //if (pSender == mButtonSingleInstance1) { gApp->mSoundOne[0].PlayPitched(mPitch); }
        
        if (pSender == mButtonReload) {
            printf("RE-LOAD!!!\n");
            
            gApp->EnqueueWadReload(1);
        }
        
        if (pSender == mButtonUnload) {
            printf("UN-LOAD!!!\n");
        }
    }
    
    if (FString(pNotification) == "segment") {
        if (pSender == mSegmentRetinaScale) {
            printf("Ret-Scale!\n");
        }
        
        if (pSender == mSegmentSpriteScale) {
            printf("Sprite-Scale!\n");
        }
    }
    
    if (FString(pNotification) == "checkbox") {
        if (pSender == mCheckBoxAutoScale) {
            printf("Auto-Scale!\n");
        }
    }
    
}

