//
//  GameTestEditorOverlay.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 5/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameTestEditorOverlay_hpp
#define GameTestEditorOverlay_hpp

#include "GFXApp.hpp"
#include "EditorMenuGameTestUtils.hpp"
#include "EditorMenuGameTest.hpp"

class Game;
class GameTestEditorOverlay : public FCanvas {
public:
    GameTestEditorOverlay();
    virtual ~GameTestEditorOverlay();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
};

#endif /* GameTestEditorOverlay_hpp */
