//
//  GameContainerContainer.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//
#include "core_includes.h"
#include "GameContainer.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"
#include "GameEditor.hpp"

GameContainer *gGameContainer = NULL;

GameContainer::GameContainer() {
    
    gGameContainer = this;
    
    mName = "GameContainer";
    
    
    mGameTestEditorOverlay = NULL;
    mGameTestRunningOverlay = NULL;
    
    mEffectsOverlay = NULL;
    mInterfaceOverlay = NULL;
    mGameMenu = NULL;
    mGameMenuAnimation = NULL;
    
    
    
    
    
    mEditorMenu = NULL;
    mEditorMenuUtils = NULL;
    
    
    SetWidth(1000.0f);
    SetHeight(1000.0f);
    
    mInterfaceLeftWidth = 4.0f;
    mInterfaceRightWidth = 4.0f;
    mInterfaceTopHeight = 4.0f;
    mInterfaceBottomHeight = 12.0f;
    
    mContainer = new FCanvas();
    mContainer->mDrawManual = true;
    //mContainer->mColor = FColor(0.25f, 1.0f, 1.0f, 0.66f);
    mContainer->SetTransformAnchor(0.5f, 0.5f);
    //mContainer->SetTransformRotation(2.0f);
    
    mPaused = false;
    mPauseFadeEnabled = false;
    
    mPauseFade = 0.0f;
    mPauseFadeMax = 0.6f;
    
    AddChild(mContainer);
    mContainer->mName = "GameContainer-InnerContainer";
    
    mGame = new Game();
    mContainer->AddChild(mGame);
    
    mEffectsOverlay = new GameOverlayEffects();
    mEffectsOverlay->mDrawManual = true;
    AddChild(mEffectsOverlay);
    
#ifndef EDITOR_MODE
    mInterfaceOverlay = new GameOverlayInterface();
    mInterfaceOverlay->mDrawManual = true;
    AddChild(mInterfaceOverlay);
#endif
    
}

GameContainer::~GameContainer() {

    if (gGameContainer == this) {
        gGameContainer = NULL;
    }
    
    if (mGameMenu != NULL) {
        mGameMenu->Kill();
        mGameMenu = NULL;
    }
    
    if (mGameMenuAnimation != NULL) {
        delete mGameMenuAnimation;
        mGameMenuAnimation = NULL;
    }
    
    
    if (mEditorMenu != NULL) {
        mEditorMenu->Kill();
        mEditorMenu = NULL;
    }
    
    if (mEditorMenuUtils != NULL) {
        mEditorMenuUtils->Kill();
        mEditorMenuUtils = NULL;
    }
    
}

void GameContainer::Layout() {
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    mInterfaceLeftWidth = gSafeAreaInsetLeft;
    mInterfaceRightWidth = gSafeAreaInsetRight;
    mInterfaceTopHeight = gSafeAreaInsetTop;
    mInterfaceBottomHeight = gSafeAreaInsetBottom;
    

    if (mGame != NULL && mContainer != NULL) {
        
        float aScale = 1.0f;
        float aGameAreaWidth = mWidth - (mInterfaceLeftWidth + mInterfaceRightWidth);
        float aGameAreaHeight = mHeight - (mInterfaceTopHeight + mInterfaceBottomHeight);
        
        FRect aFrame = FRect(0.0f, 0.0f, aGameAreaWidth, aGameAreaHeight);
        FRect aFit = FRect::FitAspectFit(aFrame, mGame->mWidth, mGame->mHeight, 0.0f, aScale);
        float aContainerWidth = round(aGameAreaWidth / aScale);
        float aContainerHeight = round(aGameAreaHeight / aScale);
        mContainer->SetTransformScale(aScale);
        mContainer->SetFrame(round(-(aContainerWidth / (2.0f))), - round((aContainerHeight / (2.0f))), aContainerWidth, aContainerHeight);
        //mContainer->SetTransformTranslate(mWidth2 + mInterfaceLeftWidth * aScale, mHeight2 + mInterfaceTopHeight * aScale);
        
        //mContainer->SetTransformTranslate(mWidth2, mHeight2);
        
        mContainer->SetTransformTranslate(mWidth2 - (mInterfaceRightWidth - mInterfaceLeftWidth) / 2.0f, mHeight2 - (mInterfaceBottomHeight - mInterfaceTopHeight) / 2.0f);
        
        mGame->mRenderShiftX = -((mInterfaceRightWidth - mInterfaceLeftWidth) / 2.0f) / aScale;
        mGame->mRenderShiftY = -((mInterfaceBottomHeight - mInterfaceTopHeight) / 2.0f) / aScale;
        
        float aGameX = round(mContainer->mWidth2 - mGame->mWidth2);
        float aGameY = round(mContainer->mHeight2 - mGame->mHeight2);
        
        mGame->SetX(aGameX);
        mGame->SetY(aGameY);
        
        if (mEffectsOverlay != NULL) {
            float aContainerCenterX = (int)(mInterfaceLeftWidth + (aGameAreaWidth) * 0.5f);
            float aContainerCenterY = (int)(mInterfaceTopHeight + (aGameAreaHeight) * 0.5f);
            mEffectsOverlay->SetFrame(aContainerCenterX - mGame->mWidth2 * aScale, aContainerCenterY - mGame->mHeight2 * aScale, mGame->mWidth * aScale, mGame->mHeight * aScale);
        }
        
        if (mInterfaceOverlay != NULL) {
            //float aContainerCenterX = (int)(mInterfaceLeftWidth + (aGameAreaWidth) * 0.5f);
            //float aContainerCenterY = (int)(mInterfaceTopHeight + (aGameAreaHeight) * 0.5f);
            
            mInterfaceOverlay->SetFrame(0.0f, 0.0f, mWidth, mHeight);
            //mInterfaceOverlay->SetFrame(aContainerCenterX - mGame->mWidth2 * aScale, aContainerCenterY - mGame->mHeight2 * aScale, mGame->mWidth * aScale, mGame->mHeight * aScale);
        }
    }
    
    
    if (mGameMenu != NULL) {
        float aWidth = gWadGameInterface.mGameMenuBack.mWidth + 20.0f;
        float aHeight = gWadGameInterface.mGameMenuBack.mHeight + 20.0f;
        mGameMenu->SetFrame(mWidth / 2.0f - aWidth / 2.0f, mHeight / 2.0f - aHeight / 2.0f, aWidth, aHeight);
    }
    
    
    
    //TODO: When to show this..?
    

    
    
    if (mGameTestEditorOverlay != NULL) {
        
        if (mGame != NULL) {
            mGameTestEditorOverlay->SetFrame(0.0f, 0.0f, mGame->mWidth, mGame->mHeight);
        }
    }
    
}

void GameContainer::Update() {
    
    if (mPauseFadeEnabled == true) {
        if (mPauseFade < mPauseFadeMax) {
            mPauseFade += 0.0085f;
            if (mPauseFade >= mPauseFadeMax) {
                mPauseFade = mPauseFadeMax;
            }
        }
    } else {
        if (mPauseFade > 0.0f) {
            mPauseFade -= 0.02f;
            if (mPauseFade <= 0.0f) {
                mPauseFade = 0.0f;
                if (mGameMenu == NULL) {
                    Unpause();
                }
            }
        }
    }
    
    
    if (mGameMenu != NULL) {
        
        if (mGameMenuAnimation != NULL) {
            mGameMenuAnimation->Update();
            if (mGameMenuAnimation->IsComplete()) {
                
                printf("ANIMATION COMPLETEEEEE!!!\n");
                delete mGameMenuAnimation;
                mGameMenuAnimation = NULL;
                
                if (mGameMenuAnimatingIn == false) {
                    mGameMenu->Kill();
                    mGameMenu = NULL;
                }
                
                if (mPauseFade <= 0) {
                    Unpause();
                }
            }
        }
    }
    
}

void GameContainer::Draw() {
    
    if (mContainer != NULL) { mContainer->DrawManual(); }
    if (mEffectsOverlay != NULL) { mEffectsOverlay->DrawManual(); }
    if (mInterfaceOverlay != NULL) { mInterfaceOverlay->DrawManual(); }
    
    
    
    if (mPauseFade != 0.0f) {
        DrawTransform();
        Graphics::PipelineStateSetShape2DAlphaBlending();
        Graphics::SetColor(0.0f, 0.0f, 0.0f, mPauseFade);
        Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
        Graphics::SetColor();
    }
    /*
    Graphics::SetColor(1.0f, 0.0f, 0.25f, 0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mInterfaceLeftWidth, mHeight);
    
    Graphics::SetColor(0.0f, 0.125f, 1.0f, 0.25f);
    Graphics::DrawRect(mWidth - mInterfaceRightWidth, 0.0f, mInterfaceRightWidth, mHeight);
    

    
    Graphics::SetColor(0.5f, 0.75f, 0.5f, 0.25f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mInterfaceTopHeight);
    
    Graphics::SetColor(1.0f, 0.5f, 0.0f, 0.25f);
    Graphics::DrawRect(0.0f, mHeight - mInterfaceBottomHeight, mWidth, mInterfaceBottomHeight);
    */
     
}

void GameContainer::Draw3D() {
    if (mGame) {
        mGame->Draw3D();
    }
    
}

void GameContainer::TouchDown(float pX, float pY, void *pData) {
    
}

void GameContainer::TouchMove(float pX, float pY, void *pData) {
    
}

void GameContainer::TouchUp(float pX, float pY, void *pData) {
    
}

void GameContainer::TouchFlush() {
    
}

void GameContainer::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (pKey == __KEY__E) {
#ifdef EDITOR_MODE
        if (aShift == false && aCtrl == true && aAlt == false) {
            if (mEditorMenu != NULL) {
                gApp->EditorTestSwitchToEditor();
            }
        }
#endif
    }
    
}

void GameContainer::KeyUp(int pKey) {
    
}

void GameContainer::Notify(void *pSender, const char *pNotification) {
    
}

//After the game + editor are ready to go.
void GameContainer::Realize() {
    
    bool aHasEditor = false;
    
#ifdef EDITOR_MODE
    if (mGameTestEditorOverlay == NULL && gEditor == NULL) {
        mGameTestEditorOverlay = new GameTestEditorOverlay();
        mGameTestEditorOverlay->mConsumesTouches = false;
        mGame->AddChild(mGameTestEditorOverlay);
        mWindow->RegisterFrameDidUpdate(this);
    }
    
    if (gEditor != NULL) {
        aHasEditor = true;
    }
    
#endif
    
    // This is what we show when we are running, not from the editor...
    if (mGameTestRunningOverlay == NULL && aHasEditor == false && mGameTestEditorOverlay == NULL) {
        mGameTestRunningOverlay = new GameTestRunningOverlay();
        mGameTestRunningOverlay->mConsumesTouches = false;
        mGame->AddChild(mGameTestRunningOverlay);
        mWindow->RegisterFrameDidUpdate(this);
    }
}

void GameContainer::PauseAndShowGameMenu() {
    
    BeginPauseFadeIn();
    Pause();
    
    if (mGameMenuAnimation != NULL) {
        delete mGameMenuAnimation;
        mGameMenuAnimation = NULL;
    }
    
    if (mGameMenu != NULL) {
        mGameMenu->Kill();
        mGameMenu = NULL;
    }
    
    mGameMenuAnimatingIn = true;

    
    float aWidth = gWadGameInterface.mGameMenuBack.mWidth + 20.0f;
    float aHeight = gWadGameInterface.mGameMenuBack.mHeight + 20.0f;
    
    mGameMenu = new GameMenu();
    mGameMenu->SetFrame(mWidth / 2.0f - aWidth / 2.0f, mHeight / 2.0f - aHeight / 2.0f, aWidth, aHeight);
    
    //mGameMenu->SetTransformTranslate(mWidth2, mHeight2);
    
    //gApp->mWindowModal.AddChild(mGameMenu);
    gApp->mWindowMain.AddChild(mGameMenu);
    
    //mGameMenu->SetTransformAnchor(1.0f, 1.0f);
    
    mGameMenuAnimation = new FCanvasAnimation(mGameMenu);
    
    
    mGameMenuAnimation->mStartX = -(gVirtualDevWidth / 2.0f + aWidth / 2.0f);
    mGameMenuAnimation->GenerateIn(76);
    mGameMenuAnimation->Update();
    
    
    //(ANIMATION_EASE_OUT_ELASTIC, 80);
    
    
//#define ANIMATION_TYPE_OVERSHOOT (ANIMATION_TYPE_EASE_OUT_BACK)
//#define ANIMATION_TYPE_OVERSHOOT_MORE 13
    
}

void GameContainer::UnpauseAndHideGameMenu() {
    
    BeginPauseFadeOut();
    
    if (mGameMenuAnimation != NULL) {
        delete mGameMenuAnimation;
        mGameMenuAnimation = NULL;
    }
    
    if (mGameMenu == NULL) {
        return;
    }
    
    
    mGameMenuAnimatingIn = false;
    
    
    mGameMenuAnimation = new FCanvasAnimation(mGameMenu);
    
    
    float aWidth = gWadGameInterface.mGameMenuBack.mWidth + 20.0f;
    //float aHeight = gWadGameInterface.mGameMenuBack.mHeight + 20.0f;
    
    
    mGameMenuAnimation->mTargetX = gVirtualDevWidth / 2.0f + aWidth / 2.0f;
    mGameMenuAnimation->GenerateOut(76);
    mGameMenuAnimation->Update();
    
    
}


void GameContainer::Pause() {
    mPaused = true;
    
}

void GameContainer::Unpause() {
    mPaused = false;
    
}

void GameContainer::BeginPauseFadeIn() {
    mPauseFadeEnabled = true;
}

void GameContainer::BeginPauseFadeOut() {
    mPauseFadeEnabled = false;
}

bool GameContainer::IsPauseFadeInComplete() {
    return (mPauseFade >= mPauseFadeMax);
}

bool GameContainer::IsPauseFadeOutComplete() {
    if ((mPauseFadeEnabled == false) && (mPauseFade >= mPauseFadeMax)) {
        return true;
    }
    return false;
}

void GameContainer::OpenEditorTestMenus() {
    
    mEditorMenu = new EditorMenuGameTest();
    gApp->mWindowTools.AddChild(mEditorMenu);
    mEditorMenu->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 680.0f);
    
    mEditorMenuUtils = new EditorMenuGameTestUtils();
    gApp->mWindowTools.AddChild(mEditorMenuUtils);
    mEditorMenuUtils->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), gSafeAreaInsetTop + 20.0f, 400.0f, 480.0f);
    
}

