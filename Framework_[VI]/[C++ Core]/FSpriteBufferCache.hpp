//
//  FSpriteBufferCache.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FSpriteBufferCache_hpp
#define FSpriteBufferCache_hpp

#include "FIntList.hpp"

class FSpriteBufferCache {
public:
    FSpriteBufferCache();
    ~FSpriteBufferCache();
    
    FIntList                        mList;
    int                             mIndex;
    
    int                             Get();
    void                            Reset();
};

#endif /* FSpriteBufferCache_hpp */
