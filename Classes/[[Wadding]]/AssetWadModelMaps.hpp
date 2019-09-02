//
//  AssetWadModelMaps.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef AssetWadModelMaps_hpp
#define AssetWadModelMaps_hpp

#include "AssetWad.hpp"

class AssetWadModelMaps : public AssetWad {
public:
    AssetWadModelMaps();
    ~AssetWadModelMaps();
    
    virtual void                                    Load();
    virtual void                                    Unload();
    
    
    
    
};

#endif /* AssetWadModelMaps_hpp */
