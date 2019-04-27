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
#define LEVEL_MOTION_SLICE_TYPE_OSCILLATE_VERTICAL 2
#define LEVEL_MOTION_SLICE_TYPE_OSCILLATE_HORIZONTAL 3
#define LEVEL_MOTION_SLICE_TYPE_OSCILLATE_ROTATION 4

#include "GameObject.hpp"

class LevelMotionControllerSlice {
public:
    LevelMotionControllerSlice();
    virtual ~LevelMotionControllerSlice();
    
    virtual void                        Apply(float pReferenceX, float pReferenceY, float *pX, float *pY) { }
    
    virtual void                        Update() { }
    
    
    
    int                                 mType;
    
    //The "primary" speed class for this slice. For example, if we're
    //a rotation movement slice, this will effect the rotation speed.
    int                                 mSpeedClass;
    
    bool                                mSpeedNegateAlways;
    bool                                mSpeedNegateRandomly;
    
    bool                                mSpeedNegateRandomlyFlag;
    
    int                                 mKillTimer;
};

class LevelMotionControllerSliceRotate : public LevelMotionControllerSlice {
public:
    LevelMotionControllerSliceRotate();
    virtual ~LevelMotionControllerSliceRotate();
    
    virtual void                        Apply(float pReferenceX, float pReferenceY, float *pX, float *pY);
    virtual void                        Update();
    
    
    float                               mPivotOffsetX;
    float                               mPivotOffsetY;
    
    
    float                               mRotation;
    
    
    
    
};


#endif /* LevelMotionControllerSlice_hpp */
