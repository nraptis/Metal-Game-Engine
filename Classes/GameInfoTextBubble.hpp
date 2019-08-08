//
//  GameInfoTextBubble.hpp
//  Crazy Darts 2 iOS
//
//  Created by Doombot on 8/7/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameInfoTextBubble_hpp
#define GameInfoTextBubble_hpp

#include "FString.hpp"

class GameInfoTextBubble {
public:
    GameInfoTextBubble(const char *pText);
    ~GameInfoTextBubble();
    
    void                            Update();
    void                            Draw();
    
    FString                         mText;
    
    bool                            mFadeOut;
    
    float                           mX;
    float                           mY;
    
    int                             mKillTimer;
    bool                            mKill;
    
    bool                            mAllComplete;
    bool                            mPermsComplete;
    bool                            mWavesComplete;
    bool                            mHasAnyObjects;
    
};

#endif /* GameInfoTextBubble_hpp */
