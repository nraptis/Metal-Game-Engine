//
//  LevelFormationNodeFormationNode.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/31/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelFormationNodeFormationNode_hpp
#define LevelFormationNodeFormationNode_hpp

#include "GameObject.hpp"

class LevelFormation;
class LevelFormationTracer;
class LevelFormationNode {
public:
    LevelFormationNode();
    virtual ~LevelFormationNode();
    
    void                                Spawn();
    
    void                                Reset();
    void                                Restart();
    
    void                                Update();
    void                                Draw();
    void                                DisposeObject(GameObject *pObject);
    
    void                                PositionObject();
    
    bool                                mDidOriginateOnWave;
    bool                                mDidOriginateAsPermanent;
    
    LevelFormation                      *mFormation;
    LevelFormationTracer                *mTracer;
    
    GameObject                          *mObject;
    
    int                                 mObjectType;
    
    int                                 mPathIndexOffset;
    
    float                               mBaseX;
    float                               mBaseY;
    
    LevelFormationNode         *Clone(LevelFormation *pFormation);
    
    
    
    //The positioned X and Y values...
    float                               mX;
    float                               mY;
    
    int                                 mKillTimer;
};


#endif /* LevelFormationNodeFormationNode_hpp */
