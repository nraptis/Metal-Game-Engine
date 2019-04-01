//
//  LevelWavePathBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWavePathBlueprint_hpp
#define LevelWavePathBlueprint_hpp

#include "LevelWavePath.hpp"
#include "Constraint.hpp"
#include "LevelWavePath.hpp"
#include "FPoint.h"
#include "FJSON.hpp"

class LevelWaveBlueprint;
class LevelWavePathBlueprintNode {
public:
    LevelWavePathBlueprintNode();
    ~LevelWavePathBlueprintNode();
    
    Constraint                                  mConstraint;
    
    float                                       mEditorX;
    float                                       mEditorY;
    
    float                                       mPercentX;
    float                                       mPercentY;
    
    float                                       mBaseGameX;
    float                                       mBaseGameY;
    
    float                                       mGameX;
    float                                       mGameY;
    
    int                                         mType;
    int                                         mWaitTimer;
    int                                         mChamferSize;
    
    void                                        ShiftX(float pShiftX);
    void                                        ShiftY(float pShiftY);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
    
};

class LevelWavePathBlueprint {
public:
    
    LevelWavePathBlueprint();
    ~LevelWavePathBlueprint();
    
    LevelWaveBlueprint                          *mWave;
    
    void                                        Update();
    void                                        Clear();
    void                                        Draw(bool pSelected);
    
    void                                        RefreshNodePositions();
    
    int                                         GetClosestIndex(float pX, float pY, float &pDist);
    void                                        GetClosestPointOnLine(float pX, float pY, float &pDist);
    
    
    void                                        Set(int pIndex, float pX, float pY);
    float                                       GetX(int pIndex);
    float                                       GetY(int pIndex);
    
    void                                        Add(float pX, float pY);
    void                                        Remove(int pIndex);
    
    LevelWavePathBlueprintNode                  *GetNode(int pIndex);
    LevelWavePathBlueprintNode                  *GetNode();
    
    int                                         mSelectedIndex;
    FList                                       mNodeList;
    
    int                                         mSpeedClass;
    bool                                        mSmooth;
    
    void                                        SnapX(int pIndex);
    void                                        SnapY(int pIndex);
    
    void                                        SetSnapXType(int pType);
    void                                        SetSnapYType(int pType);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    FList                                       mKillList;
    FList                                       mDeleteList;
};

#endif
