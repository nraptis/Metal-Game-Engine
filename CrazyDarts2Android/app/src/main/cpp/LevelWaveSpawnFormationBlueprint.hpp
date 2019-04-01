//
//  LevelWaveSpawnFormationBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveSpawnFormationBlueprint_hpp
#define LevelWaveSpawnFormationBlueprint_hpp

#include "FJSON.hpp"
#include "FPoint.h"

class LevelWaveSpawnFormation;

class LevelWaveBlueprint;
class LevelWaveSpawnFormationBlueprintNode {
public:
    LevelWaveSpawnFormationBlueprintNode();
    ~LevelWaveSpawnFormationBlueprintNode();
    
    float                                       mEditorX;
    float                                       mEditorY;
    
    float                                       mPercentX;
    float                                       mPercentY;
    
    float                                       mGameX;
    float                                       mGameY;
    
    int                                         mType;
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
};

class LevelWaveSpawnFormationBlueprint {
public:
    
    LevelWaveSpawnFormationBlueprint();
    ~LevelWaveSpawnFormationBlueprint();
    
    void                                        Update();
    void                                        Clear();
    void                                        Draw(bool pSelected);
    
    void                                        Print();
    
    
    void                                        RefreshNodePositions();
    
    int                                         GetClosestIndex(float pX, float pY, float &pDist);
    
    void                                        Set(int pIndex, float pX, float pY);
    float                                       GetX(int pIndex);
    float                                       GetY(int pIndex);
    
    void                                        Add(float pX, float pY);
    void                                        Remove(int pIndex);
    
    LevelWaveSpawnFormationBlueprintNode        *GetNode(int pIndex);
    LevelWaveSpawnFormationBlueprintNode        *GetNode();
    
    int                                         mSelectedIndex;
    FList                                       mNodeList;
    
    
    bool                                        mRotationEnabled;
    int                                         mRotationSpeedClass;
    bool                                        mRotationSpeedNegateAlways;
    bool                                        mRotationSpeedNegateRandom;
    
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                        Build();
    void                                        Build(LevelWaveSpawnFormation *pFormation);
    
    FList                                       mKillList;
    FList                                       mDeleteList;
};
    
#endif /* LevelWaveSpawnFormationBlueprint_hpp */
