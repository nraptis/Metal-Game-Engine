//
//  LevelMotionControllerSliceBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelMotionControllerSliceBlueprint_hpp
#define LevelMotionControllerSliceBlueprint_hpp

#include "LevelMotionControllerSlice.hpp"
#include "FJSON.hpp"

class LevelMotionControllerSliceBlueprint {
public:
    LevelMotionControllerSliceBlueprint();
    virtual ~LevelMotionControllerSliceBlueprint();
    
    int                                         mType;
    
    //The "primary" speed class for this slice. For example, if we're
    //a rotation movement slice, this will effect the rotation speed.
    int                                         mSpeedClass;
    
    bool                                        mSpeedNegateAlways;
    bool                                        mSpeedNegateRandomly;
    
    void                                        Build(LevelMotionControllerSlice *pSlice);
    
    virtual FJSONNode                           *Save();
    virtual void                                Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
};

//Negate
class LevelMotionControllerSliceNegateBlueprint : public LevelMotionControllerSliceBlueprint {
public:
    LevelMotionControllerSliceNegateBlueprint();
    virtual ~LevelMotionControllerSliceNegateBlueprint();
    
    void                                        Build(LevelMotionControllerSliceNegate *pSlice);
    
    virtual FJSONNode                           *Save();
    virtual void                                Load(FJSONNode *pNode);

    bool                                        mNegateHAlways;
    bool                                        mNegateHRandomly;
    
    bool                                        mNegateVAlways;
    bool                                        mNegateVRandomly;
    
};

class LevelMotionControllerSliceRotateBlueprint : public LevelMotionControllerSliceBlueprint {
public:
    LevelMotionControllerSliceRotateBlueprint();
    virtual ~LevelMotionControllerSliceRotateBlueprint();
    
    void                                        Build(LevelMotionControllerSliceRotate *pSlice);
    
    virtual FJSONNode                           *Save();
    virtual void                                Load(FJSONNode *pNode);
    
    int                                         mPivotOffsetX;
    int                                         mPivotOffsetY;
    
    void                                        ResetPivot();
};


//class  : public LevelMotionControllerSliceBlueprint {
class LevelMotionControllerSliceOscillateRotationBlueprint : public LevelMotionControllerSliceBlueprint {
public:
    LevelMotionControllerSliceOscillateRotationBlueprint();
    virtual ~LevelMotionControllerSliceOscillateRotationBlueprint();
    
    void                                        Build(LevelMotionControllerSliceOscillateRotation *pSlice);
    
    virtual FJSONNode                           *Save();
    virtual void                                Load(FJSONNode *pNode);
    
    int                                         mAngleSpan;
    int                                         mAngleSpanOffsetStart;
    int                                         mAngleSpanOffsetEnd;
    
    bool                                        mLinear;
    int                                         mLinearTimer;
    int                                         mLinearTime;
    
    int                                         mPause1;
    int                                         mPause2;
};


class LevelMotionControllerSliceOscillateVerticalBlueprint : public LevelMotionControllerSliceBlueprint {
public:
    LevelMotionControllerSliceOscillateVerticalBlueprint();
    virtual ~LevelMotionControllerSliceOscillateVerticalBlueprint();
    
    void                                        Build(LevelMotionControllerSliceOscillateVertical *pSlice);
    
    virtual FJSONNode                           *Save();
    virtual void                                Load(FJSONNode *pNode);
    
    int                                         mRadius;
    
    bool                                        mLinear;
    int                                         mLinearTimer;
    int                                         mLinearTime;
    
    int                                         mPause1;
    int                                         mPause2;
};

class LevelMotionControllerSliceOscillateHorizontalBlueprint : public LevelMotionControllerSliceBlueprint {
public:
    LevelMotionControllerSliceOscillateHorizontalBlueprint();
    virtual ~LevelMotionControllerSliceOscillateHorizontalBlueprint();
    
    void                                        Build(LevelMotionControllerSliceOscillateHorizontal *pSlice);
    
    virtual FJSONNode                           *Save();
    virtual void                                Load(FJSONNode *pNode);
    
    int                                         mRadius;
    
    bool                                        mLinear;
    int                                         mLinearTimer;
    int                                         mLinearTime;
    
    int                                         mPause1;
    int                                         mPause2;
};




//LevelMotionControllerSlice.hpp
//class



#endif /* LevelMotionControllerSliceBlueprint_hpp */
