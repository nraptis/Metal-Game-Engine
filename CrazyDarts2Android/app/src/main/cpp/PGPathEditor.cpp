//
//  PGPathEditor.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PGPathEditor.hpp"
#include "PathEditorMenu.hpp"
#include "UIImagePicker.hpp"
#include "PGMainCanvas.hpp"

PGPathEditor::PGPathEditor() {
    mName = "path_editor";

    mSprite = 0;

    mOutputAlignment.mX = -1;
    mOutputAlignment.mY = 1;

    mOutputNormalize = false;


    mEditorMenu = new PathEditorMenu(this);
    mEditorMenu->mPathEditor = this;
    AddChild(mEditorMenu);
}

PGPathEditor::~PGPathEditor() {

}

void PGPathEditor::Layout() {
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);

}

void PGPathEditor::Update() {

}

void PGPathEditor::Draw() {

    //Graphics::SetColor(0.66f, 0.25f, 0.45f, 1.0f);
    //mPointList.DrawEdges(6.0f);

    Graphics::SetColor();
    if (mSprite) {
        mSprite->Center(mWidth2, mHeight2);
    }


    Graphics::SetColor(0.125f, 0.125f, 0.125f, 0.65f);
    mPointList.DrawPoints(9.0f);

    Graphics::SetColor(0.95f, 0.95f, 0.0f, 1.0f);
    mPointList.DrawPoints(6.0f);

    Graphics::SetColor();
}

void PGPathEditor::TouchDown(float pX, float pY, void *pData) {
    if (pX <= 20 && pY >= (mHeight - 20)) {
        EnumList(FCanvas, aCanvas, mChildren) {
            if(gRand.Get(10) > 4) {
                aCanvas->Kill();
            }
        }
    }

    mPointList.Add(pX, pY);

    /*
    if (mSprite) {
        float aStartX = mWidth2 - mSprite->mWidth / 2.0f;
        float aStartY = mHeight2 - mSprite->mHeight / 2.0f;

        for (int i=0;i<mPointList.mCount;i++) {
            float aX = mPointList.GetX(i);
            float aY = mPointList.GetY(i);

            aX -= aStartX;
            aY -= aStartY;

            aX /= mSprite->mWidth;
            aY /= mSprite->mHeight;

            printf("CGPointMake(x: %.6f, y: %.6f)\n", aX, aY);
        }
    }
    */
    
}

void PGPathEditor::TouchMove(float pX, float pY, void *pData) {

}

void PGPathEditor::TouchUp(float pX, float pY, void *pData) {

}

void PGPathEditor::TouchFlush() {

}

void PGPathEditor::KeyDown(int pKey) {

}

void PGPathEditor::KeyUp(int pKey) {

}

void PGPathEditor::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "pick_image") {
        UIImagePicker *aImagePicker = (UIImagePicker *)pSender;
        mSprite = aImagePicker->mSelectedSprite;
        if (gTool) gTool->PopModal(aImagePicker);
    }
}
