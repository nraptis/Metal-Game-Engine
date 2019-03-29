//
//  SoundConfigMenu.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//


#include "SoundConfigMenu.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"

SoundConfigMenu::SoundConfigMenu() : ToolMenu() {
    mName = "SoundConfigMenu";
    
    
    mCrossfadeTicks = 200;
    mFadeTicks = 140;
    mPitch = 1.0f;
    
    
    
    
    SetScrollMode(true);
    //
    //
    
    
    
    
    mPanelVolume = new ToolMenuPanel();
    mPanelVolume->SetTitle("Volume");
    AddSection(mPanelVolume);
    
    
    mSliderSoundVolume = new UISlider();
    mSliderSoundVolume->SetText("Sound");
    mSliderSoundVolume->SetValue(&gSoundVolume);
    mSliderSoundVolume->SetRange(0.0f, 1.0f);
    mPanelVolume->AddSection(mSliderSoundVolume);
    
    
    mSliderMusicVolume = new UISlider();
    mSliderMusicVolume->SetText("Music");
    mSliderMusicVolume->SetValue(&gMusicVolume);
    mSliderMusicVolume->SetRange(0.0f, 1.0f);
    mPanelVolume->AddSection(mSliderMusicVolume);
    
    mSliderPitch = new UISlider();
    mSliderPitch->SetText("Pitch");
    mSliderPitch->SetValue(&mPitch);
    mSliderPitch->SetRange(0.25f, 3.0f);
    mPanelVolume->AddSection(mSliderPitch);
    
    
    
    
    
    
    mPanelSingleInstance = new ToolMenuPanel();
    mPanelSingleInstance->SetTitle("1-Instance");
    AddSection(mPanelSingleInstance);
    
    
    mRowSingleInstance1 = new ToolMenuSectionRow();
    mPanelSingleInstance->AddSection(mRowSingleInstance1);
    
    mButtonSingleInstance1 = new UIButton();
    mButtonSingleInstance1->SetText("S-1");
    mRowSingleInstance1->AddButton(mButtonSingleInstance1);
    
    mButtonSingleInstance2 = new UIButton();
    mButtonSingleInstance2->SetText("S-2");
    mRowSingleInstance1->AddButton(mButtonSingleInstance2);
    
    mButtonSingleInstance3 = new UIButton();
    mButtonSingleInstance3->SetText("S-3");
    mRowSingleInstance1->AddButton(mButtonSingleInstance3);
    
    
    
    mRowSingleInstance2 = new ToolMenuSectionRow();
    mPanelSingleInstance->AddSection(mRowSingleInstance2);
    
    
    mButtonSingleLoopStart = new UIButton();
    mButtonSingleLoopStart->SetText("Loop");
    mRowSingleInstance2->AddButton(mButtonSingleLoopStart);
    
    mButtonSingleLoopStop = new UIButton();
    mButtonSingleLoopStop->SetText("Stop");
    mRowSingleInstance2->AddButton(mButtonSingleLoopStop);

    
    
    
    
    mPanelMultiInstance = new ToolMenuPanel();
    mPanelMultiInstance->SetTitle("Multi-Instance");
    AddSection(mPanelMultiInstance);
    
    
    mRowMultiInstance1 = new ToolMenuSectionRow();
    mPanelMultiInstance->AddSection(mRowMultiInstance1);
    
    mButtonMultiInstance1 = new UIButton();
    mButtonMultiInstance1->SetText("S-1");
    mRowMultiInstance1->AddButton(mButtonMultiInstance1);
    
    mButtonMultiInstance2 = new UIButton();
    mButtonMultiInstance2->SetText("S-2");
    mRowMultiInstance1->AddButton(mButtonMultiInstance2);
    
    mButtonMultiInstance3 = new UIButton();
    mButtonMultiInstance3->SetText("S-3");
    mRowMultiInstance1->AddButton(mButtonMultiInstance3);
    
    
    
    mRowMultiInstance2 = new ToolMenuSectionRow();
    mPanelMultiInstance->AddSection(mRowMultiInstance2);
    
    
    mButtonMultiInstanceLoopStart = new UIButton();
    mButtonMultiInstanceLoopStart->SetText("Loop");
    mRowMultiInstance2->AddButton(mButtonMultiInstanceLoopStart);
    
    mButtonMultiInstanceLoopStop = new UIButton();
    mButtonMultiInstanceLoopStop->SetText("Stop");
    mRowMultiInstance2->AddButton(mButtonMultiInstanceLoopStop);
    

    
    
    
    mPanelMusic = new ToolMenuPanel();
    mPanelMusic->SetTitle("Music");
    AddSection(mPanelMusic);
    
    mStepperMusicFade = new UIStepper();
    mStepperMusicFade->SetText("Fade");
    mStepperMusicFade->SetTarget(&mFadeTicks);
    mPanelMusic->AddSection(mStepperMusicFade);
    
    mStepperMusicCrossfade = new UIStepper();
    mStepperMusicCrossfade->SetText("Crossfade");
    mStepperMusicCrossfade->SetTarget(&mCrossfadeTicks);
    mPanelMusic->AddSection(mStepperMusicCrossfade);
    
    
    mRowMusic1 = new ToolMenuSectionRow();
    mPanelMusic->AddSection(mRowMusic1);
    
    
    mButtonSong1Play = new UIButton();
    mButtonSong1Play->SetText("Play-1");
    mRowMusic1->AddButton(mButtonSong1Play);
    
    mButtonSong2Play = new UIButton();
    mButtonSong2Play->SetText("Play-2");
    mRowMusic1->AddButton(mButtonSong2Play);
    
    
    mButtonMusicPause = new UIButton();
    mButtonMusicPause->SetText("Pause");
    mRowMusic1->AddButton(mButtonMusicPause);
    
    mButtonMusicResume = new UIButton();
    mButtonMusicResume->SetText("Resume");
    mRowMusic1->AddButton(mButtonMusicResume);
    
   
    
    mRowMusic2 = new ToolMenuSectionRow();
    mPanelMusic->AddSection(mRowMusic2);
    
    
    mButtonSongFade = new UIButton();
    mButtonSongFade->SetText("Fade");
    mRowMusic2->AddButton(mButtonSongFade);
    
    mButtonSong1Crossfade = new UIButton();
    mButtonSong1Crossfade->SetText("X-Fade-1");
    mRowMusic2->AddButton(mButtonSong1Crossfade);
    
    mButtonSong2Crossfade = new UIButton();
    mButtonSong2Crossfade->SetText("X-Fade-2");
    mRowMusic2->AddButton(mButtonSong2Crossfade);
    
    /*
    
    
    ToolMenuPanel                           *;
    UIStepper                               *;
    UIStepper                               *;
    ToolMenuSectionRow                      *;
    UIButton                                *;
    UIButton                                *;
    
    ToolMenuSectionRow                      *mRowMusic2;
    UIButton                                *;
    UIButton                                *;
    UIButton                                *mButtonSong2Crossfade;
    
    ToolMenuSectionRow                      *mRowMusic3;
    
    
    
    */
    
    
    
    
    
    
    
    

    
    
    
    DeactivateCloseButton();
}

SoundConfigMenu::~SoundConfigMenu() {
    
}

void SoundConfigMenu::Layout() {
    ToolMenu::Layout();
    
}


void SoundConfigMenu::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        
        if (pSender == mButtonSingleInstance1) { gApp->mSoundOne[0].PlayPitched(mPitch); }
        if (pSender == mButtonSingleInstance2) { gApp->mSoundOne[1].PlayPitched(mPitch); }
        if (pSender == mButtonSingleInstance3) { gApp->mSoundOne[2].PlayPitched(mPitch); }
        
        if (pSender == mButtonSingleLoopStart) { gApp->mSoundOne[0].LoopPitched(mPitch); }
        if (pSender == mButtonSingleLoopStop) { gApp->mSoundOne[0].Stop(); }
        
        
        // = new UIButton();
        //mButtonSingleLoopStart->SetText("Loop");
        //mRowSingleInstance2->AddButton(mButtonSingleLoopStart);
        
        // = new UIButton();
        //mButtonSingleLoopStop->SetText("Stop");
        //mRowSingleInstance2->AddButton(mButtonSingleLoopStop);
        

        
        
        if (pSender == mButtonMultiInstance1) { gApp->mSoundMulti[0].PlayPitched(mPitch); }
        if (pSender == mButtonMultiInstance2) { gApp->mSoundMulti[1].PlayPitched(mPitch); }
        if (pSender == mButtonMultiInstance3) { gApp->mSoundMulti[2].PlayPitched(mPitch); }
        if (pSender == mButtonMultiInstanceLoopStart) { gApp->mSoundMulti[0].LoopPitched(mPitch); }
        if (pSender == mButtonMultiInstanceLoopStop) { gApp->mSoundMulti[0].Stop(); }
        
        
        
        if (pSender == mButtonSong1Play) { music_play("music_game_loop.mp3", false); }
        if (pSender == mButtonSong2Play) { music_play("music_idle.mp3", false); }
        
        if (pSender == mButtonMusicPause) { music_pause(); }
        if (pSender == mButtonMusicResume) { music_resume(); }
        
        if (pSender == mButtonSongFade) { music_fadeout(mFadeTicks); }
        
        if (pSender == mButtonSong1Crossfade) { music_crossfade("music_game_loop.mp3", mCrossfadeTicks, false); }
        if (pSender == mButtonSong2Crossfade) { music_crossfade("music_idle.mp3", mCrossfadeTicks, false); }

    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

