//
//  Sprite3D.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef Sprite3D_hpp
#define Sprite3D_hpp

#include "FSprite.hpp"

class Sprite3D {
public:
    Sprite3D();
    virtual ~Sprite3D();
    
    //IMMEDIATELY - KNOW - This sprite is lible to change SIZE...
    //So we either need to constantly regenerate our quads, or we need fixed ASPECT RATIO? Quads?
    //So the imaher... is look right on scren?
    void                    SetSprite(FSprite *pSprite);
    FSprite                 *mSprite;
    float                   mAspect;
    
};



#endif /* Sprite3D_hpp */
