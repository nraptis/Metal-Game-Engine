//
//  EditorMenuPermSpawnPicker.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/22/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuPermSpawnPicker.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuPermSpawnPicker.hpp"
#include "GamePermanentEditor.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuPermSpawnPickerCell::EditorMenuPermSpawnPickerCell() {
    mSelected = false;
    
    mCheckBackground.mCornerRadius = 3.0f;
    
    mCheckBackground.SetColorTop(0.165f, 0.65f, 0.165f);
    mCheckBackground.SetColorBottom(0.168f, 0.68f, 0.168f);
    
    mCheckOutline.mCornerRadius = 4.0f;
    mCheckOutline.SetColorTop(0.56f, 0.56f, 0.56f);
    mCheckOutline.SetColorBottom(0.52f, 0.52f, 0.52f);
    
    mNodeCount = 0;
}

EditorMenuPermSpawnPickerCell::~EditorMenuPermSpawnPickerCell() {
    
}

void EditorMenuPermSpawnPickerCell::Layout() {
    UIButton::Layout();
    mCheckOutline.SetRect(mWidth2 - mWidth2 / 2.0f - 2.0f, mHeight2 - mHeight2 / 2.0f - 2.0f, mWidth2 + 4.0f, mHeight2 + 4.0f);
    mCheckBackground.SetRect(mWidth2 - mWidth2 / 2.0f, mHeight2 - mHeight2 / 2.0f, mWidth2, mHeight2);
    mCheckOutline.mRefresh = true;
    mCheckBackground.mRefresh = true;
}

void EditorMenuPermSpawnPickerCell::Update() {
    UIButton::Update();
}

void EditorMenuPermSpawnPickerCell::Draw() {
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

void EditorMenuPermSpawnPickerCell::SetSelected(bool pSelected) {
    if (pSelected != mSelected) {
        mSelected = pSelected;
    }
}

EditorMenuPermSpawnPicker::EditorMenuPermSpawnPicker(GamePermanentEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuPermSpawnPicker";
    
    mEditor = pEditor;
    
    SetTitle("Spawn Selector");
    SetScrollMode(false);
    mResizeDragAllowedH = true;
    mResizeDragAllowedV = false;
    
    mPickerSection = new ToolMenuSection();
    
    mPickerSection->StyleSetPicker();
    mPickerSection->SetHeight(92.0f);
    AddSection(mPickerSection);
}

EditorMenuPermSpawnPicker::~EditorMenuPermSpawnPicker() {
    if (mEditor != NULL ) {
        if (mEditor->mMenuSpawnPicker == this) {
            mEditor->mMenuSpawnPicker = NULL;
        }
    }
}

void EditorMenuPermSpawnPicker::Layout() {
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
        EditorMenuPermSpawnPickerCell *aCell = (EditorMenuPermSpawnPickerCell *)mCells.mData[i];
        
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

void EditorMenuPermSpawnPicker::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    if (mEditor == NULL) { return; }
    
    if (FString(pNotification) == "button_click") {
        for (int i=0;i<mCells.mCount;i++) {
            EditorMenuPermSpawnPickerCell *aCell = (EditorMenuPermSpawnPickerCell *)mCells.mData[i];
            if (pSender == aCell) {
                mEditor->PermSpawnSelect(i);
                return;
            }
        }
    }
}

void EditorMenuPermSpawnPicker::Update() {
    
    if (gEditor == NULL) { return; }
    if (mEditor == NULL) { return; }
    
    
    LevelSectionPermBlueprint *aPerm = mEditor->GetPerm();
   
    int aCount = 0;
    
    if (aPerm != NULL) {
        if (aPerm->IsPathPerm()) {
            aCount = aPerm->mSpawnCount;
        }
    }
    
    bool aNeedsLayout = false;
    while (mCells.mCount > aCount) {
        EditorMenuPermSpawnPickerCell *aCell = (EditorMenuPermSpawnPickerCell *)mCells.PopLast();
        aCell->Deactivate();
        mCellQueue.Add(aCell);
        aNeedsLayout = true;
    }
    
    while (mCells.mCount < aCount) {
        EditorMenuPermSpawnPickerCell *aCell = (EditorMenuPermSpawnPickerCell *)mCellQueue.PopLast();
        if (aCell == NULL) {
            aCell = new EditorMenuPermSpawnPickerCell();
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
    
    int aSelectedIndex = mEditor->PermSpawnIndex();
    for (int i=0;i<mCells.mCount;i++) {
        EditorMenuPermSpawnPickerCell *aCell = (EditorMenuPermSpawnPickerCell *)mCells.mData[i];
        
        if (aSelectedIndex == i) {
            aCell->SetSelected(true);
        } else {
            aCell->SetSelected(false);
        }
        
        aCell->mNodeCount = gEditor->WaveCount(i);
    }
}
