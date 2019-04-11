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




class LevelFormationTracer;
class LevelFormation {
public:
    LevelFormation();
    ~LevelFormation();
    
    void                                        Reset();
    void                                        Spawn();
    void                                        Update();
    void                                        Draw(int pSelectedIndex);
    void                                        DisposeObject(GameObject *pObject);
    
    
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
    
    LevelFormation                     *Clone();
    
    
    //For Editor
    void                                        EditorKillAllObjects();
    
private:
    
    FList                                       mNodeKillList;
    FList                                       mNodeDeleteList;
    
    FList                                       mTracerKillList;
    FList                                       mTracerDeleteList;
    
};

#endif /* LevelWaveFormation_hpp */
