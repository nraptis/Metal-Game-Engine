//
//  LevelWave.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWave_hpp
#define LevelWave_hpp

#include "GameObject.hpp"

class LevelWave {
public:
    LevelWave();
    virtual ~LevelWave();
    
    virtual void                        Spawn();
    virtual void                        Update();
    virtual void                        Draw();
    
    virtual void                        Dispose();
    virtual void                        DisposeObject(GameObject *pObject);
    
    bool                                mIsComplete;
    bool                                mRight;
    int                                 mAliveTimer;
    
    
    
    
};


#endif /* LevelWave_hpp */
