//
//  UIStepper.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIStepper.hpp"


UIStepper::UIStepper() {
    mPreviousDrawMin = -1;
    mPreviousDrawMax = -1;

    mValue = 0.0f;
    mTargetValue = 0;

    mBarHeight = 10.0f;

    mLabelTitle.mScale = 0.75f;
    mLabelTitle.mAlignment = 1;

    mLabelValue.mScale = 0.75f;
    mLabelValue.mAlignment = -1;

    mLabelTitleWidth = 80.0f;
    mLabelValueWidth = 60.0f;


    mBaseSlider.SetFrame(0.0f, 0.0f, mWidth, mHeight);
    mBaseSlider.SetThumb(0.0f, 0.0f, 40.0f, mHeight);
    mBaseSlider.mDrawManual = true;
    AddChild(mBaseSlider);

    gNotify.Register(this, &mBaseSlider, "slider_update");

    FRect aRectBar = FRect(6.0f, mHeight / 2.0f - mBarHeight / 2.0f, mWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(0.0f, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);

    mRectBar.mCornerRadius = 5.0f;
    mRectBar.mCornerPointCount = 6;

    mRectBar.SetColorTop(0.12f, 0.14f, 0.19f);
    mRectBar.SetColorBottom(0.05f, 0.02f, 0.06f);
    mRectBar.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);

    mRectThumb.mCornerRadius = 16.0f;
    mRectThumb.mCornerPointCount = 18;

    mRectThumb.SetColorTop(0.6f, 0.63f, 0.66f, 0.45f);
    mRectThumb.SetColorBottom(0.54f, 0.55f, 0.60f, 0.45f);

    mRectThumb.SetRect(0.0f, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);

    mRectBarShine.Copy(&mRectBar);// SetRect(7.0f, mHeight / 2.0f - mBarHeightInner / 2.0f, mWidth - 14, mBarHeightInner);
    mRectBarShine.SetColorTop(1.0f, 1.0f, 1.0f, 0.35f);
    mRectBarShine.SetColorBottom(1.0f, 0.95f, 0.9f, 0.1f);


    mRectThumbShine.Copy(&mRectThumb);
    mRectThumbShine.SetColorTop(1.0f, 1.0f, 1.0f, 0.40f);
    mRectThumbShine.SetColorBottom(1.0f, 1.0f, 1.0f, 0.0f);
}

UIStepper::~UIStepper()
{

}

void UIStepper::Layout() {

    ToolMenuSectionRow::Layout();



    mLabelTitle.SetFrame(2.0f, 2.0f, mLabelTitleWidth, mHeight - 4.0f);
    mLabelValue.SetFrame(mWidth - (mLabelValueWidth + 2.0f), 2.0f, mLabelValueWidth, mHeight - 4.0f);

    float aSliderLeft = mLabelTitle.GetRight() + 2.0f;
    float aSliderRight = mLabelValue.GetLeft() - 2.0f;
    float aSliderWidth = (aSliderRight - aSliderLeft);


    mBaseSlider.SetFrame(aSliderLeft, 0.0f, aSliderWidth, mHeight);
    mBaseSlider.mThumbHeight = mHeight;


    FRect aRectBar = FRect(aSliderLeft + 6.0f, mHeight / 2.0f - mBarHeight / 2.0f, aSliderWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(aSliderLeft, 6.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight - 6.0f);

    mRectBar.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);
    mRectBarShine.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);

    mRectThumb.SetRect(aSliderLeft, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);
    mRectThumbShine.SetRect(aSliderLeft, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);

    mRectBar.mRefresh = true;
    mRectBarShine.mRefresh = true;
    mRectThumb.mRefresh = true;
    mRectThumbShine.mRefresh = true;

    mBaseSlider.SetValue(mValue);
}

void UIStepper::Draw()
{
    mRectBar.Draw();
    mRectBarShine.Draw();

    mRectThumb.Draw(mBaseSlider.mThumbX, 0.0f);
    mRectThumbShine.Draw(mBaseSlider.mThumbX, 0.0f);


    bool aUpdateText = false;

    if(mBaseSlider.mMin != mPreviousDrawMin)
    {
        mPreviousDrawMin = mBaseSlider.mMin;
        aUpdateText = true;
    }

    if(mBaseSlider.mMax != mPreviousDrawMax)
    {
        mPreviousDrawMax = mBaseSlider.mMax;
        aUpdateText = true;
    }


    if(aUpdateText || true)
    {
        int aDecimals = 1;

        float aRange = mBaseSlider.mMax - mBaseSlider.mMin;

        if(aRange <= 2.0f)
        {
            aDecimals = 2;

            if(aRange < 0.5f)
            {
                aDecimals = 4;
            }

        }

        mLabelValue.mText = FString(mBaseSlider.mValue, 3.0f);
        Graphics::SetColor();
    }
}

void UIStepper::SetValue(float *pTargetValue) {
    mTargetValue = pTargetValue;
    if (mTargetValue) {
        mBaseSlider.ForceValue(*mTargetValue);
        mValue = mBaseSlider.GetValue();
    } else {
        if ((mValue < mBaseSlider.mMin) || (mValue > mBaseSlider.mMax)) {
            mValue = mBaseSlider.mMin;
            mBaseSlider.ForceValue(mValue);
        }
    }
}

float UIStepper::GetValue() {
    return mBaseSlider.GetValue();
}

void UIStepper::Notify(void *pSender, const char *pNotification) {





    if (FString("slider_update") == pNotification) {

        if (pSender == &mBaseSlider) {

            mValue = mBaseSlider.mValue;
            if (mTargetValue) {
                *mTargetValue = mValue;
            }

            gNotify.Post(this, "slider_update");
        }
    }
}
