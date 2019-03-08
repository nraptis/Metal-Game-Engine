//
//  ScreenTransformMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/7/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ScreenTransformMenu.hpp"


//
//  PathEditorMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "PathEditorMenu.hpp"

//
//  ScreenTransformMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ScreenTransformMenu.hpp"
#include "FApp.hpp"

ScreenTransformMenu::ScreenTransformMenu() {
    mName = "ScreenTransformMenu";

    SetTitle("Polygon Editor");
    SetScrollMode(true);

    mPanel1 = new ToolMenuPanel();
    mPanel1->SetTitle("Point Editor");
    mPanel1->SetFrame(10, 20, 300, 70.0f);
    AddSection(mPanel1);

    UISlider *aSlider = new UISlider();
    mPanel1->AddSection(aSlider);

    UISegment *aSegment = new UISegment();
    aSegment->SetSegmentCount(3);
    aSegment->SetTitles("Item 1", "2", "3..");
    mPanel1->AddSection(aSegment);

    aSegment = new UISegment(5);
    aSegment->SetTitles("0001", "0002", "00003" , "000004" , "0000005");
    mPanel1->AddSection(aSegment);

    ToolMenuSectionRow *aRow = new ToolMenuSectionRow();

    mCB1 = new UICheckBox();
    mCB1->SetText("Check Box 1");
    mCB1->SetHeight(aRow->GetHeight());
    aRow->AddChild(mCB1);

    mPanel1->AddSection(aRow);

    mPanel2 = new ToolMenuPanel();
    mPanel2->SetTitle("Tangent Editor");
    mPanel2->SetFrame(-20, -100, 120, 110.0f);
    AddSection(mPanel2);

    mPanel3 = new ToolMenuPanel();
    mPanel3->SetFrame(-100, -120, 3000, 100);
    AddSection(mPanel3);

    mSection1 = new ToolMenuSection();
    mSection1->SetFrame(30.0f, 80.0f, 220.0f, 220.0f);
    AddSection(mSection1);

    mSection2 = new ToolMenuSection();
    mSection2->SetFrame(30.0f, 80.0f, 220.0f, 90.0f);
    AddSection(mSection2);

    mSection3 = new ToolMenuSection();
    mSection3->SetFrame(30.0f, 80.0f, 220.0f, 280.0f);
    AddSection(mSection3);

    mSubPanel1 = new ToolMenuPanel();
    mSubPanel1->SetTitle("+[]ASDF.,|");
    mSubPanel1->SetFrame(10, 20, 300, 70.0f);
    mPanel1->AddSection(mSubPanel1);

    ToolMenuPanel *mSubSub1 = new ToolMenuPanel();
    mSubSub1->SetTitle("+[]ASDF.,|");
    mSubSub1->SetFrame(10, 20, 300, 70.0f);
    mSubPanel1->AddSection(mSubSub1);

    ToolMenuPanel *mSubSub2 = new ToolMenuPanel();
    mSubSub2->SetTitle("+[]ASDF.,|");
    mSubSub2->SetFrame(10, 20, 300, 70.0f);
    mSubPanel1->AddSection(mSubSub2);

    ToolMenuPanel *mSubSubSub1 = new ToolMenuPanel();
    mSubSubSub1->SetTitle("+[]ASDF.,|");
    mSubSubSub1->SetFrame(10, 20, 300, 70.0f);
    mSubSub2->AddSection(mSubSubSub1);

    mSubPanel2 = new ToolMenuPanel();
    mSubPanel2->SetTitle("Amazing??");
    mSubPanel2->SetFrame(10, 20, 300, 70.0f);
    mPanel1->AddSection(mSubPanel2);

    mSubPanel1 = new ToolMenuPanel();
    mSubPanel1->SetTitle("Amazing journey through junkyard");
    mSubPanel1->SetFrame(10, 20, 300, 70.0f);
    mPanel2->AddSection(mSubPanel1);

    mSubPanel2 = new ToolMenuPanel();
    mSubPanel2->SetTitle("Amazing journey");
    mSubPanel2->SetFrame(10, 20, 300, 70.0f);
    mPanel2->AddSection(mSubPanel2);

    mSubPanel1 = new ToolMenuPanel();
    mSubPanel1->SetTitle("journey through junkyard");
    mSubPanel1->SetFrame(10, 20, 300, 70.0f);
    mPanel2->AddSection(mSubPanel1);

}

ScreenTransformMenu::~ScreenTransformMenu() {

}

void ScreenTransformMenu::Layout() {
    ToolMenu::Layout();

}


void ScreenTransformMenu::Notify(void *pSender, const char *pNotification) {

}







