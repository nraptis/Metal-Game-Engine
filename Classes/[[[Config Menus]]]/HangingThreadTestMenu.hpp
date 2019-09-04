//
//  HangingThreadTestMenu.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef HangingThreadTestMenu_hpp
#define HangingThreadTestMenu_hpp

#include "ToolMenu.hpp"
#include "FloatingCamera.hpp"
#include "FVec2.hpp"

class Game;
class HangingThreadTestMenu : public ToolMenu {
public:
    HangingThreadTestMenu(Game *pGame);
    virtual ~HangingThreadTestMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    void                                    RefreshTestMode();
    
    ToolMenuPanel                           *mPanelTestAxis;
    UISlider                                *mSliderTestAxisX;
    UISlider                                *mSliderTestAxisY;
    UISlider                                *mSliderTestAxisZ;
    
    
    
};
#endif /* HangingThreadTestMenu_hpp */
