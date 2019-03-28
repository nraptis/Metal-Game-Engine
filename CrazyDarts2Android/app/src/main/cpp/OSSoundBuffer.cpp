//
//  OSSoundBuffer.cpp
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#include <assert.h>

#include "OSSoundBuffer.h"
#include "OSSoundBufferPool.h"
#include "os_core_sound.h"
#include "os_core_includes.h"
#include "core_includes.h"


OSSoundBuffer::OSSoundBuffer() {
    mIsPlaying = false;
    mIsLooping = false;
    mDidFail = false;
    bqPlayerObject = nullptr;
    bqPlayerPlay = nullptr;
    bqPlayerBufferQueue = NULL;
    bqPlayerEffectSend = NULL;
    bqPlayerPlaybackRate = NULL;
    bqPlayerVolume = NULL;
    bqPlaybackRateMin = 1000;
    bqPlaybackRateMax = 1000;
    bqVolumeMax = 2000;
    mSoundInstance = NULL;
    mSoundData = NULL;
    mVolume = 1.0f;
    mPitch = 1.0f;
}

OSSoundBuffer::~OSSoundBuffer() {

}

void BufferCompleteCallback(SLAndroidSimpleBufferQueueItf pBufferQueue, void *pContext) {

    Log("BufferCompleteCallback[%X %X]\n\n", pBufferQueue, pContext);

    gSoundBufferPool.BufferComplete(pBufferQueue);
}

void OSSoundBuffer::SetUp() {
    mDidFail = false;
    mIsPlaying = false;
    mIsLooping = false;
    bqPlayerObject = nullptr;
    bqPlayerPlay = nullptr;
    bqPlayerBufferQueue = nullptr;
    bqPlayerEffectSend = nullptr;
    bqPlayerPlaybackRate = nullptr;
    bqPlayerVolume = NULL;
    bqPlaybackRateMin = 1000;
    bqPlaybackRateMax = 1000;
    mSoundInstance = NULL;
    mSoundData = NULL;
    mVolume = 1.0f;

    if (engineEngine == NULL) {
        Log("OSSoundBuffer::SetUp() - MISSING ENGINE!!!\n\n");
        mDidFail = true;
        return;
    }

    SLresult aResult;

    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    //SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,              //formatType
    //                               2,                              //numChannels
    //                               SL_SAMPLINGRATE_44_1,           //samplesPerSec
    //                               SL_PCMSAMPLEFORMAT_FIXED_16,    //bitsPerSample
    //                               SL_PCMSAMPLEFORMAT_FIXED_16,    //containerSize
    //                               SL_SPEAKER_FRONT_LEFT |
    //                               SL_SPEAKER_FRONT_RIGHT,         //channelMask
    //                               SL_BYTEORDER_LITTLEENDIAN};     //endianness

    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,              //formatType
                                   2,                              //numChannels
                                   SL_SAMPLINGRATE_48,             //samplesPerSec
                                   SL_PCMSAMPLEFORMAT_FIXED_16,    //bitsPerSample
                                   SL_PCMSAMPLEFORMAT_FIXED_16,    //containerSize
                                   SL_SPEAKER_FRONT_LEFT |
                                   SL_SPEAKER_FRONT_RIGHT,         //channelMask
                                   SL_BYTEORDER_LITTLEENDIAN};     //endianness




                                   //

    SLDataSource audioSrc = {&loc_bufq, &format_pcm};

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
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface (SL_IID_PLAY)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE, &bqPlayerBufferQueue);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface (SL_IID_BUFFERQUEUE)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAYBACKRATE, &bqPlayerPlaybackRate);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface (SL_IID_PLAYBACKRATE)\n");
    }

    if (bqPlayerPlaybackRate) {
        SLuint32 aCapa;
        SLpermille aStepSize;
        aResult = (*bqPlayerPlaybackRate)->GetRateRange(bqPlayerPlaybackRate, 0, &bqPlaybackRateMin, &bqPlaybackRateMax, &aStepSize, &aCapa);
        if (aResult != SL_RESULT_SUCCESS) {
            Log("CoreSound::Failed To GetRateRange (%d - %d)\n",
                    (int)bqPlaybackRateMin,
                    (int)bqPlaybackRateMax);
            bqPlaybackRateMin = 1000;
            bqPlaybackRateMax = 1000;
        }
    }

    aResult = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, BufferCompleteCallback, NULL);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To RegisterCallback\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND, &bqPlayerEffectSend);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface(SL_IID_EFFECTSEND)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface(SL_IID_VOLUME)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To SetPlayState(SL_PLAYSTATE_PLAYING)\n");
        mDidFail = true;
        return;
    }

    Log("OSSoundBuffer::SetUp(COMPLETED!!!)\n");
}

void OSSoundBuffer::TearDown() {

}

void OSSoundBuffer::Play(FSoundInstanceAndroid *pSoundInstance,
            FSoundDataAndroid *pSoundData, float pVolume, float pPitch, bool pLoop) {

    mPitch = pPitch;
    mVolume = pVolume;

    pVolume *= gSoundVolume;

    if (pSoundInstance == NULL || pSoundData == NULL || bqPlayerPlay == NULL) {
        mSoundInstance = NULL;
        mSoundData = NULL;
        mIsPlaying = false;
        mIsLooping = false;
    }

    if (pSoundData->mData == NULL || pSoundData->mDataLength <= 0) {
        mSoundInstance = NULL;
        mSoundData = NULL;
        mIsPlaying = false;
        mIsLooping = false;
    }

    pSoundInstance->mSoundBuffer = this;

    mSoundInstance = pSoundInstance;
    mSoundData = pSoundData;

    if (pVolume <= 0.0f) {
        mIsPlaying = false;
        mIsLooping = false;
        return;
    }

    SLresult aResult;
    if (bqPlayerVolume!= NULL) {
        SLmillibel aMillibel = 0;
        if (pVolume >= 1.0f) {

        } else {
            float aInterp = 0.0f;
            aInterp= (float)log2(pVolume + 0.05f);

            float aValueMin = -4.322f;
            float aValueMax = 0.1374;

            aInterp = (aInterp - aValueMin) / (aValueMax - aValueMin);

            float aMin = -4000.0f;
            float aMax = 0.0f;

            int aVolumeUint = aMin + (aMax - aMin) * aInterp;

            aMillibel = aVolumeUint;
            if (aMillibel < -4000) { aMillibel = -4000; }
            if (aMillibel > 0) { aMillibel = 0; }
        }

        aResult = (*(bqPlayerVolume))->SetVolumeLevel((bqPlayerVolume), aMillibel );
        if (aResult != SL_RESULT_SUCCESS) {
            Log("SBB - SetVolumeLevel FAILED =  [%d]\n", (int)aMillibel);
        }
    }

    /*
    if (bqPlayerPlaybackRate != NULL) {
        SLpermille aRate= SLpermille(1000.0f * pPitch);

        if (aRate < bqPlaybackRateMin) { aRate = bqPlaybackRateMin; }
        if (aRate > bqPlaybackRateMax) { aRate = bqPlaybackRateMax; }

        aResult = (*(bqPlayerPlaybackRate))->SetRate((bqPlayerPlaybackRate), aRate);

        int aPitchInt = aRate;
        if (aResult != SL_RESULT_SUCCESS) {
            Log("SBB - SetRate FAILED = [%d] (%f)  [%d to %d]\n", aPitchInt, pPitch, bqPlaybackRateMin, bqPlaybackRateMax);
        }
    }
    */

    aResult = (*bqPlayerBufferQueue)->Clear(bqPlayerBufferQueue);
    if (SL_RESULT_SUCCESS != aResult) {
        Log("SBB - Clear Failed LOL! X_X\n\n\n");

        gSoundBufferPool.BufferComplete(bqPlayerBufferQueue);
        return;
    }

    aResult = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, pSoundData->mData, pSoundData->mDataLength);
    if (SL_RESULT_SUCCESS != aResult) {
        Log("SBB - Enqueue Failed LOL! X_X\n\n\n");


        gSoundBufferPool.BufferComplete(bqPlayerBufferQueue);
        return;

    }

    mIsPlaying = true;
    mIsLooping = pLoop;
}

void OSSoundBuffer::Loop() {
    Play(mSoundInstance, mSoundData, mVolume, mPitch, true);
}

void OSSoundBuffer::Complete() {
    mIsPlaying = false;
    mIsLooping = false;
    if (mSoundInstance) {
        mSoundInstance->mSoundBuffer = NULL;
    }
}

void OSSoundBuffer::Stop() {
    Complete();
    if (bqPlayerBufferQueue) {
        SLresult aResult;
        aResult = (*bqPlayerBufferQueue)->Clear(bqPlayerBufferQueue);
        if (SL_RESULT_SUCCESS != aResult) {
            Log("SBB - Failed \"Clear\"()\n");
            return;
        }
    }
}

bool OSSoundBuffer::IsAvailable() {
    if (mDidFail == false && mIsPlaying == false ) {
        return true;
    }
    return false;
}
