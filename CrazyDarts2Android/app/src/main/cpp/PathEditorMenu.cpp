//
//  PathEditorMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//


#include "PathEditorMenu.hpp"
#include "PGPathEditor.hpp"
#include "PGMainCanvas.hpp"
#include "FApp.hpp"
#include "ScreenTransformMenu.hpp"
#include "UIImagePicker.hpp"

PathEditorMenu::PathEditorMenu(PGPathEditor *pEditor) : ToolMenu() {
    mName = "PathEditorMenu";
    
    mPathEditor = pEditor;

    SetTitle("Path Builder");
    SetScrollMode(true);


    mRowTop = new ToolMenuSectionRow();
    AddSection(mRowTop);

    mButtonScreenTransform = new UIButton();
    mButtonScreenTransform->SetText("Screen Transform");
    mRowTop->AddButton(mButtonScreenTransform);
    gNotify.Register(this, mButtonScreenTransform, "button_click");

    mButtonClose = new UIButton();
    mButtonClose->mDrawCloseX = true;
    mRowTop->AddButton(mButtonClose);
    gNotify.Register(this, mButtonClose, "button_click");

    mButtonPickImage = new UIButton();
    mButtonPickImage->SetText("Image");
    mRowTop->AddButton(mButtonPickImage);
    gNotify.Register(this, mButtonPickImage, "button_click");

    mSegmentMode = new UISegment(2);
    mSegmentMode->SetTitles("Add Point", "Select & Drag");
    AddSection(mSegmentMode);
    gNotify.Register(this, mSegmentMode, "segment");



    mPanelSymmetry = new ToolMenuPanel();
    mPanelSymmetry->SetTitle("Symmetry");
    AddSection(mPanelSymmetry);

    mPanelExport = new ToolMenuPanel();
    mPanelExport->SetTitle("Export Options");
    AddSection(mPanelExport);


    mRowExportOptions = new ToolMenuSectionRow();
    mPanelExport->AddSection(mRowExportOptions);

    mAlignmentPickerExport = new UIAlignmentPicker();
    mAlignmentPickerExport->SetTarget(&pEditor->mOutputAlignment);
    mRowExportOptions->AddAlignmentPicker(mAlignmentPickerExport);

    mCheckBoxNormalizeExport = new UICheckBox();
    mCheckBoxNormalizeExport->SetTarget(&pEditor->mOutputNormalize);
    mRowExportOptions->AddCheckBox(mCheckBoxNormalizeExport);
}

PathEditorMenu::~PathEditorMenu() {

}

void PathEditorMenu::Layout() {
    ToolMenu::Layout();

}


void PathEditorMenu::Notify(void *pSender, const char *pNotification) {

    if (FString(pNotification) == "pick_image") {
        UIImagePicker *aImagePicker = (UIImagePicker *)pSender;
    }

    if (FString(pNotification) == "button_click") {
        if (pSender == mButtonClose) {

            if (gTool) {
                

                gTool->PopModal(mPathEditor);
            }
        }

        if (pSender == mButtonPickImage) {
            gTool->ShowImagePicker(mPathEditor);
        }
    }

    //
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        if (aSegment == mSegmentMode) {
            //aSegment->mSelectedIndex
        }
    }
}







