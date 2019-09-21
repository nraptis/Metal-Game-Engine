//
//  FreeLife.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FreeLife_hpp
#define FreeLife_hpp

#include "Balloon.hpp"
#include "FPointList.hpp"

class FreeLife : public Balloon {
public:
    FreeLife();
    virtual ~FreeLife();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual bool                            WillCollide(float pStartX, float pStartY, float pEndX, float pEndY);
    
    void                                    BuildEdgePointListBase();
    void                                    BuildEdgePointList();
    
    FPointList                              mEdgePointList3DBase;
    FPointList                              mEdgePointList3D;
    FPointList                              mEdgePointList2D;
    
};


#endif /* FreeLife_hpp */
