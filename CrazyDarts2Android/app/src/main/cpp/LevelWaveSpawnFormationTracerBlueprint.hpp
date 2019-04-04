//
//  LevelWaveSpawnFormationTracerTracerBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveSpawnFormationTracerTracerBlueprint_hpp
#define LevelWaveSpawnFormationTracerTracerBlueprint_hpp

#include "FJSON.hpp"

class LevelWaveSpawnFormationTracer;
class LevelWaveSpawnFormationTracerBlueprintNode {
public:
    LevelWaveSpawnFormationTracerBlueprintNode();
    ~LevelWaveSpawnFormationTracerBlueprintNode();
    
    float                                               mEditorX;
    float                                               mEditorY;
    
    float                                               mPercentX;
    float                                               mPercentY;
    
    FJSONNode                                           *Save();
    void                                                Load(FJSONNode *pNode);
    
    int                                                 mKillTimer;
};

class LevelWaveSpawnFormationTracerBlueprint {
public:
    
    LevelWaveSpawnFormationTracerBlueprint();
    ~LevelWaveSpawnFormationTracerBlueprint();
    
    void                                                Update();
    void                                                Clear();
    void                                                Draw(bool pSelected);
    
    void                                                RefreshNodePositions();
    
    int                                                 GetClosestIndex(float pX, float pY, float &pDist);
    
    void                                                Set(int pIndex, float pX, float pY);
    float                                               GetX(int pIndex);
    float                                               GetY(int pIndex);
    
    void                                                Add(float pX, float pY);
    void                                                Remove(int pIndex);
    
    LevelWaveSpawnFormationTracerBlueprintNode          *GetNode(int pIndex);
    LevelWaveSpawnFormationTracerBlueprintNode          *GetNode();
    
    int                                                 mSelectedNodeIndex;
    FList                                               mNodeList;
    
    FJSONNode                                           *Save();
    void                                                Load(FJSONNode *pNode);
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                                Build(LevelWaveSpawnFormationTracer *pTracer);
    
    bool                                                IsValid();
    
    
    int                                                 mCount;
    int                                                 mSpeedClass;
    
    
private:
    FList                                               mKillNodeList;
    FList                                               mDeleteNodeList;
};
    
#endif /* LevelWaveSpawnFormationTracerTracerBlueprint_hpp */
