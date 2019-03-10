//
//  FVec3.cpp
//  SRT
//
//  Created by Nick Raptis on 10/8/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FVec3.h"
#include "core_includes.h"

float FVec3::Length()
{
    float aLength = mX * mX + mY * mY + mZ * mZ;
    if(aLength > SQRT_EPSILON)aLength = sqrtf(aLength);
    return aLength;
}

float FVec3::LengthSquared()
{
    return mX * mX + mY * mY;
}

void FVec3::Normalize()
{
    float aLength = mX * mX + mY * mY + mZ * mZ;
    if(aLength > SQRT_EPSILON)
    {
        aLength = sqrtf(aLength);
        mX /= aLength;
        mY /= aLength;
        mZ /= aLength;
    }
    else
    {
        mX = 0.0f;
        mY = -1.0f;
        mZ = 0.0f;
    }
}


/*

FVec3 FVec3Make(float x, float y, float z)
{
    FVec3 v = { x, y, z };
    return v;
}

FVec3 FVec3MakeWithArray(float values[3])
{
    FVec3 v = { values[0], values[1], values[2] };
    return v;
}

FVec3 FVec3Negate(FVec3 vector)
{
    FVec3 v = { -vector.mX, -vector.mY, -vector.mZ };
    return v;
}

FVec3 FVec3Add(FVec3 vectorLeft, FVec3 vectorRight)
{
    FVec3 v = { vectorLeft.mX + vectorRight.mX,
        vectorLeft.mY + vectorRight.mY,
        vectorLeft.mZ + vectorRight.mZ };
    return v;
}

FVec3 FVec3Subtract(FVec3 vectorLeft, FVec3 vectorRight)
{
    FVec3 v = { vectorLeft.mX - vectorRight.mX,
        vectorLeft.mY - vectorRight.mY,
        vectorLeft.mZ - vectorRight.mZ };
    return v;
}

FVec3 FVec3Multiply(FVec3 vectorLeft, FVec3 vectorRight)
{
    FVec3 v = { vectorLeft.mX * vectorRight.mX,
        vectorLeft.mY * vectorRight.mY,
        vectorLeft.mZ * vectorRight.mZ };
    return v;
}

FVec3 FVec3Divide(FVec3 vectorLeft, FVec3 vectorRight)
{
    FVec3 v = { vectorLeft.mX / vectorRight.mX,
        vectorLeft.mY / vectorRight.mY,
        vectorLeft.mZ / vectorRight.mZ };
    return v;
}

FVec3 FVec3AddScalar(FVec3 vector, float value)
{
    FVec3 v = { vector.mX + value,
        vector.mY + value,
        vector.mZ + value };
    return v;
}

FVec3 FVec3SubtractScalar(FVec3 vector, float value)
{
    FVec3 v = { vector.mX - value,
        vector.mY - value,
        vector.mZ - value };
    return v;
}

FVec3 FVec3MultiplyScalar(FVec3 vector, float value)
{
    FVec3 v = { vector.mX * value,
        vector.mY * value,
        vector.mZ * value };
    return v;
}

FVec3 FVec3DivideScalar(FVec3 vector, float value)
{
    FVec3 v = { vector.mX / value,
        vector.mY / value,
        vector.mZ / value };
    return v;
}

FVec3 FVec3Maximum(FVec3 vectorLeft, FVec3 vectorRight)
{
    FVec3 max = vectorLeft;
    if(vectorRight.mX > vectorLeft.mX)
        max.mX = vectorRight.mX;
    if(vectorRight.mY > vectorLeft.mY)
        max.mY = vectorRight.mY;
    if(vectorRight.mZ > vectorLeft.mZ)
        max.mZ = vectorRight.mZ;
    return max;
}

FVec3 FVec3Minimum(FVec3 vectorLeft, FVec3 vectorRight)
{
    FVec3 min = vectorLeft;
    if(vectorRight.mX < vectorLeft.mX)
        min.mX = vectorRight.mX;
    if(vectorRight.mY < vectorLeft.mY)
        min.mY = vectorRight.mY;
    if(vectorRight.mZ < vectorLeft.mZ)
        min.mZ = vectorRight.mZ;
    return min;
}

FVec3 FVec3Normalize(FVec3 vector)
{
    float scale = 1.0f / FVec3Length(vector);
    FVec3 v = { vector.mX * scale, vector.mY * scale, vector.mZ * scale };
    return v;
}

float FVec3DotProduct(FVec3 vectorLeft, FVec3 vectorRight)
{
    return vectorLeft.mX * vectorRight.mX + vectorLeft.mY * vectorRight.mY + vectorLeft.mZ * vectorRight.mZ;
}

float FVec3Length(FVec3 vector)
{
    return sqrt(vector.mX * vector.mX + vector.mY * vector.mY + vector.mZ * vector.mZ);
}

float FVec3Distance(FVec3 vectorStart, FVec3 vectorEnd)
{
    return FVec3Length(FVec3Subtract(vectorEnd, vectorStart));
}

FVec3 FVec3Lerp(FVec3 vectorStart, FVec3 vectorEnd, float t)
{
    FVec3 v = { vectorStart.mX + ((vectorEnd.mX - vectorStart.mX) * t),
        vectorStart.mY + ((vectorEnd.mY - vectorStart.mY) * t),
        vectorStart.mZ + ((vectorEnd.mZ - vectorStart.mZ) * t) };
    return v;
}

FVec3 FVec3CrossProduct(FVec3 vectorLeft, FVec3 vectorRight)
{
    FVec3 v = { vectorLeft.mY * vectorRight.mZ - vectorLeft.mZ * vectorRight.mY,
        vectorLeft.mZ * vectorRight.mX - vectorLeft.mX * vectorRight.mZ,
        vectorLeft.mX * vectorRight.mY - vectorLeft.mY * vectorRight.mX };
    return v;
}

FVec3 FVec3Project(FVec3 vectorToProject, FVec3 projectionVector)
{
    float scale = FVec3DotProduct(projectionVector, vectorToProject) / FVec3DotProduct(projectionVector, projectionVector);
    FVec3 v = FVec3MultiplyScalar(projectionVector, scale);
    return v;
}

*/
