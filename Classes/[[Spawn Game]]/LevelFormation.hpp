//
//  LevelWaveFormation.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveFormation_hpp
#define LevelWaveFormation_hpp


#include "FList.hpp"
#include "LevelFormationTracer.hpp"
#include "LevelFormationNode.hpp"
#include "LevelMotionController.hpp"
#include "LevelStyleController.hpp"
#include "LevelFormationConfiguration.hpp"

class LevelWaveSpawn;
class LevelPermSpawn;

class LevelFormationTracer;
class LevelFormation {
public:
    LevelFormation();
    ~LevelFormation();
    
    bool                                        mDidSpawn;
    bool                                        IsClearForSectionCompletion(); //For perms
    bool                                        HasAnyObjects();
    
    void                                        Reset();
    void                                        Spawn(LevelMotionController *pMotionController, LevelFormationConfiguration *pConfiguration);
    void                                        Update(LevelMotionController *pMotionController);
    
    void                                        Draw(int pSelectedIndex);
    void                                        DisposeObject(GameObject *pObject);
    
    //Gets called on every update...
    void                                        ApplyMotionController(LevelMotionController *pMotionController);
    
    //Gets called once after SPAWN...
    void                                        ApplyStyleController(LevelStyleController *pStyleController);
    
    
    bool                                        IsClear();
    
    void                                        HandOffAllGameObjects(FList *pList);
    
    bool                                        mDidOriginateOnWave;
    bool                                        mDidOriginateAsPermanent;
    
    
    FString                                     mID;
    
    FList                                       mSpawnNodeList;
    FList                                       mTracerList;
    
    
    

    
    
    ///////////////////
    //
    //   Copy Vars...
    //
    float                                       mX;
    float                                       mY;
    //
    //
    //////////////////
    
    
    float                                       mRotation;
    
    void                                        GetExtremeties(float &pTop, float &pRight, float &pBottom, float &pLeft);
    
    void                                        SetWaveSpawn(LevelWaveSpawn *pSpawn);
    void                                        SetPermSpawn(LevelPermSpawn *pSpawn);
    
    LevelFormation                              *Clone();
    
    //For Editor
    
    void                                        EditorKillAllObjects();
    bool                                        EditorHasAnyTracers();
    bool                                        EditorHasNonTracers();
    bool                                        EditorHasMixedTypes();
    bool                                        EditorHasBalloonsOnly();
    bool                                        EditorHasType(int pType);
    
private:
    
    FList                                       mNodeKillList;
    FList                                       mNodeDeleteList;
    
    FList                                       mTracerKillList;
    FList                                       mTracerDeleteList;
    
};

#endif /* LevelWaveFormation_hpp */
