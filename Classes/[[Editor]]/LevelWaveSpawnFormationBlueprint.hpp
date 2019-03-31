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

class LevelWaveSpawnFormationBlueprintNode {
public:
    LevelWaveSpawnFormationBlueprintNode();
    ~LevelWaveSpawnFormationBlueprintNode();
    
    float                                       mX;
    float                                       mY;
    
    //From the center of the formation, percent * 100 of game width / height..
    float                                       mFormationX;
    float                                       mFormationY;
    
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
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    FList                                       mKillList;
    FList                                       mDeleteList;
};

#endif /* LevelWaveSpawnFormationBlueprint_hpp */
