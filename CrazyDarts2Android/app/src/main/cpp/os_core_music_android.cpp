//
//  os_core_sound.cpp
//  Graveyard
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "os_core_music.h"
#include "os_core_outlets.h"
#include "os_core_outlets.h"
#include "core_includes.h"

void music_initialize() {

}

void music_play(const char *pFilePath, bool pLoop) {


}

void music_crossfade(const char *pFilePath, int pDurationTicks, bool pLoop) {


}

void music_fadeout(int pDurationTicks) {

}

void music_stop() {

}

bool music_isPlaying() {
    bool aResult = false;


    return aResult;
}

void music_setVolume(float pVolume) {
    gMusicVolume = pVolume;
}

float music_getVolume() {
    return gMusicVolume;
}

void music_resume() {


}

void music_pause() {


}

void music_update() {


}

void music_active() {

}

void music_inactive() {


}
