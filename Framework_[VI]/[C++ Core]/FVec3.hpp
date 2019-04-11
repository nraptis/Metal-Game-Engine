//
//  FVec3.h
//  SRT
//
//  Created by Nick Raptis on 10/8/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_VEC_3
#define FRAMEWORK_VEC_3

#include "FVec2.hpp"

class FVec3
{
public:
	FVec3() {mX=0;mY=0;mZ=0;}
	FVec3(const float pX, const float pY, const float pZ) {mX=pX;mY=pY;mZ=pZ;}
	FVec3(const FVec3 &pFVec3) {*this=pFVec3;}
	FVec3(const FVec2 &pFVec2) {*this=pFVec2;}
	
	inline FVec3 &operator=(const FVec3 &pFVec3) {if(this!=&pFVec3) {mX=pFVec3.mX;mY=pFVec3.mY;mZ=pFVec3.mZ;}return *this;}
	inline FVec3 &operator=(const FVec2 &pFVec2) {mX=pFVec2.mX;mY=pFVec2.mY;mZ=0;return *this;}
	
	inline bool	operator==(const FVec3 &pFVec3) {return (mX==pFVec3.mX)&(mY==pFVec3.mY)&(mZ==pFVec3.mZ);}
	inline bool	operator!=(const FVec3 &pFVec3) {return (mX!=pFVec3.mX)|(mY!=pFVec3.mY)|(mZ!=pFVec3.mZ);}
	
	inline const FVec3	operator*(const FVec3 &pFVec3) const {return FVec3(mX*pFVec3.mX,mY*pFVec3.mY,mZ*pFVec3.mZ);}
	inline FVec3 &operator*=(const FVec3 &pFVec3) {mX*=pFVec3.mX;mY*=pFVec3.mY;mZ*=pFVec3.mZ;return *this;}
	inline const FVec3 operator*(const float pFloat) const {return FVec3(mX*pFloat,mY*pFloat,mZ*pFloat);}
	inline FVec3 &operator*=(const float pFloat) {mX*=pFloat;mY*=pFloat;mZ*=pFloat;return *this;}
	inline const FVec3	operator/(const FVec3 &pFVec3) const {return FVec3(mX/pFVec3.mX,mY/pFVec3.mY,mZ/pFVec3.mZ);}
	inline FVec3 &operator/=(const FVec3 &pFVec3) {mX/=pFVec3.mX;mY/=pFVec3.mY;mZ/=pFVec3.mZ;return *this;}
	inline const FVec3 operator/(const float pFloat) const {return FVec3(mX/pFloat,mY/pFloat,mZ/pFloat);}
	inline FVec3 &operator/=(const float pFloat) {mX/=pFloat;mY/=pFloat;mZ/=pFloat;return *this;}
	inline const FVec3 operator+(const FVec3 &pFVec3) const {return FVec3(mX+pFVec3.mX,mY+pFVec3.mY,mZ+pFVec3.mZ);}
	inline FVec3 &operator+=(const FVec3 &pFVec3) {mX+=pFVec3.mX;mY+=pFVec3.mY;mZ+=pFVec3.mZ;return *this;}
	inline const FVec3 operator+(const float pFloat) const {return FVec3(mX+pFloat,mY+pFloat,mZ+pFloat);}
	inline FVec3 &operator+=(const float pFloat) {mX+=pFloat;mY+=pFloat;mZ+=pFloat;return *this;}
	inline const FVec3 operator-(const FVec3 &pFVec3) const {return FVec3(mX-pFVec3.mX,mY-pFVec3.mY,mZ-pFVec3.mZ);}
	inline FVec3 &operator-=(const FVec3 &pFVec3) {mX-=pFVec3.mX;mY-=pFVec3.mY;mZ-=pFVec3.mZ;return *this;}
	inline const FVec3 operator-(const float pFloat) const {return FVec3(mX-pFloat,mY-pFloat,mZ-pFloat);}
	inline FVec3 & operator-=(const float pFloat) {mX-=pFloat;mY-=pFloat;mZ-=pFloat;return *this;}
	inline const FVec3 operator-() const {return FVec3(-mX,-mY,-mZ);}
	
    
	inline const FVec3	operator*(const FVec2 &pFVec2) const {return FVec3(mX*pFVec2.mX,mY*pFVec2.mY,mZ);}
	inline FVec3 &operator*=(const FVec2 &pFVec2) {mX*=pFVec2.mX;mY*=pFVec2.mY;return *this;}
	inline const FVec3	operator/(const FVec2 &pFVec2) const {return FVec3(mX/pFVec2.mX,mY/pFVec2.mY,mZ);}
	inline FVec3 &operator/=(const FVec2 &pFVec2) {mX/=pFVec2.mX;mY/=pFVec2.mY;;return *this;}
	inline const FVec3 operator+(const FVec2 &pFVec2) const {return FVec3(mX+pFVec2.mX,mY+pFVec2.mY,mZ);}
	inline FVec3 &operator+=(const FVec2 &pFVec2) {mX+=pFVec2.mX;mY+=pFVec2.mY;return *this;}
	inline const FVec3 operator-(const FVec2 &pFVec2) const {return FVec3(mX-pFVec2.mX,mY-pFVec2.mY,mZ);}
	inline FVec3 &operator-=(const FVec2 &pFVec2) {mX-=pFVec2.mX;mY-=pFVec2.mY;return *this;}
    
    
    float                               Length();
    float                               LengthSquared();
    
    void                                Normalize();
    
    float                               mX;
	float                               mY;
    float                               mZ;
    
    /*
	inline float Dot(FVec3 &pVector){return mX*pVector.mX+mY*pVector.mY+mZ*pVector.mZ;}
	FVec3 Cross(FVec3 &pVector)
    {
        FVec3 aResult;
        aResult.mX = (mY*pVector.mZ)-(pVector.mY*mZ);
        aResult.mY = -(mX*pVector.mZ)+(pVector.mX*mZ);
        aResult.mZ = (mX*pVector.mY)-(mY*pVector.mX);
        return aResult;
    }
    
	
	inline float LengthSquared(){return mX*mX+mY*mY+mZ*mZ;}
	inline float Length(){return sqrtf(mX*mX+mY*mY+mZ*mZ);}
	inline void SetLength(float pLength){Normalize();mX*=pLength;mY*=pLength;mZ*=pLength;}
	inline void Normalize(){float aLen=Length();if(aLen>0){mX/=aLen;mY/=aLen;mZ/=aLen;}}
    */
};

/*
FVec3 FVec3Make(float x, float y, float z);
FVec3 FVec3MakeWithArray(float values[3]);
FVec3 FVec3Negate(FVec3 vector);
FVec3 FVec3Add(FVec3 vectorLeft, FVec3 vectorRight);
FVec3 FVec3Subtract(FVec3 vectorLeft, FVec3 vectorRight);
FVec3 FVec3Multiply(FVec3 vectorLeft, FVec3 vectorRight);
FVec3 FVec3Divide(FVec3 vectorLeft, FVec3 vectorRight);
FVec3 FVec3AddScalar(FVec3 vector, float value);
FVec3 FVec3SubtractScalar(FVec3 vector, float value);
FVec3 FVec3MultiplyScalar(FVec3 vector, float value);
FVec3 FVec3DivideScalar(FVec3 vector, float value);
FVec3 FVec3Maximum(FVec3 vectorLeft, FVec3 vectorRight);
FVec3 FVec3Minimum(FVec3 vectorLeft, FVec3 vectorRight);
FVec3 FVec3Normalize(FVec3 vector);
float FVec3DotProduct(FVec3 vectorLeft, FVec3 vectorRight);
float FVec3Length(FVec3 vector);
float FVec3Distance(FVec3 vectorStart, FVec3 vectorEnd);
FVec3 FVec3Lerp(FVec3 vectorStart, FVec3 vectorEnd, float t);
FVec3 FVec3CrossProduct(FVec3 vectorLeft, FVec3 vectorRight);
FVec3 FVec3Project(FVec3 vectorToProject, FVec3 projectionVector);
*/

#endif
