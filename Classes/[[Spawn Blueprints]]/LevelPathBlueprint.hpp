//
//  LevelPathBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelPathBlueprint_hpp
#define LevelPathBlueprint_hpp

#include "LevelPath.hpp"
#include "Constraint.hpp"
#include "LevelPath.hpp"
#include "FPoint.hpp"
#include "FJSON.hpp"

class LevelWaveBlueprint;
class LevelSectionPermanentBlueprint;



class LevelPathNodeBlueprint {
public:
    LevelPathNodeBlueprint();
    ~LevelPathNodeBlueprint();
    
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
    int                                         mDecelDistance;
    
    void                                        ShiftX(float pShiftX);
    void                                        ShiftY(float pShiftY);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
    
};

class LevelPathBlueprint {
public:
    
    LevelPathBlueprint();
    ~LevelPathBlueprint();
    
    LevelWaveBlueprint                          *mWave;
    LevelSectionPermanentBlueprint              *mPerm;
    
    void                                        Update();
    void                                        Reset();
    void                                        Draw(bool pSelected);
    
    void                                        RefreshNodePositions();
    
    int                                         GetClosestIndex(float pX, float pY, float &pDist);
    void                                        GetClosestPointOnLine(float pX, float pY, float &pDist);
    
    
    void                                        Set(int pIndex, float pX, float pY);
    float                                       GetX(int pIndex);
    float                                       GetY(int pIndex);
    
    void                                        Add(float pX, float pY);
    void                                        Remove(int pIndex);
    
    LevelPathNodeBlueprint                      *GetNode(int pIndex);
    LevelPathNodeBlueprint                      *GetNode();
    
    int                                         mSelectedIndex;
    FList                                       mNodeList;
    
    int                                         mSpeedClass; //Default: SPEED_CLASS_MEDIUM
    bool                                        mSmooth; //Default: false
    
    void                                        SnapX(int pIndex);
    void                                        SnapY(int pIndex);
    
    void                                        SetSnapXType(int pType);
    void                                        SetSnapYType(int pType);
    
    void                                        ApplyEditorConstraints();
    
    int                                         mMaxSpawnSize;
    
    
    //
    //
    //
    
    int                                         GetExitType();
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                        Build(LevelPath *pPath);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
private:
    FList                                       mKillList;
    FList                                       mDeleteList;
};

#endif
