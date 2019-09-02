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
#include "FModelDataPacked.hpp"

class AssetWadModelMaps : public AssetWad {
public:
    AssetWadModelMaps();
    ~AssetWadModelMaps();
    
    
    FModelDataPacked                                mDartRegularModel[6];
    FSprite                                         mDartRegular[6];
    
    FSprite                                         mDartMini[6];
    FSprite                                         mDartBat[6];
    
    FSprite                                         mExtraLife;
    
    FSprite                                         mTurtle;
    FSprite                                         mTurtleDamaged;
    
    
    FSprite                                         mTurtlePropeller;
    
    FSprite                                         mPrizeStar;
    
    //batdart_color_6_map
    //dart_color_4_map
    //minidart_color_6_map
    //extra_life_map
    //turtle_map
    //turtle_damaged_map
    //turtle_propeller_map
    //prize_star_map
    
    
    virtual void                                    Load();
    virtual void                                    Unload();
    
    
    
    
};

#endif /* AssetWadModelMaps_hpp */
