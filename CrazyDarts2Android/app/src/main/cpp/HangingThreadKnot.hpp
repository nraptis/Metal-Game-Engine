//
//  HangingThreadKnot.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef HangingThreadKnot_hpp
#define HangingThreadKnot_hpp

class HangingThreadKnot {
public:
    HangingThreadKnot();
    ~HangingThreadKnot();
    
    float                   GetX() { return mBaseX + mOffsetX; }
    float                   GetY() { return mBaseY + mOffsetY; }
    float                   GetZ() { return mBaseZ + mOffsetZ; }
    
    float                   mBaseX;
    float                   mBaseY;
    float                   mBaseZ;
    
    float                   mOffsetX;
    float                   mOffsetY;
    float                   mOffsetZ;
    
    
};

#endif /* HangingThreadKnot_hpp */
