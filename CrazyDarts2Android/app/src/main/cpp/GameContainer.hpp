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
#include "FloatingCamera.hpp"
#include "Dart.hpp"
#include "Balloon.hpp"

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
    
    Game                                        *mGame;
    FCanvas                                     *mContainer;
    
    bool                                        mLayoutRefresh;
    int                                         mInitialLayoutTick;
    
    //Including Safe Area...
    float                                       mInterfaceLeftWidth;
    float                                       mInterfaceRightWidth;
    float                                       mInterfaceTopHeight;
    float                                       mInterfaceBottomHeight;
    
    
};

#endif
