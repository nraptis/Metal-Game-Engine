//
//  LevelFormationTracerTracerBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelFormationTracerTracerBlueprint_hpp
#define LevelFormationTracerTracerBlueprint_hpp

#include "FJSON.hpp"

class LevelFormationTracer;
class LevelFormationTracerNodeBlueprint {
public:
    LevelFormationTracerNodeBlueprint();
    ~LevelFormationTracerNodeBlueprint();
    
    float                                               mEditorX;
    float                                               mEditorY;
    
    float                                               mPercentX;
    float                                               mPercentY;
    
    FJSONNode                                           *Save();
    void                                                Load(FJSONNode *pNode);
    
    int                                                 mKillTimer;
};

class LevelFormationTracerBlueprint {
public:
    
    LevelFormationTracerBlueprint();
    ~LevelFormationTracerBlueprint();
    
    void                                                Update();
    void                                                Reset(); //Keeps spawn nodes...
    void                                                Nuke();  //Clears + removes spawn nodes...
    
    
    void                                                Draw(bool pSelected);
    
    int                                                 CountProgressObjects();
        
    void                                                RefreshNodePositions();
    
    void                                                RefreshSpawnNodeList();
    
    int                                                 GetClosestIndex(float pX, float pY, float &pDist);
    
    void                                                Set(int pIndex, float pX, float pY);
    float                                               GetX(int pIndex);
    float                                               GetY(int pIndex);
    
    void                                                Add(float pX, float pY);
    void                                                Remove(int pIndex);
    
    LevelFormationTracerNodeBlueprint                   *GetNode(int pIndex);
    LevelFormationTracerNodeBlueprint                   *GetNode();
    
    int                                                 mSelectedTracerNodeIndex;
    FList                                               mTracerNodeList;
    
    
    int                                                 mSelectedSpawnNodeIndex;
    FList                                               mSpawnNodeList;
    
    FJSONNode                                           *Save();
    void                                                Load(FJSONNode *pNode);
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                                Build(LevelFormationTracer *pTracer);
    
    bool                                                IsValid();
    
    int                                                 mCount;
    //int                                                 mSpeedClass;
    
    int                                                 mSpecialType;
    
    float                                               mSpecialPercentX;
    float                                               mSpecialPercentY;
    
    float                                               mSpecialSpecialEditorX;
    float                                               mSpecialSpecialEditorY;
    
    int                                                 mSpecialRadius;
    int                                                 mSpecialCornerRadius;
    
    
private:
    FList                                               mKillTracerNodeList;
    FList                                               mDeleteTracerNodeList;
    
    FList                                               mKillSpawnNodeList;
    FList                                               mDeleteSpawnNodeList;
};
    
#endif /* LevelFormationTracerTracerBlueprint_hpp */
