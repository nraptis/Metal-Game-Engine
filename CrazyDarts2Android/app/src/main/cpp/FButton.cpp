//
//  FButton.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/23/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FButton.h"
#include "core_includes.h"

FButton::FButton() {
    mName = "Button";

    mClickData = 0;

    mDrawManual = false;
    
    mDrawRectIfSpriteIsNull = true;

    mTriggerOnDown = false;
    mTriggerOnUp = true;
    
    mButtonLayer = new FButtonLayer();
    
    
    //mColor.mRed = 1.0f;
    //mColor.mGreen = 1.0f;
    //mColor.mBlue = 1.0f;
    mColor.mAlpha = 1.0f;
    
    //mSpriteUp = 0;
    //mSpriteOver = 0;
    //mSpriteDown = 0;
    
    //mSpriteOverlayUp = 0;
    //mSpriteOverlayOver = 0;
    //mSpriteOverlayDown = 0;
    
    //mColorUp = FColor(1.0f, 1.0f, 1.0f);
    //mColorOver = FColor(1.0f, 1.0f, 1.0f);
    //mColorDown = FColor(1.0f, 1.0f, 1.0f);
    
    //mListener = 0;

}

FButton::~FButton() {
    FreeList(FButtonLayer, mButtonLayersUnder);
    FreeList(FButtonLayer, mButtonLayersOver);
    delete mButtonLayer;
    mButtonLayer = 0;
}

/*
void FButton::Setup(int x, int y, int pWidth, int pHeight, FView *pListener)
{
    SetFrame(x, y, pWidth, pHeight);
    
    if(pListener)
    {
        pListener->AddSubview(this);
        
        GetContainer()->mRetainedByParent = true;
    }
}

void FButton::Setup(int x, int y, FSprite *pSpriteArray, int pSpriteCount, FView *pListener)
{
    if(pSpriteCount > 0)
    {
        mSpriteUp = &(pSpriteArray[0]);
        
        if(pSpriteCount > 1)
        {
            if(pSpriteCount < 3)
            {
                mSpriteDown = &(pSpriteArray[1]);
            }
            else
            {
                mSpriteOver = &(pSpriteArray[1]);
                mSpriteDown = &(pSpriteArray[2]);
            }
        }
    }
    
    float aWidth = 0.0f;
    float aHeight = 0.0f;
    
    if(mSpriteUp)
    {
        aWidth = mSpriteUp->mWidth;
        aHeight = mSpriteUp->mHeight;
    }
    
    Setup(x, y, aWidth, aHeight, pListener);
}

void FButton::Setup(int x, int y, FSprite *pSprite, FView *pListener)
{
    mSpriteUp = pSprite;
    
    float aWidth = 0.0f;
    float aHeight = 0.0f;
    
    if(mSpriteUp)
    {
        aWidth = mSpriteUp->mWidth;
        aHeight = mSpriteUp->mHeight;
    }
    
    Setup(x, y, aWidth, aHeight, pListener);
}

void FButton::Setup(int x, int y, FSprite *pSprite)
{
    mSpriteUp = pSprite;
    
    float aWidth = 0.0f;
    float aHeight = 0.0f;
    
    if(mSpriteUp)
    {
        aWidth = mSpriteUp->mWidth;
        aHeight = mSpriteUp->mHeight;
    }
    
    Setup(x, y, aWidth, aHeight, 0);
}

void FButton::Setup(float pX, float pY, float pWidth, float pHeight)
{
    SetFrame(pX, pY, pWidth, pHeight);
}


void FButton::SetUpTopLeft(float pX, float pY, FView *pListener, bool pAutoSize)
{
    float aWidth = GetFrame().mWidth;
    float aHeight = GetFrame().mHeight;
    
    if(pAutoSize)
    {
        FSprite *aCheck = 0;
        
        for(int i=0;i<6;i++)
        {
            if(i == 0)aCheck = mSpriteUp;
            if(i == 1)aCheck = mSpriteOver;
            if(i == 2)aCheck = mSpriteDown;
            if(i == 3)aCheck = mSpriteOverlayUp;
            if(i == 4)aCheck = mSpriteOverlayOver;
            if(i == 5)aCheck = mSpriteOverlayDown;
            
            if(aCheck)
            {
                if(aCheck->mWidth > aWidth)aWidth = aCheck->mWidth;
                if(aCheck->mHeight > aHeight)aHeight = aCheck->mHeight;
            }
        }
    }
    
    Setup(pX, pY, aWidth, aHeight, pListener);
}

void FButton::SetUpCentered(float pX, float pY, FView *pListener, bool pAutoSize)
{
    float aWidth = GetFrame().mWidth;
    float aHeight = GetFrame().mHeight;
    
    
    if(pAutoSize)
    {
        
        FSprite *aCheck = 0;
        
        for(int i=0;i<6;i++)
        {
            if(i == 0)aCheck = mSpriteUp;
            if(i == 1)aCheck = mSpriteOver;
            if(i == 2)aCheck = mSpriteDown;
            if(i == 3)aCheck = mSpriteOverlayUp;
            if(i == 4)aCheck = mSpriteOverlayOver;
            if(i == 5)aCheck = mSpriteOverlayDown;
            
            if(aCheck)
            {
                if(aCheck->mWidth > aWidth)aWidth = aCheck->mWidth;
                if(aCheck->mHeight > aHeight)aHeight = aCheck->mHeight;
            }
        }
    }
    
    float aX = (pX - (aWidth / 2.0f));
    float aY = (pY - (aHeight / 2.0f));
    
    Setup(aX, aY, aWidth, aHeight, pListener);
    
}
 
*/

void FButton::AddOverlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown)
{
    FButtonLayer *aLayer = new FButtonLayer();
    aLayer->SetUp(pSpriteUp, pSpriteOver, pSpriteDown);
    mButtonLayersOver.Add(aLayer);
    
    if(mWidth < aLayer->mWidth)SetWidth(aLayer->mWidth);
    if(mHeight < aLayer->mHeight)SetHeight(aLayer->mHeight);
}

void FButton::AddUnderlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown)
{
    FButtonLayer *aLayer = new FButtonLayer();
    aLayer->SetUp(pSpriteUp, pSpriteOver, pSpriteDown);
    mButtonLayersUnder.Add(aLayer);
    
    if(mWidth < aLayer->mWidth)SetWidth(aLayer->mWidth);
    if(mHeight < aLayer->mHeight)SetHeight(aLayer->mHeight);
}

void FButton::SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown, float pX, float pY)
{
    if(mButtonLayer == 0)mButtonLayer = new FButtonLayer();
    mButtonLayer->SetUp(pSpriteUp, pSpriteOver, pSpriteDown);
    
    float aWidth = mWidth;
    float aHeight = mHeight;
    
    if(aWidth < mButtonLayer->mWidth)aWidth = mButtonLayer->mWidth;
    if(aHeight < mButtonLayer->mHeight)aHeight = mButtonLayer->mHeight;
    
    SetFrame(pX, pY, aWidth, aHeight);
    
    /*
    if(pSpriteUp)
    {
        if(pSpriteUp->DidLoad())
        {
            mSpriteUp = pSpriteUp;
        }
        else
        {
            mSpriteUp = 0;
        }
    }
    else mSpriteUp = 0;
    
    if(pSpriteOver)
    {
        if(pSpriteOver->DidLoad())
        {
            mSpriteOver = pSpriteOver;
        }
        else
        {
            mSpriteOver = 0;
        }
    }
    else mSpriteOver = 0;
    
    if(pSpriteDown)
    {
        if(pSpriteDown->DidLoad())
        {
            mSpriteDown = pSpriteDown;
        }
        else
        {
            mSpriteDown = 0;
        }
    }
    else mSpriteDown = 0;
    
    if(mSpriteDown == 0)
    {
        //mColorDown = FColor(0.85f, 0.85f, 0.85f);
        mColorDown = FColor(0.05f, 0.05f, 0.05f);
    }
    */
    
    //FSprite *aSprite = GetButtonImage();
    
    //if(aSprite)
    //{
    //    SetFrame(pX, pY, aSprite->mWidth, aSprite->mHeight);
    //}
}

void FButton::Update() {

}

void FButton::Draw() {
    bool aIsActive = true;
    bool aIsOver = mMouseOver;
    bool aIsDown = false;
    if (mTouchDownInside && mClickData != 0) {
        aIsDown = true;
    }

    EnumList(FButtonLayer, aLayer, mButtonLayersUnder) {
        aLayer->Draw(this, aIsActive, aIsOver, aIsDown);
    }
    if (mButtonLayer) {
        mButtonLayer->Draw(this, aIsActive, aIsOver, aIsDown);
    }
    EnumList(FButtonLayer, aLayer, mButtonLayersOver) {
        aLayer->Draw(this, aIsActive, aIsOver, aIsDown);
    }
    
    if ((mButtonLayersUnder.mCount == 0) && (mButtonLayersOver.mCount == 0)) {
        bool aDrawRect = mDrawRectIfSpriteIsNull;
        if (mButtonLayer) {
            if (mButtonLayer->mSpriteUp != 0) {
                aDrawRect = false;
            }
        }
        if (aDrawRect) {
            Graphics::SetColor(0.65f, 0.65f, 0.65f);
            if(mTouchDownInside)Graphics::SetColor(0.75f, 0.75f, 0.75f);

            Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
            Graphics::SetColor(mColor);
            Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 4.0f);
            Graphics::SetColor();
        }
    }
}

void FButton::TouchDown(float pX, float pY, void *pData) {

    if (mClickData == 0) {
        mClickData = pData;
    }

    gNotify.Post(this, "button_down");
    if (mTriggerOnDown) {
        gNotify.Post(this, "button_click");
    }
}

void FButton::TouchMove(float pX, float pY, void *pData) {
    if (pData == mClickData) {

    }
}

void FButton::TouchUp(float pX, float pY, void *pData) {
    if (mClickData == pData) {
        if (pX >= 0 && pY >= 0 && pX <= mWidth && pY <= mHeight) {
            if (mTriggerOnUp) {
                gNotify.Post(this, "button_click");
            }
            gNotify.Post(this, "button_up");
        }
        mClickData = 0;
    }
}

void FButton::TouchFlush() {
    mClickData = 0;
}


/*
FSprite *FButton::GetButtonImage()
{
    FSprite *aResult = 0;
    
    if(mTouchDownInside)
    {
        if(mSpriteDown)
        {
            aResult = mSpriteDown;
        }
        else
        {
            aResult = mSpriteOver;
        }
    }
    //else if(mIsOver)
    //{
    //    aResult = mSpriteOver;
    //}
    else
    {
        aResult = mSpriteUp;
    }
    
    if(aResult == 0)
    {
        if(mSpriteUp)aResult = mSpriteUp;
        else if(mSpriteOver)aResult = mSpriteOver;
        else if(mSpriteDown)aResult = mSpriteDown;
    }
    
    return aResult;
}

FSprite *FButton::GetOverlayImage()
{
    FSprite *aResult = 0;
    
    if(mTouchDownInside)
    {
        if(mSpriteOverlayDown)
        {
            aResult = mSpriteOverlayDown;
        }
        else
        {
            aResult = mSpriteOverlayOver;
        }
    }
    //else if(mIsOver)
    //{
    //    aResult = mSpriteOverlayOver;
    //}
    else
    {
        aResult = mSpriteOverlayUp;
    }
    
    if(aResult == 0)
    {
        if(mSpriteOverlayUp)aResult = mSpriteOverlayUp;
        else if(mSpriteOverlayOver)aResult = mSpriteOverlayOver;
        else if(mSpriteOverlayDown)aResult = mSpriteOverlayDown;
    }
    
    return aResult;
}
*/




FButtonLayer::FButtonLayer() {
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    
    mRotation = 0.0f;
    
    mScale = 1.0f;
    
    mSpriteUp = 0;
    mSpriteOver = 0;
    mSpriteDown = 0;
    
    mActive = true;
    
    mColorUp.mRed = 1.0f;
    mColorUp.mGreen = 1.0f;
    mColorUp.mBlue = 1.0f;
    mColorUp.mAlpha = 1.0f;
    
    mColorOver.mRed = 0.925f;
    mColorOver.mGreen = 0.925f;
    mColorOver.mBlue = 0.925f;
    mColorOver.mAlpha = 1.0f;
    
    mColorDown.mRed = 0.85f;
    mColorDown.mGreen = 0.85f;
    mColorDown.mBlue = 0.85f;
    mColorDown.mAlpha = 1.0f;
    
    mWidth = 0.0f;
    mHeight = 0.0f;
}

FButtonLayer::~FButtonLayer() {
    
}

void FButtonLayer::SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown) {
    mSpriteUp = pSpriteUp;
    mSpriteOver = pSpriteOver;
    mSpriteDown = pSpriteDown;
    mWidth = 0.0f;
    mHeight = 0.0f;
    if (pSpriteDown != 0) {
        mColorOver.mRed = 1.0f;
        mColorOver.mGreen = 1.0f;
        mColorOver.mBlue = 1.0f;
        mColorOver.mAlpha = 1.0f;
        mColorDown.mRed = 1.0f;
        mColorDown.mGreen = 1.0f;
        mColorDown.mBlue = 1.0f;
        mColorDown.mAlpha = 1.0f;
    }
    else if(mSpriteOver != 0)
    {
        mColorOver.mRed = 1.0f;
        mColorOver.mGreen = 1.0f;
        mColorOver.mBlue = 1.0f;
        mColorOver.mAlpha = 1.0f;
    }
    
    if(mSpriteUp != 0)
    {
        if(mSpriteUp->mWidth > mWidth)mWidth = mSpriteUp->mWidth;
        if(mSpriteUp->mHeight > mHeight)mHeight = mSpriteUp->mHeight;
    }
    
    if(mSpriteOver != 0)
    {
        if(mSpriteOver->mWidth > mWidth)mWidth = mSpriteOver->mWidth;
        if(mSpriteOver->mHeight > mHeight)mHeight = mSpriteOver->mHeight;
    }
    
    if(mSpriteDown != 0)
    {
        if(mSpriteDown->mWidth > mWidth)mWidth = mSpriteDown->mWidth;
        if(mSpriteDown->mHeight > mHeight)mHeight = mSpriteDown->mHeight;
    }
    
}

void FButtonLayer::Draw(FButton *pButton, bool pActive, bool pIsOver, bool pIsDown)
{
    FSprite *aSprite = 0;
    
    if((pActive == true) && (pButton != 0))
    {
        
        float aX = pButton->mWidth2;
        float aY = pButton->mHeight2;
        
        if(pIsDown)
        {
            Graphics::SetColor(mColorDown.mRed * pButton->mColor.mRed, mColorDown.mGreen * pButton->mColor.mGreen, mColorDown.mBlue * pButton->mColor.mBlue, mColorDown.mAlpha * pButton->mColor.mAlpha);
            aSprite = mSpriteDown;
        }
        else if(pIsOver)
        {
            Graphics::SetColor(mColorOver.mRed * pButton->mColor.mRed, mColorOver.mGreen * pButton->mColor.mGreen, mColorOver.mBlue * pButton->mColor.mBlue, mColorOver.mAlpha * pButton->mColor.mAlpha);
            
            //Graphics::SetColor(mColorOver);
            aSprite = mSpriteOver;
        }
        else
        {
            Graphics::SetColor(mColorUp.mRed * pButton->mColor.mRed, mColorUp.mGreen * pButton->mColor.mGreen, mColorUp.mBlue * pButton->mColor.mBlue, mColorUp.mAlpha * pButton->mColor.mAlpha);
            
            //Graphics::SetColor(mColorUp);
            
        }
        
        if(aSprite == 0)
        {
            aSprite = mSpriteUp;
        }
        
        //Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.85f);
        
        if(aSprite != 0)
        {
            aSprite->Draw(aX + mOffsetX, aY + mOffsetY, mScale, mRotation);
        }
        
        Graphics::SetColor();
    }
}



