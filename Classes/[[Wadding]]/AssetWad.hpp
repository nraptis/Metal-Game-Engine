//
//  AssetWad.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef AssetWad_hpp
#define AssetWad_hpp

#include "FList.hpp"
#include "FSprite.hpp"
#include "FSpriteSequence.h"
#include "FHashMap.hpp"
#include "FFont.hpp"
#include "core_includes.h"

class AssetWad {
public:
    AssetWad();
    ~AssetWad();
    
    virtual void                                    Print();
    virtual void                                    Load();
    virtual void                                    Unload();
    
    //void                                            QuickLoad(const char *pKey, FSprite *pSprite);
    
    //FList                                           mSpriteList;
    //FStringMap                                      mSpriteMap;
    
    
    
};

#endif /* AssetWad_hpp */
