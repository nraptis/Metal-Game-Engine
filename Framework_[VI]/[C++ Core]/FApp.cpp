//
//  FApp.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FApp.hpp"
#include "core_includes.h"
#include "core_app_shell.h"
#include "PlatformGraphicsInterface.hpp"

FApp *gAppBase = NULL;
PlatformGraphicsInterface *gGraphicsInterface = NULL;

FApp::FApp() {
    gAppBase = this;
    
    mFrameCaptureUpdateCount = 0;
    
    
    mFrameCaptureDrawCount = 0;
    mSelectedCanvas = NULL;
    
    mIsGraphicsSetUpEnqueued = false;
    mGraphicsSetUpEnqueuedTimer = 0;
    
    
    mDidInitialize = false;
    mDidDetachFrameController = false;
    mDidUpdate = false;
    mActive = true;
    
    mDidInitializeGraphicsInterface = false;
    
    mTouchX = 0.0f;
    mTouchY = 0.0f;
    
    mSelectedInputWindow = 0;
    
    mTimeSinceLastInteraction = 0;
    
    mQuit = false;
    
    mThrottleLock = -1;
    mSystemLock = -1;
    //
    //
    //
    mWindowMain.mRoot.mName = "root-main";
    mWindowModal.mRoot.mName = "root-modal";
    mWindowTools.mRoot.mName = "root-tools";
    //
    //
    //
    
    mIsLoading = false;
    mIsLoadingComplete = false;
    
    mUpdatesPerSecond = 100.0f;
    RecoverTime();
}

FApp::~FApp()
{
    
}

void FApp::BaseInitialize() {
    if (mDidInitialize == false) {
        mDidInitialize = true;
        mImageLoadDirectoryList += new FString("");
        if (gDirBundle.mLength > 0) mImageLoadDirectoryList += new FString(gDirBundle.c());
        if (gDirDocuments.mLength > 0) mImageLoadDirectoryList += new FString(gDirDocuments.c());
        
        mImageLoadExtensionList += new FString("jpg");
        mImageLoadExtensionList += new FString("png");

        mImageLoadMutableSuffixList += new FString("");
        mImageLoadSuffixList += new FString("");
        
        while (gGraphicsInterface->IsReady() == false) {
            printf("BaseInitialize:: Waiting for GFX...\n");
            os_sleep(10);
        }
        
        Graphics::SetDeviceSize(gDeviceWidth, gDeviceHeight);
        
        
        //Initialize the graphics interface...
        gGraphicsInterface->Initialize();
        
        os_sleep(10);
        
        //Initialize the graphics engine...
        Graphics::Initialize();
        Graphics::SetUp();
        
        Initialize();
    }
}


void FApp::BaseSetDeviceSize(int pWidth, int pHeight) {
    
    //Log("DeviceSize[%.2f, %.2f]----\n", gDeviceWidth, gDeviceHeight);
    
    if (gGraphicsInterface && gGraphicsInterface->IsReady()) {
        Graphics::SetDeviceSize(pWidth, pHeight);
    }
    
    //mViewControllerTools.DeviceSizeChanged(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    SetDeviceSize(pWidth, pHeight);
    
    //mWindowTools.SetVirtualFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    mWindowTools.SetDeviceSize(gDeviceWidth, gDeviceHeight);
    mWindowModal.SetDeviceSize(gDeviceWidth, gDeviceHeight);
    mWindowMain.SetDeviceSize(gDeviceWidth, gDeviceHeight);
}

void FApp::BaseSetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    
    //Log("Virtual Frame(%.2f, %.2f  %.2f, %.2f]  Dev[%.2f, %.2f]----\n", gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight, gDeviceWidth, gDeviceHeight);
    
    mWindowMain.SetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    mWindowModal.SetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    mWindowTools.SetVirtualFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    SetVirtualFrame(pX, pY, pWidth, pHeight);
}

void FApp::BaseSetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft) {
    
    //Log("SafeAreaInsets(%.2f, %.2f, %.2f, %.2f)----\n", gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    
    mWindowMain.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    mWindowModal.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    mWindowTools.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    SetSafeAreaInsets(pInsetUp, pInsetRight, pInsetDown, pInsetLeft);
}

void AppFrameThread(void *pArgs) {
    Log("AppFrameThread(%X)\n", pArgs);
    
    gAppBase->MainRunLoop();
}

//Externally, we are getting a "frame" ...
void FApp::BaseFrame() {

    if (mDidInitialize == false) {
        BaseInitialize();
    }
    
    if (mDidDetachFrameController == false) {
        mDidDetachFrameController = true;
        os_detach_thread(AppFrameThread, (void*)0xB00BFACE);
        
    }
    
    if (mIsGraphicsSetUpEnqueued) {
        if (mGraphicsSetUpEnqueuedTimer > 0) {
            mGraphicsSetUpEnqueuedTimer -= 1;
        } else {
            mIsGraphicsSetUpEnqueued = false;
            Graphics::SetUp();
        }
    }
    
    gBufferCache.Reset();
    
    while (mDidUpdate == false) {
        Log("Waiting for An Update...\n");
        os_sleep(18);
    }
    
    //for (int i=0;i<aUpdateCount;i++) {
    //BaseUpdate();
    
        ThrottleLock();
    
        if (gGraphicsInterface) {
            gGraphicsInterface->SetContext();
        }
        gGraphicsInterface->Prerender();
        Graphics::PreRender();
        gAppBase->Prerender();
        //
        ////
        //
        BaseDraw();
        //
        ////
        //
        
        gAppBase->Postrender();
        Graphics::PostRender();
        gGraphicsInterface->Postrender();
        
        gGraphicsInterface->Commit();
        
        ThrottleUnlock();
    
}

void FApp::BaseUpdate() {
    if (mDidInitialize == false) {
        BaseInitialize();
    }
    
    
    int aSlot = 0;
    if (mFrameCaptureUpdateCount < FRAME_TIME_CAPTURE_COUNT) {
        aSlot = mFrameCaptureUpdateCount;
        ++mFrameCaptureUpdateCount;
    } else {
        for (int i=1;i<FRAME_TIME_CAPTURE_COUNT;i++) {
            mFrameCaptureUpdateTime[i-1] = mFrameCaptureUpdateTime[i];
        }
        aSlot = FRAME_TIME_CAPTURE_COUNT - 1;
    }
    mFrameCaptureUpdateTime[aSlot] = os_system_time();
    
    
    //if (mLo == false) {
    //    gTouch.Reset();
    //    return;
    //}
    
    mDidUpdate = true;
    
    InterfaceLock();
    gTouch.Update();
    InterfaceUnlock();
    
    
    
    Update();
    
    mWindowMain.Update();
    mWindowModal.Update();
    mWindowTools.Update();
    
    core_sound_update();

    
}

void FApp::BaseDraw() {
    
    if (mActive == false) { return; }
    if (mIsGraphicsSetUpEnqueued == true) {
        printf("BLOCKING: SETUP...\n");
        return;
    }

    int aSlot = 0;
    if (mFrameCaptureDrawCount < FRAME_TIME_CAPTURE_COUNT) {
        aSlot = mFrameCaptureDrawCount;
        ++mFrameCaptureDrawCount;
    } else {
        for (int i=1;i<FRAME_TIME_CAPTURE_COUNT;i++) {
            mFrameCaptureDrawTime[i-1] = mFrameCaptureDrawTime[i];
        }
        aSlot = FRAME_TIME_CAPTURE_COUNT - 1;
    }
    mFrameCaptureDrawTime[aSlot] = os_system_time();
    

    //Graphics::ViewportSet(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    FMatrix aOrtho = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -2048.0f, 2048.0f);
    Graphics::MatrixProjectionSet(aOrtho);
    
    //FMatrix aScreenProjection = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -1024.0f, 1024.0f);
    //Graphics::MatrixProjectionSet(aScreenProjection);
    Graphics::MatrixModelViewReset();
    //Graphics::Clear(0.0f, 0.0f, 0.0f);
    
    
    Graphics::TextureSetClamp();
    
    //TODO: Attach the appropriate
    //pipeline state...
    
    //Graphics::BlendEnable();
    //Graphics::CullFacesEnable();
    //Graphics::CullFacesSetFront();
    
    Graphics::ClipDisable();
    
    
    Draw();
    
    mWindowMain.Draw();
    mWindowModal.Draw();
    mWindowTools.Draw();
    
    Graphics::MatrixProjectionSet(aOrtho);
    Graphics::MatrixModelViewReset();
    DrawOver();
    
    if (mIsLoadingComplete && Graphics::RenderPass() == GFX_RENDER_PASS_2D_MAIN) {
        Graphics::MatrixProjectionResetOrtho();
        Graphics::MatrixModelViewReset();
        Graphics::SetColor();
        Graphics::PipelineStateSetSpritePremultipliedBlending();
        Graphics::BufferSetIndicesSprite();
        
        
        mSysFont.Draw(FString("FPS = ") + FString(GetFPS()), gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 6.0f, 0.5f);
        mSysFont.Draw(FString("UPS = ") + FString(GetUPS()), gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 6.0f + 18.0f, 0.5f);
    }
    
    if (mIsLoadingComplete && Graphics::RenderPass() == GFX_RENDER_PASS_2D_MAIN) {
        
        /*
        Graphics::PipelineStateSetShape2DAlphaBlending();
        Graphics::SetColor(0.55f, 0.55f, 0.55f, 0.5f);
        Graphics::DrawLine(gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY, gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY + gVirtualDevHeight, 2.0f);
        Graphics::DrawLine(gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY, gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY + gVirtualDevHeight, 2.0f);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gSafeAreaInsetTop, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gSafeAreaInsetTop, 2.0f);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, 2.0f);
        
        
        Graphics::SetColor(0.11f, 0.11f, 0.11f, 0.5f);
        Graphics::DrawLine(gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY, gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY + gVirtualDevHeight);
        Graphics::DrawLine(gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY, gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY + gVirtualDevHeight);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gSafeAreaInsetTop, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gSafeAreaInsetTop, 1.0f);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, 1.0f);
        */
    }
}

void FApp::BaseLoad() {
    if (mDidInitialize == false) {
        BaseInitialize();
    }
    
    mIsLoading = true;
    
    if (gQuadBufferPosition == -1) {
        gQuadBufferPosition = Graphics::BufferArrayGenerate(sizeof(float) * 8);
        gQuadBufferTextureCoord = Graphics::BufferArrayGenerate(sizeof(float) * 8);
    }
    
    gImageBundler.Load("bundle_sys_font_bold", "bundle_sys_font_bold_512");
    if (gImageBundler.mBundleWidth > 32 && gImageBundler.mBundleHeight > 32) {
        mSysFontBold.Load("sys_font_bold_256_", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-=.,()[]!/");
    }
    mSysFontBold.mDataScale = 0.125f;
    mSysFontBold.mSpriteScale = 0.125f;
    mSysFontBold.mPointSize = 290.0f;
    
    
    gImageBundler.Load("bundle_sys_font", "bundle_sys_font_512");
    if (gImageBundler.mBundleWidth > 32 && gImageBundler.mBundleHeight > 32) {
        mSysFont.Load("sys_font_256_", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-=.,()[]!/{}_*&%$?");
    }
    mSysFont.mDataScale = 0.125f;
    mSysFont.mSpriteScale = 0.125f;
    mSysFont.mPointSize = 290.0f;
    
    gImageBundler.Clear();
    //gSpriteList.Clear();
    
    
    
    Load();
    //
    //
    //
}

void FApp::BaseLoadComplete() {
    
    mIsLoading = false;
    mIsLoadingComplete = true;
    
    mSysFont.SetKern(32, 65, -13); mSysFont.SetKern(32, 84, -4); mSysFont.SetKern(32, 89, -4); mSysFont.SetKern(121, 46, -17); mSysFont.SetKern(121, 44, -17); mSysFont.SetKern(119, 46, -13); mSysFont.SetKern(119, 44, -13); mSysFont.SetKern(118, 46, -17); mSysFont.SetKern(118, 44, -17); mSysFont.SetKern(114, 46, -13); mSysFont.SetKern(49, 49, -17); mSysFont.SetKern(65, 32, -13); mSysFont.SetKern(65, 84, -17); mSysFont.SetKern(65, 86, -17); mSysFont.SetKern(65, 87, -9); mSysFont.SetKern(65, 89, -17); mSysFont.SetKern(65, 118, -4); mSysFont.SetKern(65, 119, -4); mSysFont.SetKern(65, 121, -4); mSysFont.SetKern(114, 44, -13); mSysFont.SetKern(70, 44, -25); mSysFont.SetKern(70, 46, -25); mSysFont.SetKern(70, 65, -13); mSysFont.SetKern(76, 32, -9); mSysFont.SetKern(76, 84, -17); mSysFont.SetKern(76, 86, -17); mSysFont.SetKern(76, 87, -17); mSysFont.SetKern(76, 89, -17); mSysFont.SetKern(76, 121, -9); mSysFont.SetKern(102, 102, -4); mSysFont.SetKern(80, 32, -4); mSysFont.SetKern(80, 44, -30); mSysFont.SetKern(80, 46, -30); mSysFont.SetKern(80, 65, -17); mSysFont.SetKern(82, 84, -4); mSysFont.SetKern(82, 86, -4); mSysFont.SetKern(82, 87, -4); mSysFont.SetKern(82, 89, -4); mSysFont.SetKern(84, 32, -4); mSysFont.SetKern(84, 44, -25); mSysFont.SetKern(84, 45, -13); mSysFont.SetKern(84, 46, -25); mSysFont.SetKern(84, 58, -25); mSysFont.SetKern(89, 118, -13); mSysFont.SetKern(84, 65, -17); mSysFont.SetKern(84, 79, -4); mSysFont.SetKern(84, 97, -25); mSysFont.SetKern(84, 99, -25); mSysFont.SetKern(84, 101, -25); mSysFont.SetKern(84, 105, -9); mSysFont.SetKern(84, 111, -25); mSysFont.SetKern(84, 114, -9); mSysFont.SetKern(84, 115, -25); mSysFont.SetKern(84, 117, -9); mSysFont.SetKern(84, 119, -13); mSysFont.SetKern(84, 121, -13); mSysFont.SetKern(86, 44, -21); mSysFont.SetKern(86, 45, -13); mSysFont.SetKern(86, 46, -21); mSysFont.SetKern(86, 58, -9); mSysFont.SetKern(89, 117, -13); mSysFont.SetKern(86, 65, -17); mSysFont.SetKern(86, 97, -17); mSysFont.SetKern(86, 101, -13); mSysFont.SetKern(86, 105, -4); mSysFont.SetKern(86, 111, -13); mSysFont.SetKern(86, 114, -9); mSysFont.SetKern(86, 117, -9); mSysFont.SetKern(86, 121, -9); mSysFont.SetKern(87, 44, -13); mSysFont.SetKern(87, 45, -4); mSysFont.SetKern(87, 46, -13); mSysFont.SetKern(87, 58, -4); mSysFont.SetKern(89, 113, -21); mSysFont.SetKern(87, 65, -9); mSysFont.SetKern(87, 97, -9); mSysFont.SetKern(87, 101, -4); mSysFont.SetKern(89, 112, -17); mSysFont.SetKern(87, 111, -4); mSysFont.SetKern(87, 114, -4); mSysFont.SetKern(87, 117, -4); mSysFont.SetKern(87, 121, -2); mSysFont.SetKern(89, 32, -4); mSysFont.SetKern(89, 44, -30); mSysFont.SetKern(89, 45, -21); mSysFont.SetKern(89, 46, -30); mSysFont.SetKern(89, 58, -13); mSysFont.SetKern(89, 111, -21); mSysFont.SetKern(89, 65, -17); mSysFont.SetKern(89, 97, -17); mSysFont.SetKern(89, 101, -21); mSysFont.SetKern(89, 105, -9);
    
    mSysFont.SetStride(32, -16, 64); mSysFont.SetStride(33, 3, 64); mSysFont.SetStride(34, -6, 82); mSysFont.SetStride(35, -14, 128); mSysFont.SetStride(36, -9, 128); mSysFont.SetStride(37, -3, 205); mSysFont.SetStride(38, -7, 153); mSysFont.SetStride(39, -7, 44); mSysFont.SetStride(40, -3, 77); mSysFont.SetStride(41, -2, 77); mSysFont.SetStride(42, -9, 90); mSysFont.SetStride(43, -4, 134); mSysFont.SetStride(44, 3, 64); mSysFont.SetStride(45, -9, 77); mSysFont.SetStride(46, 4, 64); mSysFont.SetStride(47, -17, 64); mSysFont.SetStride(48, -7, 128); mSysFont.SetStride(49, 8, 128); mSysFont.SetStride(50, -10, 128); mSysFont.SetStride(51, -7, 128); mSysFont.SetStride(52, -14, 128); mSysFont.SetStride(53, -7, 128); mSysFont.SetStride(54, -8, 128); mSysFont.SetStride(55, -6, 128); mSysFont.SetStride(56, -7, 128); mSysFont.SetStride(57, -7, 128); mSysFont.SetStride(58, 4, 64); mSysFont.SetStride(59, 2, 64); mSysFont.SetStride(60, -4, 134); mSysFont.SetStride(61, -4, 134); mSysFont.SetStride(62, -4, 134); mSysFont.SetStride(63, -7, 128); mSysFont.SetStride(64, -4, 233); mSysFont.SetStride(65, -17, 153); mSysFont.SetStride(66, 0, 153); mSysFont.SetStride(67, -5, 166); mSysFont.SetStride(68, 1, 166); mSysFont.SetStride(69, 1, 153); mSysFont.SetStride(70, 2, 140); mSysFont.SetStride(71, -4, 179);
    mSysFont.SetStride(72, 2, 166); mSysFont.SetStride(73, 5, 64); mSysFont.SetStride(74, -10, 115); mSysFont.SetStride(75, 0, 153);
    mSysFont.SetStride(76, 0, 128); mSysFont.SetStride(77, 0, 192); mSysFont.SetStride(78, 1, 166); mSysFont.SetStride(79, -6, 179);
    mSysFont.SetStride(80, 1, 153); mSysFont.SetStride(81, -7, 179); mSysFont.SetStride(82, 1, 166); mSysFont.SetStride(83, -6, 153);
    mSysFont.SetStride(84, -11, 140); mSysFont.SetStride(85, 1, 166); mSysFont.SetStride(86, -16, 153); mSysFont.SetStride(87, -14, 217);
    mSysFont.SetStride(88, -15, 153); mSysFont.SetStride(89, -16, 153); mSysFont.SetStride(90, -12, 140); mSysFont.SetStride(91, -1, 64);
    mSysFont.SetStride(92, -17, 64); mSysFont.SetStride(93, -12, 64); mSysFont.SetStride(94, -11, 108); mSysFont.SetStride(95, -20, 128);
    mSysFont.SetStride(96, -6, 77); mSysFont.SetStride(97, -8, 128); mSysFont.SetStride(98, -2, 128); mSysFont.SetStride(99, -8, 115);
    mSysFont.SetStride(100, -9, 128); mSysFont.SetStride(101, -8, 128); mSysFont.SetStride(102, -15, 64); mSysFont.SetStride(103, -9, 128);
    mSysFont.SetStride(104, -2, 128); mSysFont.SetStride(105, -1, 51); mSysFont.SetStride(106, -27, 51); mSysFont.SetStride(107, -1, 115);
    mSysFont.SetStride(108, -2, 51); mSysFont.SetStride(109, -1, 192); mSysFont.SetStride(110, -2, 128); mSysFont.SetStride(111, -9, 128);
    mSysFont.SetStride(112, -2, 128); mSysFont.SetStride(113, -9, 128); mSysFont.SetStride(114, -2, 77); mSysFont.SetStride(115, -10, 115);
    mSysFont.SetStride(116, -13, 64); mSysFont.SetStride(117, -2, 128); mSysFont.SetStride(118, -14, 115); mSysFont.SetStride(119, -16, 166);
    mSysFont.SetStride(120, -15, 115); mSysFont.SetStride(121, -13, 115); mSysFont.SetStride(122, -12, 115); mSysFont.SetStride(123, -10, 77);
    mSysFont.SetStride(124, 3, 57); mSysFont.SetStride(125, -11, 77); mSysFont.SetStride(126, -7, 134); mSysFont.SetStride(164, -8, 128); mSysFont.SetStride(167, -8, 128); mSysFont.SetStride(169, -16, 169); mSysFont.SetStride(188, -5, 192); mSysFont.SetStride(189, -5, 192); mSysFont.SetStride(198, -16, 230);
    
    mSysFontBold.SetKern(32, 65, -9); mSysFontBold.SetKern(32, 89, -4); mSysFontBold.SetKern(121, 46, -17); mSysFontBold.SetKern(121, 44, -17);
    mSysFontBold.SetKern(119, 46, -9); mSysFontBold.SetKern(119, 44, -9); mSysFontBold.SetKern(118, 46, -17); mSysFontBold.SetKern(118, 44, -17);
    mSysFontBold.SetKern(49, 49, -13); mSysFontBold.SetKern(65, 32, -9); mSysFontBold.SetKern(65, 84, -17); mSysFontBold.SetKern(65, 86, -17); mSysFontBold.SetKern(65, 87, -13); mSysFontBold.SetKern(65, 89, -21); mSysFontBold.SetKern(65, 118, -9); mSysFontBold.SetKern(65, 119, -4);
    mSysFontBold.SetKern(65, 121, -9); mSysFontBold.SetKern(114, 46, -13);
    mSysFontBold.SetKern(70, 44, -25); mSysFontBold.SetKern(70, 46, -25);
    mSysFontBold.SetKern(70, 65, -13); mSysFontBold.SetKern(76, 32, -4);
    mSysFontBold.SetKern(76, 84, -17); mSysFontBold.SetKern(76, 86, -17);
    mSysFontBold.SetKern(76, 87, -13); mSysFontBold.SetKern(76, 89, -21);
    mSysFontBold.SetKern(76, 121, -9); mSysFontBold.SetKern(114, 44, -13);
    mSysFontBold.SetKern(80, 32, -4); mSysFontBold.SetKern(80, 44, -30);
    mSysFontBold.SetKern(80, 46, -30); mSysFontBold.SetKern(80, 65, -17);
    mSysFontBold.SetKern(82, 86, -4); mSysFontBold.SetKern(82, 87, -4);
    mSysFontBold.SetKern(82, 89, -9); mSysFontBold.SetKern(84, 44, -25);
    mSysFontBold.SetKern(84, 45, -13); mSysFontBold.SetKern(84, 46, -25);
    mSysFontBold.SetKern(84, 58, -25); mSysFontBold.SetKern(89, 118, -13);
    mSysFontBold.SetKern(84, 65, -17); mSysFontBold.SetKern(84, 79, -4);
    mSysFontBold.SetKern(84, 97, -17); mSysFontBold.SetKern(84, 99, -17);
    mSysFontBold.SetKern(84, 101, -17); mSysFontBold.SetKern(84, 105, -4);
    mSysFontBold.SetKern(84, 111, -17); mSysFontBold.SetKern(84, 114, -13);
    mSysFontBold.SetKern(84, 115, -17); mSysFontBold.SetKern(84, 117, -17);
    mSysFontBold.SetKern(84, 119, -17); mSysFontBold.SetKern(84, 121, -17);
    mSysFontBold.SetKern(86, 44, -21); mSysFontBold.SetKern(86, 45, -13);
    mSysFontBold.SetKern(86, 46, -21); mSysFontBold.SetKern(86, 58, -13);
    mSysFontBold.SetKern(89, 117, -13); mSysFontBold.SetKern(86, 65, -17);
    mSysFontBold.SetKern(86, 97, -13); mSysFontBold.SetKern(86, 101, -13);
    mSysFontBold.SetKern(86, 105, -4); mSysFontBold.SetKern(86, 111, -17);
    mSysFontBold.SetKern(86, 114, -13); mSysFontBold.SetKern(86, 117, -9);
    mSysFontBold.SetKern(86, 121, -9); mSysFontBold.SetKern(87, 44, -13);
    mSysFontBold.SetKern(87, 45, -5); mSysFontBold.SetKern(87, 46, -13);
    mSysFontBold.SetKern(87, 58, -4); mSysFontBold.SetKern(89, 113, -17);
    mSysFontBold.SetKern(87, 65, -13); mSysFontBold.SetKern(87, 97, -9);
    mSysFontBold.SetKern(87, 101, -4); mSysFontBold.SetKern(87, 105, -2);
    mSysFontBold.SetKern(87, 111, -4); mSysFontBold.SetKern(87, 114, -4);
    mSysFontBold.SetKern(87, 117, -4); mSysFontBold.SetKern(87, 121, -4);
    mSysFontBold.SetKern(89, 32, -4); mSysFontBold.SetKern(89, 44, -25);
    mSysFontBold.SetKern(89, 45, -13); mSysFontBold.SetKern(89, 46, -25);
    mSysFontBold.SetKern(89, 58, -17); mSysFontBold.SetKern(89, 112, -13);
    mSysFontBold.SetKern(89, 65, -21); mSysFontBold.SetKern(89, 97, -13);
    mSysFontBold.SetKern(89, 101, -13); mSysFontBold.SetKern(89, 105, -9);
    mSysFontBold.SetKern(89, 111, -17); mSysFontBold.SetStride(32, -16, 62);
    mSysFontBold.SetStride(33, 3, 74); mSysFontBold.SetStride(34, -5, 106);
    mSysFontBold.SetStride(35, -15, 125); mSysFontBold.SetStride(36, -9, 125);
    mSysFontBold.SetStride(37, -7, 196); mSysFontBold.SetStride(38, -7, 162);
    mSysFontBold.SetStride(39, -7, 53); mSysFontBold.SetStride(40, -5, 75);
    mSysFontBold.SetStride(41, -9, 75); mSysFontBold.SetStride(42, -14, 87);
    mSysFontBold.SetStride(43, -7, 131); mSysFontBold.SetStride(44, -4, 62);
    mSysFontBold.SetStride(45, -4, 75); mSysFontBold.SetStride(46, -1, 62);
    mSysFontBold.SetStride(47, -17, 62); mSysFontBold.SetStride(48, -7, 125);
    mSysFontBold.SetStride(49, 1, 125); mSysFontBold.SetStride(50, -11, 125);
    mSysFontBold.SetStride(51, -8, 125); mSysFontBold.SetStride(52, -13, 125);
    mSysFontBold.SetStride(53, -7, 125); mSysFontBold.SetStride(54, -7, 125);
    mSysFontBold.SetStride(55, -7, 125); mSysFontBold.SetStride(56, -8, 125);
    mSysFontBold.SetStride(57, -10, 125); mSysFontBold.SetStride(58, 5, 75);
    mSysFontBold.SetStride(59, 2, 75); mSysFontBold.SetStride(60, -6, 131);
    mSysFontBold.SetStride(61, -7, 131); mSysFontBold.SetStride(62, -6, 131);
    mSysFontBold.SetStride(63, -5, 137); mSysFontBold.SetStride(64, -10, 218); mSysFontBold.SetStride(65, -17, 162); mSysFontBold.SetStride(66, 0, 162); mSysFontBold.SetStride(67, -6, 162); mSysFontBold.SetStride(68, -1, 162); mSysFontBold.SetStride(69, -1, 149); mSysFontBold.SetStride(70, 0, 137); mSysFontBold.SetStride(71, -6, 174); mSysFontBold.SetStride(72, 0, 162); mSysFontBold.SetStride(73, -2, 62); mSysFontBold.SetStride(74, -13, 125); mSysFontBold.SetStride(75, 0, 162); mSysFontBold.SetStride(76, 0, 137); mSysFontBold.SetStride(77, -1, 187); mSysFontBold.SetStride(78, 0, 162); mSysFontBold.SetStride(79, -7, 174); mSysFontBold.SetStride(80, -1, 149); mSysFontBold.SetStride(81, -7, 174); mSysFontBold.SetStride(82, 0, 162); mSysFontBold.SetStride(83, -9, 149); mSysFontBold.SetStride(84, -11, 137); mSysFontBold.SetStride(85, -1, 162); mSysFontBold.SetStride(86, -17, 149); mSysFontBold.SetStride(87, -16, 211); mSysFontBold.SetStride(88, -16, 149); mSysFontBold.SetStride(89, -17, 149); mSysFontBold.SetStride(90, -14, 137); mSysFontBold.SetStride(91, -1, 75); mSysFontBold.SetStride(92, -17, 62); mSysFontBold.SetStride(93, -12, 75); mSysFontBold.SetStride(94, -4, 131); mSysFontBold.SetStride(95, -19, 125); mSysFontBold.SetStride(96, -12, 75); mSysFontBold.SetStride(97, -9, 125); mSysFontBold.SetStride(98, -2, 137); mSysFontBold.SetStride(99, -7, 125); mSysFontBold.SetStride(100, -8, 137); mSysFontBold.SetStride(101, -10, 125); mSysFontBold.SetStride(102, -14, 75); mSysFontBold.SetStride(103, -8, 137); mSysFontBold.SetStride(104, -1, 137); mSysFontBold.SetStride(105, -1, 62); mSysFontBold.SetStride(106, -27, 62); mSysFontBold.SetStride(107, -2, 125); mSysFontBold.SetStride(108, -1, 62); mSysFontBold.SetStride(109, -3, 199); mSysFontBold.SetStride(110, -1, 137); mSysFontBold.SetStride(111, -8, 137); mSysFontBold.SetStride(112, -2, 137); mSysFontBold.SetStride(113, -7, 137); mSysFontBold.SetStride(114, -2, 87); mSysFontBold.SetStride(115, -11, 125); mSysFontBold.SetStride(116, -13, 75); mSysFontBold.SetStride(117, -1, 137); mSysFontBold.SetStride(118, -15, 125); mSysFontBold.SetStride(119, -16, 174); mSysFontBold.SetStride(120, -15, 125); mSysFontBold.SetStride(121, -15, 123); mSysFontBold.SetStride(122, -13, 112); mSysFontBold.SetStride(123, -10, 87); mSysFontBold.SetStride(124, 3, 63); mSysFontBold.SetStride(125, -12, 87); mSysFontBold.SetStride(126, -9, 131); mSysFontBold.SetStride(164, -11, 125); mSysFontBold.SetStride(167, -10, 125); mSysFontBold.SetStride(169, -18, 165); mSysFontBold.SetStride(188, -7, 187); mSysFontBold.SetStride(189, -7, 187); mSysFontBold.SetStride(198, -26, 224);
    
    LoadComplete();
    
    
    BaseSetDeviceSize(gDeviceWidth, gDeviceHeight);
    BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    BaseSetSafeAreaInsets(gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    
}

void FApp::MouseDown(float pX, float pY, int pButton) {
    
}

void FApp::MouseMove(float pX, float pY) {
    
}

void FApp::MouseUp(float pX, float pY, int pButton) {
    
}

void FApp::MouseWheel(int pDirection) {
    
}

void FApp::KeyDown(int pKey) {
    
}

void FApp::KeyUp(int pKey) {
    
}

void FApp::BaseTouchDown(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchDown(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchMove(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchMove(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchUp(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchUp(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchCanceled(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchCanceled(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchDownDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchDownDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseTouchMoveDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchMoveDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseTouchUpDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchUpDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseTouchCanceledDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchCanceledDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseMouseDown(float pX, float pY, int pButton) {
    InterfaceLock();
    gTouch.BaseMouseDown(pX, pY, pButton);
    InterfaceUnlock();
    
}

void FApp::BaseMouseMove(float pX, float pY) {
    InterfaceLock();
    gTouch.BaseMouseMove(pX, pY);
    InterfaceUnlock();
}

void FApp::BaseMouseUp(float pX, float pY, int pButton) {
    InterfaceLock();
    gTouch.BaseMouseUp(pX, pY, pButton);
    InterfaceUnlock();
}

void FApp::BaseMouseWheel(int pDirection) {
    InterfaceLock();
    gTouch.BaseMouseWheel(pDirection);
    InterfaceUnlock();
}

void FApp::BaseKeyDown(int pKey) {
    if ((pKey >= 0) && (pKey < 256)) {
        InterfaceLock();
        gKeyPressed[pKey] = true;
        gTouch.EnqueueKeyDown(pKey);
        InterfaceUnlock();
    }
}

void FApp::BaseKeyUp(int pKey) {
    if ((pKey >= 0) && (pKey < 256)) {
        InterfaceLock();
        gKeyPressed[pKey] = false;
        gTouch.EnqueueKeyUp(pKey);
        InterfaceUnlock();
    }
}

void FApp::ProcessMouseDown(float pX, float pY, int pButton) {
    MouseDown(pX, pY, pButton);
    
    mSelectedCanvas = NULL;
    if (mWindowTools.MouseDown(pX, pY, pButton)) {
        mSelectedInputWindow = &mWindowTools;
        mSelectedCanvas = mWindowTools.mSelectedCanvas;
    } else if (mWindowModal.MouseDown(pX, pY, pButton)) {
        mSelectedInputWindow = &mWindowModal;
        mSelectedCanvas = mWindowModal.mSelectedCanvas;
    } else if (mWindowMain.MouseDown(pX, pY, pButton)) {
        mSelectedInputWindow = &mWindowMain;
        mSelectedCanvas = mWindowMain.mSelectedCanvas;
    } else {
        mSelectedInputWindow = 0;
    }
}

void FApp::ProcessMouseMove(float pX, float pY) {
    MouseMove(pX, pY);
    if (mSelectedInputWindow != 0) {
        mSelectedInputWindow->MouseMove(pX, pY);
    } else {
        if (mWindowTools.MouseMove(pX, pY)) {
        } else if (mWindowModal.MouseMove(pX, pY)) {
        } else if (mWindowMain.MouseMove(pX, pY)) { }
    }
}

void FApp::ProcessMouseUp(float pX, float pY, int pButton) {
    MouseUp(pX, pY, pButton);
    if (mSelectedInputWindow != 0) {
        mSelectedInputWindow->MouseUp(pX, pY, pButton);
    }
}

void FApp::ProcessMouseWheel(int pDir) {
    MouseWheel(pDir);
    mWindowTools.MouseWheel(pDir);
    mWindowModal.MouseWheel(pDir);
    mWindowMain.MouseWheel(pDir);
}

void FApp::ProcessTouchDown(float pX, float pY, void *pData) {
    if (mWindowTools.TouchDown(pX, pY, pData)) {
        mSelectedInputWindow = &mWindowTools;
    } else if (mWindowModal.TouchDown(pX, pY, pData)) {
        mSelectedInputWindow = &mWindowModal;
    } else if (mWindowMain.TouchDown(pX, pY, pData)) {
        mSelectedInputWindow = &mWindowMain;
    } else {
        mSelectedInputWindow = 0;
    }
    TouchDown(pX, pY, pData);
}

void FApp::ProcessTouchMove(float pX, float pY, void *pData) {
    mWindowTools.TouchMove(pX, pY, pData);
    mWindowModal.TouchMove(pX, pY, pData);
    mWindowMain.TouchMove(pX, pY, pData);
    TouchMove(pX, pY, pData);
}

void FApp::ProcessTouchUp(float pX, float pY, void *pData) {
    mTouchX = pX;
    mTouchY = pY;
    mWindowTools.TouchUp(pX, pY, pData);
    mWindowModal.TouchUp(pX, pY, pData);
    mWindowMain.TouchUp(pX, pY, pData);
    TouchUp(pX, pY, pData);
}

void FApp::ProcessTouchFlush() {
    mWindowMain.TouchFlush();
    mWindowModal.TouchFlush();
    mWindowTools.TouchFlush();
    TouchFlush();
}

void FApp::ProcessKeyDown(int pKey) {
    mWindowMain.KeyDown(pKey);
    mWindowModal.KeyDown(pKey);
    mWindowTools.KeyDown(pKey);
    KeyDown(pKey);
}

void FApp::ProcessKeyUp(int pKey) {
    mWindowMain.KeyUp(pKey);
    mWindowModal.KeyUp(pKey);
    mWindowTools.KeyUp(pKey);
    KeyUp(pKey);
}

void FApp::BaseInactive() {
    if (mActive == true) {
        mActive = false;
        ProcessTouchFlush();
        Inactive();
        
        InterfaceLock();
        gTouch.Inactive();
        InterfaceUnlock();
        
        
        mWindowMain.Inactive();
        mWindowModal.Inactive();
        mWindowTools.Inactive();
        
        core_sound_stopAll();
        core_sound_inactive();
        
        #if (CURRENT_ENV == ENV_ANDROID)
        //|| (CURRENT_ENV == ENV_IOS)
        Graphics::TearDown();
        #endif
        
    }
}

void FApp::BaseActive() {
    if(mActive == false) {
        mActive = true;
        Active();
        
        #if (CURRENT_ENV == ENV_ANDROID)
        //|| (CURRENT_ENV == ENV_IOS)
        mIsGraphicsSetUpEnqueued = true;
        mGraphicsSetUpEnqueuedTimer = 4;
        #endif
        
        InterfaceLock();
        gTouch.Active();
        InterfaceUnlock();
        
        mWindowMain.Active();
        mWindowModal.Active();
        mWindowTools.Active();
        
        core_sound_active();
        core_sound_musicResume();
    }
}

void FApp::BaseMemoryWarning(bool pSevere) {
    MemoryWarning(pSevere);
    mWindowMain.MemoryWarning(pSevere);
    mWindowModal.MemoryWarning(pSevere);
    mWindowTools.MemoryWarning(pSevere);
}

void FApp::BaseQuit() {
    Quit();
    mQuit = true;
}

void FApp::Quit() {
    
}

bool FApp::ShouldQuit() {
    return mQuit;
}

void FApp::BaseSetImageFileScale(int pScale) {
    mImageLoadScaleSuffix = FString("_scale_") + FString(gImageFileScale);
    SetImageFileScale(pScale);
}

static int clockCount = 0;
void FApp::ThrottleLock() {
    if (os_thread_lock_exists(mThrottleLock) == false) {
        mThrottleLock = os_create_thread_lock();
    }
    clockCount += 1;
    os_lock_thread(mThrottleLock);
}

void FApp::ThrottleUnlock() {
    os_unlock_thread(mThrottleLock);
}

void FApp::SystemLock() {
    if (os_thread_lock_exists(mSystemLock) == false) {
        mSystemLock = os_create_thread_lock();
    }
    os_lock_thread(mSystemLock);
}

void FApp::SystemUnlock() {
    os_unlock_thread(mSystemLock);
}

void FApp::InterfaceLock() {
    if (os_thread_lock_exists(mInterfaceLock) == false) {
        mInterfaceLock = os_create_thread_lock();
    }
    os_lock_thread(mInterfaceLock);
}

void FApp::InterfaceUnlock() {
    os_unlock_thread(mInterfaceLock);
}

void FApp::SystemProcess() {
    if (gGraphicsInterface) {
        SystemLock();
        gGraphicsInterface->PollEvents();
        SystemUnlock();
    }
}

void FApp::MainRunLoop() {
    
     while (gGraphicsInterface->IsReady() == false) {
         Log("Waiting for Graphics Module...\n");
         os_sleep(18);
     }
    
     while (!ShouldQuit()) {
         FrameController();
     }
}

void FApp::RecoverTime() {
    mFrame.mBaseUpdateTime = os_system_time();
    mFrame.mCurrentUpdateNumber = 0;
    mFrame.mBreakUpdate = true;
    mFrame.mDesiredUpdate = 0;
}

void FApp::FrameController() {

    ThrottleLock();
    
    if (mActive == false) {
        if (os_updates_in_background()) {
            
            /*
             if (mIdleWhenInBackground) {
             #ifndef AppRunsInThread
             OS_Core::Pump();
             #endif
             System_Process();
             if (mNeedBackgroundDraw)
             {
             ThrottleDraw();
             mNeedBackgroundDraw=false;
             }
             else OS_Core::Sleep(200);
             }
             */
            
        } else {
            SystemProcess();
            os_sleep(20);
            return;
        }
    }
    
    //
    // Frame controller for static number of updates/sec
    //
    {
        
        /////////////////////////////////////////////////////////////////
        //
        // Main control loop... calls Update() and Draw() appropriately
        //
        /////////////////////////////////////////////////////////////////
        
        
        mFrame.mDesiredUpdate = (float)(os_system_time() - mFrame.mBaseUpdateTime);
        mFrame.mDesiredUpdate /= 10;
        mFrame.mDesiredUpdate *= (float)mUpdatesPerSecond / 100.0f;
        
        if (mFrame.mDesiredUpdate < mFrame.mCurrentUpdateNumber) {
            RecoverTime();
        }
        
        mFrame.mBreakUpdate=false;
        bool aShouldDraw = false;
        int aUpdateCheck = (int)mFrame.mDesiredUpdate - mFrame.mCurrentUpdateNumber;
        
        if (aUpdateCheck > 0) {
            
            while (mFrame.mCurrentUpdateNumber < (int)mFrame.mDesiredUpdate && !mFrame.mBreakUpdate) {
                aShouldDraw = true;
                
                SystemProcess();
                
                if (ShouldQuit()) {
                    break;
                }
                //
                // Process the actual update
                //
                mFrame.mCurrentUpdateNumber++;
                
                BaseUpdate();
            }
        }
    }
    
    
    ThrottleUnlock();
    
    
    
    //if ((mActive == false) && (true)) {
    //    RecoverTime();
    //}
    
    //if (mInBackground && mIdleWhenInBackground) RecoverTime();
    
}





int FApp::GetUPS() {
    int aResult = 100;
    if (mFrameCaptureUpdateCount > 2) {
        int aTimeDiff = (int)(mFrameCaptureUpdateTime[mFrameCaptureUpdateCount - 1] - mFrameCaptureUpdateTime[0]);
        float aSecondsEllapsed = ((float)aTimeDiff) / 1000.0f;
        if (aTimeDiff > 0) {
            aResult = (int)(((float)mFrameCaptureUpdateCount) / aSecondsEllapsed);
            
        }
    }
    return aResult;
}

int FApp::GetFPS() {
    int aResult = 60;
    if (mFrameCaptureDrawCount > 2) {
        int aTimeDiff = (int)(mFrameCaptureDrawTime[mFrameCaptureDrawCount - 1] - mFrameCaptureDrawTime[0]);
        float aSecondsEllapsed = ((float)aTimeDiff) / 1000.0f;
        if (aTimeDiff > 0) {
            aResult = (int)(((float)mFrameCaptureDrawCount) / aSecondsEllapsed);
            
        }
    }
    return aResult;
}


