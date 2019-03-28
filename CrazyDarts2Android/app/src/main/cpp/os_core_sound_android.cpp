//
//  os_core_sound.cpp
//  Ghibli
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#include <assert.h>
#include <jni.h>
#include "os_core_sound.h"
#include "os_core_includes.h"
#include "core_includes.h"
#include "FSound.h"
#include "FFile.hpp"

#include "OSSoundBuffer.h"
#include "OSSoundBufferPool.h"

#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>


FSoundInstanceAndroid::FSoundInstanceAndroid() {
    
}

FSoundInstanceAndroid::~FSoundInstanceAndroid() {
    
}

FSoundDataAndroid::FSoundDataAndroid() {
    mData = 0;
    mDataLength = 0;
}

FSoundDataAndroid::~FSoundDataAndroid() {
    
}




// pre-recorded sound clips, both are 8 kHz mono 16-bit signed little endian
static const char hello[] =
#include "hello_clip.h"
;

static const char android[] =
#include "android_clip.h"
;


char *xTextFile;
int xTextFileLength;



// buffer queue player interfaces
static SLObjectItf bqPlayerObject = NULL;
static SLPlayItf bqPlayerPlay = NULL;
static SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue = NULL;
static SLEffectSendItf bqPlayerEffectSend = NULL;
static SLPlaybackRateItf bqPlayerPlaybackRate = NULL;
static SLVolumeItf bqPlayerVolume = NULL;
static SLmilliHertz bqPlayerSampleRate = NULL;
SLpermille bqPlaybackRateMin = 1000;
SLpermille bqPlaybackRateMax = 1000;



// a mutext to guard against re-entrance to record & playback
// as well as make recording and playing back to be mutually exclusive
// this is to avoid crash at situations like:
//    recording is in session [not finished]
//    user presses record button and another recording coming in
// The action: when recording/playing back is not finished, ignore the new request
static pthread_mutex_t  audioEngineLock = PTHREAD_MUTEX_INITIALIZER;

// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;
//static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_DEFAULT;


//#define  \
//{ SL_MILLIBEL_MIN,    0,  1000,   500, SL_MILLIBEL_MIN,  20, SL_MILLIBEL_MIN,  40, 1000,1000 }

// pointer and size of the next player buffer to enqueue, and number of remaining buffers
static short *nextBuffer;
static unsigned nextSize;
static int nextCount;

// this callback handler is called every time a buffer finishes playing
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
    assert(bq == bqPlayerBufferQueue);
    assert(NULL == context);
    // for streaming playback, replace this test by logic to find and fill the next buffer
    if (--nextCount > 0 && NULL != nextBuffer && 0 != nextSize) {
        SLresult aResult;
        // enqueue another buffer
        aResult = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffer, nextSize);
        // the most likely other aResult is SL_RESULT_BUFFER_INSUFFICIENT,
        // which for this code example would indicate a programming error
        if (SL_RESULT_SUCCESS != aResult) {
            pthread_mutex_unlock(&audioEngineLock);
        }
        (void)aResult;
    } else {

        pthread_mutex_unlock(&audioEngineLock);
    }
}



void createBufferQueueAudioPlayer()
{
    SLresult aResult;

    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    //SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_8,
    //        SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
    //        SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN};

    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,              //formatType
                                   2,                              //numChannels
                                   SL_SAMPLINGRATE_44_1,           //samplesPerSec
                                   SL_PCMSAMPLEFORMAT_FIXED_16,    //bitsPerSample
                                   SL_PCMSAMPLEFORMAT_FIXED_16,    //containerSize
                                   SL_SPEAKER_FRONT_LEFT |
                                   SL_SPEAKER_FRONT_RIGHT,         //channelMask
                                   SL_BYTEORDER_LITTLEENDIAN};     //endianness

    SLDataSource audioSrc = {&loc_bufq, &format_pcm};
    
    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    const SLInterfaceID aIDExtended[4] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME, SL_IID_PLAYBACKRATE};
    const SLboolean aReqExtended[4] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_FALSE};

    aResult = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk, 4, aIDExtended, aReqExtended);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;

    aResult = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE, &bqPlayerBufferQueue);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAYBACKRATE, &bqPlayerPlaybackRate);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;

    if (bqPlayerPlaybackRate) {
        SLuint32 aCapa;
        SLpermille aStepSize;
        aResult = (*bqPlayerPlaybackRate)->GetRateRange(bqPlayerPlaybackRate, 0,
                                               &bqPlaybackRateMin, &bqPlaybackRateMax,
                                               &aStepSize, &aCapa);
        assert(SL_RESULT_SUCCESS == aResult);

        Log("Playbacl [%d %d %d]\n", (int)bqPlaybackRateMin, (int)bqPlaybackRateMax, (int)aStepSize);

        //aResult = (*bqPlayerPlaybackRate)->SetPropertyConstraints(bqPlayerPlaybackRate, SL_RATEPROP_PITCHCORAUDIO);


    }



    
    // register callback on the buffer queue
    aResult = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, NULL);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
    
    // get the effect send interface
    bqPlayerEffectSend = NULL;
    if( 0 == bqPlayerSampleRate) {
        aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
                                                 &bqPlayerEffectSend);
        assert(SL_RESULT_SUCCESS == aResult);
        (void)aResult;
    }


    // get the volume interface
    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
    
    // set the player's state to playing
    aResult = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
}


void sound_initialize() {


    FFile aFile;
    aFile.Load("magic_woosh.wav");



    xTextFileLength = aFile.mLength;

    xTextFile = new char[xTextFileLength + 1];
    for (int i=0;i<aFile.mLength;i++) {
        xTextFile[i] = aFile.mData[i];
    }

    Log("Loaded MAGIC WOOSH: %d\n", xTextFileLength);

//





    Log("sound_initialize(0)\n");


    SLresult aResult;
    
    // create engine
    aResult = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
    
    // realize the engine
    aResult = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
    
    // get the engine interface, which is needed in order to create other objects
    aResult = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
    
    // create output mix, with environmental reverb specified as a non-required interface
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    aResult = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
    
    // realize the output mix
    aResult = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == aResult);
    (void)aResult;
    
    // get the environmental reverb interface
    // this could fail if the environmental reverb effect is not available,
    // either because the feature is not present, excessive CPU load, or
    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
    aResult = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
                                              &outputMixEnvironmentalReverb);
    if (SL_RESULT_SUCCESS == aResult) {
        aResult = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
                                                                                   outputMixEnvironmentalReverb, &reverbSettings);
        (void)aResult;
    }
    // ignore unsuccessful aResult codes for environmental reverb, as it is optional for this example
    
    //
    //createBufferQueueAudioPlayer(48000, 960);

    createBufferQueueAudioPlayer();


}

bool sound_load(FSound *pSound, const char *pFileName, int pInstanceCount) {
    Log("Loading Sound [%s]\n", pFileName);

    if (pInstanceCount <= 0) pInstanceCount = 1;
    if (pInstanceCount > 10) pInstanceCount = 10;
    int aLoadedInstanceCount = 0;

    if (pSound != 0) {
        FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)pSound->mSoundData;
        if (aSoundData) {

            FFile aFile;
            aFile.Load(pFileName);

            if (aFile.mLength > 0) {
                aSoundData->mData = new unsigned char [aFile.mLength];
                memcpy(aSoundData->mData, aFile.mData, aFile.mLength);

                aSoundData->mDataLength = aFile.mLength;

                pSound->mDidLoad = true;

                Log("SOUND [%s] LENGTH = [%d] INST[%d]\n", pFileName, aSoundData->mDataLength, pInstanceCount);

                for (int i=0;i<pInstanceCount;i++) {
                    FSoundInstanceAndroid *aInstance = new FSoundInstanceAndroid();
                    aInstance->mDidLoad = true;
                    aInstance->mSound = pSound;
                    pSound->mInstances += aInstance;

                }

                return true;
            }
        }
    }
    return false;
}

void sound_play(FSound *pSound) {
    
}

void sound_play(FSound *pSound, float pVolume) {
    
}

void sound_playPitched(FSound *pSound, float pPitch, float pVolume) {
    
    Log("sound_playPitched(Enter)[%s]\n", pSound->mFileName.c());
    if (pSound) {
        
        
    }


    int which = 2;
    int count = 1;

    if (pthread_mutex_trylock(&audioEngineLock)) {
        // If we could not acquire audio engine lock, reject this request and client should re-try
        Log("NIXON FAILS\n\n\n\n");
        return;
    }


    nextBuffer = (short*)xTextFile;
    nextSize  = xTextFileLength;



    if (pSound) {
        Log("core_sound_playPitched(1)[%s]\n", pSound->mFileName.c());
        FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)(pSound->mSoundData);
        if ((pSound->mDidLoad == true) && (aSoundData != 0)) {
            Log("core_sound_playPitched(2)[%s]\n", pSound->mFileName.c());
            FSoundInstanceAndroid *aInstanceCheck = (FSoundInstanceAndroid *)(pSound->mInstances.Fetch(0));
            if (aInstanceCheck) {
                Log("core_sound_playPitched(3)[%s]\n", pSound->mFileName.c());
                FSoundInstanceAndroid *aInstancePlay = 0;
                if (sound_instance_isPlaying((FSoundInstanceAndroid *)aInstanceCheck) == false) {
                    Log("core_sound_playPitched(4)[%s]\n", pSound->mFileName.c());
                    aInstancePlay = aInstanceCheck;
                    pSound->mInstances.RotateFrontToBack();
                } else {
                    EnumList (FSoundInstanceAndroid, aInstance, pSound->mInstances) {
                        if (sound_instance_isPlaying((FSoundInstanceAndroid *)aInstance) == false) {
                            Log("core_sound_playPitched(HIT)[%s]\n", pSound->mFileName.c());
                            aInstancePlay = aInstance;
                        }
                    }
                }
                if (aInstancePlay) {


                    nextBuffer = (short*)aSoundData->mData;
                    nextSize  = aSoundData->mDataLength;

                    Log("core_sound_playPitched(FINAL)[%s]\n", pSound->mFileName.c());
                    //cEffectPool.Play(aInstancePlay, pVolume);

                    Log("CS: Sound Final Buff[%x]\n", aInstancePlay);
                }
            }
        }
    }






    nextCount = count;
    if (nextSize > 0) {

        SLresult aResult;

        Log("bqPlayerPlaybackRate = %x\n", bqPlayerPlaybackRate);

        if (bqPlayerPlaybackRate != NULL) {
            SLpermille aRate= SLpermille(1000.0f * pPitch);

            if (aRate < bqPlaybackRateMin) { aRate = bqPlaybackRateMin; }
            if (aRate > bqPlaybackRateMax) { aRate = bqPlaybackRateMax; }

            aResult = (*(bqPlayerPlaybackRate))->SetRate((bqPlayerPlaybackRate), aRate);

            int aPitchInt = aRate;
            if (aResult != SL_RESULT_SUCCESS) {
                Log("Pitch FAILED = [%d] (%f)  [%d to %d]\n", aPitchInt, pPitch, bqPlaybackRateMin, bqPlaybackRateMax);
            } else {
                Log("Pitch SUCCEEDED= [%d] (%f)  [%d to %d]\n", aPitchInt, pPitch, bqPlaybackRateMin, bqPlaybackRateMax);
            }
        }

        // here we only enqueue one buffer because it is a long clip,
        // but for streaming playback we would typically enqueue at least 2 buffers to start

        aResult = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffer, nextSize);
        if (SL_RESULT_SUCCESS != aResult) {
            pthread_mutex_unlock(&audioEngineLock);
            Log("Failed @ CLip LOOOL!\n\n\n");
            
            return ;
        }
        
        Log("WINNING @ CLip LOOOL!\n\n\n");
    } else {
        pthread_mutex_unlock(&audioEngineLock);
    }
    
    Log("We played any sound? LOL!!\n\n\n");
    
    
    
    
    Log("sound_playPitched(Exit)[%s]\n", pSound->mFileName.c());
}

void sound_loop(FSound *pSound, float pVolume) {
    Log("sound_loop(Enter)[%s]\n", pSound->mFileName.c());
    if (pSound) {
        
        
    }
    Log("sound_loop(Exit)[%s]\n", pSound->mFileName.c());
}

void sound_loopPitched(FSound *pSound, float pPitch, float pVolume) {
    Log("sound_loopPitched(Enter)[%s]\n", pSound->mFileName.c());
    if (pSound) {
        
        
    }
    Log("sound_loopPitched(Exit)[%s]\n", pSound->mFileName.c());
}

void sound_stop(FSound *pSound) {
    
    
}

void sound_clear(FSound *pSound) {
    
    
}

bool sound_isPlaying(FSound *pSound) {
    bool aReturn = false;
    if (pSound) {
        EnumList(FSoundInstance, aInstance, pSound->mInstances) {
            if (sound_instance_isPlaying(aInstance)) {
                aReturn = true;
                break;
            }
        }
    }
    return aReturn;
}

bool sound_didLoad(FSound *pSound) {
    bool aReturn = false;
    if (pSound) {
        EnumList(FSoundInstance, aInstance, pSound->mInstances) {
            if (aInstance->mDidLoad == true) {
                aReturn = true;
            }
        }
    }
    return aReturn;
}

void sound_setVolume(float pVolume) {
    gSoundVolume = pVolume;
}

float sound_getVolume() {
    return gSoundVolume;
}

void sound_instance_play(FSoundInstance *pInstance, float pVolume) {
    
    
    
}

void sound_instance_resetPitch(FSoundInstance *pInstance) {
    
}

void sound_instance_setPitch(FSoundInstance *pInstance, float pPitch) {
    
}

void sound_instance_setVolume(FSoundInstance *pInstance, float pVolume) {
    
}

void sound_instance_pause(FSoundInstance *pInstance) {
    
}

void sound_instance_unpause(FSoundInstance *pInstance) {
    
}

void sound_instance_loop(FSoundInstance *pInstance, float pVolume) {
    
}

void sound_instance_stop(FSoundInstance *pInstance) {
    
}

bool sound_instance_isPlaying(FSoundInstance *pInstance) {
    bool aReturn = false;
    
    return aReturn;
}

void sound_instance_destroy(FSoundInstance *pInstance) {
    
}

void sound_stopAll() {
    
}

void sound_stopAllEffects()  {
    
}

FSoundData *sound_spawn_data()  {
    return new FSoundDataAndroid();
}

void sound_unloadEffects()  {
    
}

void sound_reloadEffects()  {
    
}

void sound_update() {
    
}

void sound_active()  {
    music_resume();
}

void sound_inactive()  {
    music_pause();
}





