//
//  ToolMenuModalUnderlay.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuModalUnderlay.hpp"
#include "FApp.hpp"

ToolMenuModalUnderlay::ToolMenuModalUnderlay() {
    mConsumesTouches = false;
    mClipDisabled = false;

    mName = "ToolMenuModalUnderlay";

    /*
    mB1.SetFrame(-10.0f, -10.0f, 120.0f, 66.0f);
    AddChild(mB1);

    mB2.SetFrame(40.0f, 100.0f, 660.0f, 100.0f);
    AddChild(mB2);

    mB3.SetFrame(170.0f, 260.0f, 180.0f, 100.0f);
    AddChild(mB3);

    mB4.SetFrame(170, 330.0f, 260.0f, 680.0f);
    AddChild(mB4);
    */

}

ToolMenuModalUnderlay::~ToolMenuModalUnderlay() {
    Log("Free(ToolMenuModalUnderlay)\n");
}

void ToolMenuModalUnderlay::Layout() {
    if (mParent) {
        SetFrame(0.0f, 0.0f, mParent->mWidth, mParent->mHeight);
    }
}

void ToolMenuModalUnderlay::Update() {

}

void ToolMenuModalUnderlay::Draw() {
    if (gRand.Get(10) == 5) {
        Graphics::SetColor(1.0f, 0.25f, 0.5f, 0.4f);
        Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 40);
        Graphics::SetColor();
    }
}
