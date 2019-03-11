//
//  FSpriteBufferCache.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FSpriteBufferCache.hpp"
#include "os_core_graphics.h"

FSpriteBufferCache::FSpriteBufferCache() {
    mIndex = 0;
}

FSpriteBufferCache::~FSpriteBufferCache() {
    
}

int FSpriteBufferCache::Get() {
    int aResult = -1;
    //mList
    
    if (mIndex >= mList.mCount) {
        aResult = Graphics::Graphics::BufferArrayGenerate(sizeof(float) * 8);
        mList.Add(aResult);
    } else {
        aResult = mList.mData[mIndex];
        
    }
    mIndex++;
    return aResult;
}

void FSpriteBufferCache::Reset() {
    mIndex = 0;
    
    
}

