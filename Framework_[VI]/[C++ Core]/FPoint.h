//
//  FPoint.h
//  RaptisGame
//
//  Created by Nick Raptis on 3/20/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_POINT_HPP
#define FRAMEWORK_POINT_HPP

class FPoint
{
public:
    FPoint(){mX=0;mY=0;}
    FPoint(const float pX, const float pY) {mX=pX;mY=pY;}
    FPoint(const float pX, const int pY) {mX=pX;mY=(float)pY;}
    FPoint(const int pX, const float pY) {mX=(float)pX;mY=pY;}
    FPoint(const int pX, const int pY) {mX=(float)pX;mY=(float)pY;}
    FPoint(const FPoint &pFPoint) {*this=pFPoint;}
    
    inline FPoint &operator=(const FPoint &pFPoint) {if(this!=&pFPoint) {mX=pFPoint.mX;mY=pFPoint.mY;}return *this;}
    inline FPoint &operator=(float &pValue) {mX=pValue;mY=pValue;return *this;}
    inline FPoint &operator=(int &pValue) {mX=(float)pValue;mY=(float)pValue;return *this;}
    
    inline bool    operator==(const FPoint &pFPoint) {return (mX==pFPoint.mX)&(mY==pFPoint.mY);}
    inline bool    operator!=(const FPoint &pFPoint) {return (mX!=pFPoint.mX)|(mY!=pFPoint.mY);}
    
    inline const FPoint    operator*(const FPoint &pFPoint) const {return FPoint(mX*pFPoint.mX,mY*pFPoint.mY);}
    inline FPoint &operator*=(const FPoint &pFPoint) {mX*=pFPoint.mX;mY*=pFPoint.mY;return *this;}
    inline const FPoint operator*(const float pFloat) const {return FPoint(mX*pFloat,mY*pFloat);}
    inline FPoint &operator*=(const float pFloat) {mX*=pFloat;mY*=pFloat;return *this;}
    inline const FPoint    operator/(const FPoint &pFPoint) const {return FPoint(mX/pFPoint.mX,mY/pFPoint.mY);}
    inline FPoint &operator/=(const FPoint &pFPoint) {mX/=pFPoint.mX;mY/=pFPoint.mY;return *this;}
    inline const FPoint operator/(const float pFloat) const {return FPoint(mX/pFloat,mY/pFloat);}
    inline FPoint &operator/=(const float pFloat) {mX/=pFloat;mY/=pFloat;return *this;}
    inline const FPoint operator+(const FPoint &pFPoint) const {return FPoint(mX+pFPoint.mX,mY+pFPoint.mY);}
    inline FPoint &operator+=(const FPoint &pFPoint) {mX+=pFPoint.mX;mY+=pFPoint.mY;return *this;}
    inline const FPoint operator+(const float pFloat) const {return FPoint(mX+pFloat,mY+pFloat);}
    inline FPoint &operator+=(const float pFloat) {mX+=pFloat;mY+=pFloat;return *this;}
    inline const FPoint operator-(const FPoint &pFPoint) const {return FPoint(mX-pFPoint.mX,mY-pFPoint.mY);}
    inline FPoint &operator-=(const FPoint &pFPoint) {mX-=pFPoint.mX;mY-=pFPoint.mY;return *this;}
    inline const FPoint operator-(const float pFloat) const {return FPoint(mX-pFloat,mY-pFloat);}
    inline FPoint & operator-=(const float pFloat) {mX-=pFloat;mY-=pFloat;return *this;}
    inline const FPoint operator-() const {return FPoint(-mX,-mY);}
    
    float                               Length();
    float                               LengthSquared();
    
    void                                Normalize();
    
    float                               mX;
    float                               mY;
    
    float                               Dot(FPoint &pVector){return mX*pVector.mX+mY*pVector.mY;}
    float                               Cross(FPoint &pVector){return mX*pVector.mY-mY*pVector.mX;}
    
    void                                SetLength(float pLength){Normalize();mX*=pLength;mY*=pLength;}
};

class FIntPoint
{
public:
    FIntPoint(){mX=0;mY=0;}
    FIntPoint(const int pX, const int pY) {mX=pX;mY=pY;}
    FIntPoint(const int pX, const float pY) {mX=pX;mY=(int)pY;}
    FIntPoint(const float pX, const int pY) {mX=(int)pX;mY=pY;}
    FIntPoint(const float pX, const float pY) {mX=(int)pX;mY=(int)pY;}
    FIntPoint(const FIntPoint &pFIntPoint) {*this=pFIntPoint;}
    
    inline FIntPoint &operator=(const FIntPoint &pFIntPoint) {if(this!=&pFIntPoint) {mX=pFIntPoint.mX;mY=pFIntPoint.mY;}return *this;}
    inline FIntPoint &operator=(int &pValue) {mX=pValue;mY=pValue;return *this;}
    inline FIntPoint &operator=(float &pValue) {mX=(int)pValue;mY=(int)pValue;return *this;}
    
    inline bool    operator==(const FIntPoint &pFIntPoint) {return (mX==pFIntPoint.mX)&(mY==pFIntPoint.mY);}
    inline bool    operator!=(const FIntPoint &pFIntPoint) {return (mX!=pFIntPoint.mX)|(mY!=pFIntPoint.mY);}
    
    inline const FIntPoint    operator*(const FIntPoint &pFIntPoint) const {return FIntPoint(mX*pFIntPoint.mX,mY*pFIntPoint.mY);}
    inline FIntPoint &operator*=(const FIntPoint &pFIntPoint) {mX*=pFIntPoint.mX;mY*=pFIntPoint.mY;return *this;}
    inline const FIntPoint operator*(const int pint) const {return FIntPoint(mX*pint,mY*pint);}
    inline FIntPoint &operator*=(const int pint) {mX*=pint;mY*=pint;return *this;}
    inline const FIntPoint    operator/(const FIntPoint &pFIntPoint) const {return FIntPoint(mX/pFIntPoint.mX,mY/pFIntPoint.mY);}
    inline FIntPoint &operator/=(const FIntPoint &pFIntPoint) {mX/=pFIntPoint.mX;mY/=pFIntPoint.mY;return *this;}
    inline const FIntPoint operator/(const int pint) const {return FIntPoint(mX/pint,mY/pint);}
    inline FIntPoint &operator/=(const int pint) {mX/=pint;mY/=pint;return *this;}
    inline const FIntPoint operator+(const FIntPoint &pFIntPoint) const {return FIntPoint(mX+pFIntPoint.mX,mY+pFIntPoint.mY);}
    inline FIntPoint &operator+=(const FIntPoint &pFIntPoint) {mX+=pFIntPoint.mX;mY+=pFIntPoint.mY;return *this;}
    inline const FIntPoint operator+(const int pint) const {return FIntPoint(mX+pint,mY+pint);}
    inline FIntPoint &operator+=(const int pint) {mX+=pint;mY+=pint;return *this;}
    inline const FIntPoint operator-(const FIntPoint &pFIntPoint) const {return FIntPoint(mX-pFIntPoint.mX,mY-pFIntPoint.mY);}
    inline FIntPoint &operator-=(const FIntPoint &pFIntPoint) {mX-=pFIntPoint.mX;mY-=pFIntPoint.mY;return *this;}
    inline const FIntPoint operator-(const int pint) const {return FIntPoint(mX-pint,mY-pint);}
    inline FIntPoint & operator-=(const int pint) {mX-=pint;mY-=pint;return *this;}
    inline const FIntPoint operator-() const {return FIntPoint(-mX,-mY);}
    
    int                               mX;
    int                               mY;    
};

#endif
