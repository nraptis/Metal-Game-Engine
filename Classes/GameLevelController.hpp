//
//  GameLevelController.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameLevelController_hpp
#define GameLevelController_hpp

#include "LevelData.hpp"
#include "GFXApp.hpp"

class Game;
class GameLevelController {
public:
    GameLevelController(Game *pGame);
    ~GameLevelController();
    
    void                            Setup(LevelData *pData);
    
    Game                            *mGame;
    LevelData                       *mData;
    
    void                            Update();
    void                            DrawMarkers();
    
    
    
};

#endif /* GameLevelController_hpp */
