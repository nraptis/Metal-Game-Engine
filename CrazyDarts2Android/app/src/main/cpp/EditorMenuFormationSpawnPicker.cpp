//
//  EditorMenuFormationSpawnPicker.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormationSpawnPicker.hpp"
#include "LightConfigurationScene.hpp"
#include "GameFormationEditor.hpp"
#include "FApp.hpp"


EditorMenuFormationSpawnPickerCell::EditorMenuFormationSpawnPickerCell() {
    mSelected = false;
    
    mCheckBackground.mCornerRadius = 3.0f;
    
    mCheckBackground.SetColorTop(0.165f, 0.65f, 0.165f);
    mCheckBackground.SetColorBottom(0.168f, 0.68f, 0.168f);
    
    mCheckOutline.mCornerRadius = 4.0f;
    mCheckOutline.SetColorTop(0.56f, 0.56f, 0.56f);
    mCheckOutline.SetColorBottom(0.52f, 0.52f, 0.52f);
    
    mSpawnIndex = 0;
}

EditorMenuFormationSpawnPickerCell::~EditorMenuFormationSpawnPickerCell() {
    
}

void EditorMenuFormationSpawnPickerCell::Layout() {
    UIButton::Layout();
    
    mCheckOutline.SetRect(mWidth2 - mWidth2 / 2.0f - 2.0f, mHeight2 - mHeight2 / 2.0f - 2.0f, mWidth2 + 4.0f, mHeight2 + 4.0f);
    mCheckBackground.SetRect(mWidth2 - mWidth2 / 2.0f, mHeight2 - mHeight2 / 2.0f, mWidth2, mHeight2);
    mCheckOutline.mRefresh = true;
    mCheckBackground.mRefresh = true;
}

void EditorMenuFormationSpawnPickerCell::Update() {
    UIButton::Update();
}

void EditorMenuFormationSpawnPickerCell::Draw() {
    UIButton::Draw();
    if (mSelected) {
        Graphics::PipelineStateSetShapeNodeAlphaBlending();
        mCheckOutline.Draw();
        mCheckBackground.Draw();
    }
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    FString aText = FString(mSpawnIndex);
    gAppBase->mSysFont.Center(aText.c(), mWidth2, mHeight2, 0.5f);
}

void EditorMenuFormationSpawnPickerCell::SetSelected(bool pSelected) {
    if (pSelected != mSelected) {
        mSelected = pSelected;
    }
}

EditorMenuFormationSpawnPicker::EditorMenuFormationSpawnPicker(GameFormationEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuFormationSpawnPicker";
    
    mEditor = pEditor;
    
    SetTitle("Spawn Selector");
    SetScrollMode(true);
    mResizeDragAllowedH = true;
    mResizeDragAllowedV = false;
    
    mTracerEnabled = false;
    
    
    mPanelObjectTypes = new ToolMenuPanel();
    mPanelObjectTypes->SetTitle("Object");
    AddSection(mPanelObjectTypes);
    
    mRowObjectTypes1 = new ToolMenuSectionRow();
    mPanelObjectTypes->AddSection(mRowObjectTypes1);
    
    mButtonPickBalloon = new UIButton();
    mButtonPickBalloon->SetText("Bloon");
    mRowObjectTypes1->AddButton(mButtonPickBalloon);
    
    mButtonPickBrickHead = new UIButton();
    mButtonPickBrickHead->SetText("Brick");
    mRowObjectTypes1->AddButton(mButtonPickBrickHead);
    
    
    mRowObjectTypes2 = new ToolMenuSectionRow();
    mPanelObjectTypes->AddSection(mRowObjectTypes2);
    
    
    mButtonPickBomb = new UIButton();
    mButtonPickBomb->SetText("Bomb");
    mRowObjectTypes2->AddButton(mButtonPickBomb);
    
    mButtonPickTurtle = new UIButton();
    mButtonPickTurtle->SetText("Turtle");
    mRowObjectTypes2->AddButton(mButtonPickTurtle);
    
    
    
    //mRowObjectTypes2 = new ToolMenuSectionRow();
    //mPanelObjectTypes->AddSection(mRowObjectTypes2);
    
    
    
    mPickerSection = new ToolMenuSection();
    mPickerSection->StyleSetPicker();
    //mPickerSection->SetHeight(174.0f);
    mPickerSection->SetHeight(92.0f);
    AddSection(mPickerSection);
    
    
    
    DeactivateCloseButton();
}

EditorMenuFormationSpawnPicker::~EditorMenuFormationSpawnPicker() {
    
    
}

void EditorMenuFormationSpawnPicker::Layout() {
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
        EditorMenuFormationSpawnPickerCell *aCell = (EditorMenuFormationSpawnPickerCell *)mCells.mData[i];
        aCell->SetFrame(aX, aY, aCellWidth, aCellHeight);
        
        if (aY + aCellHeight > (mPickerSection->mHeight + 6.0f)) {
            aCell->Deactivate();
        } else {
            aCell->Activate();
        }
        
        aX += (aCellWidth + aCellSpacingH);
        aGridX += 1;
        if (aGridX >= aCountH) {
            aGridX = 0;
            aX = aCellSpacingH + 4.0f;
            aY += aCellHeight + aCellSpacingV;
        }
    }
}

void EditorMenuFormationSpawnPicker::Notify(void *pSender, const char *pNotification) {
    
    if (mEditor == NULL) { return; }
    
    if (FString("slider_update") == pNotification) {
        
    }
    
    if (FString(pNotification) == "button_click") {
        for (int i=0;i<mCells.mCount;i++) {
            EditorMenuFormationSpawnPickerCell *aCell = (EditorMenuFormationSpawnPickerCell *)mCells.mData[i];
            if (pSender == aCell) {
                mEditor->SpawnSelect(i);
                return;
            }
        }
        
    }
    
    if (pSender == mButtonPickBalloon)   { mEditor->SpawnPickBalloon(); }
    if (pSender == mButtonPickBrickHead) { mEditor->SpawnPickBrickHead(); }
    if (pSender == mButtonPickBomb) { mEditor->SpawnPickBomb(); }
    if (pSender == mButtonPickTurtle) { mEditor->SpawnPickTurtle(); }
    
}

void EditorMenuFormationSpawnPicker::Update() {
    
    
    if (mEditor == NULL) { return; }
    
    bool aTracerEnabled = mEditor->mTracerEnabled;
    
    int aSpawnCount = 0;//gEditor->mSection.mWaveList.mCount;
    
    LevelWaveBlueprint *aWave = NULL;

    if (aTracerEnabled) {
        LevelFormationTracerBlueprint *aTracer = mEditor->TracerGet();
        if (aTracer != NULL) {
            aSpawnCount = aTracer->mSpawnNodeList.mCount;
        }
    } else {
        aSpawnCount = mEditor->mFormation.mNodeList.mCount;
    }
    
    bool aNeedsLayout = false;
    if (aTracerEnabled != mTracerEnabled) {
        aNeedsLayout = true;
    }
    
    while (mCells.mCount > aSpawnCount) {
        EditorMenuFormationSpawnPickerCell *aCell = (EditorMenuFormationSpawnPickerCell *)mCells.PopLast();
        aCell->Deactivate();
        mCellQueue.Add(aCell);
        aNeedsLayout = true;
    }
    
    while (mCells.mCount < aSpawnCount) {
        EditorMenuFormationSpawnPickerCell *aCell = (EditorMenuFormationSpawnPickerCell *)mCellQueue.PopLast();
        if (aCell == NULL) {
            aCell = new EditorMenuFormationSpawnPickerCell();
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
    
    int aSelectedIndex = mEditor->SpawnIndex();
    for (int i=0;i<mCells.mCount;i++) {
        EditorMenuFormationSpawnPickerCell *aCell = (EditorMenuFormationSpawnPickerCell *)mCells.mData[i];
        if (aSelectedIndex == i) {
            aCell->SetSelected(true);
        } else {
            aCell->SetSelected(false);
        }
        aCell->mSpawnIndex = i;
    }
    
    
    mTracerEnabled = aTracerEnabled;
}
