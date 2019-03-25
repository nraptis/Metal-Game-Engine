//
//  PGMainCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGMainCanvas.hpp"
#include "FApp.hpp"
#include "ToolMenuModalUnderlay.hpp"
#include "UIImagePicker.hpp"
#include "PGPathEditor.hpp"

PGMainCanvas *gTool = 0;
PGMainCanvas::PGMainCanvas() {
    gTool = this;
    mName = "_Playground_";
    mClipEnabled = false;

    mImagePicker = 0;
    mPathEditor = 0;




    SetBackgroundDark();

    mMainToolbar = new PGMainToolbar();
    AddChild(mMainToolbar);
}

PGMainCanvas::~PGMainCanvas() {
    gTool = 0;
}

void PGMainCanvas::Layout() {
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mBackQuad.SetRect(0.0f, 0.0f, mWidth, mHeight);
}

void PGMainCanvas::Update() {
    
}

void PGMainCanvas::Draw() {
    mBackQuad.Draw();
}

void PGMainCanvas::TouchDown(float pX, float pY, void *pData) {
    if (pX <= 20 && pY >= (mHeight - 20)) {
        EnumList(FCanvas, aCanvas, mChildren) {
            if(gRand.Get(10) > 4) {
                aCanvas->Kill();
            }
        }
    }
}

void PGMainCanvas::TouchMove(float pX, float pY, void *pData) {

}

void PGMainCanvas::TouchUp(float pX, float pY, void *pData) {

}

void PGMainCanvas::TouchFlush() {

}

void PGMainCanvas::MouseDown(float pX, float pY, int pButton) {

}

void PGMainCanvas::MouseMove(float pX, float pY) {

}

void PGMainCanvas::MouseUp(float pX, float pY, int pButton) {

}

void PGMainCanvas::MouseWheel(int pDirection) {

}

void PGMainCanvas::KeyDown(int pKey) {

}

void PGMainCanvas::KeyUp(int pKey) {

}

void PGMainCanvas::Notify(void *pSender, const char *pNotification) {

    if (FString(pNotification) == "path_edit") {
        PGPathEditor *aPathEditor = (PGPathEditor *)pSender;

        if (aPathEditor == mPathEditor) {
            PopModal(mPathEditor);
        }




    }


}

bool PGMainCanvas::IsModal(FCanvas *pCanvas) {
    EnumList(FCanvas, aCanvas, mModalList) {
        if (aCanvas == pCanvas) {
            return true;
        }
    }
    return false;
}

void PGMainCanvas::PushModal(FCanvas *pCanvas) {
    if (pCanvas) {
        ToolMenuModalUnderlay *aUnderlay = new ToolMenuModalUnderlay();
        AddChild(aUnderlay);
        aUnderlay->Layout();
        aUnderlay->AddChild(pCanvas);
        mModalUnderlayList.Add(aUnderlay);
        mModalList.Add(pCanvas);
    }
    RefreshModalStack();
}

void PGMainCanvas::PopModal(FCanvas *pCanvas) {
    if (!pCanvas) return;

    int aIndex = mModalList.Find(pCanvas);
    if (aIndex != -1) {
        ToolMenuModalUnderlay *aUnderlay = (ToolMenuModalUnderlay *)mModalUnderlayList.Fetch(aIndex);
        FCanvas *aModal = (FCanvas *)mModalList.Fetch(aIndex);

        if (aModal == mImagePicker) {
            mImagePicker = 0;
            Log("NULLING IMAGE PICKR\n");
        }

        if (aModal == mPathEditor) {
            mPathEditor = 0;
            Log("NULLING PATH EDITOR\n");
        }

        mModalUnderlayList.RemoveAtIndex(aIndex);
        mModalList.RemoveAtIndex(aIndex);

        aUnderlay->Kill();
    }
    RefreshModalStack();
}

void PGMainCanvas::PopModal() {
    PopModal((FCanvas *)(mModalList.Last()));
}

void PGMainCanvas::RefreshModalStack() {

    for (int i=0;i<mModalList.mCount;i++) {
        ToolMenuModalUnderlay *aUnderlay = (ToolMenuModalUnderlay *)mModalUnderlayList.Fetch(i);
        FCanvas *aModal = (FCanvas *)mModalList.Fetch(i);
        if (i >= mModalList.mCount - 1) {
            aUnderlay->mEnabled = true;
            aUnderlay->mHidden = false;
            aModal->mEnabled = true;
            aModal->mHidden = false;
        } else {
            aUnderlay->mEnabled = false;
            aUnderlay->mHidden = true;
            aModal->mEnabled = false;
            aModal->mHidden = true;
        }
    }

    if (mModalList.mCount > 0) {
        mMainToolbar->mEnabled = false;
        mMainToolbar->mHidden = true;
    } else {
        mMainToolbar->mEnabled = true;
        mMainToolbar->mHidden = false;
    }
}

PGPathEditor *PGMainCanvas::ShowPathEditor(FCanvas *pObserver) {
    if (mPathEditor) {
        PopModal(mPathEditor);
        mImagePicker = 0;
    }
    mPathEditor = new PGPathEditor();
    gNotify.Register(pObserver, mPathEditor, "path_edit");
    PushModal(mPathEditor);
    return mPathEditor;
}

UIImagePicker *PGMainCanvas::ShowImagePicker(FCanvas *pObserver) {
    if (mImagePicker) {
        PopModal(mImagePicker);
        mImagePicker = 0;
    }
    mImagePicker = new UIImagePicker();
    mImagePicker->FillWithImages();
    gNotify.Register(pObserver, mImagePicker, "pick_image");
    PushModal(mImagePicker);
    return mImagePicker;
}

void PGMainCanvas::SetBackgroundDark() {
    mBackQuad.Corner2SetColor(0.06f, 0.02f, 0.03f);
    mBackQuad.Corner4SetColor(0.08f, 0.05f, 0.09f);
    mBackQuad.Corner3SetColor(0.07f, 0.06f, 0.06f);
    mBackQuad.Corner1SetColor(0.05f, 0.07f, 0.04f);
}

void PGMainCanvas::SetBackgroundGray() {
    mBackQuad.Corner1SetColor(0.48f, 0.45f, 0.49f);
    mBackQuad.Corner3SetColor(0.46f, 0.47f, 0.48f);
    mBackQuad.Corner4SetColor(0.47f, 0.46f, 0.46f);
    mBackQuad.Corner2SetColor(0.45f, 0.47f, 0.44f);
}

void PGMainCanvas::SetBackgroundLight() {
    mBackQuad.Corner1SetColor(0.96f, 0.92f, 0.88f);
    mBackQuad.Corner2SetColor(0.98f, 0.95f, 0.99f);
    mBackQuad.Corner3SetColor(0.97f, 0.96f, 0.96f);
    mBackQuad.Corner4SetColor(0.95f, 0.97f, 0.94f);
}
