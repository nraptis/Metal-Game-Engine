//
//  EditorMenuPermPicker.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPermPicker.hpp"

//
//  EditorMenuPermPicker.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPermPicker.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuPermPicker.hpp"
#include "GamePermanentEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuPermPickerCell::EditorMenuPermPickerCell() {
    mSelected = false;
    
    mCheckBackground.mCornerRadius = 3.0f;
    
    mCheckBackground.SetColorTop(0.165f, 0.65f, 0.165f);
    mCheckBackground.SetColorBottom(0.168f, 0.68f, 0.168f);
    
    mCheckOutline.mCornerRadius = 4.0f;
    mCheckOutline.SetColorTop(0.56f, 0.56f, 0.56f);
    mCheckOutline.SetColorBottom(0.52f, 0.52f, 0.52f);
    
    mNodeCount = 0;
}

EditorMenuPermPickerCell::~EditorMenuPermPickerCell() {
    
}

void EditorMenuPermPickerCell::Layout() {
    UIButton::Layout();
    mCheckOutline.SetRect(mWidth2 - mWidth2 / 2.0f - 2.0f, mHeight2 - mHeight2 / 2.0f - 2.0f, mWidth2 + 4.0f, mHeight2 + 4.0f);
    mCheckBackground.SetRect(mWidth2 - mWidth2 / 2.0f, mHeight2 - mHeight2 / 2.0f, mWidth2, mHeight2);
    mCheckOutline.mRefresh = true;
    mCheckBackground.mRefresh = true;
}

void EditorMenuPermPickerCell::Update() {
    UIButton::Update();
}

void EditorMenuPermPickerCell::Draw() {
    UIButton::Draw();
    if (mSelected) {
        Graphics::PipelineStateSetShapeNodeAlphaBlending();
        mCheckOutline.Draw();
        mCheckBackground.Draw();
    }
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    FString aText = FString(mNodeCount);
    gAppBase->mSysFont.Center(aText.c(), mWidth2, mHeight2, 0.5f);
}

void EditorMenuPermPickerCell::SetSelected(bool pSelected) {
    if (pSelected != mSelected) {
        mSelected = pSelected;
    }
}

EditorMenuPermPicker::EditorMenuPermPicker(GamePermanentEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPermPicker";
    
    mEditor = pEditor;
    
    SetTitle("Perm Selector");
    SetScrollMode(false);
    mResizeDragAllowedH = true;
    mResizeDragAllowedV = false;
    
    mPickerSection = new ToolMenuSection();
    
    mPickerSection->StyleSetPicker();
    mPickerSection->SetHeight(92.0f);
    AddSection(mPickerSection);
}

EditorMenuPermPicker::~EditorMenuPermPicker() {
    if (mEditor != NULL ) {
        if (mEditor->mMenuPermPicker == this) {
            mEditor->mMenuPermPicker = NULL;
        }
    }
}

void EditorMenuPermPicker::Layout() {
    ToolMenu::Layout();
    
    float aTargetCellWidth = 40.0f;
    float aCellWidth = 40.0f;
    float aCellHeight = 40.0f;
    float aCellSpacingH = 2.0f;
    float aCellSpacingV = 2.0f;
    
    float aCellLayoutWidth = (mPickerSection->mWidth - 6.0);
    if (aCellLayoutWidth < 200.0f) { aCellLayoutWidth = 200.0f; }
    
    int aCountH = (int)(aCellLayoutWidth / aTargetCellWidth);
    if (aCountH < 3) {
        aCountH = 3;
    }
    
    float aX = aCellSpacingH + 4.0f;
    float aY = aCellSpacingV + 2.0f;
    
    aCellWidth = (aCellLayoutWidth -  2.0f * ((float)(aCountH + 1))) / ((float)aCountH);
    
    if (mCells.mCount <= aCountH) {
        if (mCells.mCount > 0) {
            float aButtonGroupWidth = aCellSpacingH;
            for (int i=0;i<mCells.mCount;i++) {
                aButtonGroupWidth += aCellWidth + aCellSpacingH;
            }
            aX += (aCellLayoutWidth / 2.0f) - (aButtonGroupWidth / 2.0f);
        }
    }
    
    int aGridX = 0;
    for (int i=0;i<mCells.mCount;i++) {
        EditorMenuPermPickerCell *aCell = (EditorMenuPermPickerCell *)mCells.mData[i];
        
        if (aY + aCellHeight > (mPickerSection->mHeight + 6.0f)) {
            aCell->Deactivate();
        } else {
            aCell->Activate();
        }
        
        aCell->SetFrame(aX, aY, aCellWidth, aCellHeight);
        aX += (aCellWidth + aCellSpacingH);
        aGridX += 1;
        if (aGridX >= aCountH) {
            aGridX = 0;
            aX = aCellSpacingH + 4.0f;
            aY += aCellHeight + aCellSpacingV;
        }
    }
}

void EditorMenuPermPicker::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    if (mEditor == NULL) { return; }
    
    if (FString(pNotification) == "button_click") {
        for (int i=0;i<mCells.mCount;i++) {
            EditorMenuPermPickerCell *aCell = (EditorMenuPermPickerCell *)mCells.mData[i];
            if (pSender == aCell) {
                mEditor->PermSelect(i);
                return;
            }
        }
    }
}

void EditorMenuPermPicker::Update() {
    
    if (gEditor == NULL) { return; }
    if (mEditor == NULL) { return; }
    
    
    int aCount = gEditor->mSection.mPermList.mCount;
    
    bool aNeedsLayout = false;
    while (mCells.mCount > aCount) {
        EditorMenuPermPickerCell *aCell = (EditorMenuPermPickerCell *)mCells.PopLast();
        aCell->Deactivate();
        mCellQueue.Add(aCell);
        aNeedsLayout = true;
    }
    
    while (mCells.mCount < aCount) {
        EditorMenuPermPickerCell *aCell = (EditorMenuPermPickerCell *)mCellQueue.PopLast();
        if (aCell == NULL) {
            aCell = new EditorMenuPermPickerCell();
            mPickerSection->AddChild(aCell);
            gNotify.Register(this, aCell, "button_click");
        }
        aCell->Activate();
        mCells.Add(aCell);
        aNeedsLayout = true;
    }
    
    if (aNeedsLayout == true) {
        Layout();
    }
    
    int aSelectedIndex = gEditor->PermIndex();
    for (int i=0;i<mCells.mCount;i++) {
        EditorMenuPermPickerCell *aCell = (EditorMenuPermPickerCell *)mCells.mData[i];
        
        if (aSelectedIndex == i) {
            aCell->SetSelected(true);
        } else {
            aCell->SetSelected(false);
        }
        
        aCell->mNodeCount = i;
    }
}
