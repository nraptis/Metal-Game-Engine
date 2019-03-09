//
//  VideoBuffer.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "VideoBuffer.hpp"

VideoBuffer::VideoBuffer(int pSize, int pIndex) {
    mIndex = pIndex;
    mData = new unsigned char[pSize];
    mLength = pSize;
}

VideoBuffer::~VideoBuffer() {
    
}
