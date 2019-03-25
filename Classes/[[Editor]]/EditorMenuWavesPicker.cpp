//
//  EditorMenuWavesPicker.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuWavesPicker.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuWavesPicker.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"


EditorMenuWavesPickerCell::EditorMenuWavesPickerCell() {
    
    mSelected = false;
    
    mCheckBackground.mCornerRadius = 3.0f;
    
    mCheckBackground.SetColorTop(0.165f, 0.65f, 0.165f);
    mCheckBackground.SetColorBottom(0.168f, 0.68f, 0.168f);
    
    mCheckOutline.mCornerRadius = 4.0f;
    mCheckOutline.SetColorTop(0.56f, 0.56f, 0.56f);
    mCheckOutline.SetColorBottom(0.52f, 0.52f, 0.52f);
    
    mNodeCount = 0;
}

EditorMenuWavesPickerCell::~EditorMenuWavesPickerCell() {
    
}

void EditorMenuWavesPickerCell::Layout() {
    UIButton::Layout();
    
    mCheckOutline.SetRect(mWidth2 - mWidth2 / 2.0f - 2.0f, mHeight2 - mHeight2 / 2.0f - 2.0f, mWidth2 + 4.0f, mHeight2 + 4.0f);
    mCheckBackground.SetRect(mWidth2 - mWidth2 / 2.0f, mHeight2 - mHeight2 / 2.0f, mWidth2, mHeight2);
    mCheckOutline.mRefresh = true;
    mCheckBackground.mRefresh = true;
    
    
}

void EditorMenuWavesPickerCell::Update() {
    UIButton::Update();
    
}

void EditorMenuWavesPickerCell::Draw() {
    UIButton::Draw();
    
    if (mSelected) {
        Graphics::PipelineStateSetShapeNodeAlphaBlending();
        mCheckOutline.Draw();
        mCheckBackground.Draw();
    } else {
        
    }
    
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    FString aText = FString(mNodeCount);
    gAppBase->mSysFont.Center(aText.c(), mWidth2, mHeight2, 0.5f);
    
}

void EditorMenuWavesPickerCell::SetSelected(bool pSelected) {
    if (pSelected != mSelected) {
        mSelected = pSelected;
        
        
        
    }
}


EditorMenuWavesPicker::EditorMenuWavesPicker(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuWavesPicker";
    
    mEditor = pEditor;
    
    SetTitle("Wave Chooser");
    SetScrollMode(false);
    mResizeDragAllowedH = true;
    mResizeDragAllowedV = false;
    
    mPickerSection = new ToolMenuSection();
    //mPickerSection->SetTransparentBackground();
    mPickerSection->SetHeight(176.0f);
    AddSection(mPickerSection);
    
}

EditorMenuWavesPicker::~EditorMenuWavesPicker() {
    if (gEditor->mMenuWavesPicker == this) {
        gEditor->mMenuWavesPicker = NULL;
    }
}

void EditorMenuWavesPicker::Layout() {
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
    
    aCellWidth = (aCellLayoutWidth -  2.0f * ((float)(aCountH + 1))) / ((float)aCountH);
    
    int aGridX = 0;
    float aX = aCellSpacingH + 4.0f;
    float aY = aCellSpacingV + 2.0f;
    for (int i=0;i<mCells.mCount;i++) {
        
        EditorMenuWavesPickerCell *aCell = (EditorMenuWavesPickerCell *)mCells.mData[i];
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


void EditorMenuWavesPicker::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) {
        return;
    }
    
    if (FString("slider_update") == pNotification) {
        
    }
    
    if (FString(pNotification) == "button_click") {
        
        for (int i=0;i<mCells.mCount;i++) {
            EditorMenuWavesPickerCell *aCell = (EditorMenuWavesPickerCell *)mCells.mData[i];
            if (pSender == aCell) {
                gEditor->WaveSelect(i);
            }
        }
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
    
    if (FString(pNotification) == "stepper") {
        UIStepper *aStepper = (UIStepper *)pSender;
    }
}

void EditorMenuWavesPicker::Update() {
    
    if (gEditor == NULL) { return; }
    
    int aWaveCount = gEditor->mSection.mWaveList.mCount;
    
    bool aNeedsLayout = false;
    
    while (mCells.mCount > aWaveCount) {
        EditorMenuWavesPickerCell *aCell = (EditorMenuWavesPickerCell *)mCells.PopLast();
        aCell->Deactivate();
        mCellQueue.Add(aCell);
        aNeedsLayout = true;
    }
    
    while (mCells.mCount < aWaveCount) {
        EditorMenuWavesPickerCell *aCell = (EditorMenuWavesPickerCell *)mCellQueue.PopLast();
        if (aCell == NULL) {
            aCell = new EditorMenuWavesPickerCell();
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
    
    int aSelectedIndex = gEditor->WaveIndex();
    for (int i=0;i<mCells.mCount;i++) {
        EditorMenuWavesPickerCell *aCell = (EditorMenuWavesPickerCell *)mCells.mData[i];
     
        if (aSelectedIndex == i) {
            aCell->SetSelected(true);
        } else {
            aCell->SetSelected(false);
        }
        
        aCell->mNodeCount = gEditor->WaveCount(i);
    }
}
