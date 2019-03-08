//
//  PGNode.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PGNode_hpp
#define PGNode_hpp

#include "FObject.h"
#include "FSprite.h"
#include "FColor.hpp"
#include "FCanvas.hpp"

class PGNode : public FObject {
public:

    PGNode(FSprite *pSprite);
    PGNode();
    virtual ~PGNode();
    
    virtual void                            Update();
    virtual void                            Draw();

    void                                    SetSprite(FSprite *pSprite);

    FCanvasTransform                        mTransform;
    FCanvasAbsoluteTransform                mTransformAbsolute;

    float                                   mX;
    float                                   mY;
    float                                   mWidth;
    float                                   mHeight;

    FSprite                                 *mSprite;
};

#endif
