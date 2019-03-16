#include "FTexture.hpp"
#include "FSprite.h"
#include "FImage.hpp"
#include "FApp.hpp"
#include "PlatformGraphicsInterface.hpp"

#include "core_includes.h"
#include "os_core_graphics.h"

FTexture::FTexture(const char *pFileName) {
    Initialize(pFileName);
}

FTexture::FTexture() {
	mBindIndex = -1;
	//mBundleTexture = 0;

	mWidth = 0;
	mHeight = 0;
    
    mScale = 1;
    
	mExpandedWidth = 0;
	mExpandedHeight = 0;

	mOffsetX = 0;
	mOffsetY = 0;
	//FTexture::FTexture();


	//mFileNameBundle = "";

	mDidFailLoad = false;

    Initialize();
}

FTexture::~FTexture()
{
    
}

bool FTexture::IsValid()
{
    bool aResult = false;
    
    //(mBindIndex >= 0) && 
    if((mExpandedWidth > 0) && (mExpandedHeight > 0))
    {
        aResult = true;
    }
    
    return aResult;
}

void FTexture::Initialize(const char *pFilePath)
{
	mBindIndex = -1;
	//mBundleTexture = 0;

	mWidth = 0;
	mHeight = 0;

	mExpandedWidth = 0;
	mExpandedHeight = 0;

	mOffsetX = 0;
	mOffsetY = 0;
	//FTexture::FTexture();


	//mFileNameBundle = "";

	mDidFailLoad = false;

    Initialize();
    
    mFileName = pFilePath;
    Realize();
}

void FTexture::Initialize()
{
    
}

//Realize.. If we're gonna be
void FTexture::Realize() {
    if ((mBindIndex == -1) && (mDidFailLoad == false)) {
        FImage aImage;
        aImage.Load(mFileName);
        mScale = aImage.mScale;
        Load(&aImage);
    }
    
}

void FTexture::Load(FImage *pImage) {
    
    pImage->MakePowerOf2();
    
    mWidth = pImage->mWidth;
    mHeight = pImage->mHeight;
    
    mExpandedWidth = pImage->mExpandedWidth;
    mExpandedHeight = pImage->mExpandedHeight;
    
    mOffsetX = pImage->mOffsetX;
    mOffsetY = pImage->mOffsetY;
    
    mDidFailLoad = false;
    
    if(pImage->DidLoad()) {
        //if (Graphics::ThreadIsLocked()) {
        //    mBindIndex = Graphics::TextureGenerate(pImage->mData, mExpandedWidth, mExpandedHeight);
        //} else {
            //Graphics::ThreadLock();
        mBindIndex = Graphics::TextureGenerate(pImage->mData, mExpandedWidth, mExpandedHeight);
            //Graphics::ThreadUnlock();
        //}
    } else {
        mDidFailLoad = true;
        mBindIndex = -1;
    }
}

void FTexture::Unload() {
    if (mBindIndex != -1) {
        Graphics::TextureDelete(mBindIndex);
    }
    mBindIndex = -1;
    mDidFailLoad = false;
}

float FTexture::GetStartU() {
    float aResult = 0.0f;
    if (mExpandedWidth > 0) {
        aResult = ((float)mOffsetX) / ((float)mExpandedWidth);
    }
    return aResult;
}

float FTexture::GetStartV() {
    float aResult = 0.0f;
    if (mExpandedHeight > 0) {
        aResult = ((float)(mOffsetY)) / ((float)mExpandedHeight);
    }
    return aResult;
}

float FTexture::GetEndU()
{
    float aResult = 1.0f;
    if(mExpandedWidth > 0)
    {
        aResult = ((float)(mOffsetX + mWidth)) / ((float)mExpandedWidth);
    }
    return aResult;
}

float FTexture::GetEndV()
{
    float aResult = 1.0f;
    if(mExpandedHeight > 0)
    {
        aResult = ((float)(mOffsetY + mHeight)) / ((float)mExpandedHeight);
    }
    return aResult;
}





/*

void FTexture::Add(FSprite *pSprite)
{
    for(int i=0;i<mSpriteListCount;i++)
    {
        if(mSprite[i] == pSprite)
        {
            return;
        }
    }
    
    if(mSpriteListCount >= mSpriteListSize)
    {
        mSpriteListSize = (mSpriteListCount + mSpriteListCount / 2 + 1);
        
        FSprite **aSpriteNew = new FSprite*[mSpriteListSize];
        
        for(int i=0;i<mSpriteListCount;i++)
        {
            aSpriteNew[i] = mSprite[i];
        }
        
        delete [] mSprite;
        
        mSprite = aSpriteNew;
    }
    
    mSprite[mSpriteListCount] = pSprite;
    mSpriteListCount++;
}

void FTexture::Remove(FSprite *pSprite)
{
    
}
 
*/




FTextureRect::FTextureRect() {
    mVertex[0] = -128.0f;
    mVertex[1] = -128.0f;
    mVertex[2] = 128.0f;
    mVertex[3] = -128.0f;
    mVertex[4] = -128.0f;
    mVertex[5] = 128.0f;
    mVertex[6] = 128.0f;
    mVertex[7] = 128.0f;
    
    mTextureCoord[0] = 0.0f;
    mTextureCoord[1] = 0.0f;
    mTextureCoord[2] = 1.0f;
    mTextureCoord[3] = 0.0f;
    mTextureCoord[4] = 0.0f;
    mTextureCoord[5] = 1.0f;
    mTextureCoord[6] = 1.0f;
    mTextureCoord[7] = 1.0f;
}

FTextureRect::~FTextureRect() {
    
}

void FTextureRect::Set(FTexture *pTexture, float pX, float pY) {
    if (pTexture) {
        SetRect(pX, pY, pX + pTexture->mWidth, pY + pTexture->mHeight);
        SetUVQuad(pTexture->GetStartU(), pTexture->GetStartV(), pTexture->GetEndU(), pTexture->GetEndV());
    }
}

void FTextureRect::SetUVQuad(float pStartU, float pStartV, float pEndU, float pEndV)
{
    SetStartU(pStartU);
    SetStartV(pStartV);
    SetEndU(pEndU);
    SetEndV(pEndV);
}

void FTextureRect::SetUVRect(float pStartU, float pStartV, float pWidthU, float pHeightV)
{
    SetStartU(pStartU);
    SetStartV(pStartV);
    SetEndU(pStartU + pWidthU);
    SetEndV(pStartV + pHeightV);
}

void FTextureRect::SetQuad(float pStartX, float pStartY, float pEndX, float pEndY)
{
    SetStartX(pStartX);
    SetStartY(pStartY);
    SetEndX(pEndX);
    SetEndY(pEndY);
}

void FTextureRect::SetRect(float pStartX, float pStartY, float pWidth, float pHeight)
{
    SetStartX(pStartX);
    SetStartY(pStartY);
    SetEndX(pStartX + pWidth);
    SetEndY(pStartY + pHeight);
    
}

void FTextureRect::SetQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4)
{
    mVertex[0] = pX1;
    mVertex[1] = pY1;
    mVertex[2] = pX2;
    mVertex[3] = pY2;
    mVertex[4] = pX3;
    mVertex[5] = pY3;
    mVertex[6] = pX4;
    mVertex[7] = pY4;
}



FTextureTriangle::FTextureTriangle()
{
    mVertex[0] = -128.0f;
    mVertex[1] = -128.0f;
    mVertex[2] = 128.0f;
    mVertex[3] = -128.0f;
    mVertex[4] = -128.0f;
    mVertex[5] = 128.0f;
    
    mTextureCoord[0] = 0.0f;
    mTextureCoord[1] = 0.0f;
    mTextureCoord[2] = 1.0f;
    mTextureCoord[3] = 0.0f;
    mTextureCoord[4] = 0.0f;
    mTextureCoord[5] = 1.0f;
}

FTextureTriangle::~FTextureTriangle()
{
    
}

void FTextureTriangle::SetXYTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3) {
    mVertex[0] = pX1;
    mVertex[1] = pY1;
    mVertex[2] = pX2;
    mVertex[3] = pY2;
    mVertex[4] = pX3;
    mVertex[5] = pY3;
}

//void FTextureTriangle::SetUVTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3)
void FTextureTriangle::SetUVTriangle(float pU1, float pV1, float pU2, float pV2, float pU3, float pV3) {
    mTextureCoord[0] = pU1;
    mTextureCoord[1] = pV1;
    
    mTextureCoord[2] = pU2;
    mTextureCoord[3] = pV2;
    
    mTextureCoord[4] = pU3;
    mTextureCoord[5] = pV3;
}


