//
//  LevelWaveSpawnFormationTracerTracerNode.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelWaveSpawnFormationTracerTracerNode_hpp
#define LevelWaveSpawnFormationTracerTracerNode_hpp

class LevelWaveSpawnFormationTracer;
class LevelWaveSpawnFormationTracerNode {
public:
    LevelWaveSpawnFormationTracerNode(LevelWaveSpawnFormationTracer *pTracer);
    virtual ~LevelWaveSpawnFormationTracerNode();
    
    //Position the node relative to (0.0f, 0.0f), (size for game)
    void                                SetUp();
    
    void                                Update();
    void                                Draw();
    
    LevelWaveSpawnFormationTracer       *mTracer;
    
    //////////
    //
    //     Clone copy
    float                               mBaseX;
    float                               mBaseY;
    //
    //
    ////////
    
    
    //The positioned X and Y values...
    float                               mX;
    float                               mY;
    
    LevelWaveSpawnFormationTracerNode   *Clone(LevelWaveSpawnFormationTracer *pTracer);
    
    
    int                                 mKillTimer;
};


#endif /* LevelWaveSpawnFormationTracerTracerNode_hpp */
