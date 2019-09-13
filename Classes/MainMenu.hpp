//
//  MainMenu.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/12/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "GFXApp.hpp"
#include "FCanvas.hpp"
#include "MainMenuPlayButton.hpp"

class MainMenu : public FCanvas {
public:
    MainMenu();
    virtual ~MainMenu();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    void                                        Draw3D();
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    
    MainMenuPlayButton                          *mPlayButton;

    
    
};

extern MainMenu *gMainMenu;

#endif /* MainMenu_hpp */
