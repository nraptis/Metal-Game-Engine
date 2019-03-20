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

#define PATH_CHAMFER_SIZE 90.0

class LevelWavePathBlueprintNode {
public:
    LevelWavePathBlueprintNode();
    ~LevelWavePathBlueprintNode();
    
    Constraint                                  mConstraint;
    
    float                                       mX;
    float                                       mY;
    
    float                                       mGameX;
    float                                       mGameY;
    
    int                                         mType;
    int                                         mWaitTimer;
    
    bool                                        mChamfer;
};

class LevelWavePathBlueprint {
public:
    
    LevelWavePathBlueprint();
    ~LevelWavePathBlueprint();
    
    void                                        Draw(bool pSelected);
    
    int                                         GetClosestIndex(float pX, float pY, float &pDist);
    void                                        Set(int pIndex, float pX, float pY);
    float                                       GetX(int pIndex);
    float                                       GetY(int pIndex);
    
    void                                        Add(float pX, float pY);
    void                                        Remove(int pIndex);
    void                                        Clear();
    
    bool                                        mSmooth;
    
    int                                         mSelectedIndex;
    FList                                       mNodeList;
    
    void                                        SnapX(int pIndex);
    void                                        SnapY(int pIndex);
    
    void                                        SetSnapXType(int pType);
    void                                        SetSnapYType(int pType);
    
    void                                        ApplyEditorConstraints();
    
    
    FPoint                                      GetGamePos(LevelWavePathBlueprintNode *pNode);
    FPoint                                      GetGamePos(float pX, float pY);
    
    
    void                                        Build();
    void                                        Build(LevelWavePath *pPath);
    
    
};

#endif
