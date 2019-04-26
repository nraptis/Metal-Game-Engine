//
//  LevelMotionControllerBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelMotionControllerBlueprint_hpp
#define LevelMotionControllerBlueprint_hpp

#include "LevelMotionController.hpp"
#include "LevelMotionControllerSliceBlueprint.hpp"
#include "FVec2.hpp"
#include "FJSON.hpp"

class LevelWaveBlueprint;
class LevelSectionPermanentBlueprint;

class LevelMotionControllerBlueprint {
public:
    
    LevelMotionControllerBlueprint();
    ~LevelMotionControllerBlueprint();
    
    void                                        Update();
    void                                        Reset();
    void                                        Draw();
    
    //LevelMotionControllerSliceBlueprint         mSlice[BLUEPRINT_MOTION_SLICE_COUNT];
    
    bool                                        IsEmpty();
    
    void                                        RemoveAllSlices();
    void                                        RemoveFirstSlice();
    void                                        RemoveLastSlice();
    
    void                                        AddSliceRotate();
    void                                        AddSliceOscillateRotation();
    void                                        AddSliceOscillateV();
    void                                        AddSliceOscillateH();
    
    FList                                       mSliceList;
    //LevelMotionControllerSliceBlueprint
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                        Build(LevelMotionController *pMotionController);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
private:
    FList                                       mKillList;
    FList                                       mDeleteList;
};

#endif
