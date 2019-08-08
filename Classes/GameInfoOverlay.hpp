//
//  GameInfoOverlay.hpp
//  Crazy Darts 2 iOS
//
//  Created by Doombot on 8/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameInfoOverlay_hpp
#define GameInfoOverlay_hpp

#include "FCanvas.hpp"
#include "GameInfoTextBubble.hpp"

class GameInfoOverlay : public FCanvas {
public:
    GameInfoOverlay();
    virtual ~GameInfoOverlay();
    
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
    
    
    void                                        AddBubble(const char *pText);
    void                                        RemoveBubble(const char *pText);
    
    void                                        SetBubbleStatusAllComplete(const char *pName, bool pStatus);
    void                                        SetBubbleStatusPermsComplete(const char *pName, bool pStatus);
    void                                        SetBubbleStatusWavesComplete(const char *pName, bool pStatus);
    void                                        SetBubbleStatusHasObjects(const char *pName, bool pStatus);
    
    
    
    
    //mAllComplete = false;
    //mPermsComplete = false;
    //mWavesComplete = false;
    
    
    FList                                       mBubbleList;
    FList                                       mBubbleKillList;
    FList                                       mBubbleDeleteList;
    
    //GameInfoTextBubble
    
    
};

#endif /* GameInfoOverlay_hpp */
