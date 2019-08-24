//
//  EditorMenuMotionTypePanel.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/25/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuMotionTypePanel.hpp"
#include "GameEditor.hpp"

EditorMenuMotionTypePanel::EditorMenuMotionTypePanel() {
    
    SetTitle("Generic");
    
    mMotionSlice = NULL;
    mType = LEVEL_MOTION_SLICE_TYPE_NONE;
    mSpeedIndex = 0;
    
    mSegmentSpeed = NULL;
    mRowGeneric1 = NULL;
    mCheckBoxNegateSpeed = NULL;
    mCheckBoxNegateSpeedRandomly = NULL;
}

EditorMenuMotionTypePanel::~EditorMenuMotionTypePanel() {
    
}

void EditorMenuMotionTypePanel::Update() {
    
    if (gEditor == NULL) { return; }
    
    if (mMotionSlice == NULL) {
        mSpeedIndex = -1;
    } else {
        mSpeedIndex = gEditor->SpeedConvertTypeToSegment(mMotionSlice->mSpeedClass);
    }
    
    
    if (mCheckBoxNegateSpeed != NULL) {
        bool aUnlink = true;
        if (mMotionSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegateSpeed->SetTarget(&(mMotionSlice->mSpeedNegateAlways));
        }
        if (aUnlink) { mCheckBoxNegateSpeed->SetTarget(NULL); }
    }
    
    if (mCheckBoxNegateSpeedRandomly != NULL) {
        bool aUnlink = true;
        if (mMotionSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegateSpeedRandomly->SetTarget(&(mMotionSlice->mSpeedNegateRandomly));
        }
        if (aUnlink) { mCheckBoxNegateSpeedRandomly->SetTarget(NULL); }
    }
}

void EditorMenuMotionTypePanel::Notify(void *pSender, const char *pNotification) {
    ToolMenuPanel::Notify(pSender, pNotification);
    if (gEditor == NULL) { return; }
    if (pSender == mSegmentSpeed) {
        if (mMotionSlice != NULL) {
            mMotionSlice->mSpeedClass = gEditor->SpeedConvertSegmentToType(mSegmentSpeed->mSelectedIndex);
            gEditor->RefreshPlayback();
        }
    }
    if (pSender == mCheckBoxNegateSpeed) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxNegateSpeedRandomly) { gEditor->RefreshPlayback(); }
}


void EditorMenuMotionTypePanel::AddSpeedSegment() {
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(7);
    mSegmentSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    mSegmentSpeed->SetTarget(&mSpeedIndex);
    AddSection(mSegmentSpeed);
    gNotify.Register(this, mSegmentSpeed, "segment");
    
    
    
}

void EditorMenuMotionTypePanel::AddSpeedNegation() {
    mRowGeneric1 = new ToolMenuSectionRow();
    AddSection(mRowGeneric1);
    
    mCheckBoxNegateSpeed = new UICheckBox();
    mCheckBoxNegateSpeed->SetText("Negate");
    mRowGeneric1->AddCheckBox(mCheckBoxNegateSpeed);
    gNotify.Register(this, mCheckBoxNegateSpeed, "checkbox");
    
    mCheckBoxNegateSpeedRandomly = new UICheckBox();
    mCheckBoxNegateSpeedRandomly->SetText("Rand Negate");
    mRowGeneric1->AddCheckBox(mCheckBoxNegateSpeedRandomly);
    gNotify.Register(this, mCheckBoxNegateSpeedRandomly, "checkbox");
}









EditorMenuMotionTypePanelNegate::EditorMenuMotionTypePanelNegate() {
    mType = LEVEL_MOTION_SLICE_TYPE_NEGATE;
    
    SetTitle("Negate");
    
    mRowNegs1 = new ToolMenuSectionRow();
    AddSection(mRowNegs1);
    
    mRowNegs2 = new ToolMenuSectionRow();
    AddSection(mRowNegs2);
    
    mCheckBoxNegateSpeedH = new UICheckBox();
    mCheckBoxNegateSpeedH->SetText("Neg-H");
    mRowNegs1->AddCheckBox(mCheckBoxNegateSpeedH);
    gNotify.Register(this, mCheckBoxNegateSpeedH, "checkbox");
    
    mCheckBoxNegateSpeedHRandomly = new UICheckBox();
    mCheckBoxNegateSpeedHRandomly->SetText("Neg-H-Rand");
    mRowNegs1->AddCheckBox(mCheckBoxNegateSpeedHRandomly);
    gNotify.Register(this, mCheckBoxNegateSpeedHRandomly, "checkbox");
    
    
    mCheckBoxNegateSpeedV = new UICheckBox();
    mCheckBoxNegateSpeedV->SetText("Neg-V");
    mRowNegs2->AddCheckBox(mCheckBoxNegateSpeedV);
    gNotify.Register(this, mCheckBoxNegateSpeedV, "checkbox");
    
    mCheckBoxNegateSpeedVRandomly = new UICheckBox();
    mCheckBoxNegateSpeedVRandomly->SetText("Neg-V-Rand");
    mRowNegs2->AddCheckBox(mCheckBoxNegateSpeedVRandomly);
    gNotify.Register(this, mCheckBoxNegateSpeedVRandomly, "checkbox");
}


EditorMenuMotionTypePanelNegate::~EditorMenuMotionTypePanelNegate() {
    
}

void EditorMenuMotionTypePanelNegate::Update() {
    
    if (gEditor == NULL) { return; }
    
    EditorMenuMotionTypePanel::Update();
    
    LevelMotionControllerSliceNegateBlueprint *aSlice = (LevelMotionControllerSliceNegateBlueprint *)mMotionSlice;
    
    if (mCheckBoxNegateSpeedH != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegateSpeedH->SetTarget(&(aSlice->mNegateHAlways));
        }
        if (aUnlink) { mCheckBoxNegateSpeedH->SetTarget(NULL); }
    }
    
    if (mCheckBoxNegateSpeedHRandomly != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegateSpeedHRandomly->SetTarget(&(aSlice->mNegateHRandomly));
        }
        if (aUnlink) { mCheckBoxNegateSpeedHRandomly->SetTarget(NULL); }
    }
    
    if (mCheckBoxNegateSpeedV != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegateSpeedV->SetTarget(&(aSlice->mNegateVAlways));
        }
        if (aUnlink) { mCheckBoxNegateSpeedV->SetTarget(NULL); }
    }
    
    if (mCheckBoxNegateSpeedVRandomly != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegateSpeedVRandomly->SetTarget(&(aSlice->mNegateVRandomly));
        }
        if (aUnlink) { mCheckBoxNegateSpeedVRandomly->SetTarget(NULL); }
    }
}

void EditorMenuMotionTypePanelNegate::Notify(void *pSender, const char *pNotification) {
    if (gEditor == NULL) { return; }
    EditorMenuMotionTypePanel::Notify(pSender, pNotification);
    if (pSender == mCheckBoxNegateSpeedH) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxNegateSpeedHRandomly) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxNegateSpeedV) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxNegateSpeedVRandomly) { gEditor->RefreshPlayback(); }
}







EditorMenuMotionTypePanelRotate::EditorMenuMotionTypePanelRotate() {
    mType = LEVEL_MOTION_SLICE_TYPE_ROTATE;
    
    SetTitle("Rotate");
    
    AddSpeedSegment();
    AddSpeedNegation();
    
    mRowOffsets1 = new ToolMenuSectionRow();
    AddSection(mRowOffsets1);
    
    mLabelPivotOffsetX = new UILabel();
    mRowOffsets1->AddLabel(mLabelPivotOffsetX);
    
    mLabelPivotOffsetY = new UILabel();
    mRowOffsets1->AddLabel(mLabelPivotOffsetY);
    
    mRowOffsets2 = new ToolMenuSectionRow();
    AddSection(mRowOffsets2);
    
    mButtonResetPivotOffsetX = new UIButton();
    mButtonResetPivotOffsetX->SetText("Reset-X");
    mRowOffsets2->AddButton(mButtonResetPivotOffsetX);
    gNotify.Register(this, mButtonResetPivotOffsetX, "button_click");
    
    mButtonResetPivotOffsetY = new UIButton();
    mButtonResetPivotOffsetY->SetText("Reset-Y");
    mRowOffsets2->AddButton(mButtonResetPivotOffsetY);
    gNotify.Register(this, mButtonResetPivotOffsetY, "button_click");
    
    mStepperPivotOffsetX = new UIStepper();
    mStepperPivotOffsetX->SetText("Off-X");
    AddSection(mStepperPivotOffsetX);
    gNotify.Register(this, mStepperPivotOffsetX, "stepper");
    
    mStepperPivotOffsetY = new UIStepper();
    mStepperPivotOffsetY->SetText("Off-Y");
    AddSection(mStepperPivotOffsetY);
    gNotify.Register(this, mStepperPivotOffsetY, "stepper");
}


EditorMenuMotionTypePanelRotate::~EditorMenuMotionTypePanelRotate() {
    
}

void EditorMenuMotionTypePanelRotate::Update() {
    
    if (gEditor == NULL) { return; }
    
    EditorMenuMotionTypePanel::Update();
    
    LevelMotionControllerSliceRotateBlueprint *aSlice = (LevelMotionControllerSliceRotateBlueprint *)mMotionSlice;
    
    if (mStepperPivotOffsetX != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPivotOffsetX->SetTarget(&(aSlice->mPivotOffsetX));
        }
        if (aUnlink) { mStepperPivotOffsetX->SetTarget(NULL); }
    }
    
    if (mStepperPivotOffsetY != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPivotOffsetY->SetTarget(&(aSlice->mPivotOffsetY));
        }
        if (aUnlink) { mStepperPivotOffsetY->SetTarget(NULL); }
    }
    
    if (mLabelPivotOffsetX != NULL) {
        if (aSlice != NULL) {
            mLabelPivotOffsetX->SetText(FString(aSlice->mPivotOffsetX));
        } else {
            mLabelPivotOffsetX->SetText("---");
        }
    }
    
    if (mLabelPivotOffsetY != NULL) {
        if (aSlice != NULL) {
            mLabelPivotOffsetY->SetText(FString(aSlice->mPivotOffsetY));
        } else {
            mLabelPivotOffsetY->SetText("---");
        }
    }
}

void EditorMenuMotionTypePanelRotate::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    
    LevelMotionControllerSliceRotateBlueprint *aSlice = (LevelMotionControllerSliceRotateBlueprint *)mMotionSlice;
    
    EditorMenuMotionTypePanel::Notify(pSender, pNotification);
    
    if (pSender == mButtonResetPivotOffsetX) {
        if (aSlice != NULL) {
            aSlice->mPivotOffsetX = 0;
            gEditor->RefreshPlayback();
        }
    }
    
    if (pSender == mButtonResetPivotOffsetY) {
        if (aSlice != NULL) {
            aSlice->mPivotOffsetY = 0;
            gEditor->RefreshPlayback();
        }
    }
    
    if (pSender == mStepperPivotOffsetX) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPivotOffsetY) { gEditor->RefreshPlayback(); }
}









EditorMenuMotionTypePanelOscillateRotation::EditorMenuMotionTypePanelOscillateRotation() {
    mType = LEVEL_MOTION_SLICE_TYPE_OSCILLATE_ROTATION;
    
    SetTitle("Osc-Rot");
    
    mRowOptions = new ToolMenuSectionRow();
    AddSection(mRowOptions);
    
    mCheckBoxLinear = new UICheckBox();
    mCheckBoxLinear->SetText("Linear");
    mRowOptions->AddCheckBox(mCheckBoxLinear);
    gNotify.Register(this, mCheckBoxLinear, "checkbox");
    
    mStepperLinearTime = new UIStepper();
    mStepperLinearTime->SetText("L-Time");
    AddSection(mStepperLinearTime);
    gNotify.Register(this, mStepperLinearTime, "stepper");
    
    mStepperLinearTimer = new UIStepper();
    mStepperLinearTimer->SetText("L-Tick");
    AddSection(mStepperLinearTimer);
    gNotify.Register(this, mStepperLinearTimer, "stepper");
    
    mStepperPause1 = new UIStepper();
    mStepperPause1->SetText("Paus-1");
    AddSection(mStepperPause1);
    gNotify.Register(this, mStepperPause1, "stepper");
    
    mStepperPause2 = new UIStepper();
    mStepperPause2->SetText("Paus-2");
    AddSection(mStepperPause2);
    gNotify.Register(this, mStepperPause2, "stepper");
    
    
    mStepperAngleSpan = new UIStepper();
    mStepperAngleSpan->SetText("AngSpan:");
    AddSection(mStepperAngleSpan);
    gNotify.Register(this, mStepperAngleSpan, "stepper");
    
    mStepperAngleSpanStartOffset = new UIStepper();
    mStepperAngleSpanStartOffset->SetText("Off-Start:");
    AddSection(mStepperAngleSpanStartOffset);
    gNotify.Register(this, mStepperAngleSpanStartOffset, "stepper");
    
    mStepperAngleSpanEndOffset = new UIStepper();
    mStepperAngleSpanEndOffset->SetText("Off-End:");
    AddSection(mStepperAngleSpanEndOffset);
    gNotify.Register(this, mStepperAngleSpanEndOffset, "stepper");
    
}


EditorMenuMotionTypePanelOscillateRotation::~EditorMenuMotionTypePanelOscillateRotation() {
    
}

void EditorMenuMotionTypePanelOscillateRotation::Update() {
    
    if (gEditor == NULL) { return; }
    
    EditorMenuMotionTypePanel::Update();
    
    LevelMotionControllerSliceOscillateRotationBlueprint *aSlice = (LevelMotionControllerSliceOscillateRotationBlueprint *)mMotionSlice;
    if (mCheckBoxLinear != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mCheckBoxLinear->SetTarget(&(aSlice->mLinear));
        }
        if (aUnlink) { mCheckBoxLinear->SetTarget(NULL); }
    }
    
    if (mStepperLinearTime != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperLinearTime->SetTarget(&(aSlice->mLinearTime));
        }
        if (aUnlink) { mStepperLinearTime->SetTarget(NULL); }
    }
    
    if (mStepperLinearTimer != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperLinearTimer->SetTarget(&(aSlice->mLinearTimer));
        }
        if (aUnlink) { mStepperLinearTimer->SetTarget(NULL); }
    }
    
    if (mStepperAngleSpan != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperAngleSpan->SetTarget(&(aSlice->mAngleSpan));
        }
        if (aUnlink) { mStepperAngleSpan->SetTarget(NULL); }
    }
    
    if (mStepperAngleSpanStartOffset != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperAngleSpanStartOffset->SetTarget(&(aSlice->mAngleSpanOffsetStart));
        }
        if (aUnlink) { mStepperAngleSpanStartOffset->SetTarget(NULL); }
    }
    
    if (mStepperAngleSpanEndOffset != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperAngleSpanEndOffset->SetTarget(&(aSlice->mAngleSpanOffsetEnd));
        }
        if (aUnlink) { mStepperAngleSpanEndOffset->SetTarget(NULL); }
    }
    
    if (mStepperPause1 != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPause1->SetTarget(&(aSlice->mPause1));
        }
        if (aUnlink) { mStepperPause1->SetTarget(NULL); }
    }
    
    if (mStepperPause2 != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPause2->SetTarget(&(aSlice->mPause2));
        }
        if (aUnlink) { mStepperPause2->SetTarget(NULL); }
    }
}

void EditorMenuMotionTypePanelOscillateRotation::Notify(void *pSender, const char *pNotification) {
    if (gEditor == NULL) { return; }
    EditorMenuMotionTypePanel::Notify(pSender, pNotification);
    if (pSender == mCheckBoxLinear) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperLinearTime) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperLinearTimer) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPause1) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPause2) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperAngleSpan) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperAngleSpanStartOffset) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperAngleSpanEndOffset) { gEditor->RefreshPlayback(); }
}










EditorMenuMotionTypePanelOscillateVertical::EditorMenuMotionTypePanelOscillateVertical() {
    mType = LEVEL_MOTION_SLICE_TYPE_OSCILLATE_VERTICAL;
    
    SetTitle("Osc-Ver");
    
    mRowOptions = new ToolMenuSectionRow();
    AddSection(mRowOptions);
    
    mCheckBoxLinear = new UICheckBox();
    mCheckBoxLinear->SetText("Linear");
    mRowOptions->AddCheckBox(mCheckBoxLinear);
    gNotify.Register(this, mCheckBoxLinear, "checkbox");
    
    mStepperLinearTime = new UIStepper();
    mStepperLinearTime->SetText("L-Time");
    AddSection(mStepperLinearTime);
    gNotify.Register(this, mStepperLinearTime, "stepper");
    
    mStepperLinearTimer = new UIStepper();
    mStepperLinearTimer->SetText("L-Tick");
    AddSection(mStepperLinearTimer);
    gNotify.Register(this, mStepperLinearTimer, "stepper");
    
    mStepperPause1 = new UIStepper();
    mStepperPause1->SetText("Paus-1");
    AddSection(mStepperPause1);
    gNotify.Register(this, mStepperPause1, "stepper");
    
    mStepperPause2 = new UIStepper();
    mStepperPause2->SetText("Paus-2");
    AddSection(mStepperPause2);
    gNotify.Register(this, mStepperPause2, "stepper");
    
    mStepperRadius = new UIStepper();
    mStepperRadius->SetText("Rad:");
    AddSection(mStepperRadius);
    gNotify.Register(this, mStepperRadius, "stepper");
}


EditorMenuMotionTypePanelOscillateVertical::~EditorMenuMotionTypePanelOscillateVertical() {
    
}

void EditorMenuMotionTypePanelOscillateVertical::Update() {
    
    if (gEditor == NULL) { return; }
    
    EditorMenuMotionTypePanel::Update();
    
    LevelMotionControllerSliceOscillateVerticalBlueprint *aSlice = (LevelMotionControllerSliceOscillateVerticalBlueprint *)mMotionSlice;
    if (mCheckBoxLinear != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mCheckBoxLinear->SetTarget(&(aSlice->mLinear));
        }
        if (aUnlink) { mCheckBoxLinear->SetTarget(NULL); }
    }
    
    if (mStepperLinearTime != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperLinearTime->SetTarget(&(aSlice->mLinearTime));
        }
        if (aUnlink) { mStepperLinearTime->SetTarget(NULL); }
    }
    
    if (mStepperLinearTimer != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperLinearTimer->SetTarget(&(aSlice->mLinearTimer));
        }
        if (aUnlink) { mStepperLinearTimer->SetTarget(NULL); }
    }
    
    if (mStepperRadius != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperRadius->SetTarget(&(aSlice->mRadius));
        }
        if (aUnlink) { mStepperRadius->SetTarget(NULL); }
    }
    
    if (mStepperPause1 != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPause1->SetTarget(&(aSlice->mPause1));
        }
        if (aUnlink) { mStepperPause1->SetTarget(NULL); }
    }
    
    if (mStepperPause2 != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPause2->SetTarget(&(aSlice->mPause2));
        }
        if (aUnlink) { mStepperPause2->SetTarget(NULL); }
    }
}

void EditorMenuMotionTypePanelOscillateVertical::Notify(void *pSender, const char *pNotification) {
    if (gEditor == NULL) { return; }
    EditorMenuMotionTypePanel::Notify(pSender, pNotification);
    if (pSender == mCheckBoxLinear) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperLinearTime) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperLinearTimer) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPause1) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPause2) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperRadius) { gEditor->RefreshPlayback(); }
}








EditorMenuMotionTypePanelOscillateHorizontal::EditorMenuMotionTypePanelOscillateHorizontal() {
    mType = LEVEL_MOTION_SLICE_TYPE_OSCILLATE_HORIZONTAL;
    
    SetTitle("Osc-Hor");
    
    mRowOptions = new ToolMenuSectionRow();
    AddSection(mRowOptions);
    
    mCheckBoxLinear = new UICheckBox();
    mCheckBoxLinear->SetText("Linear");
    mRowOptions->AddCheckBox(mCheckBoxLinear);
    gNotify.Register(this, mCheckBoxLinear, "checkbox");
    
    mStepperLinearTime = new UIStepper();
    mStepperLinearTime->SetText("L-Time");
    AddSection(mStepperLinearTime);
    gNotify.Register(this, mStepperLinearTime, "stepper");
    
    mStepperLinearTimer = new UIStepper();
    mStepperLinearTimer->SetText("L-Tick");
    AddSection(mStepperLinearTimer);
    gNotify.Register(this, mStepperLinearTimer, "stepper");
    
    mStepperPause1 = new UIStepper();
    mStepperPause1->SetText("Paus-1");
    AddSection(mStepperPause1);
    gNotify.Register(this, mStepperPause1, "stepper");
    
    mStepperPause2 = new UIStepper();
    mStepperPause2->SetText("Paus-2");
    AddSection(mStepperPause2);
    gNotify.Register(this, mStepperPause2, "stepper");
    
    mStepperRadius = new UIStepper();
    mStepperRadius->SetText("Rad:");
    AddSection(mStepperRadius);
    gNotify.Register(this, mStepperRadius, "stepper");
}


EditorMenuMotionTypePanelOscillateHorizontal::~EditorMenuMotionTypePanelOscillateHorizontal() {
    
}

void EditorMenuMotionTypePanelOscillateHorizontal::Update() {
    
    if (gEditor == NULL) { return; }
    
    EditorMenuMotionTypePanel::Update();
    
    LevelMotionControllerSliceOscillateVerticalBlueprint *aSlice = (LevelMotionControllerSliceOscillateVerticalBlueprint *)mMotionSlice;
    if (mCheckBoxLinear != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mCheckBoxLinear->SetTarget(&(aSlice->mLinear));
        }
        if (aUnlink) { mCheckBoxLinear->SetTarget(NULL); }
    }
    
    if (mStepperLinearTime != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperLinearTime->SetTarget(&(aSlice->mLinearTime));
        }
        if (aUnlink) { mStepperLinearTime->SetTarget(NULL); }
    }
    
    if (mStepperLinearTimer != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperLinearTimer->SetTarget(&(aSlice->mLinearTimer));
        }
        if (aUnlink) { mStepperLinearTimer->SetTarget(NULL); }
    }
    
    if (mStepperRadius != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperRadius->SetTarget(&(aSlice->mRadius));
        }
        if (aUnlink) { mStepperRadius->SetTarget(NULL); }
    }
    
    if (mStepperPause1 != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPause1->SetTarget(&(aSlice->mPause1));
        }
        if (aUnlink) { mStepperPause1->SetTarget(NULL); }
    }
    
    if (mStepperPause2 != NULL) {
        bool aUnlink = true;
        if (aSlice != NULL) {
            aUnlink = false;
            mStepperPause2->SetTarget(&(aSlice->mPause2));
        }
        if (aUnlink) { mStepperPause2->SetTarget(NULL); }
    }
}

void EditorMenuMotionTypePanelOscillateHorizontal::Notify(void *pSender, const char *pNotification) {
    if (gEditor == NULL) { return; }
    EditorMenuMotionTypePanel::Notify(pSender, pNotification);
    if (pSender == mCheckBoxLinear) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperLinearTime) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperLinearTimer) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPause1) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPause2) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperRadius) { gEditor->RefreshPlayback(); }
}




