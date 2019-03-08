//
//  os_core_sound.h
//  Ghibli
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#ifndef FRAMEWORK_OS_CORE_SOUND_H
#define FRAMEWORK_OS_CORE_SOUND_H

#include "FSound.h"

class FSoundInstanceIOS : public FSoundInstance
{
public:
    FSoundInstanceIOS();
    virtual ~FSoundInstanceIOS();
    
    unsigned int                    mIndexOpenAL;
    
};


class FSoundDataIOS : public FSoundData
{
public:
    FSoundDataIOS();
    virtual ~FSoundDataIOS();
    
    unsigned int                    *mData;
	unsigned int                    *mInstanceID;
	float                           *mSourceBuffer;
    
};




//Android wrapper.. LOL..!
typedef int SLObjectItf;
typedef int SLPlayItf;
typedef int SLSeekItf;
typedef int SLMuteSoloItf;
typedef int SLVolumeItf;
typedef int SLRatePitchItf;
typedef int SLPitchItf;
//
//
//
class FSound;
class FSoundInstance;

//Must be called before all other sound functions. (For OpenAL at least)
void core_sound_initialize();

bool core_sound_load(FSound *pSound, const char *pFileName, int pInstanceCount);

void core_sound_play(FSound *pSound);
void core_sound_play(FSound *pSound, float pVolume=1.0f);
void core_sound_playPitched(FSound *pSound, float pPitch, float pVolume=1.0f);
void core_sound_stop(FSound *pSound);
void core_sound_clear(FSound *pSound);
bool core_sound_isPlaying(FSound *pSound);
bool core_sound_didLoad(FSound *pSound);

void core_sound_instance_play(FSoundInstance *pInstance, float pVolume);
void core_sound_instance_resetPitch(FSoundInstance *pInstance);
void core_sound_instance_setPitch(FSoundInstance *pInstance, float pPitch);
void core_sound_instance_setVolume(FSoundInstance *pInstance, float pVolume);
void core_sound_instance_pause(FSoundInstance *pInstance);
void core_sound_instance_unpause(FSoundInstance *pInstance);
void core_sound_instance_loop(FSoundInstance *pInstance, float pVolume);
void core_sound_instance_stop(FSoundInstance *pInstance);
bool core_sound_instance_isPlaying(FSoundInstance *pInstance);
void core_sound_instance_destroy(FSoundInstance *pInstance);

void core_sound_setVolume(float pVolume);
float core_sound_getVolume();

void core_sound_musicPlay(const char *pFilePath, bool pLoop);
void core_sound_musicCrossFade(const char *pFilePath, int pDurationTicks, bool pLoop);
void core_sound_musicFadeOut(int pDurationTicks);
void core_sound_musicStop();

void core_sound_musicSetVolume(float pVolume);
float core_sound_musicGetVolume();

bool core_sound_musicIsPlaying();

void core_sound_musicResume();
void core_sound_musicPause();

void core_sound_stopAll();
void core_sound_stopAllEffects();

void core_sound_unloadEffects();
void core_sound_reloadEffects();


void core_sound_update();
void core_sound_active();
void core_sound_inactive();

FSoundData *core_sound_spawn_data();

#endif


