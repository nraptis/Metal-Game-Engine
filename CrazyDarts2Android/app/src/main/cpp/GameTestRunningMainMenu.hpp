//
//  GameTestRunningMainMenu.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameTestRunningMainMenu_hpp
#define GameTestRunningMainMenu_hpp

#include "ToolMenu.hpp"
#include "FVec2.hpp"

class Game;
class GameTestRunningMainMenu : public ToolMenu {
public:
    GameTestRunningMainMenu(Game *pGame);
    virtual ~GameTestRunningMainMenu();
    
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    ToolMenuPanel                           *mMainPanel;
    
    ToolMenuSectionRow                      *mRowMain1;
    ToolMenuSectionRow                      *mRowMain2;
    ToolMenuSectionRow                      *mRowMain3;
    
    UIButton                                *mButtonRestart;
    UIButton                                *mButtonPause;
    
};

#endif
