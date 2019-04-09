//
//  LevelFormationTracerTracerNode.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelFormationTracerTracerNode_hpp
#define LevelFormationTracerTracerNode_hpp

class LevelFormationTracer;
class LevelFormationTracerNode {
public:
    LevelFormationTracerNode(LevelFormationTracer *pTracer);
    virtual ~LevelFormationTracerNode();
    
    //Position the node relative to (0.0f, 0.0f), (size for game)
    void                                SetUp();
    
    void                                Update();
    void                                Draw();
    
    LevelFormationTracer       *mTracer;
    
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
    
    LevelFormationTracerNode   *Clone(LevelFormationTracer *pTracer);
    
    
    int                                 mKillTimer;
};


#endif /* LevelFormationTracerTracerNode_hpp */
