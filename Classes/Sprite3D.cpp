//
//  Sprite3D.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/14/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "Sprite3D.hpp"


Sprite3D::Sprite3D() {
    
    mSprite = NULL;
    mAspect = 1.0f;
    
    
}

Sprite3D::~Sprite3D() {
    
}

//IMMEDIATELY - KNOW - This sprite is lible to change SIZE...
//So we either need to constantly regenerate our quads, or we need fixed ASPECT RATIO? Quads?
//So the imaher... is look right on scren?
void Sprite3D::SetSprite(FSprite *pSprite) {
    
    mSprite = pSprite;
    mAspect = 1.0f;
    
    if (mSprite != NULL) {
        
        
    }
    
    
    
}





