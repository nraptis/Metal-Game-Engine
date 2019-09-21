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

SpeedControlMenu::SpeedControlMenu() : ToolMenu() {
    mName = "SpeedControlMenu";
    
    
    
    SetTitle("Speed");
    SetScrollMode(false);
    //
    //
    
    
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(9);
    mSegmentSpeed->SetTitles("XXXS", "XXS", "XS", "S", "N", "F", "XF", "XXF", "XXXF");
    AddSection(mSegmentSpeed);


    mRowFreezeFrame = new ToolMenuSectionRow();
    AddSection(mRowFreezeFrame);

    mCheckBoxFreezeFrameEnabled = new UICheckBox();
    mCheckBoxFreezeFrameEnabled->SetText("Freeze");
    mRowFreezeFrame->AddCheckBox(mCheckBoxFreezeFrameEnabled);
    
    mTextBoxFreezeFrame = new UITextBox();
    mTextBoxFreezeFrame->SetText("200");
    mRowFreezeFrame->AddTextBox(mTextBoxFreezeFrame);
    
    mButtonPrevFrame = new UIButton();
    mButtonPrevFrame->SetText("Prev Frame");
    mRowFreezeFrame->AddButton(mButtonPrevFrame);
    
    
    mButtonNextFrame = new UIButton();
    mButtonNextFrame->SetText("Next Frame");
    mRowFreezeFrame->AddButton(mButtonNextFrame);
    
    
    
    DeactivateCloseButton();
}

SpeedControlMenu::~SpeedControlMenu() {
    
}

void SpeedControlMenu::Layout() {
    ToolMenu::Layout();
    
}


void SpeedControlMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
        /*
        
        if (pSender == mButtonSong1Play) { music_play("demo_song_1.mp3", true); }
        if (pSender == mButtonSong2Play) { music_play("demo_song_2.mp3", true); }
        
        if (pSender == mButtonMusicPause) { music_pause(); }
        if (pSender == mButtonMusicResume) { music_resume(); }
        
        if (pSender == mButtonSongFade) { music_fadeout(mFadeTicks); }
        
        if (pSender == mButtonSong1Crossfade) { music_crossfade("demo_song_1.mp3", mCrossfadeTicks, true); }
        if (pSender == mButtonSong2Crossfade) { music_crossfade("demo_song_2.mp3", mCrossfadeTicks, true); }
        
        */
        
        
        
        
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

