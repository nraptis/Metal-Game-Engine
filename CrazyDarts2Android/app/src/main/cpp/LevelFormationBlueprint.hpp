//
//  LevelFormationBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelFormationBlueprint_hpp
#define LevelFormationBlueprint_hpp

#include "FJSON.hpp"
#include "LevelFormationTracerBlueprint.hpp"

#define BLUEPRINT_TRACER_COUNT 6

class LevelFormation;

class LevelWaveBlueprint;
class LevelFormationNodeBlueprint {
public:
    LevelFormationNodeBlueprint();
    ~LevelFormationNodeBlueprint();
    
    float                                       mEditorX;
    float                                       mEditorY;
    
    float                                       mPercentX;
    float                                       mPercentY;
    
    float                                       mGameX;
    float                                       mGameY;
    
    //int                                         mType;
    int                                         mObjectType;
    
    FJSONNode                                   *Save(bool pFromTracer);
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
};

class LevelFormationBlueprint {
public:
    
    LevelFormationBlueprint();
    ~LevelFormationBlueprint();
    
    void                                        Update();
    void                                        Reset();
    void                                        Draw(bool pSelected);
    
    void                                        Print();
    
    void                                        RefreshNodePositions();
    
    int                                         GetClosestIndex(float pX, float pY, float &pDist);
    
    
    void                                        Add(float pX, float pY);
    void                                        Remove(int pIndex);
    void                                        Set(int pIndex, float pX, float pY);
    float                                       GetX(int pIndex);
    float                                       GetY(int pIndex);
    LevelFormationNodeBlueprint        *GetNode(int pIndex);
    LevelFormationNodeBlueprint        *GetNode();
    
    int                                         mSelectedNodeIndex;
    FList                                       mNodeList;
    
    
    
    void                                        TracerAdd(float pX, float pY);
    void                                        TracerRemovePoint();
    void                                        TracerNuke();
    
    void                                        TracerSet(int pIndex, float pX, float pY);
    float                                       TracerGetX(int pIndex);
    float                                       TracerGetY(int pIndex);
    LevelFormationTracerBlueprint      *GetTracer();
    LevelFormationTracerNodeBlueprint  *TracerGetNode(int pIndex);
    LevelFormationTracerNodeBlueprint  *TracerGetNode();
    
    int                                         mCurrentTracerIndex;
    LevelFormationTracerBlueprint      mTracer[BLUEPRINT_TRACER_COUNT];
    
    float                                       mRotation;
    
    bool                                        mRotationEnabled;
    int                                         mRotationSpeedClass;
    bool                                        mRotationSpeedNegateAlways;
    bool                                        mRotationSpeedNegateRandom;
    
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    bool                                        IsValid();
    
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                        Build();
    void                                        Build(LevelFormation *pFormation);
    
private:
    FList                                       mKillNodeList;
    FList                                       mDeleteNodeList;
};
    
#endif /* LevelFormationBlueprint_hpp */
