//
//  VideoBuffer.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef VideoBuffer_hpp
#define VideoBuffer_hpp

class VideoBuffer {
public:
    VideoBuffer(int pSize, int pIndex);
    ~VideoBuffer();
    unsigned char *mData;
    int mLength;
    int mIndex;
};

#endif /* VideoBuffer_hpp */
