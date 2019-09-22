//
//  LevelSectionPermBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelSectionPermBlueprint_hpp
#define LevelSectionPermBlueprint_hpp

#include "LevelPathBlueprint.hpp"
#include "LevelPermSpawnBlueprint.hpp"
#include "LevelMotionControllerBlueprint.hpp"
#include "LevelStyleControllerBlueprint.hpp"
#include "LevelFormationConfigurationBlueprint.hpp"


#define PERM_MAX_SPAWN_COUNT 12

class LevelSectionPerm;
class LevelSectionPermBlueprint {
public:
    LevelSectionPermBlueprint();
    ~LevelSectionPermBlueprint();
    
    void                                        Reset();
    
    void                                        Update();
    void                                        Draw(bool pSelected);
    
    int                                         CountProgressObjects();
    
    LevelPathBlueprint                          mPath;
    void                                        ApplyEditorConstraints();
    void                                        DeletePath();
    
    bool                                        IsPathPerm();
    
    Constraint                                  mConstraint;
    
    float                                       mEditorX;
    float                                       mEditorY;
    
    float                                       mPercentX;
    float                                       mPercentY;
    
    float                                       mBaseGameX;
    float                                       mBaseGameY;
    
    float                                       mGameX;
    float                                       mGameY;
    
    void                                        ShiftX(float pShiftX);
    void                                        ShiftY(float pShiftY);
    
    
    LevelMotionControllerBlueprint              mMotionController;
    LevelStyleControllerBlueprint               mStyleController;
    
    LevelPermSpawnBlueprint                     mSpawn[PERM_MAX_SPAWN_COUNT + 1];
    
    int                                         mSpawnCount;
    int                                         mSelectedSpawnIndex;
    
    bool                                        mSpawnEqualSpacing;
    int                                         mSpawnSpacing;
    
    
    
    FString                                     mFormationID;
    LevelFormationConfigurationBlueprint        mFormationConfiguration;
    
    int                                         mObjectType;
    
    void                                        ShiftSpawnFromIndex(int pIndex);
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                        Build(LevelSectionPerm *pPerm);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
};

#endif /* LevelSectionPermBlueprint_hpp */
