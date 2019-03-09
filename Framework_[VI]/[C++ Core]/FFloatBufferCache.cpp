//
//  FFloatBufferCache.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FFloatBufferCache.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"

FFloatBufferCacheResult::FFloatBufferCacheResult() {
    mBufferIndex = -1;
    mBufferOffset = 0;
    mSuccess = false;
}

FFloatBufferCacheResult::~FFloatBufferCacheResult() {
    
}

FFloatBufferCacheSlice::FFloatBufferCacheSlice() {
    mFetchBufferIndex = Graphics::BufferArrayGenerate(FLOAT_CACHE_SLICE_SIZE);
    mFetchBufferOffset = 0;
    mFetchSuccess = false;
    mInternalBufferOffset = 0;
}

FFloatBufferCacheSlice::~FFloatBufferCacheSlice() {
    Graphics::BufferArrayDelete(mFetchBufferIndex);
    mFetchBufferIndex = -1;
    mFetchBufferOffset = 0;
    mFetchSuccess = false;
}

void FFloatBufferCacheSlice::Reset() {
    mFetchBufferOffset = 0;
    mInternalBufferOffset = 0;
    mFetchSuccess = false;
}

bool FFloatBufferCacheSlice::AttemptFetch(int pBytes) {
    bool aResult = false;
    if ((mInternalBufferOffset + pBytes) > FLOAT_CACHE_SLICE_SIZE) {
        mFetchSuccess = false;
    } else {
        mFetchSuccess = true;
        mFetchBufferOffset = mInternalBufferOffset;
        mInternalBufferOffset += pBytes;
    }
    return aResult;
}

FFloatBufferCache::FFloatBufferCache() {
    mCurrentSlice = NULL;
}

FFloatBufferCache::~FFloatBufferCache() {
    Purge();
}

void FFloatBufferCache::Purge() {
    if (mCurrentSlice) {
        delete mCurrentSlice;
        mCurrentSlice = NULL;
    }
    FreeList(FFloatBufferCacheSlice, mConsumedSlices);
    FreeList(FFloatBufferCacheSlice, mAvailableSlices);
}

void FFloatBufferCache::Reset() {
    mAvailableSlices.Add(mConsumedSlices);
    mConsumedSlices.RemoveAll();
    if (mCurrentSlice) {
        mCurrentSlice->Reset();
    }
    EnumList(FFloatBufferCacheSlice, aSlice, mAvailableSlices) {
        aSlice->Reset();
    }
}

void FFloatBufferCache::Get(int pSize) {
    if (mCurrentSlice == NULL) {
        if (mAvailableSlices.IsEmpty()) {
            mCurrentSlice = new FFloatBufferCacheSlice();
        } else {
            mCurrentSlice = (FFloatBufferCacheSlice *)mAvailableSlices.PopLast();
        }
        
        //At this point, we must be able to assign the space, otherwise
        //the buffer we are requesting is too large for this module...
        mCurrentSlice->AttemptFetch(pSize);
        if (mCurrentSlice->mFetchSuccess) {
            mResult.mSuccess = true;
            mResult.mBufferIndex = mCurrentSlice->mFetchBufferIndex;
            mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
        } else {
            //There is no chance at success with this module...
            mResult.mSuccess = false;
        }
        return;
    }
    
    mCurrentSlice->AttemptFetch(pSize);
    if (mCurrentSlice->mFetchSuccess) {
        mResult.mSuccess = true;
        mResult.mBufferIndex = mCurrentSlice->mFetchBufferIndex;
        mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
    } else {
        if (mCurrentSlice->mInternalBufferOffset == 0) {
            //Hard-Failure case, we are requesting too many bytes...
            mResult.mSuccess = false;
        } else {
            
            //We MAY POSSIBLY be able to allocate this memory on another slice...
            mConsumedSlices.Add(mCurrentSlice);
            if (mAvailableSlices.IsEmpty()) {
                mCurrentSlice = new FFloatBufferCacheSlice();
            } else {
                mCurrentSlice = (FFloatBufferCacheSlice *)mAvailableSlices.PopLast();
                mCurrentSlice->Reset();
            }
            mCurrentSlice->AttemptFetch(pSize);
            if (mCurrentSlice->mFetchSuccess) {
                mResult.mSuccess = true;
                mResult.mBufferIndex = mCurrentSlice->mFetchBufferIndex;
                mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
            } else {
                //There is no chance at success with this module...
                mResult.mSuccess = false;
            }
        }
    }
}




FFloatBufferCacheByteAligned256::FFloatBufferCacheByteAligned256() {
    mCurrentSlice = NULL;
}

FFloatBufferCacheByteAligned256::~FFloatBufferCacheByteAligned256() {
    Purge();
}

void FFloatBufferCacheByteAligned256::Purge() {
    if (mCurrentSlice) {
        delete mCurrentSlice;
        mCurrentSlice = NULL;
    }
    FreeList(FFloatBufferCacheSlice, mConsumedSlices);
    FreeList(FFloatBufferCacheSlice, mAvailableSlices);
}

void FFloatBufferCacheByteAligned256::Reset() {
    mAvailableSlices.Add(mConsumedSlices);
    mConsumedSlices.RemoveAll();
    if (mCurrentSlice) {
        mCurrentSlice->Reset();
    }
    EnumList(FFloatBufferCacheSlice, aSlice, mAvailableSlices) {
        aSlice->Reset();
    }
}

void FFloatBufferCacheByteAligned256::Get(int pSize) {
    if ((pSize % 256) != 0) {
        int aHold = pSize;
        pSize = pSize >> 8;
        pSize = (pSize + 1) << 8;
    }
    if (mCurrentSlice == NULL) {
        if (mAvailableSlices.IsEmpty()) {
            mCurrentSlice = new FFloatBufferCacheSlice();
        } else {
            mCurrentSlice = (FFloatBufferCacheSlice *)mAvailableSlices.PopLast();
        }
        
        //At this point, we must be able to assign the space, otherwise
        //the buffer we are requesting is too large for this module...
        mCurrentSlice->AttemptFetch(pSize);
        if (mCurrentSlice->mFetchSuccess) {
            mResult.mSuccess = true;
            mResult.mBufferIndex = mCurrentSlice->mFetchBufferIndex;
            mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
        } else {
            //There is no chance at success with this module...
            mResult.mSuccess = false;
        }
        return;
    }
    
    mCurrentSlice->AttemptFetch(pSize);
    if (mCurrentSlice->mFetchSuccess) {
        mResult.mSuccess = true;
        mResult.mBufferIndex = mCurrentSlice->mFetchBufferIndex;
        mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
    } else {
        if (mCurrentSlice->mInternalBufferOffset == 0) {
            //Hard-Failure case, we are requesting too many bytes...
            mResult.mSuccess = false;
        } else {
            
            //We MAY POSSIBLY be able to allocate this memory on another slice...
            mConsumedSlices.Add(mCurrentSlice);
            if (mAvailableSlices.IsEmpty()) {
                mCurrentSlice = new FFloatBufferCacheSlice();
            } else {
                mCurrentSlice = (FFloatBufferCacheSlice *)mAvailableSlices.PopLast();
                mCurrentSlice->Reset();
            }
            mCurrentSlice->AttemptFetch(pSize);
            if (mCurrentSlice->mFetchSuccess) {
                mResult.mSuccess = true;
                mResult.mBufferIndex = mCurrentSlice->mFetchBufferIndex;
                mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
            } else {
                //There is no chance at success with this module...
                mResult.mSuccess = false;
            }
        }
    }
}


