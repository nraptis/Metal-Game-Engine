//
//  os_core_sound.h
//  Ghibli
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#ifndef FRAMEWORK_OS_CORE_SOUND_H
#define FRAMEWORK_OS_CORE_SOUND_H

#include "os_core_includes.h"
#include "FSound.h"



#define SOUND_VOLUME_MILLIBEL_MIN (-4000)
#define SOUND_VOLUME_MILLIBEL_MAX (0)


class FSoundInstanceAndroid;

#define AUDIO_BUFFER_COUNT 12

class FAudioBuffer
{
public:

    FAudioBuffer();
    ~FAudioBuffer();

    void                                    Initialize();

    SLObjectItf                             mObject;
    SLPlayItf                               mPlay;
    SLAndroidSimpleBufferQueueItf           mBufferQueueInterface;
    SLEffectSendItf                         mEffectSend;
    SLVolumeItf                             mVolumeInterface;
    SLPlaybackRateItf                       mPlaybackRate; //SL_IID_PLAYBACKRATE
    SLPitchItf                              mPitch; //SL_IID_PITCH
    SLRatePitchItf                          mRatePitch; //SL_IID_RATEPITCH

    FSoundInstanceAndroid                   *mInstance;
    FSound                                  *mSound;

    FString                                 mName;

    bool                                    mDidLoad;
};


class FMusicBuffer
{
public:

    FMusicBuffer();
    ~FMusicBuffer();

    void                                    Initialize(const char *pFileName);
    void                                    Play(bool pLoop);

    void                                    Pause();
    void                                    Stop();
    void                                    SetVolume(float pVolume);

    SLObjectItf                             mObject;
    SLPlayItf                               mPlay;
    SLSeekItf                               mSeek;
    SLVolumeItf                             mVolume;

    SLDataSource                            mAudioSrc;

    FString                                 mName;

    bool                                    mDidLoad;
    bool                                    mLooping;

};

class FAudioBufferPool
{
public:

    FAudioBufferPool();
    ~FAudioBufferPool();

    FAudioBuffer                            *GetBuffer();

    void                                    Play(FSoundInstanceAndroid *pInstance, float pVolume);
    void                                    PlayPitched(FSoundInstanceAndroid *pInstance, float pVolume, float pPitch);

    void                                    Finish(FAudioBuffer *pBuffer);
    void                                    HandleError(FAudioBuffer *pBuffer);

    FAudioBuffer                            *mAudioBufferUninitialized[AUDIO_BUFFER_COUNT];
    int                                     mAudioBufferUninitializedCount;

    FAudioBuffer                            *mAudioBufferFinished[AUDIO_BUFFER_COUNT];
    int                                     mAudioBufferFinishedCount;

    FAudioBuffer                            *mAudioBufferPlaying[AUDIO_BUFFER_COUNT];
    int                                     mAudioBufferPoolPlayingCount;


    FAudioBuffer                            *mAudioBufferFailed[AUDIO_BUFFER_COUNT];
    int                                     mAudioBufferPoolFailedCount;
};







class FSoundInstanceAndroid : public FSoundInstance
{
public:
    FSoundInstanceAndroid();
    virtual ~FSoundInstanceAndroid();

    FAudioBuffer                            *mBuffer;

};


class FSoundDataAndroid : public FSoundData
{
public:
    FSoundDataAndroid();
    virtual ~FSoundDataAndroid();

    unsigned char                           *mData;
    int                                     mDataLength;
};

static FAudioBufferPool cEffectPool;




//Must be called before all other sound functions. (For OpenAL at least)

int GetFileDescriptor(const char *pFileName, off_t &pStartIndex, off_t &pLength);

void EffectBufferCallback(SLAndroidSimpleBufferQueueItf pBufferQueue, void *pContext);

SLmillibel GetMillibels(float pVolume);

void core_sound_initialize();

bool core_sound_load(FSound *pSound, const char *pFileName, int pInstanceCount);

void core_sound_play(FSound *pSound);
void core_sound_play(FSound *pSound, float pVolume=1.0f);
void core_sound_playPitched(FSound *pSound, float pPitch, float pVolume=1.0f);
void core_sound_stop(FSound *pSound);
void core_sound_clear(FSound *pSound);
bool core_sound_isPlaying(FSound *pSound);
bool core_sound_didLoad(FSound *pSound);
void core_sound_setVolume(float pVolume);
float core_sound_getVolume();


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



void core_sound_musicPlay(const char *pFileName, bool pLoop=false);
void core_sound_musicCrossFade(const char *pFileName, int pDurationTicks, bool pLoop);
void core_sound_musicFadeOut(int pDurationTicks);
void core_sound_musicStop();
bool core_sound_musicIsPlaying();
void core_sound_musicSetVolume(float pVolume);
float core_sound_musicGetVolume();

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


