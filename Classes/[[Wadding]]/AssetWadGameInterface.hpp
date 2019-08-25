//
//  AssetWadGameInterface.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef AssetWadGameInterface_hpp
#define AssetWadGameInterface_hpp

#include "AssetWad.hpp"

class AssetWadGameInterface : public AssetWad {
public:
    AssetWadGameInterface();
    ~AssetWadGameInterface();
    
    virtual void                                    Load();
    virtual void                                    Unload();
    
    FSprite                                         mSpriteTest;
    
    
};


#endif /* AssetWadGameInterface_hpp */
