//
//  SkyRenderer.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef SkyRenderer_hpp
#define SkyRenderer_hpp

//#include "FPrimitive.hpp"
#include "FDrawQuad.hpp"

class SkyRenderer {
public:
    SkyRenderer();
    ~SkyRenderer();
    
    void                        Refresh(float pTop, float pRight, float pBottom, float pLeft, float pPadding);
    FDrawQuadGrid               mGrid;
    
    void                        Update();
    void                        Draw();
    
    
    
    
};


#endif /* SkyRenderer_hpp */
