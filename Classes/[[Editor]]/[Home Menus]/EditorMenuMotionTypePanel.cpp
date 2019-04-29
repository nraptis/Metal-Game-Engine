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
    
    mPanelGeneric = new ToolMenuPanel();
    mPanelGeneric->SetTitle("Generic");
    AddSection(mPanelGeneric);
    
    mSegmentSpeed = new UISegment();
    mSegmentSpeed->SetSegmentCount(7);
    mSegmentSpeed->SetTitles("XS", "S", "MS", "M", "MF", "F", "XF");
    mSegmentSpeed->SetTarget(&mSpeedIndex);
    mPanelGeneric->AddSection(mSegmentSpeed);
    gNotify.Register(this, mSegmentSpeed, "segment");
    
    
    mRowGeneric1 = new ToolMenuSectionRow();
    mPanelGeneric->AddSection(mRowGeneric1);
    
    
    mCheckBoxNegate = new UICheckBox();
    mCheckBoxNegate->SetText("Negate");
    mRowGeneric1->AddCheckBox(mCheckBoxNegate);
    gNotify.Register(this, mCheckBoxNegate, "checkbox");
    
    mCheckBoxNegateRandomly = new UICheckBox();
    mCheckBoxNegateRandomly->SetText("Rand Negate");
    mRowGeneric1->AddCheckBox(mCheckBoxNegateRandomly);
    gNotify.Register(this, mCheckBoxNegateRandomly, "checkbox");
    
    
    

//
//    mStepperSpawnCount = new UIStepper();
//    mStepperSpawnCount->SetText("Count");
//    mStepperSpawnCount->mMin = 1;
//    mStepperSpawnCount->mMax = (WAVE_MAX_SPAWN_COUNT);
//    mGenerationPanel->AddSection(mStepperSpawnCount);
//
//    mStepperSpacing = new UIStepper();
//    mStepperSpacing->SetText("Spacing");
//    mStepperSpacing->mMin = -1000;
//    mStepperSpacing->mMax = 1000;
//    mGenerationPanel->AddSection(mStepperSpacing);
//
//
//
//    mTimingPanel = new ToolMenuPanel();
//    mTimingPanel->SetTitle("Timing");
//    AddSection(mTimingPanel);
//
//
//
//
//
//
//    //mStepperCreationType = new UISegment();
//    //mStepperCreationType->SetSegmentCount(4);
//    //mStepperCreationType->SetTitles("P-W-Sta", "P-W-End", "P-W-Clr", "S-Clr-NoP", "S-Cle-AndP");
//    //mTimingPanel->AddSection(mStepperCreationType);
//
//
//
//    mStepperCreationDelay = new UIStepper();
//    mStepperCreationDelay->SetText("Delay");
//    mStepperCreationDelay->mMin = 0;
//    mStepperCreationDelay->mMax = 2048;
//    mTimingPanel->AddSection(mStepperCreationDelay);
//
//
//    mTimingRow1 = new ToolMenuSectionRow();
//    mTimingPanel->AddSection(mTimingRow1);
//
//
//
//    mCheckBoxCreationRequiresPrevWaveComplete = new UICheckBox();
//    mCheckBoxCreationRequiresPrevWaveComplete->SetText("P-W-Compl");
//    mTimingRow1->AddCheckBox(mCheckBoxCreationRequiresPrevWaveComplete);
//
//
//    mTimingRow2 = new ToolMenuSectionRow();
//    mTimingPanel->AddSection(mTimingRow2);
//
//    mCheckBoxCreationRequiresScreenWavesClear = new UICheckBox();
//    mCheckBoxCreationRequiresScreenWavesClear->SetText("Scr-Wav-Clr");
//    mTimingRow2->AddCheckBox(mCheckBoxCreationRequiresScreenWavesClear);
//
//    mCheckBoxCreationRequiresScreenPermsClear = new UICheckBox();
//    mCheckBoxCreationRequiresScreenPermsClear->SetText("Scr-Prm-Clr");
//    mTimingRow2->AddCheckBox(mCheckBoxCreationRequiresScreenPermsClear);
//
    
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
    
    
    if (mCheckBoxNegate != NULL) {
        bool aUnlink = true;
        if (mMotionSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegate->SetTarget(&(mMotionSlice->mSpeedNegateAlways));
        }
        if (aUnlink) { mCheckBoxNegate->SetTarget(NULL); }
    }
    
    if (mCheckBoxNegateRandomly != NULL) {
        bool aUnlink = true;
        if (mMotionSlice != NULL) {
            aUnlink = false;
            mCheckBoxNegateRandomly->SetTarget(&(mMotionSlice->mSpeedNegateRandomly));
        }
        if (aUnlink) { mCheckBoxNegateRandomly->SetTarget(NULL); }
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
    
    if (pSender == mCheckBoxNegate) { gEditor->RefreshPlayback(); }
    if (pSender == mCheckBoxNegateRandomly) { gEditor->RefreshPlayback(); }
    
}


EditorMenuMotionTypePanelRotate::EditorMenuMotionTypePanelRotate() {
    mType = LEVEL_MOTION_SLICE_TYPE_ROTATE;
    
    SetTitle("Rotate");
    
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


EditorMenuMotionTypePanelOscillateRotation::~EditorMenuMotionTypePanelOscillateRotation() {
    
}

void EditorMenuMotionTypePanelOscillateRotation::Update() {
    
    if (gEditor == NULL) { return; }
    
    EditorMenuMotionTypePanel::Update();
    
    LevelMotionControllerSliceOscillateRotationBlueprint *aSlice = (LevelMotionControllerSliceOscillateRotationBlueprint *)mMotionSlice;
    
    /*
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
    */
}

void EditorMenuMotionTypePanelOscillateRotation::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    
    LevelMotionControllerSliceOscillateRotationBlueprint *aSlice = (LevelMotionControllerSliceOscillateRotationBlueprint *)mMotionSlice;
    
    EditorMenuMotionTypePanel::Notify(pSender, pNotification);
    
    /*
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
    */
    
    if (pSender == mStepperPivotOffsetX) { gEditor->RefreshPlayback(); }
    if (pSender == mStepperPivotOffsetY) { gEditor->RefreshPlayback(); }
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
