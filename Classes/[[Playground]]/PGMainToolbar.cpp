//
//  PGMainToolbar.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGMainToolbar.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"
#include "UIImagePicker.hpp"
#include "PGPathEditor.hpp"
#include "UIAlignmentPicker.hpp"

PGMainToolbar::PGMainToolbar() {
    mName = "PGMainToolbar";
    mClipEnabled = false;
    mClipDisabled = true;
    mExpanded = true;
    mResizeDragAllowedV = false;
    

    mExpandedWidth = 0.0f;

    mContent.mConsumesTouches = false;

    mToolbarBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mToolbarBackground.SetColorBottom(0.165f, 0.135f, 0.085f);
    mToolbarBackground.mCornerRadius = 8.0f;

    mToolbarBackgroundOutline.SetColorTop(0.925f, 0.925f, 0.925f);
    mToolbarBackgroundOutline.SetColorBottom(0.965f, 0.965f, 0.965f);
    mToolbarBackgroundOutline.mCornerRadius = 8.0f;

    mToolbarBackgroundShadow.SetColorTop(0.021f, 0.021f, 0.021f, 0.25f);
    mToolbarBackgroundShadow.SetColorBottom(0.025f, 0.025f, 0.025f, 0.25f);
    mToolbarBackgroundShadow.mCornerRadius = 8.0f;

    AddChild(mContent);

    AddRow(&mMainRow);
    AddRow(&mRow1);
    AddRow(&mRow2);

    float aRowHeight = ToolMenuSectionRow::RowHeight();
    mButtonMinimize.SetFrame(2.0f, 2.0f, aRowHeight * 1.5f - 4.0f, aRowHeight);
    mButtonMinimize.mDrawMinimize = true;
    mButtonMinimize.mButtonBackground.SetColorTop(0.231f, 0.373f, 0.7847059f);
    mButtonMinimize.mButtonBackground.SetColorBottom(0.2157f, 0.353f, 0.7647059f);

    mButtonMinimize.mButtonBackgroundDown.SetColorTop(0.231f * 0.82f, 0.373f * 0.82f, 0.7847059f * 0.82f);
    mButtonMinimize.mButtonBackgroundDown.SetColorBottom(0.2157f * 0.82f, 0.353f * 0.82f, 0.7647059f * 0.82f);
    AddChild(mButtonMinimize);
    gNotify.Register(this, &mButtonMinimize, "button_click");

    mSegmentBackground = new UISegment();
    mSegmentBackground->SetSegmentCount(3);
    mSegmentBackground->SetTitles("Dark", "Gray", "Light");
    gNotify.Register(this, mSegmentBackground, "segment");
    mSegmentBackground->SetWidth(160.0f);
    mSegmentBackground->SetY(4.0f);
    AddChild(mSegmentBackground);

    mSizeMinWidth = 500.0f;
    mSizeMinHeight = aRowHeight + 4.0f;

    SetX(70.0f);
    SetY(110.0f);
    SetWidth(mSizeMinWidth + 260.0f);

    mLabelTitle = new UILabel();
    mLabelTitle->SetText("Main Toolbar");
    mLabelTitle->SetTransparentBackground();
    mMainRow.AddLabel(mLabelTitle);

    mButtonPathEditor = new UIButton();
    mButtonPathEditor->SetText("Path Editor");
    mMainRow.AddButton(mButtonPathEditor);
    gNotify.Register(this, mButtonPathEditor, "button_click");

    UIAlignmentPicker *aAlignment = new UIAlignmentPicker();
    mMainRow.AddAlignmentPicker(aAlignment);

    mButtonNodeEditor = new UIButton();
    mButtonNodeEditor->SetText("Node Editor");
    mMainRow.AddButton(mButtonNodeEditor);


    mButtonQuadEditor = new UIButton();
    mButtonQuadEditor->SetText("Quad Editor");
    mRow1.AddButton(mButtonQuadEditor);

    mButtonSceneEditor = new UIButton();
    mButtonSceneEditor->SetText("Scene Editor");
    mRow1.AddButton(mButtonSceneEditor);


    mLabel1 = new UILabel();
    mLabel1->SetText("Here are some buttons");
    mRow2.AddLabel(mLabel1);


    mLabel2 = new UILabel();
    mLabel2->SetText("Small");
    mRow2.AddLabel(mLabel2);

    mLabel3 = new UILabel();
    mLabel3->SetText("Loooooooonger");
    mRow1.AddLabel(mLabel3);


    mCheck1 = new UICheckBox();
    mCheck1->SetText("Toggle SOmething");
    mRow2.AddCheckBox(mCheck1);

    mCheck2 = new UICheckBox();
    mCheck2->SetText("Toggle");
    mRow2.AddCheckBox(mCheck2);




}

PGMainToolbar::~PGMainToolbar() {

}

void PGMainToolbar::Layout() {

    float aContentWidth = mWidth - 4.0f;
    float aContentHeight = 0.0f;
    int aRowIndex = 0;
    float aInset = 2.0f;
    float aRowHeight = ToolMenuSectionRow::RowHeight();

    mSegmentBackground->SetX(GetWidth() - aInset * 2.0f - (mSegmentBackground->GetWidth()));

    EnumList(ToolMenuSectionRow, aRow, mRowList) {
        if (aRowIndex == 0) {
            float aTopContentWidth = aContentWidth - (mButtonMinimize.GetRight() + aInset * 3.0f + mSegmentBackground->GetWidth());
            aRow->SetFrame(mButtonMinimize.GetRight() + aInset, aInset, aTopContentWidth, aRowHeight);
        } else {
            aRow->SetFrame(aInset, aContentHeight + aInset, aContentWidth - (aInset * 2.0f), aRowHeight);
        }
        aContentHeight += aRow->mHeight + 2.0f;
        aRowIndex++;
    }
    mContent.SetFrame(2.0f, 2.0f, aContentWidth, mHeight - 4.0f);
    mToolbarBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mToolbarBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mToolbarBackgroundShadow.SetRect(-2.0f, -2.0f, mWidth + 4.0f, mHeight + 4.0f);
    mToolbarBackground.mRefresh = true;
    mToolbarBackgroundOutline.mRefresh = true;
    mToolbarBackgroundShadow.mRefresh = true;

    if (mExpanded) {
        SetHeight(aContentHeight + 4.0f);
    } else {

        SetHeight(aRowHeight + 4.0f);
    }
}

void PGMainToolbar::Update() {

}

void PGMainToolbar::Draw() {
    mToolbarBackgroundShadow.Draw();
    mToolbarBackgroundOutline.Draw();
    mToolbarBackground.Draw();
}

void PGMainToolbar::TouchDown(float pX, float pY, void *pData) {
    if (mParent) {
        mParent->BringChildToFront(this);
    }
}

void PGMainToolbar::TouchMove(float pX, float pY, void *pData) {

}

void PGMainToolbar::TouchUp(float pX, float pY, void *pData) {

}

void PGMainToolbar::TouchFlush() {

}

void PGMainToolbar::Notify(void *pSender, const char *pNotification) {

    if (FString(pNotification) == "button_click") {
        if (pSender == &mButtonMinimize) {
            if (mExpanded) {
                Collapse();
            } else {
                Expand();
            }
        }

        if (pSender == mButtonPathEditor) {
            if (gTool) gTool->ShowPathEditor(0);

            //PGPathEditor *aEditor = new PGPathEditor();
            //gTool->AddChild(aEditor);
        }
        
        if (pSender == mButtonNodeEditor) {
            
        }
    }

    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;

        if (aSegment == mSegmentBackground) {
            if (aSegment->mSelectedIndex == 0) {
                gTool->SetBackgroundDark();
            }
            if (aSegment->mSelectedIndex == 1) {
                gTool->SetBackgroundGray();
            }
            if (aSegment->mSelectedIndex == 2) {
                gTool->SetBackgroundLight();
            }
        }


    }
}

void PGMainToolbar::AddRow(ToolMenuSectionRow *pRow) {
    mRowList.Add(pRow);
    mContent.AddChild(pRow);
}

void PGMainToolbar::Expand() {
    mExpanded = true;
    mResizeDragAllowed = true;
    float aContentHeight = 0.0f;
    EnumList(ToolMenuSectionRow, aRow, mRowList) {
        aContentHeight += aRow->mHeight + 2.0f;
    }
    mContent.mEnabled = true;
    mContent.mHidden = false;
    mSegmentBackground->mEnabled = true;
    mSegmentBackground->mHidden = false;
    SetExpandedLayout();
    SetHeight(aContentHeight + 4.0f);
    SetWidth(mExpandedWidth);
}

void PGMainToolbar::Collapse() {
    mExpandedWidth = mWidth;
    mExpanded = false;
    mResizeDragAllowed = false;
    mContent.mEnabled = false;
    mContent.mHidden = true;
    mSegmentBackground->mEnabled = false;
    mSegmentBackground->mHidden = true;

    float aRowHeight = ToolMenuSectionRow::RowHeight();
    SetHeight(aRowHeight + 4.0f);
    SetWidth(260.0f);
    SetCollapsedLayout();
}

void PGMainToolbar::SetExpandedLayout() {
    mButtonMinimize.mDrawMaximize = false;
    mButtonMinimize.mDrawMinimize = true;
}

void PGMainToolbar::SetCollapsedLayout() {
    mButtonMinimize.mDrawMaximize = true;
    mButtonMinimize.mDrawMinimize = false;
}






