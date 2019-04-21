//
//  LevelMotionControllerSlice.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelMotionControllerSlice_hpp
#define LevelMotionControllerSlice_hpp

#define LEVEL_MOTION_SLICE_TYPE_NONE 0
#define LEVEL_MOTION_SLICE_TYPE_ROTATE 1
#define LEVEL_MOTION_SLICE_TYPE_OSCILLATE 2

class LevelMotionControllerSlice {
public:
    LevelMotionControllerSlice();
    ~LevelMotionControllerSlice();
    
    int                                 mType;
    
    
    
};

#endif /* LevelMotionControllerSlice_hpp */
