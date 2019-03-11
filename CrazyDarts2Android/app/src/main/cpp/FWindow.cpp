//
//  FWindow.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/14/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "FWindow.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"

FWindow::FWindow() {
    mRoot.mWindow = this;
    mRoot.mParent = 0;
    mRoot.mClipEnabled = false;
    mRoot.mClipDisabled = true;
    mRoot.mConsumesTouches = false;
    mRoot.mDeleteWhenKilled = false;
    
    
    mDeviceWidth = 800;
    mDeviceHeight = 600;
    
    mVirtualFrameX = 0;
    mVirtualFrameY = 0;
    mVirtualFrameWidth = 800;
    mVirtualFrameHeight = 600;
    
    mSafeAreaInsetTop = 0;
    mSafeAreaInsetRight = 0;
    mSafeAreaInsetBottom = 0;
    mSafeAreaInsetLeft = 0;
    
}

FWindow::~FWindow() {

}

void FWindow::AddChild(FCanvas *pCanvas) {
    mRoot.AddChild(pCanvas);
}

void FWindow::AddChild(FCanvas &pCanvas) {
    pCanvas.mDeleteWhenKilled = false;
    AddChild(&pCanvas);
}

void FWindow::PrintTempList(const char *pName) {
    Log("List[%s] => {", pName);
    for (int i=0;i<mTemp.mCount;i++) {
        FCanvas *aCanvas = ((FCanvas *)mTemp.mData[i]);
        Log("%s", aCanvas->mName.c());
        if (i < mTemp.mCount - 1) {
            Log(", ");
        }
    }
    Log("}\n\n");
}

void FWindow::Update() {
    //Assumption: When a canvas is killed, all the children
    //are also intended to be killed, and since we dump recursively,
    //we can remove child / parent relationships as we go along.
    if (!mKillBucket.IsEmpty()) {
        mTemp.RemoveAll();
        mKillBucket.AddCanvasesAndChildrenRecursivelyToListAndRemoveAll(&mTemp);

        EnumList(FCanvas, aCanvas, mTemp) {
            gNotify.Unregister(aCanvas);
        }

        EnumListReverse(FCanvas, aCanvas, mTemp) {
            mRealizeBucket.Remove(aCanvas);
            mLayoutBucket.Remove(aCanvas);
            mTransformUpdateBucket.Remove(aCanvas);
            EnumList(FCanvas, aChild, aCanvas->mChildren) {
                aChild->mParent = 0;
            }

            aCanvas->mWindow = 0;
            aCanvas->mChildren.RemoveAll();

            if (aCanvas->mParent) {
                aCanvas->mParent->mChildren.Remove(aCanvas);
                aCanvas->mParent = 0;
            }

            if (aCanvas->mDeleteWhenKilled == true) {
                delete aCanvas;
            }
        }
    }

    while (!(mRealizeBucket.IsEmpty() && mLayoutBucket.IsEmpty())) {
        if (!mRealizeBucket.IsEmpty()) {
            mTemp.RemoveAll();
            mRealizeBucket.AddCanvasesToList(&mTemp);
            EnumList(FCanvas, aCanvas, mTemp) { RegisterTransformDidUpdate(aCanvas); }

            //Now we need to layout all the canvases and their children...
            mTemp.RemoveAll();
            mRealizeBucket.AddCanvasesAndChildrenRecursivelyToListAndRemoveAll(&mTemp);

            //We can remove all of these canvases from layout-bucket,
            //and frame-update-bucket.
            EnumList(FCanvas, aCanvas, mTemp) {
                aCanvas->mWindow = this;
                mLayoutBucket.Remove(aCanvas);
            }
            EnumList(FCanvas, aCanvas, mTemp) {
                if (aCanvas->mKill) {
                    RegisterKill(aCanvas);
                } else {
                    aCanvas->BaseLayout();
                }
            }
        }

        //"Layout" everything from layout-bucket, and they all
        //need to update their transform...
        if (!mLayoutBucket.IsEmpty()) {
            mTemp.RemoveAll();
            mLayoutBucket.AddCanvasesToListAndRemoveAll(&mTemp);
            EnumList(FCanvas, aCanvas, mTemp) {
                RegisterTransformDidUpdate(aCanvas);
                aCanvas->BaseLayout();
            }
        }
    }

    if (!mTransformUpdateBucket.IsEmpty()) {
        mTemp.RemoveAll();
        mTransformUpdateBucket.AddCanvasesToListAndRemoveAll(&mTemp);
        EnumList(FCanvas, aCanvas, mTemp) {
            aCanvas->ComputeAbsoluteTransformation();
        }
    }

    mRoot.BaseUpdate();
}

void FWindow::Draw() {
    mRoot.BaseDraw();
}

bool FWindow::TouchDown(float pX, float pY, void *pData) {
    bool aConsumed = false;
    FCanvas *aCollider = mRoot.BaseTouchDown(pX, pY, pX, pY, pData, false, aConsumed);
    if (aCollider) {
        return aConsumed;
    }
    return false;
}

void FWindow::TouchMove(float pX, float pY, void *pData) {
    mRoot.BaseTouchMove(pX, pY, pX, pY, pData, false);
}

void FWindow::TouchUp(float pX, float pY, void *pData) {
    mRoot.BaseTouchUp(pX, pY, pX, pY, pData, false);
}

void FWindow::TouchFlush() {
    mRoot.BaseTouchFlush();
}

bool FWindow::MouseDown(float pX, float pY, int pButton) {
    bool aConsumed = false;
    FCanvas *aCollider = mRoot.BaseMouseDown(pX, pY, pX, pY, pButton, false, aConsumed);
    if (aCollider) {
        return aConsumed;
    }
    return false;
}

bool FWindow::MouseMove(float pX, float pY) {
    mRoot.BaseMouseMove(pX, pY, pX, pY, false);
    return false;
}

void FWindow::MouseUp(float pX, float pY, int pButton) {
    mRoot.BaseMouseUp(pX, pY, pX, pY, pButton, false);
}

void FWindow::MouseWheel(int pDirection) {
    mRoot.BaseMouseWheel(pDirection);
}

void FWindow::KeyDown(int pKey) {
    mRoot.BaseKeyDown(pKey);
}

void FWindow::KeyUp(int pKey) {
    mRoot.BaseKeyUp(pKey);
}

void FWindow::Active() {
    //mRoot.BaseActive();

}

void FWindow::Inactive() {

}

void FWindow::MemoryWarning(bool pSevere) {
    
}

void FWindow::SetDeviceSize(int pWidth, int pHeight) {
    mDeviceWidth = pWidth;
    mDeviceHeight = pHeight;
    RegisterTransformDidUpdate(&mRoot);
}

void FWindow::SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    if (mVirtualFrameX != pX || mVirtualFrameY != pY || mVirtualFrameWidth != pWidth || mVirtualFrameHeight != pHeight) {
        mVirtualFrameX = pX;
        mVirtualFrameY = pY;
        mVirtualFrameWidth = pWidth;
        mVirtualFrameHeight = pHeight;
        mRoot.SetFrame(pX, pY, pWidth, pHeight);
    }
}

void FWindow::SetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft) {
    if (mSafeAreaInsetTop != pInsetUp || mSafeAreaInsetRight != pInsetRight || mSafeAreaInsetBottom != pInsetDown || mSafeAreaInsetLeft != pInsetLeft) {
        
        //
        Log("FWindow::SetSafeAreaInsets(%d, %d, %d, %d)\n", pInsetUp, pInsetRight, pInsetDown, pInsetLeft);
        //
        
        mSafeAreaInsetTop = pInsetUp;
        mSafeAreaInsetRight = pInsetRight;
        mSafeAreaInsetBottom = pInsetDown;
        mSafeAreaInsetLeft = pInsetLeft;
        
        RegisterFrameDidUpdate(&mRoot);
    }
}

void FWindow::RegisterRealize(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    if (!mRealizeBucket.Exists(pCanvas)) {
        if (!mRealizeBucket.ParentExists(pCanvas)) {
            mRealizeBucket.RemoveAllChildren(pCanvas);
            mRealizeBucket.Add(pCanvas);
        }
    }
}

void FWindow::RegisterChildrenDidUpdate(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    mLayoutBucket.Add(pCanvas);
}

//Transform updates must be recursive through children.
void FWindow::RegisterTransformDidUpdate(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    if (!mTransformUpdateBucket.Exists(pCanvas)) {
        if (!mTransformUpdateBucket.ParentExists(pCanvas)) {
            mTransformUpdateBucket.RemoveAllChildren(pCanvas);
            mTransformUpdateBucket.Add(pCanvas);
        }
    }
}

void FWindow::RegisterFrameDidUpdate(FCanvas *pCanvas) {
    if (pCanvas == NULL) return;
    
    mLayoutBucket.Add(pCanvas);

    //The parent's child has updated its frame...
    FCanvas *aParent = pCanvas->mParent;
    if (aParent) {
        int aDepth = pCanvas->mLayoutBubbleUpDepth;
        while (aParent && aDepth > 0) {
            RegisterChildrenDidUpdate(aParent);
            aParent = aParent->mParent;
            aDepth--;
        }
    }
    
    //The children's parent has updated its frame..
    EnumList(FCanvas, aChild, pCanvas->mChildren) {
        mLayoutBucket.Add(aChild);
        //RegisterParentDidUpdate(aChild);
    }
    RegisterTransformDidUpdate(pCanvas);
}

void FWindow::RegisterKill(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    if (!mKillBucket.Exists(pCanvas)) {
        if (!mKillBucket.ParentExists(pCanvas)) {
            mKillBucket.RemoveAllChildren(pCanvas);
            mKillBucket.Add(pCanvas);
        }
    }
}

void FWindow::RegisterDealloc(FCanvas *pCanvas) {
    mRealizeBucket.Remove(pCanvas);
    mLayoutBucket.Remove(pCanvas);
    mTransformUpdateBucket.Remove(pCanvas);
    mKillBucket.Remove(pCanvas);
}
