//
//  PGNode.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGNode.hpp"
#include "core_includes.h"

PGNode::PGNode(FSprite *pSprite) : PGNode() {
    SetSprite(pSprite);
}

PGNode::PGNode() {
    mX = 0.0f;
    mY = 0.0f;
    mWidth = 0.0f;
    mHeight = 0.0f;
    mSprite = 0;
}

PGNode::~PGNode() {

}

void PGNode::Update() {

}

void PGNode::Draw() {

}

void PGNode::SetSprite(FSprite *pSprite) {
    mSprite = pSprite;
    if (mSprite) {
        if (mWidth <= SQRT_EPSILON && mHeight < SQRT_EPSILON) {
            mWidth = mSprite->mWidth;
            mHeight = mSprite->mHeight;
        }
    }
}




