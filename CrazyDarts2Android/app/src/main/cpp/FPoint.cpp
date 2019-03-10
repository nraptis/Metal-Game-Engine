//
//  FPoint.cpp
//  RaptisGame
//
//  Created by Nick Raptis on 3/20/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FPoint.h"
#include "core_includes.h"

float FPoint::Length() {
    float aLength = mX * mX + mY * mY;
    if(aLength > SQRT_EPSILON)aLength = sqrtf(aLength);
    return aLength;
}

float FPoint::LengthSquared() {
    return mX * mX + mY * mY;
}

void FPoint::Normalize() {
    float aLength = mX * mX + mY * mY;
    if (aLength > SQRT_EPSILON) {
        aLength = sqrtf(aLength);
        mX /= aLength;
        mY /= aLength;
    } else {
        mX = 0.0f;
        mY = -1.0f;
    }
}

FPoint FPointLerp(FPoint vectorStart, FPoint vectorEnd, float t) {
    FPoint aResult;
    aResult.mX = vectorStart.mX + ((vectorEnd.mX - vectorStart.mX) * t);
    aResult.mY = vectorStart.mY + ((vectorEnd.mY - vectorStart.mY) * t);
    return aResult;
}
