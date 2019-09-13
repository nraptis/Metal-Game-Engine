//
//  GameContainerContainer.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameContainerContainer_hpp
#define GameContainerContainer_hpp

#include "GFXApp.hpp"
#include "GameTestEditorOverlay.hpp"
#include "GameTestRunningOverlay.hpp"
#include "GameMenu.hpp"
#include "GameOverlayEffects.hpp"
#include "GameOverlayInterface.hpp"
#include "EditorMenuGameTestUtils.hpp"
#include "EditorMenuGameTest.hpp"

class Game;
class GameContainer : public FCanvas {
public:
    GameContainer();
    virtual ~GameContainer();
    
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
    
    //After the game + editor are ready to go.
    void                                        Realize();
    
    Game                                        *mGame;
    FCanvas                                     *mContainer;
    GameTestEditorOverlay                       *mGameTestEditorOverlay;
    GameTestRunningOverlay                      *mGameTestRunningOverlay;
    
    //This is essentially a scaled-down 2-D overlay which rests atop the game...
    GameOverlayEffects                          *mEffectsOverlay;
    GameOverlayInterface                        *mInterfaceOverlay;
    
    
    EditorMenuGameTest                          *mEditorMenu;
    EditorMenuGameTestUtils                     *mEditorMenuUtils;
    
    //Including Safe Area...
    float                                       mInterfaceLeftWidth;
    float                                       mInterfaceRightWidth;
    float                                       mInterfaceTopHeight;
    float                                       mInterfaceBottomHeight;
    
    
    GameMenu                                    *mGameMenu;
    FCanvasAnimation                            *mGameMenuAnimation;
    bool                                        mGameMenuAnimatingIn;
    
    void                                        PauseAndShowGameMenu();
    void                                        UnpauseAndHideGameMenu();
    
    void                                        Pause();
    void                                        Unpause();
    
    void                                        BeginPauseFadeIn();
    void                                        BeginPauseFadeOut();
    
    bool                                        IsPauseFadeInComplete();
    bool                                        IsPauseFadeOutComplete();
    
    bool                                        mPaused;
    bool                                        mPauseFadeEnabled;
    
    float                                       mPauseFade;
    float                                       mPauseFadeMax;
    
    
    
    void                                        OpenEditorTestMenus();
    
};

extern GameContainer *gGameContainer;

#endif
