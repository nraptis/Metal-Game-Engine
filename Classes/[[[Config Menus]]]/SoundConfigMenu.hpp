//
//  SoundConfigMenu.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef SoundConfigMenu_hpp
#define SoundConfigMenu_hpp

#include "ToolMenu.hpp"

class SoundConfigMenu : public ToolMenu {
public:
    SoundConfigMenu();
    virtual ~SoundConfigMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    
    ToolMenuPanel                           *mPanelVolume;
    UISlider                                *mSliderSoundVolume;
    UISlider                                *mSliderMusicVolume;
    UISlider                                *mSliderPitch;
    
    
    
    
    ToolMenuPanel                           *mPanelSingleInstance;
    ToolMenuSectionRow                      *mRowSingleInstance1;
    ToolMenuSectionRow                      *mRowSingleInstance2;
    
    UIButton                                *mButtonSingleInstance1;
    UIButton                                *mButtonSingleInstance2;
    UIButton                                *mButtonSingleInstance3;
    
    UIButton                                *mButtonSingleLoopStart;
    UIButton                                *mButtonSingleLoopStop;
    
    
    
    
    ToolMenuPanel                           *mPanelMultiInstance;
    ToolMenuSectionRow                      *mRowMultiInstance1;
    ToolMenuSectionRow                      *mRowMultiInstance2;
    
    UIButton                                *mButtonMultiInstance1;
    UIButton                                *mButtonMultiInstance2;
    UIButton                                *mButtonMultiInstance3;
    
    UIButton                                *mButtonMultiInstanceLoopStart;
    UIButton                                *mButtonMultiInstanceLoopStop;
    
    
    
    
    
    ToolMenuPanel                           *mPanelMusic;
    UIStepper                               *mStepperMusicFade;
    UIStepper                               *mStepperMusicCrossfade;
    ToolMenuSectionRow                      *mRowMusic1;
    UIButton                                *mButtonSong1Play;
    UIButton                                *mButtonSong2Play;
    UIButton                                *mButtonMusicPause;
    UIButton                                *mButtonMusicResume;
    
    ToolMenuSectionRow                      *mRowMusic2;
    UIButton                                *mButtonSongFade;
    UIButton                                *mButtonSong1Crossfade;
    UIButton                                *mButtonSong2Crossfade;
    
    
    
    
    
    
    
    int                                     mCrossfadeTicks;
    int                                     mFadeTicks;
    float                                   mPitch;
    
    
};

#endif /* SoundConfigMenu_hpp */
