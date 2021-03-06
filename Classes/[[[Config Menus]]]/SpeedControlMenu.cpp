//
//  SpeedControlMenu.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "SpeedControlMenu.hpp"
#include "FApp.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"
#include "GameEditor.hpp"
#include "GameContainer.hpp"

SpeedControlMenu::SpeedControlMenu() : ToolMenu() {
    mName = "SpeedControlMenu";
    
    mRowFreezeFrame = NULL;
    mCheckBoxPause = NULL;
    mCheckBoxFreezeFrameEnabled = NULL;
    mTextBoxFreezeFrame = NULL;
    
    mButtonNextFrame = NULL;
    mButtonPrevFrame = NULL;
    
    
    mButtonNext10Frame = NULL;
    mButtonPrev10Frame = NULL;
    
    mButtonNext100Frame = NULL;
    mButtonPrev100Frame = NULL;
    
    
    
    SetTitle("Speed");
    SetScrollMode(false);
    //
    //
    
    
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(9);
    mSegmentSpeed->SetTitles("XXXS", "XXS", "XS", "S", "N", "F", "XF", "XXF", "XXXF");
    AddSection(mSegmentSpeed);


#ifdef EDITOR_MODE

    if (gEditor != NULL) {
        
        mRowFreezeFrame = new ToolMenuSectionRow();
        AddSection(mRowFreezeFrame);

        mCheckBoxFreezeFrameEnabled = new UICheckBox();
        mCheckBoxFreezeFrameEnabled->SetText("Freeze");
        mRowFreezeFrame->AddCheckBox(mCheckBoxFreezeFrameEnabled);
        
        mTextBoxFreezeFrame = new UITextBox();
        mTextBoxFreezeFrame->SetText("200");
        mRowFreezeFrame->AddTextBox(mTextBoxFreezeFrame);
        
        mButtonPrev100Frame = new UIButton();
        mButtonPrev100Frame->SetText("-100");
        mRowFreezeFrame->AddButton(mButtonPrev100Frame);
        
        mButtonPrev10Frame = new UIButton();
        mButtonPrev10Frame->SetText("-10");
        mRowFreezeFrame->AddButton(mButtonPrev10Frame);
        
        mButtonPrevFrame = new UIButton();
        mButtonPrevFrame->SetText("-1");
        mRowFreezeFrame->AddButton(mButtonPrevFrame);
        
        
        mButtonNextFrame = new UIButton();
        mButtonNextFrame->SetText("+1");
        mRowFreezeFrame->AddButton(mButtonNextFrame);
        
        mButtonNext10Frame = new UIButton();
        mButtonNext10Frame->SetText("+10");
        mRowFreezeFrame->AddButton(mButtonNext10Frame);
        
        mButtonNext100Frame = new UIButton();
        mButtonNext100Frame->SetText("+100");
        mRowFreezeFrame->AddButton(mButtonNext100Frame);
        
    }
    
#endif
    
    
    DeactivateCloseButton();
}

SpeedControlMenu::~SpeedControlMenu() {
    
}

void SpeedControlMenu::Layout() {
    ToolMenu::Layout();
    
}

void SpeedControlMenu::Update() {
#ifdef EDITOR_MODE
    
    if (mTextBoxFreezeFrame != NULL) {
        int aValue = mTextBoxFreezeFrame->mText.ToInt();
        if (aValue != gEditor->mFreezeFrame) {
            mTextBoxFreezeFrame->mText = FString(gEditor->mFreezeFrame).c();
        }
    }
    
    if (mCheckBoxFreezeFrameEnabled != NULL) {
        mCheckBoxFreezeFrameEnabled->SetTarget(&(gEditor->mFreeze));
    }
    
#endif
    
    
    if (mSegmentSpeed != NULL) {
        
        if (gGameContainer != NULL) {
            mSegmentSpeed->SetTarget(&(gGameContainer->mPlaybackSpeedCategory));
        } else {
            mSegmentSpeed->SetTarget(NULL);
            mSegmentSpeed->SetSelectedIndex(-1);
        }
        
    }
    
}

void SpeedControlMenu::Notify(void *pSender, const char *pNotification) {
    
    
    /*
#ifdef EDITOR_MODE
    mCheckBoxFreezeFrameEnabled->SetTarget(&(gEditor->mFreeze));
#endif
    
    //mFreeze = false;
    //mFreezeFrame = 100;
    
    mRowFreezeFrame->AddCheckBox(mCheckBoxFreezeFrameEnabled);
    */
    
    if (pSender == mTextBoxFreezeFrame) {
        int aValue = mTextBoxFreezeFrame->mText.ToInt();
#ifdef EDITOR_MODE
        gEditor->mFreezeFrame = aValue;
#endif
        
        
    }
    
    
    
#ifdef EDITOR_MODE
    if (pSender == mButtonPrev100Frame) {
        gEditor->mFreezeFrame -= 100;
        if (gEditor->mFreezeFrame <= 0) { gEditor->mFreezeFrame = 0; }
    }
    
    if (pSender == mButtonPrev10Frame) {
        gEditor->mFreezeFrame -= 10;
        if (gEditor->mFreezeFrame <= 0) { gEditor->mFreezeFrame = 0; }
    }
    
    if (pSender == mButtonPrevFrame) {
        gEditor->mFreezeFrame -= 1;
        if (gEditor->mFreezeFrame <= 0) { gEditor->mFreezeFrame = 0; }
    }
    
    if (pSender == mButtonNextFrame) {
        gEditor->mFreezeFrame += 1;
    }
    
    if (pSender == mButtonNext10Frame) {
        gEditor->mFreezeFrame += 10;
    }
    
    if (pSender == mButtonNext100Frame) {
        gEditor->mFreezeFrame += 100;
    }
    
    
#endif
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

