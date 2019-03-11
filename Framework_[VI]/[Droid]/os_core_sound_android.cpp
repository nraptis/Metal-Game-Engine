//
//  os_core_sound.cpp
//  Ghibli
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#include "os_core_sound.h"
#include "os_core_outlets.h"


#include "os_core_outlets.h"
#include "core_includes.h"

#include "FSound.h"



int otherAudioIsPlaying;

void core_sound_initialize() {
    
}



bool core_sound_load(FSound *pSound, const char *pFileName, int pInstanceCount) {
    bool aReturn = false;
    
    return aReturn;
}

void core_sound_play(FSound *pSound) {
    core_sound_play(pSound, 1.0f);
}

void core_sound_play(FSound *pSound, float pVolume) {
    if (pSound) {
        
    }
}

void core_sound_playPitched(FSound *pSound, float pPitch, float pVolume) {
    if (pSound) {
        
    }
}

void core_sound_stop(FSound *pSound) {
    if (pSound) {
        
    }
}

void core_sound_clear(FSound *pSound) {
    if (pSound) {
        
    }
}

bool core_sound_isPlaying(FSound *pSound)
{
    bool aReturn = false;
    
    if (pSound) {
        
    }
    
    return aReturn;
}

bool core_sound_didLoad(FSound *pSound) {
    bool aReturn = false;
    if (pSound) {
        
    }
    return aReturn;
}

void core_sound_setVolume(float pVolume) {
    gVolumeSound = pVolume;
}

float core_sound_getVolume() {
    return gVolumeSound;
}









void core_sound_instance_resetPitch(FSoundInstance *pInstance) {
    
}

void core_sound_instance_setPitch(FSoundInstance *pInstance, float pPitch) {
    
}

void core_sound_instance_setVolume(FSoundInstance *pInstance, float pVolume) {
    
}

void core_sound_instance_play(FSoundInstance *pInstance, float pVolume) {
    
}

void core_sound_instance_pause(FSoundInstance *pInstance) {
    
}

void core_sound_instance_unpause(FSoundInstance *pInstance) {
    
}


void core_sound_instance_loop(FSoundInstance *pInstance, float pVolume) {
    
}

void core_sound_instance_stop(FSoundInstance *pInstance) {
    
}

bool core_sound_instance_isPlaying(FSoundInstance *pInstance) {
    if (pInstance) {
        
    }
    return false;
}

void core_sound_instance_destroy(FSoundInstance *pInstance) {
    
}

void core_sound_musicPlay(const char *pFilePath, bool pLoop) {
    
}

void core_sound_musicCrossFade(const char *pFilePath, int pDurationTicks, bool pLoop) {
    
}

void core_sound_musicFadeOut(int pDurationTicks) {

}

void core_sound_musicStop() {

}

bool core_sound_musicIsPlaying() {
    bool aResult = false;
    

    return aResult;
}

void core_sound_musicSetVolume(float pVolume) {
    gVolumeMusic = pVolume;
}

float core_sound_musicGetVolume() {
    return gVolumeMusic;
}

void core_sound_musicResume() {
    
}

void core_sound_musicPause() {
    
}

void core_sound_stopAll() {
    core_sound_stopAllEffects();
    core_sound_musicPause();
}

void core_sound_stopAllEffects() {
    
}

FSoundData *core_sound_spawn_data() {
    return NULL;
}

void core_sound_unloadEffects() {
    
}

void core_sound_reloadEffects() {
    
}

void core_sound_update() {

}

void core_sound_active() {
    
}

void core_sound_inactive() {
    
}



