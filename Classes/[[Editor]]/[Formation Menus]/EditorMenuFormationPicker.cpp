//
//  EditorMenuFormationPicker.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/30/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuFormationPicker.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuFormationPicker.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"
#include "EditorMenuFormationPickerCell.hpp"
#include "FormationCollection.hpp"
#include "core_includes.h"


LevelFormation *gSelectedFormation = NULL;

EditorMenuFormationPicker::EditorMenuFormationPicker() {
    
    mName = "Formation Picker";
    
    float aX = gDeviceWidth2 / 3.0f;
    float aY = gDeviceHeight2 / 3.0f;
    float aWidth = gDeviceWidth2 + gDeviceWidth2 / 2.0f;
    float aHeight = gDeviceHeight2 + gDeviceHeight2 / 2.0f;
    if (aWidth > 768.0f) {
        aWidth = 768.0f;
    }
    if (aHeight > 640.0f) {
        aHeight = 640.0f;
    }
    
    SetFrame(aX, aY, aWidth, aHeight);
    
    mSelectedSprite = 0;
    mSelectedSpriteSequence = 0;
    
    SetTitle("Formation Picker");
    SetScrollMode(false);
    
    mManualSectionLayout = true;
    mResizeDragAllowedV = false;
    
    
    mFilterRow1 = new ToolMenuSectionRow();
    AddSection(mFilterRow1);
    
    mButtonApplyFilter = new UIButton();
    mButtonApplyFilter->SetText("Apply...");
    mFilterRow1->AddButton(mButtonApplyFilter);
    
    mTextBoxFilter = new UITextBox();
    mFilterRow1->AddTextBox(mTextBoxFilter);
    
    
    mFilterRow2 = new ToolMenuSectionRow();
    AddSection(mFilterRow2);
    
    
    mCheckBoxBalloonsOnly = new UICheckBox();
    mCheckBoxBalloonsOnly->SetText("Bal Only");
    mFilterRow2->AddCheckBox(mCheckBoxBalloonsOnly);
    
    mCheckBoxMixedOnly = new UICheckBox();
    mCheckBoxMixedOnly->SetText("Mixed Only");
    mFilterRow2->AddCheckBox(mCheckBoxMixedOnly);
    
    mCheckBoxTracersOnly = new UICheckBox();
    mCheckBoxTracersOnly->SetText("Only Tracers");
    mFilterRow2->AddCheckBox(mCheckBoxTracersOnly);
    
    mCheckBoxNoTracersOnly = new UICheckBox();
    mCheckBoxNoTracersOnly->SetText("Ignore Tracers");
    mFilterRow2->AddCheckBox(mCheckBoxNoTracersOnly);
    
    
    
    mSection = new ToolMenuSection();
    AddSection(mSection);
    
    
    mDidSetUp = false;
    mScrollContent = new EditorMenuFormationPickerScrollContent();
    mSection->AddChild(mScrollContent);
    
    AddAllFormations();
}

EditorMenuFormationPicker::~EditorMenuFormationPicker() {
    
    FreeList(LevelFormation, mFormationListFiltered);
    FreeList(LevelFormation, mFormationList);
    
    gSelectedFormation = NULL;
}

void EditorMenuFormationPicker::Update() {
    if (mDidSetUp == false) {
        if (mScrollContent) {
            mScrollContent->SetUp();
            mDidSetUp = true;
        }
    }
}

void EditorMenuFormationPicker::Draw() {
    ToolMenu::Draw();
}

void EditorMenuFormationPicker::Notify(void *pSender, const char *pNotification) {
    if (mScrollContent != NULL) {
        EnumList(EditorMenuFormationPickerCell, aCell, mScrollContent->mCellList) {
            if (aCell == pSender && aCell->mTouchCanceled == false) {
                gSelectedFormation = aCell->mFormation;
                gNotify.Post(this, "formation_selected");
                Kill();
                return;
            }
        }
    }
    
    if (pSender == mButtonApplyFilter) { ApplyFilter(); }
    if (pSender == mCheckBoxBalloonsOnly) { ApplyFilter(); }
    if (pSender == mCheckBoxMixedOnly) { ApplyFilter(); }
    if (pSender == mCheckBoxTracersOnly) { ApplyFilter(); }
    if (pSender == mCheckBoxNoTracersOnly) { ApplyFilter(); }
    
}

void EditorMenuFormationPicker::AddAllFormations() {
    EnumList(LevelFormation, aFormation, gFormationCollection.mFormationList) {
        
        LevelFormation *aClone = aFormation->Clone();
        
        AddFormation(aClone);
    }
    
    ApplyFilter();
    
}

void EditorMenuFormationPicker::AddFormation(LevelFormation *pFormation) {
    
    if (pFormation == NULL) { return; }
    
    mFormationList.Add(pFormation);
    
    /*
    EditorMenuFormationPickerCell *aCell = new EditorMenuFormationPickerCell(pFormation);
    aCell->SetFrame(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
    gNotify.Register(this, aCell, "button_click");
    mScrollContent->AddCell(aCell);
    FrameDidUpdate();
    */
}

void EditorMenuFormationPicker::Layout() {
    ToolMenu::Layout();
    
    mFilterRow1->SetFrame(0.0f, 0.0f, mContent.GetWidth(), mFilterRow1->GetHeight());
    mFilterRow2->SetFrame(0.0f, mFilterRow1->GetHeight(), mContent.GetWidth(), mFilterRow1->GetHeight());
    
    float aOffset = mFilterRow1->GetHeight() + mFilterRow2->GetHeight();
    mSection->SetFrame(0.0f, aOffset, mContent.GetWidth(), mContent.GetHeight() - aOffset);
}

void EditorMenuFormationPicker::ApplyFilter() {
    
    if (mScrollContent == NULL) { return; }
    
    FString aText = mTextBoxFilter->mText.c();
    
    
    mScrollContent->ClearAll();
    
    FreeList(LevelFormation, mFormationListFiltered);
    
    EnumList(LevelFormation, aFormation, mFormationList) {
        
        bool aUse = true;
        
        if (aText.mLength > 0) {
            
            if (aFormation->mID.FindI(aText) == -1) {
                aUse = false;
            }
            
        }
        
        
        if (aUse == true) {
            mFormationListFiltered.Add(aFormation->Clone());
        }
    }
    
    EnumList(LevelFormation, aFormation, mFormationListFiltered) {
        EditorMenuFormationPickerCell *aCell = new EditorMenuFormationPickerCell(aFormation);
        aCell->SetFrame(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
        gNotify.Register(this, aCell, "button_click");
        mScrollContent->AddCell(aCell);
        
    }
    FrameDidUpdate();
    
    mDidSetUp = false;
    
}



EditorMenuFormationPickerScrollContent::EditorMenuFormationPickerScrollContent() {
    mClipEnabled = true;
    mName = "Image Picker Scroller";
    mMaxRows = 5;
    mCellGrid = 0;
    mScrollSpeedX = 0.0f;
    mScrollSpeedY = 0.0f;
    mScrollOffsetX = 0.0f;
    mScrollOffsetY = 0.0f;
    mStartOffsetX = 0.0f;
    mStartOffsetY = 0.0f;
    mGridOffsetX = 0;
    mGridOffsetY = 0;
    mCellSpacingH = 2.0f;
    mCellSpacingV = 2.0f;
    mCellWidth = 60.0f;
    mCellHeight = 60.0f;
    mColCount = 0;
    mRowCount = 0;
    float aWidth = gAppWidth;
    float aProbeX = mCellSpacingH;
    int aScreenColCount = 0;
    while (aProbeX < aWidth) {
        aScreenColCount++;
        aProbeX += (mCellWidth + mCellSpacingH);
    }
    mScreenGridWidth = (aScreenColCount);// + 2);
    mCellGrid = 0;
    mColCount = 0;
    mRowCount = 1;
}

EditorMenuFormationPickerScrollContent::~EditorMenuFormationPickerScrollContent() {
    for (int aCol=0;aCol<mColCount;aCol++) {
        delete [] mCellGrid[aCol];
    }
    delete [] mCellGrid;
    mCellGrid = 0;
    mColCount = 0;
    mRowCount = 0;
}

void EditorMenuFormationPickerScrollContent::Layout() {
    if (!mParent) return;
    SetFrame(2.0f, 2.0f, mParent->mWidth - 4.0f, mParent->mHeight - 4.0f);
}

void EditorMenuFormationPickerScrollContent::SetUp() {
    float aIdealCellHeight = 88.0f;
    if (mWidth < 200 || mHeight < 200) {
        mMaxRows = 5;
        mCellSpacingH = 2.0f;
        mCellSpacingV = 2.0f;
        mCellWidth = 60.0f;
        mCellHeight = 60.0f;
        mColCount = 0;
        mRowCount = 0;
    } else {
        mCellSpacingH = 2.0f;
        mCellSpacingV = 2.0f;
        mMaxRows = (int)(mHeight / aIdealCellHeight);
        if (mMaxRows < 3) { mMaxRows = 3; }
        if (mMaxRows > 8) { mMaxRows = 8; }
        float aMaxRows = (float)mMaxRows;
        mCellHeight = mHeight - mCellSpacingV * (aMaxRows + 1.0f);
        mCellHeight /= aMaxRows;
        mCellWidth = mCellHeight;
    }
    int aCount = mCellList.mCount;
    for (int aCol=0;aCol<mColCount;aCol++) {
        delete [] mCellGrid[aCol];
    }
    if(mScreenGridWidth < 2) { mScreenGridWidth = 2; }
    mCellGrid = 0;
    mColCount = 0;
    mRowCount = 1;
    if (aCount > 0) {
        if (aCount <= mScreenGridWidth) {
            mColCount = aCount;
        } else {
            int aScan = aCount;
            while (aScan > mScreenGridWidth) {
                aScan -= mScreenGridWidth;
                mRowCount++;
            }
            if (mRowCount > mMaxRows) {
                mRowCount = mMaxRows;
                mColCount = (aCount / mRowCount);
                if((aCount % mRowCount) != 0) { mColCount++; }
            } else {
                mColCount = mScreenGridWidth;
            }
        }
        
        mCellGrid = new EditorMenuFormationPickerCell**[mColCount];
        for (int aCol=0;aCol<mColCount;aCol++) {
            mCellGrid[aCol] = new EditorMenuFormationPickerCell*[mRowCount];
            for (int aRow=0;aRow<mRowCount;aRow++) {
                mCellGrid[aCol][aRow] = 0;
            }
        }
        
        int aIndex = 0;
        float aProbeX = mCellSpacingH;
        float aProbeY = mCellSpacingV;
        for (int aRow=0;aRow<mRowCount;aRow++) {
            aProbeX = mCellSpacingH;
            for (int aCol=0;aCol<mColCount;aCol++) {
                EditorMenuFormationPickerCell *aCell = ((EditorMenuFormationPickerCell *)(mCellList.Fetch(aIndex)));
                if (aCell) {
                    mCellGrid[aCol][aRow] = aCell;
                    aCell->SetFrame(aProbeX, aProbeY, mCellWidth, mCellHeight);
                }
                aProbeX += (mCellWidth + mCellSpacingH);
                aIndex++;
            }
            aProbeY += (mCellHeight + mCellSpacingV);
        }
    }
}

void EditorMenuFormationPickerScrollContent::Update() {
    if (mScrollFlingSpeed > 0) {
        mScrollFlingSpeed *= 0.940f;
        mScrollFlingSpeed -= 0.1f;
        if (mScrollFlingSpeed <= 0) {
            mScrollFlingSpeed = 0;
        }
        mScrollOffsetX += mScrollFlingSpeed * mScrollSpeedX;
    }
    
    float aCellWidth = (mCellWidth + mCellSpacingH);
    
    EditorMenuFormationPickerCell *aHold = 0;
    if (mCellGrid != 0) {
        while (mScrollOffsetX >= aCellWidth) {
            mGridOffsetX++;
            if(mGridOffsetX >= mColCount) { mGridOffsetX -= mColCount; }
            mScrollOffsetX -= aCellWidth;
            mStartOffsetX -= aCellWidth;
            
            for (int n = 0; n < mRowCount; n++) {
                aHold = mCellGrid[mColCount - 1][n];
                for (int i = (mColCount - 2); i >= 0; i--) {
                    mCellGrid[i + 1][n] = mCellGrid[i][n];
                }
                mCellGrid[0][n] = aHold;
            }
        }
        while (mScrollOffsetX <= 0.0f) {
            mGridOffsetX--;
            if (mGridOffsetX < 0) { mGridOffsetX += mColCount; }
            mScrollOffsetX += aCellWidth;
            mStartOffsetX += aCellWidth;
            for (int n = 0; n < mRowCount; n++) {
                aHold = mCellGrid[0][n];
                for (int i = 1; i < mColCount; i++) {
                    mCellGrid[i - 1][n] = mCellGrid[i][n];
                }
                mCellGrid[mColCount - 1][n] = aHold;
            }
        }
        
        int aIndex = 0;
        float aProbeX = mCellSpacingH;
        float aProbeY = mCellSpacingV;
        for (int aRow = 0; aRow < mRowCount; aRow++) {
            aProbeX = (mCellSpacingH - aCellWidth);
            
            for (int aCol = 0; aCol < mColCount; aCol++) {
                EditorMenuFormationPickerCell *aCell = mCellGrid[aCol][aRow];
                
                if (aCell) {
                    aCell->SetFrame(aProbeX + mScrollOffsetX, aProbeY, mCellWidth, mCellHeight);
                    
                    if ((aCell->mX >= (-mCellWidth)) && (aCell->mX < (mWidth))) {
                        aCell->mHidden = false;
                        aCell->mEnabled = true;
                    } else {
                        aCell->mHidden = true;
                        aCell->mEnabled = false;
                    }
                }
                aProbeX += (mCellWidth + mCellSpacingH);
                aIndex++;
            }
            aProbeY += (mCellHeight + mCellSpacingV);
        }
    }
}

void EditorMenuFormationPickerScrollContent::Draw() {
    
}

void EditorMenuFormationPickerScrollContent::AddCell(EditorMenuFormationPickerCell *pCell) {
    if (pCell) {
        float aPlaceX = ((float)(mCellList.mCount)) * mCellWidth;
        pCell->SetFrame(aPlaceX, 0.0f, mCellWidth, mCellHeight);
        mCellList += pCell;
        AddChild(pCell);
        pCell->mConsumesTouches = false;
    }
}

void EditorMenuFormationPickerScrollContent::ClearAll() {
    
    for (int aRow = 0; aRow < mRowCount; aRow++) {
        for (int aCol = 0; aCol < mColCount; aCol++) {
            mCellGrid[aCol][aRow] = NULL;
        }
    }
    
    EnumList(EditorMenuFormationPickerCell, aCell, mCellList) {
        aCell->Kill();
    }
    
    mCellList.RemoveAll();
    
}

void EditorMenuFormationPickerScrollContent::TouchDown(float pX, float pY, void *pData) {
    mScrollFlingSpeed = 0.0f;
    
    mScrollSpeedX = 0.0f;
    mScrollSpeedY = 0.0f;
}

void EditorMenuFormationPickerScrollContent::PanBegin(float pX, float pY) {
    mStartOffsetX = mScrollOffsetX;
    mStartOffsetY = mScrollOffsetY;
}

void EditorMenuFormationPickerScrollContent::Pan(float pX, float pY) {
    mScrollOffsetX = mStartOffsetX + mGesturePanDistX;
    mScrollOffsetY = mStartOffsetY + mGesturePanDistY;
    EnumList(EditorMenuFormationPickerCell, aCell, mCellList) {
        aCell->mTouchCanceled = true;
    }
}

void EditorMenuFormationPickerScrollContent::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {
    float aSpeed = pSpeedX * pSpeedX + pSpeedY * pSpeedY;
    if (aSpeed > 0.1f) {
        aSpeed = sqrtf(aSpeed);
        pSpeedX /= aSpeed;
        pSpeedY /= aSpeed;
    }
    
    mScrollSpeedX = (pSpeedX * 0.65f);
    mScrollSpeedY = (pSpeedY * 0.65f);
    
    mScrollFlingSpeed = aSpeed;
    
    if (mScrollFlingSpeed > 50.0f) { mScrollFlingSpeed = 50.0f; }
    
    EnumList(EditorMenuFormationPickerCell, aCell, mCellList) {
        aCell->mTouchCanceled = false;
    }
}





