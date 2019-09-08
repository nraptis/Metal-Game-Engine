//
//  GameMenu.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameMenu_hpp
#define GameMenu_hpp

#include "GFXApp.hpp"
#include "FButton.hpp"

class Game;
class GameMenu : public FCanvas {
public:
    GameMenu();
    virtual ~GameMenu();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    
    
    FButton                                     *mOptionsButton;
    FButton                                     *mMainMenuButton;
    FButton                                     *mResumeButton;
    
};

#endif /* GameMenu_hpp */
