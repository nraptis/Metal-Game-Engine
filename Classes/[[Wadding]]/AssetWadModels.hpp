//
//  AssetWadModels.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef AssetWadModels_hpp
#define AssetWadModels_hpp

#include "AssetWad.hpp"
#include "FModelDataPacked.hpp"

class AssetWadModels : public AssetWad {
public:
    AssetWadModels();
    ~AssetWadModels();
    
    FModelDataPacked                                mDartRegular[6];
    FSprite                                         mDartRegularMap[6];
    
    FModelDataPacked                                mDartMini[6];
    FSprite                                         mDartMiniMap[6];
    
    FModelDataPacked                                mDartBat[6];
    FSprite                                         mDartBatMap[6];
    
    FModelDataPacked                                mExtraLife;
    FSprite                                         mExtraLifeMap;
    
    FModelDataPacked                                mTurtle;
    FModelDataPacked                                mTurtleDamaged;
    FSprite                                         mTurtleMap;
    FSprite                                         mTurtleDamagedMap;
    
    FModelDataPacked                                mTurtlePropeller;
    FSprite                                         mTurtlePropellerMap;
    
    FModelDataPacked                                mPrizeStar;
    FSprite                                         mPrizeStarMap;
    
    
    
    FModelDataPackedSequence                        mTestSequence1;
    FModelDataPackedSequence                        mTestSequence2;
    FSprite                                         mTestSequenceMap;
    
    
    virtual void                                    Load();
    virtual void                                    Unload();
    
    
    
    
    /*
    butterfly_body_19.obj
    butterfly_body_0.obj
    butterfly_map.png
    butterfly_wings_0.obj
    butterfly_wings_19.obj
    */
    
};

#endif /* AssetWadModels_hpp */
