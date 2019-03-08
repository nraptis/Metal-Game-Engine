
#include "os_core_includes.h"
#include "core_includes.h"
#include "os_core_app_shell.h"
#include "FApp.hpp"
#include "PlatformGraphicsInterface.hpp"

static int gOpenGLWindow = 0;

int gWindowX = 110.0f;
int gWindowY = 4.0f;
//int gWindowWidth = 320.0f * 1.5f;
//int gWindowHeight = 568.0f * 1.5f;

int gWindowWidth = 640.0f;
int gWindowHeight = 480.0f;

int gVirtualX = 4.0f;
int gVirtualY = 4.0f;
int gVirtualWidth = gWindowWidth - 8.0f;
int gVirtualHeight = gWindowHeight - 8.0f;

//using namespace std;

bool gKeyDownCtrl = false;
bool gKeyDownShift = false;
bool gKeyDownAlt = false;

#import <Foundation/Foundation.h>



void os_core_findDirectories() {
    FString aPathBundle;
    if(gDirBundle.mLength > 0){ aPathBundle = gDirBundle.c(); }

    FString aPathDocuments;
    if(gDirDocuments.mLength > 0) { aPathDocuments = gDirDocuments.c(); }

    AppShellSetDirectoryBundle(aPathBundle.c());
    AppShellSetDirectoryDocuments(aPathDocuments.c());

    //TODO: What scale?
    AppShellSetImageFileScale(2);
}

void os_core_refreshModifierKeys() {
    
    /*
    int aModifier = glutGetModifiers();
    if ((aModifier & GLUT_ACTIVE_SHIFT) != 0) {
        if (gKeyDownShift == false) {
            gKeyDownShift = true;
            AppShellKeyDown(__KEY__LSHIFT);
        }
    } else {
        if (gKeyDownShift == true) {
            gKeyDownShift = false;
            AppShellKeyUp(__KEY__LSHIFT);
        }
    }

    if ((aModifier & GLUT_ACTIVE_CTRL) != 0) {
        if (gKeyDownCtrl == false) {
            gKeyDownCtrl = true;
            AppShellKeyDown(__KEY__LCONTROL);
        }
    } else {
        if (gKeyDownCtrl == true) {
            gKeyDownCtrl = false;
            AppShellKeyUp(__KEY__LCONTROL);
        }
    }
    
    if ((aModifier & GLUT_ACTIVE_ALT) != 0) {
        if (gKeyDownAlt == false) {
            gKeyDownAlt = true;
            AppShellKeyDown(__KEY__LALT);
        }
    } else {
        if (gKeyDownAlt == true) {
            gKeyDownAlt = false;
            AppShellKeyUp(__KEY__LALT);
        }
    }
    
    */
}


int os_core_getSystemKeySpecial(int pKey)
{
    int aKey = pKey;
    
    if((pKey >= 0) && (pKey <= 12))
    {
        if(pKey == 1)aKey = __KEY__F1;
        if(pKey == 2)aKey = __KEY__F2;
        if(pKey == 3)aKey = __KEY__F3;
        if(pKey == 4)aKey = __KEY__F4;
        if(pKey == 5)aKey = __KEY__F5;
        if(pKey == 6)aKey = __KEY__F6;
        if(pKey == 7)aKey = __KEY__F7;
        if(pKey == 8)aKey = __KEY__F8;
        if(pKey == 9)aKey = __KEY__F9;
        if(pKey == 10)aKey = __KEY__F10;
        if(pKey == 11)aKey = __KEY__F11;
        if(pKey == 12)aKey = __KEY__F12;
    }
    else if(pKey == 101){aKey = __KEY__UP;}
    else if(pKey == 102){aKey = __KEY__RIGHT;}
    else if(pKey == 103){aKey = __KEY__DOWN;}
    else if(pKey == 100){aKey = __KEY__LEFT;}
    return aKey;
}

int os_core_getSystemKey(char pKey) {
    int aKey = (int)pKey;
    if (((aKey) >= 65) && ((aKey) <= 90)) { aKey += 32; }

    if ((aKey >= 'a') && (aKey <= 'z')) {
        aKey -= 'a';
        
             if(aKey == 0 )aKey = __KEY__A;
        else if(aKey == 1 )aKey = __KEY__B;
        else if(aKey == 2 )aKey = __KEY__C;
        else if(aKey == 3 )aKey = __KEY__D;
        else if(aKey == 4 )aKey = __KEY__E;
        else if(aKey == 5 )aKey = __KEY__F;
        else if(aKey == 6 )aKey = __KEY__G;
        else if(aKey == 7 )aKey = __KEY__H;
        else if(aKey == 8 )aKey = __KEY__I;
        else if(aKey == 9 )aKey = __KEY__J;
        else if(aKey == 10)aKey = __KEY__K;
        else if(aKey == 11)aKey = __KEY__L;
        else if(aKey == 12)aKey = __KEY__M;
        else if(aKey == 13)aKey = __KEY__N;
        else if(aKey == 14)aKey = __KEY__O;
        else if(aKey == 15)aKey = __KEY__P;
        else if(aKey == 16)aKey = __KEY__Q;
        else if(aKey == 17)aKey = __KEY__R;
        else if(aKey == 18)aKey = __KEY__S;
        else if(aKey == 19)aKey = __KEY__T;
        else if(aKey == 20)aKey = __KEY__U;
        else if(aKey == 21)aKey = __KEY__V;
        else if(aKey == 22)aKey = __KEY__W;
        else if(aKey == 23)aKey = __KEY__X;
        else if(aKey == 24)aKey = __KEY__Y;
        else aKey = __KEY__Z;
    }
    else if((aKey >= '0') && (aKey <= '9'))
    {
        aKey -= '0';
        
             if(aKey == 0)aKey = __KEY__0;
        else if(aKey == 1)aKey = __KEY__1;
        else if(aKey == 2)aKey = __KEY__2;
        else if(aKey == 3)aKey = __KEY__3;
        else if(aKey == 4)aKey = __KEY__4;
        else if(aKey == 5)aKey = __KEY__5;
        else if(aKey == 6)aKey = __KEY__6;
        else if(aKey == 7)aKey = __KEY__7;
        else if(aKey == 8)aKey = __KEY__8;
        else if(aKey == 9)aKey = __KEY__9;
    }
    else if(aKey == 127)aKey = __KEY__DELETE;
    else if(aKey == 13)aKey = __KEY__ENTER;
    else {
             if(aKey == ')')aKey = __KEY__0;
        else if(aKey == '!')aKey = __KEY__1;
        else if(aKey == '@')aKey = __KEY__2;
        else if(aKey == '#')aKey = __KEY__3;
        else if(aKey == '$')aKey = __KEY__4;
        else if(aKey == '%')aKey = __KEY__5;
        else if(aKey == '^')aKey = __KEY__6;
        else if(aKey == '&')aKey = __KEY__7;
        else if(aKey == '*')aKey = __KEY__8;
        else if(aKey == '(')aKey = __KEY__9;
    }
    
    return aKey;
}


