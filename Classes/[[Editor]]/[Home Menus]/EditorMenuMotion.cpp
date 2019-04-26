//
//  EditorMenuMotion.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuMotion.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuMotion.hpp"
#include "GameEditor.hpp"
#include "GamePermanentEditor.hpp"
#include "FApp.hpp"

EditorMenuMotion::EditorMenuMotion(GameEditor *pEditor) : ToolMenu() {
    mEditor = pEditor;
    mPermEditor = NULL;
    
    Init();
}

EditorMenuMotion::EditorMenuMotion(GamePermanentEditor *pEditor) {
    mEditor = NULL;
    mPermEditor = pEditor;
    
    Init();
}

void EditorMenuMotion::Init() {
    
    mName = "EditorMenuMotion";
    SetTitle("Target Motion");
    SetScrollMode(true);
    
    mIsForPermSpawn = false;
    mMotionController = NULL;
    
    mPanelMainControls = new ToolMenuPanel();
    mPanelMainControls->SetTitle("Main");
    AddSection(mPanelMainControls);
    
    
    mRowMain1 = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowMain1);
    
    mRowMain2 = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowMain2);
    
    mRowMain3 = new ToolMenuSectionRow();
    mPanelMainControls->AddSection(mRowMain3);
    
    
    mButtonAddRotate = new UIButton();
    mButtonAddRotate->SetText("+ Rotate");
    mRowMain1->AddButton(mButtonAddRotate);
    
    mButtonAddOscillateRotation = new UIButton();
    mButtonAddOscillateRotation->SetText("+ OscRot");
    mRowMain1->AddButton(mButtonAddOscillateRotation);
    
    mButtonAddOscillateV = new UIButton();
    mButtonAddOscillateV->SetText("+ OscV");
    mRowMain2->AddButton(mButtonAddOscillateV);
    
    mButtonAddOscillateH = new UIButton();
    mButtonAddOscillateH->SetText("+ OscH");
    mRowMain2->AddButton(mButtonAddOscillateH);
    
    
    
    mButtonRemoveAll = new UIButton();
    mButtonRemoveAll->SetText("Del All");
    mRowMain3->AddButton(mButtonRemoveAll);
    
    
    mButtonRemoveFirst = new UIButton();
    mButtonRemoveFirst->SetText("Del First");
    mRowMain3->AddButton(mButtonRemoveFirst);
    
    
    mButtonRemoveLast = new UIButton();
    mButtonRemoveLast->SetText("Del Last");
    mRowMain3->AddButton(mButtonRemoveLast);
    
    
    mPanelTypes = new ToolMenuPanel();
    mPanelTypes->SetTitle("Types");
    AddSection(mPanelTypes);
    
    
}

EditorMenuMotion::~EditorMenuMotion() {
    if (gEditor != NULL) {
        if (gEditor->mMenuMotion == this) {
            gEditor->mMenuMotion = NULL;
        }
    }
    if (gPermEditor != NULL) {
        if (gPermEditor->mMenuMotion == this) {
            gPermEditor->mMenuMotion = NULL;
        }
    }
}

void EditorMenuMotion::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuMotion::Notify(void *pSender, const char *pNotification) {
    
    if (gEditor == NULL) { return; }
    
    if (mMotionController != NULL) {
        if (pSender == mButtonAddRotate) {
            mMotionController->AddSliceRotate();
            gEditor->RefreshPlayback();
        }
        if (pSender == mButtonAddOscillateV) {
            mMotionController->AddSliceOscillateRotation();
            gEditor->RefreshPlayback();
        }
        if (pSender == mButtonAddOscillateH) {
            mMotionController->AddSliceOscillateH();
            gEditor->RefreshPlayback();
        }
        if (pSender == mButtonAddOscillateRotation) {
            mMotionController->AddSliceOscillateV();
            gEditor->RefreshPlayback();
        }
        if (pSender == mButtonRemoveAll) {
            mMotionController->RemoveAllSlices();
            gEditor->RefreshPlayback();
        }
        if (pSender == mButtonRemoveLast) {
            mMotionController->RemoveLastSlice();
            gEditor->RefreshPlayback();
        }
        if (pSender == mButtonRemoveFirst) {
            mMotionController->RemoveFirstSlice();
            gEditor->RefreshPlayback();
        }
    }
}

void EditorMenuMotion::Update() {
    
    mMotionController = NULL;
    if (gEditor == NULL) { return; }
    
    LevelPermSpawnBlueprint *aPermSpawn = gEditor->PermSpawnGet();
    LevelSectionPermanentBlueprint *aPerm = gEditor->PermGet();
    LevelWaveSpawnBlueprint *aSpawn = gEditor->SpawnGet();
    
    if (mEditor != NULL) {
        if (aSpawn != NULL) {
            mMotionController = &(aSpawn->mMotionController);
        }
    }
    
    if (mPermEditor != NULL) {
        if (mIsForPermSpawn) {
            if (aPermSpawn != NULL) {
                mMotionController = &(aPermSpawn->mMotionController);
            }
        } else {
            if (aPerm != NULL) {
                mMotionController = &(aPerm->mMotionController);
            }
        }
    }
    
    CheckSlicePanels();
    
    for (int i=0;i<mTypePanelList.mCount;i++) {
        EditorMenuMotionTypePanel *aPanel = (EditorMenuMotionTypePanel *)mTypePanelList.Fetch(i);
        aPanel->mMotionSlice = (LevelMotionControllerSliceBlueprint *)mMotionController->mSliceList.Fetch(i);
    }
    
    
    //mMotionBlueprint
    
    
    
    /*
     
     if (mCheckBoxCreationRequiresPrevWaveStart != NULL) {
     bool aUnlink = true;
     if (aWave != NULL) {
     aUnlink = false;
     mCheckBoxCreationRequiresPrevWaveStart->SetTarget(&(aWave->mCreationRequiresPrevWaveStart));
     }
     if (aUnlink) {
     mCheckBoxCreationRequiresPrevWaveStart->SetTarget(NULL);
     }
     }
     
     if (mStepperCreationDelay != NULL) {
     bool aUnlink = true;
     if (aWave != NULL) {
     aUnlink = false;
     mStepperCreationDelay->SetTarget(&(aWave->mCreationDelay));
     }
     if (aUnlink) {
     mStepperCreationDelay->SetTarget(NULL);
     }
     }
     
     */
}

void EditorMenuMotion::CheckSlicePanels() {
    
    if (mMotionController == NULL) {
        
        mPanelTypes->mSectionList.RemoveAll();
        EnumList(EditorMenuMotionTypePanel, aPanel, mTypePanelList) {
            aPanel->Kill();
        }
        mTypePanelList.RemoveAll();
        
        return;
    }
    
    bool aAllMatch = true;
    
    if (mMotionController->mSliceList.mCount != mTypePanelList.mCount) {
        aAllMatch = false;
    } else {
        
        for (int i=0;i<mTypePanelList.mCount;i++) {
            
            LevelMotionControllerSliceBlueprint *aSlice = (LevelMotionControllerSliceBlueprint *)mMotionController->mSliceList.mData[i];
            EditorMenuMotionTypePanel *aPanel = (EditorMenuMotionTypePanel *)mTypePanelList.mData[i];
            
            if (aSlice->mType != aPanel->mType) {
                aAllMatch = false;
            }
        }
    }
    
    if (aAllMatch == false) {
        
        printf("Mis-Match!!!\n");
        mPanelTypes->mSectionList.RemoveAll();
        EnumList(EditorMenuMotionTypePanel, aPanel, mTypePanelList) {
            aPanel->Kill();
        }
        mTypePanelList.RemoveAll();
        
        for (int i=0;i<mMotionController->mSliceList.mCount;i++) {
            LevelMotionControllerSliceBlueprint *aSlice = (LevelMotionControllerSliceBlueprint *)mMotionController->mSliceList.mData[i];
            if (aSlice->mType == LEVEL_MOTION_SLICE_TYPE_NONE) {
                EditorMenuMotionTypePanel *aPanel = new EditorMenuMotionTypePanel();
                mPanelTypes->AddSection(aPanel);
                mTypePanelList.Add(aPanel);
            }
            if (aSlice->mType == LEVEL_MOTION_SLICE_TYPE_ROTATE) {
                EditorMenuMotionTypePanelRotate *aPanel = new EditorMenuMotionTypePanelRotate();
                mPanelTypes->AddSection(aPanel);
                mTypePanelList.Add(aPanel);
            }
        }
    }
    
    
}

//

