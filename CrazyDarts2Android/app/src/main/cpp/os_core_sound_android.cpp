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

#include "FSound.h"
#include "core_includes.h"

// engine interfaces

//sAudiosAudioEngineObject = NULL;
//static SLEngineItf sAudioEngine;


static SLObjectItf sAudioEngineObject = NULL;
static SLEngineItf sAudioEngine;

// output mix interfaces
static SLObjectItf outputMixObject = NULL;
static SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;


// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

static FMusicBuffer *cMusicBuffer = 0;
static FMusicBuffer *cMusicBufferFading = 0;

static FList cMusicBufferList;
//FMusicBuffer


#define VOLUME_RANGE 2000.0f
SLmillibel GetMillibels(float pVolume)
{


    int aMillibels = (pVolume * VOLUME_RANGE) - VOLUME_RANGE;

    if(aMillibels < (-VOLUME_RANGE))aMillibels = (-VOLUME_RANGE);
    if(aMillibels > 0)aMillibels = 0;

    //SLmillibel aReturn = (SLmillibel)aMillibels;

    return (SLmillibel)aMillibels;
}

FAudioBuffer::FAudioBuffer()
{
    mObject = 0;

    mInstance = 0;
    mSound = 0;

    mDidLoad = false;
}

FAudioBuffer::~FAudioBuffer()
{

}

void FAudioBuffer::Initialize()
{
    SLresult aResult;

    //SL_SAMPLINGRATE_44_1, SL_PCMSAMPLEFORMAT_FIXED_16
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 2, SL_SAMPLINGRATE_44_1, SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16, SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT, SL_BYTEORDER_LITTLEENDIAN};

    SLDataSource audioSrc = {&loc_bufq, &format_pcm};
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    const SLInterfaceID aIDExtended[6] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME, SL_IID_PLAYBACKRATE, SL_IID_RATEPITCH, SL_IID_PITCH};
    const SLboolean aReqExtended[6] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_FALSE, SL_BOOLEAN_FALSE, SL_BOOLEAN_FALSE};

    aResult = (*sAudioEngine)->CreateAudioPlayer(sAudioEngine, &mObject, &audioSrc, &audioSnk, 6, aIDExtended, aReqExtended);

    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("\n\n#####\nFAIL INIT WITH RATE AND RATEPITCH\n\n######\n");


        const SLInterfaceID aIDBase[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME};
        const SLboolean aReqBase[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
        aResult = (*sAudioEngine)->CreateAudioPlayer(sAudioEngine, &mObject, &audioSrc, &audioSnk, 3, aIDBase, aReqBase);

        if(aResult != SL_RESULT_SUCCESS)
        {
            Log("Failed To Init Buffer11\n");
            return;
        }
    }


    //FAudioBuffer                            *mAudioBufferFailed[AUDIO_BUFFER_COUNT];
    //int                                     mAudioBufferPoolFailedCount;


    //assert(SL_RESULT_SUCCESS == result);

    aResult = (*mObject)->Realize(mObject, SL_BOOLEAN_FALSE);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To [Realize]\n");
        return;
    }

    aResult = (*mObject)->GetInterface(mObject, SL_IID_PLAY, &mPlay);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To Extract [SL_IID_PLAY]\n");
        return;
    }

    aResult = (*mObject)->GetInterface(mObject, SL_IID_BUFFERQUEUE, &mBufferQueueInterface);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To Extract [SL_IID_BUFFERQUEUE]\n");
        return;
    }

    aResult = (*mBufferQueueInterface)->RegisterCallback(mBufferQueueInterface, EffectBufferCallback, this);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To [RegisterCallback]\n");
        return;
    }

    aResult = (*mObject)->GetInterface(mObject, SL_IID_EFFECTSEND, &mEffectSend);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To Extract [SL_IID_EFFECTSEND]\n");
        return;
    }

    aResult = (*mObject)->GetInterface(mObject, SL_IID_PLAYBACKRATE, &mPlaybackRate);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To Extract [SL_IID_PLAYBACKRATE]\n");
    }

    /*
    aResult = (*mObject)->GetInterface(mObject, SL_IID_PITCH, &mPitch);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To Extract [SL_IID_PITCH]\n");
    }

    aResult = (*mObject)->GetInterface(mObject, SL_IID_RATEPITCH, &mRatePitch);
    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Sound - Failed To Extract [SL_IID_RATEPITCH]\n");
    }
    */




    //SLPitchItf                              mPitch; //
    //SLRatePitchItf                          ; //
    //SLPlaybackRateItf                       ; //




    //SLPitchItf                              mPitch; //SL_IID_PITCH
    //SLRatePitchItf                          mRatePitch; //SL_IID_RATEPITCH




    //result = (*mObject)->GetInterface(mObject, SL_IID_MUTESOLO, &mMuteSoloInterface);
    //assert(SL_RESULT_SUCCESS == result);

    aResult = (*mObject)->GetInterface(mObject, SL_IID_VOLUME, &mVolumeInterface);
    //assert(SL_RESULT_SUCCESS == result);

    //aResult = (*mPlay)->SetPlayState(mPlay, SL_PLAYSTATE_PLAYING);
    //assert(SL_RESULT_SUCCESS == result);

    mDidLoad = true;
}


FAudioBufferPool::FAudioBufferPool()
{
    mAudioBufferUninitializedCount = AUDIO_BUFFER_COUNT;
    for(int i=0;i<AUDIO_BUFFER_COUNT;i++)
    {
        mAudioBufferUninitialized[i] = new FAudioBuffer();
        mAudioBufferUninitialized[i]->mName = FString("Android BUFFER [") + FString((i + 1)) + FString("]");
    }

    for(int i=0;i<AUDIO_BUFFER_COUNT;i++)
    {
        mAudioBufferFinished[i] = 0;
        mAudioBufferPlaying[i] = 0;
        mAudioBufferFailed[i] = 0;
    }

    mAudioBufferFinishedCount = 0;
    mAudioBufferPoolPlayingCount = 0;
    mAudioBufferPoolFailedCount = 0;

}

FAudioBufferPool::~FAudioBufferPool()
{

}


FAudioBuffer *FAudioBufferPool::GetBuffer()
{
    FAudioBuffer *aReturn = 0;

    if(mAudioBufferFinishedCount > 0)
    {
        aReturn = mAudioBufferFinished[mAudioBufferFinishedCount - 1];
        mAudioBufferFinishedCount--;
    }
    else if(mAudioBufferUninitializedCount > 0)
    {
        aReturn = mAudioBufferUninitialized[mAudioBufferUninitializedCount - 1];
        mAudioBufferUninitializedCount--;

        aReturn->Initialize();

        if(aReturn->mDidLoad == false)
        {
            mAudioBufferFailed[mAudioBufferPoolFailedCount] = aReturn;
            mAudioBufferPoolFailedCount++;

            aReturn = 0;
        }

    }

    return aReturn;
}

void FAudioBufferPool::Play(FSoundInstanceAndroid *pInstance, float pVolume)
{
    PlayPitched(pInstance, pVolume, 1.0f);

    /*
    if(pInstance)
    {
        FSound *aSound = (pInstance->mSound);

        if(aSound)
        {
            FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)(aSound->mSoundData);

            Log("Playing Audio Buffer[%x %x]\n", (void *)aSound, (void *)aSoundData);

            if((aSound != 0) && (aSoundData != 0))
            {
                FAudioBuffer *aBuffer = GetBuffer();

                if(aBuffer)
                {
                    aBuffer->mInstance = pInstance;

                    SLresult aResult;

                    aResult = (*(aBuffer->mBufferQueueInterface))->Enqueue((aBuffer->mBufferQueueInterface), aSoundData->mData, aSoundData->mDataLength);

                    if(aResult != SL_RESULT_SUCCESS)
                    {
                        Log("Failed to Enqueue Sound [%s]\n", aSound->mFileName.c());
                        HandleError(aBuffer);
                        return;
                    }


                }
            }
        }
    }
    */

}

/*
void applyParameters(bool isLooping, float pitch, float pan, float gain, float effectsVolume)
{
    SLresult result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, (SLboolean) isLooping, 0, SL_TIME_UNKNOWN);
    assert(SL_RESULT_SUCCESS == result);

    SLpermille stereo = SLpermille(1000 * pan);
    result = (*fdPlayerVolume)->EnableStereoPosition(fdPlayerVolume, SL_BOOLEAN_TRUE);
    assert(SL_RESULT_SUCCESS == result);
    result = (*fdPlayerVolume)->SetStereoPosition(fdPlayerVolume, stereo);
    assert(SL_RESULT_SUCCESS == result);

    SLpermille playbackRate = SLpermille(1000 * pitch);
    if (fdPlaybackRate)
        result = (*fdPlaybackRate)->SetRate(fdPlaybackRate, playbackRate);
    assert(SL_RESULT_SUCCESS == result);

    _gain = gain;
    applyEffectsVolume(effectsVolume);
}
*/


void FAudioBufferPool::PlayPitched(FSoundInstanceAndroid *pInstance, float pVolume, float pPitch)
{

    if(pInstance)
    {
        FSound *aSound = (pInstance->mSound);

        if(aSound)
        {
            FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)(aSound->mSoundData);

            Log("Playing Audio Buffer 01 [%x %x]\n", (void *)aSound, (void *)aSoundData);

            if((aSound != 0) && (aSoundData != 0))
            {
                Log("Playing Audio Buffer 02 [%x %x]\n", (void *)aSound, (void *)aSoundData);
                FAudioBuffer *aBuffer = GetBuffer();

                if((aBuffer != 0) && (aSound->mDidLoad == true))
                {
                    Log("Playing Audio Buffer 03 [%x %x]\n", (void *)aSound, (void *)aSoundData);
                    aBuffer->mInstance = pInstance;

                    SLresult aResult;

                    if(aBuffer->mBufferQueueInterface)
                    {
                        Log("Playing Audio Buffer 04 [%x %x]\n", (void *)aSound, (void *)aSoundData);

                        if(aBuffer->mPlaybackRate != 0)
                        {
                            Log("Playing Audio Buffer 05 [%x %x]\n", (void *)aSound, (void *)aSoundData);
                            SLpermille playbackRate = SLpermille(1000.0f * pPitch);
                            aResult = (*(aBuffer->mPlaybackRate))->SetRate((aBuffer->mPlaybackRate), playbackRate);

                            int aPitchInt = playbackRate;

                            if(aResult != SL_RESULT_SUCCESS)
                            {
                                Log("Pitch FAILED = [%d] (%f)\n", aPitchInt, pPitch);
                            }
                            else
                            {
                                Log("Pitch WINNEDDDDDDSDSD = [%d] (%f)\n", aPitchInt, pPitch);
                            }

                        }

                        aResult = (*(aBuffer->mBufferQueueInterface))->Enqueue((aBuffer->mBufferQueueInterface), aSoundData->mData, aSoundData->mDataLength);

                        if(aResult != SL_RESULT_SUCCESS)
                        {
                            Log("Failed to Enqueue Sound [%s]\n", aSound->mFileName.c());
                            HandleError(aBuffer);
                            return;
                        }


                    }


                }
            }
        }
    }
}

void FAudioBufferPool::Finish(FAudioBuffer *pBuffer)
{
    if(pBuffer)
    {
        //Log("Audio Pool - Finished Buffer Is [%s]\n", pBuffer->mName.c());
        //Log("Finished Sound [%s]\n", pBuffer->mInstance->mSound->mFileName.c());

        FSoundInstanceAndroid *aInstance = pBuffer->mInstance;

        if(aInstance)
        {
            aInstance->mBuffer = 0;
        }

        mAudioBufferFinished[mAudioBufferFinishedCount] = pBuffer;
        mAudioBufferFinishedCount++;
    }
}

void FAudioBufferPool::HandleError(FAudioBuffer *pBuffer)
{

}


FMusicBuffer::FMusicBuffer()
{
    mDidLoad = false;
    mObject = 0;
}

FMusicBuffer::~FMusicBuffer()
{

}

void FMusicBuffer::Initialize(const char *pFileName)
{
    mName = pFileName;
    mName.RemoveExtension();

    FString aPath = mName + FString(".mp3");
    Log("Audio Buffer Init[%s]\n", aPath.c());


    off_t aStartIndex, aLength;
    int aFileDescriptor = GetFileDescriptor(aPath.c(), aStartIndex, aLength);

    //aPath
    if(aFileDescriptor == -1)
    {
        Log("***---\nFAILED PLAY MUSIC!! [%s]\n***---\n", pFileName);


        return;
    }

    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, aFileDescriptor, aStartIndex, aLength};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    mAudioSrc.pLocator = &loc_fd;
    mAudioSrc.pFormat = &format_mime;




    SLresult aResult;


    // create output mix
    //const SLInterfaceID aOutputMixID[1] = {SL_IID_ENVIRONMENTALREVERB};
    //const SLboolean aOutputMixReq[1] = {SL_BOOLEAN_FALSE};

    //aResult = (*sAudioEngine)->CreateOutputMix(sAudioEngine, &(player->mOutputMix), 1, aOutputMixID, aOutputMixReq);
    //if(aResult != SL_RESULT_SUCCESS)Log("Create - CreateOutputMix FAIL -  SL_BOOLEAN_FALSE\n");

    //aResult = (*(player->mOutputMix))->Realize(player->mOutputMix, SL_BOOLEAN_FALSE);
    //if(aResult != SL_RESULT_SUCCESS)Log("Create - REALIZE OUTPUT MIX FAIL -  SL_BOOLEAN_FALSE\n");



    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    //SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, sOutputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player



    //sAudiosAudioEngineObject = NULL;
    //static SLEngineItf sAudioEngine;


    //const SLInterfaceID ids[3] = {getInterfaceID("SL_IID_SEEK"), getInterfaceID("SL_IID_MUTESOLO"), getInterfaceID("SL_IID_VOLUME")};
    //const SLInterfaceID ids[4] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE, SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    //const SLboolean req[4] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

    //const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    //const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

    aResult = (*sAudioEngine)->CreateAudioPlayer(sAudioEngine, &mObject, &mAudioSrc, &audioSnk, 3, ids, req);
    //aResult = (*sAudioEngine)->CreateAudioPlayer(sAudioEngine, &mObject, &mAudioSrc, &audioSnk, 0, 0, 0);

    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("~~~~@@@@@ --- AudioPlayerSource FAIL -  CreateAudioPlayer\n");

        //(*(pPlayer->mObject))->AbortAsyncOperation(pPlayer->mObject);
        //aResult =
        //(*(pPlayer->mObject))->Destroy(pPlayer->mObject);

        return;
    }

    // realize the player
    aResult = (*mObject)->Realize(mObject, SL_BOOLEAN_FALSE);
    if(aResult != SL_RESULT_SUCCESS)Log("AudioPlayerSource FAIL -  SL_BOOLEAN_FALSE\n");

    // get the play interface
    aResult = (*mObject)->GetInterface(mObject, SL_IID_PLAY, &mPlay);
    if(aResult != SL_RESULT_SUCCESS)Log("AudioPlayerSource FAIL -  SL_IID_PLAY\n");

    aResult = (*mObject)->GetInterface(mObject, SL_IID_VOLUME, &mVolume);
    if(aResult != SL_RESULT_SUCCESS)Log("AudioPlayerSource FAIL -  SL_IID_VOLUME\n");


    aResult = (*mObject)->GetInterface(mObject, SL_IID_SEEK, &mSeek);
    if(aResult != SL_RESULT_SUCCESS)Log("AudioPlayerSource FAIL - SL_IID_SEEK\n");



    /*

    SLresult aResult;
    JNIEnv *aEnv = os_getJNIEnv();

    if(aEnv == 0)
    {
        Log("Create URI Playa Failed!! no Env!!\n");
        return;
    }

    // convert Java string to UTF-8
    //const char *utf8 = (*aEnv)->GetStringUTFChars(aEnv, uri, NULL);
    //const char *utf8 = aEnv->GetStringUTFChars(uri, NULL);
    //assert(NULL != utf8);

    SLDataLocator_URI loc_uri = {SL_DATALOCATOR_URI, (SLchar *)(aPath.c())};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_uri, &format_mime};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    aResult = (*sAudioEngine)->CreateAudioPlayer(sAudioEngine, &uriPlayerObject, &audioSrc, &audioSnk, 3, ids, req);

    //aEnv->ReleaseStringUTFChars(uri, utf8);

    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Music Player Failed Initialize - CreateAudioPlayer");
    }

    // note that an invalid URI is not detected here, but during prepare/prefetch on Android,
    // or possibly during Realize on other platforms
    //assert(SL_RESULT_SUCCESS == result);

    // realize the player
    aResult = (*uriPlayerObject)->Realize(uriPlayerObject, SL_BOOLEAN_FALSE);

    if(aResult != SL_RESULT_SUCCESS)
    {
        Log("Music Player Failed Initialize - uriPlayerObject");

        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;

        return;
    }

    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_PLAY, &uriPlayerPlay);
    if(aResult != SL_RESULT_SUCCESS)Log("Music Player Failed Initialize - uriPlayerPlay");

    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_SEEK, &uriPlayerSeek);
    if(aResult != SL_RESULT_SUCCESS)Log("Music Player Failed Initialize - uriPlayerSeek");

    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_MUTESOLO, &uriPlayerMuteSolo);
    if(aResult != SL_RESULT_SUCCESS)Log("Music Player Failed Initialize - uriPlayerMuteSolo");

    aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_VOLUME, &uriPlayerVolume);
    if(aResult != SL_RESULT_SUCCESS)Log("Music Player Failed Initialize - uriPlayerVolume");

    */


    Log("***\n****\n*****\nMUSIC SUCCESSFULLY LOADED!\n*****\n****\n***");


    mDidLoad = true;

}


void FMusicBuffer::Play(bool pLoop)
{
    Log("Music Buffer Playing [%s] Did Load[%d]\n", mName.c(), mDidLoad);

    mLooping = pLoop;

    if(mDidLoad == true)
    {
        SLresult aResult;

        //aResult = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_PLAY, &uriPlayerPlay);

        if(mSeek != 0)
        {
            aResult = (*mSeek)->SetLoop(mSeek, (SLboolean)mLooping, 0, SL_TIME_UNKNOWN);
            //assert(SL_RESULT_SUCCESS == result);
        }

        //aResult = (*(mPlay))->SetPlayState(mPlay, SL_PLAYSTATE_STOPPED);
        aResult = (*(mPlay))->SetPlayState(mPlay, SL_PLAYSTATE_PLAYING);







    }
    else

    {
        Log("Can't Play [%s] Didn't Load properly!\n\n", mName.c());
    }
}



void FMusicBuffer::Pause()
{
    if(mDidLoad == true)
    {
        SLresult aResult;
        aResult = (*(mPlay))->SetPlayState(mPlay, SL_PLAYSTATE_PAUSED);
    }
}

void FMusicBuffer::Stop()
{
    if(mDidLoad == true)
    {
        SLresult aResult;
        aResult = (*(mPlay))->SetPlayState(mPlay, SL_PLAYSTATE_STOPPED);
    }
}

void FMusicBuffer::SetVolume(float pVolume)
{
    SLresult aResult;

    Log("Music Buffer Set Volume! [%f]\n", pVolume);

    if(mVolume)
    {
        /*
        SLmillibel aMaxVolumeMillibels;
        aResult = (*mVolume)->GetMaxVolumeLevel(mVolume, &aMaxVolumeMillibels);

        int aMaxVolume = aMaxVolumeMillibels;

        Log("Max Volume = %d\n", aMaxVolume);



        SLmillibel aVolumeMillibels;
        aResult = (*mVolume)->GetVolumeLevel(mVolume, &aVolumeMillibels);

        int aVolume = aVolumeMillibels;

        Log("Cur Volume = %d\n", aVolume);
        */

        SLmillibel aMillibels = GetMillibels(pVolume);
        aResult = (*mVolume)->SetVolumeLevel(mVolume, aMillibels);

        if(aResult != SL_RESULT_SUCCESS)
        {
            Log("FAILED TO SET VOLUME!!!!!\n");
        }

    }
}




int GetFileDescriptor(const char *pFileName, off_t &pStartIndex, off_t &pLength)
{
    int aReturn = -1;

    //pStartIndex = 0;
    //pLength = 0;

    jmethodID aMethodID = 0;
    if ((gJVM != 0) && (pFileName != 0)) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        jclass aClass = os_getClassID(aEnv);

        if((aEnv != 0) && (aClass != 0))
        {
            aMethodID = aEnv->GetMethodID(aClass, "getAssetManager", "()Landroid/content/res/AssetManager;");
            if(aMethodID)
            {
                bool aLoadedFirstTry = false;
                jobject aAssetManagerObject = aEnv->CallObjectMethod(_objJNIHelper, aMethodID);

                if(aAssetManagerObject != 0)
                {
                    AAssetManager *aAssetManager = AAssetManager_fromJava(aEnv, aAssetManagerObject);
                    if(aAssetManager != 0)
                    {
                        AAsset* aAsset = AAssetManager_open(aAssetManager, pFileName, AASSET_MODE_UNKNOWN);

                        if(aAsset != 0)
                        {
                            int aFileDescriptor = AAsset_openFileDescriptor(aAsset, &pStartIndex, &pLength);

                            AAsset_close(aAsset);
                            if(aFileDescriptor != -1)
                            {
                                aReturn = aFileDescriptor;
                            }
                            else
                            {
                                pLength = 0;
                                pStartIndex = 0;
                            }
                        }
                    }
                }
            }
        }
        if (aDetach) {
            gJVM->DetachCurrentThread();
        }
    }

    return aReturn;
}


void EffectBufferCallback(SLAndroidSimpleBufferQueueItf pBufferQueue, void *pContext)
{
    Log("EffectBufferCallback()!!\n");

    FAudioBuffer *aBuffer = (FAudioBuffer *)pContext;

    if(aBuffer)
    {
        Log("Finished Buffer Is [%s]\n", aBuffer->mName.c());

        cEffectPool.Finish(aBuffer);
    }
}



FSoundInstanceAndroid::FSoundInstanceAndroid()
{
    mBuffer = 0;
}

FSoundInstanceAndroid::~FSoundInstanceAndroid()
{

}



FSoundDataAndroid::FSoundDataAndroid()
{
    mData = 0;
    mDataLength = 0;
}

FSoundDataAndroid::~FSoundDataAndroid()
{

}

// shut down the native audio system
void shutdown()
{
    if(outputMixObject != NULL)
    {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = NULL;
        outputMixEnvironmentalReverb = NULL;
    }

    // destroy engine object, and invalidate all associated interfaces
    if (sAudioEngineObject != NULL) {
        (*sAudioEngineObject)->Destroy(sAudioEngineObject);
        sAudioEngineObject = NULL;
        sAudioEngine = NULL;
    }

}


void core_sound_initialize()
{
    Log("core_sound_initialize(0)\n");

    SLresult aResult;

    // create engine
    Log("core_sound_initialize(1)\n");
    aResult = slCreateEngine(&sAudioEngineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == aResult);

    Log("core_sound_initialize(2)\n");
    aResult = (*sAudioEngineObject)->Realize(sAudioEngineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == aResult);

    Log("core_sound_initialize(3)\n");
    aResult = (*sAudioEngineObject)->GetInterface(sAudioEngineObject, SL_IID_ENGINE, &sAudioEngine);
    assert(SL_RESULT_SUCCESS == aResult);

    Log("core_sound_initialize(4)\n");
    //const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};

    Log("core_sound_initialize(5)\n");
    aResult = (*sAudioEngine)->CreateOutputMix(sAudioEngine, &outputMixObject, 1, ids, req);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("SL Result: %d\n", aResult);
    }

    Log("core_sound_initialize(6)\n");
    aResult = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("SL Result: %d\n", aResult);
    }

    Log("core_sound_initialize(7)\n");
    aResult = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB, &outputMixEnvironmentalReverb);

    if(SL_RESULT_SUCCESS == aResult)
    {
        Log("core_sound_initialize(8)\n");
        aResult = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(outputMixEnvironmentalReverb, &reverbSettings);

        //(void)result;
    }
    else
    {
        Log("FAIL AT SOUND INIT!!\n");
    }
}

bool core_sound_load(FSound *pSound, const char *pFileName, int pInstanceCount) {
    Log("Loading Sound [%s]\n", pFileName);

    if(pInstanceCount <= 0)pInstanceCount = 1;
    if(pInstanceCount > 10)pInstanceCount = 10;
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
                    aInstance->mSound = pSound;
                    pSound->mInstances += aInstance;

                }

                return true;
            }



            /*
            jmethodID aMethodID = 0;

            bool aDetach = false;
            JNIEnv *aEnv = os_getJNIEnv(&aDetach);
            jclass aClass = os_getClassID(aEnv);

            if((pFileName != 0) && (aEnv != 0) && (aClass != 0))
            {
                aMethodID = aEnv->GetMethodID(aClass, "getAssetManager", "()Landroid/content/res/AssetManager;");
                if(aMethodID)
                {
                    jobject aAssetManagerObject = aEnv->CallObjectMethod(_objJNIHelper, aMethodID);

                    if(aAssetManagerObject != 0)
                    {
                        AAssetManager *aAssetManager = AAssetManager_fromJava(aEnv, aAssetManagerObject);
                        if(aAssetManager != 0)
                        {
                            AAsset* aAsset = AAssetManager_open(aAssetManager, pFileName, AASSET_MODE_UNKNOWN);

                            if(aAsset != 0)
                            {
                                off_t aStartIndex, aFileLength;
                                int aFileDescriptor = AAsset_openFileDescriptor(aAsset, &aStartIndex, &aFileLength);

                                //AAsset_close(aAsset);

                                if(aFileDescriptor != -1)// && (pLength > 0))
                                {

                                    if(aFileLength <= 0)
                                    {
                                        Log("SOUND FAIL 1 - [%s]\n", pFileName);

                                        AAsset_close(aAsset);
                                        if (aDetach) {
                                            gJVM->DetachCurrentThread();
                                        }
                                        return false;
                                    }

                                    //Log("Descriptor[%s] = [%d Descriptor] [%d Start]\n", pFileName, (int)aFileDescriptor, (int)aStartIndex);

                                    void *aFileData = (void *)AAsset_getBuffer(aAsset);
                                    aFileLength = AAsset_getLength(aAsset);

                                    if(aFileLength <= 0)
                                    {
                                        //Log("SOUND FAIL 2 - [%s]\n", pFileName);

                                        AAsset_close(aAsset);
                                        if (aDetach) {
                                            gJVM->DetachCurrentThread();
                                        }
                                        return false;
                                    }

                                    aSoundData->mData = new unsigned char [aFileLength];
                                    memcpy(aSoundData->mData, aFileData, aFileLength * sizeof(char));

                                    aSoundData->mDataLength = aFileLength;

                                    pSound->mDidLoad = true;

                                    Log("SOUND [%s] LENGTH = [%d]\n", pFileName, aSoundData->mDataLength);

                                    AAsset_close(aAsset);

                                    aDidLoad = true;

                                    for(int i=0;i<pInstanceCount;i++)
                                    {

                                        FSoundInstanceAndroid *aInstance = new FSoundInstanceAndroid();
                                        aInstance->mSound = pSound;
                                        pSound->mInstances += aInstance;

                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (aDetach) {
                gJVM->DetachCurrentThread();
            }
            */

        }
    }
    return false;
}

void core_sound_play(FSound *pSound) {
    core_sound_play(pSound, 1.0f);
}

void core_sound_play(FSound *pSound, float pVolume) {
    core_sound_playPitched(pSound, 1.0f, pVolume);
}

void core_sound_playPitched(FSound *pSound, float pPitch, float pVolume) {


    Log("core_sound_playPitched(0)[%s]\n", pSound->mFileName.c());
    if (pSound) {
        Log("core_sound_playPitched(4)[%s]\n", pSound->mFileName.c());
        FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)(pSound->mSoundData);
        if ((pSound->mDidLoad == true) && (aSoundData != 0)) {
            Log("core_sound_playPitched(5)[%s]\n", pSound->mFileName.c());
            FSoundInstanceAndroid *aInstanceCheck = (FSoundInstanceAndroid *)(pSound->mInstances.Fetch(0));
            if (aInstanceCheck) {
                Log("core_sound_playPitched(88)[%s]\n", pSound->mFileName.c());
                FSoundInstanceAndroid *aInstancePlay = 0;
                if (core_sound_instance_isPlaying((FSoundInstanceAndroid *)aInstanceCheck) == false) {
                    Log("core_sound_playPitched(7)[%s]\n", pSound->mFileName.c());
                    aInstancePlay = aInstanceCheck;
                    pSound->mInstances.RotateFrontToBack();
                } else {
                    EnumList (FSoundInstanceAndroid, aInstance, pSound->mInstances) {
                        if (core_sound_instance_isPlaying((FSoundInstanceAndroid *)aInstance) == false) {
                            Log("core_sound_playPitched(HIT)[%s]\n", pSound->mFileName.c());
                            aInstancePlay = aInstance;
                        }
                    }
                }
                if (aInstancePlay) {
                    Log("core_sound_playPitched(FINAL)[%s]\n", pSound->mFileName.c());
                    //cEffectPool.Play(aInstancePlay, pVolume);
                    cEffectPool.PlayPitched(aInstancePlay, pVolume, pPitch);
                }
            }
        }
    }
    Log("core_sound_playPitched(Exit)[%s]\n", pSound->mFileName.c());
}

void core_sound_stop(FSound *pSound) {
    if (pSound) {
        EnumList (FSoundInstance, aFSoundInstance, pSound->mInstances) {
            aFSoundInstance->Stop();
        }
    }
}

void core_sound_clear(FSound *pSound) {
    if (pSound) {
        FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)(pSound->mSoundData);

        if (aSoundData) {
            delete aSoundData->mData;
            aSoundData->mData = 0;
            aSoundData->mDataLength = 0;
            aSoundData->mDidLoad = false;
        }

        pSound->mDidLoad = false;

        /*
        if(pSound->mSoundData)
        {
            alDeleteBuffers(pSound->mInstances.mCount, pSound->mSoundData);

            delete [] pSound->mSoundData;
            delete [] pSound->mInstanceID;

            pSound->mSoundData = 0;
            pSound->mInstanceID = 0;
        }
        */
    }
}

bool core_sound_isPlaying(FSound *pSound) {
    bool aReturn = false;
    if (pSound) {
        EnumList(FSoundInstance, aInstance, pSound->mInstances) {
            if (core_sound_instance_isPlaying(aInstance)) {
                aReturn = true;
                break;
            }
        }
    }
    return aReturn;
}

bool core_sound_didLoad(FSound *pSound) {
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


/*

void core_sound_play(FSound *pSound)
{
    core_sound_playPitched(pSound, 1.0f, 1.0f);
}

void core_sound_play(FSound *pSound, float pVolume)
{
    core_sound_playPitched(pSound, pVolume, 1.0f);
}

void core_sound_playPitched(FSound *pSound, float pPitch, float pVolume)
{
    if(pSound != 0)
    {
        SLresult result;

        // make sure the asset audio player was created

        int aIndex = 0;
        EnumList(FSoundInstance, aInstance, pSound->mInstances)
        {
            if((aInstance->mObject != 0) && (aInstance->mPlayerPlay != 0))
            {

                SLuint32 aPlayState = 0;
                (*(aInstance->mPlayerPlay))->GetPlayState(aInstance->mPlayerPlay, &aPlayState);


                if(aPlayState == SL_PLAYSTATE_PAUSED)Log("[%d]PlayingFromState[SL_PLAYSTATE_PAUSED]\n", aIndex);
                else if(aPlayState == SL_PLAYSTATE_STOPPED)Log("[%d]PlayingFromState[SL_PLAYSTATE_STOPPED]\n", aIndex);
                else if(aPlayState == SL_PLAYSTATE_PLAYING)Log("[%d]PlayingFromState[SL_PLAYSTATE_PLAYING]\n", aIndex);
                else Log("[%d]PlayingFromState[?? - %d]\n", aIndex, aPlayState);

                if(aPlayState != SL_PLAYSTATE_PLAYING)
                {
                    result = (*(aInstance->mPlayerPlay))->SetPlayState(aInstance->mPlayerPlay, SL_PLAYSTATE_STOPPED);
                    result = (*(aInstance->mPlayerPlay))->SetPlayState(aInstance->mPlayerPlay, SL_PLAYSTATE_PLAYING);

                    return;
                }



                //SL_PLAYSTATE_PLAYING

                // set the player's state
                //result = (*(aInstance->mObject))->SetPlayState(aInstance->mObject, pPlaying ? SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);

                aIndex++;

            }
        }
    }
}

void core_sound_stop(FSound *pSound)
{

}

void core_sound_clear(FSound *pSound)
{

}

bool core_sound_isPlaying(FSound *pSound)
{
    bool aResult = false;

    return aResult;
}

bool core_sound_didLoad(FSound *pSound)
{
    bool aResult = false;

    return aResult;
}

*/


void core_sound_setVolume(float pVolume) {
    gVolumeSound = pVolume;
}

float core_sound_getVolume() {
    return gVolumeSound;
}



void core_sound_instance_play(FSoundInstance *pInstance, float pVolume) {
    cEffectPool.Play((FSoundInstanceAndroid *)pInstance, pVolume);
}

void core_sound_instance_resetPitch(FSoundInstance *pInstance)
{

}

/*
struct SLPitchItf_ {
	SLresult (*SetPitch) (
                          SLPitchItf self,
                          SLpermille pitch
                          );
	SLresult (*GetPitch) (
                          SLPitchItf self,
                          SLpermille *pPitch
                          );
	SLresult (*GetPitchCapabilities) (
                                      SLPitchItf self,
                                      SLpermille *pMinPitch,
                                      SLpermille *pMaxPitch
                                      );
};
*/

void core_sound_instance_setPitch(FSoundInstance *pInstance, float pPitch)
{

    /*
    if(pInstance != 0)
    {
        //pInstance->mPitch = pPitch;

        if((pInstance->mObject != 0) && (pInstance->mPlayerPitch != 0) && (pInstance->mDidLoad))
        {

            SLpermille aPitch = pPitch * 1000.0f;
            //SLresult result = (*aSound->oslPlayerPitchInterface)->SetPitch(aSound->oslPlayerPitchInterface, pitch);

            //SL_IID_PITCH

            //SLresult aResult = (*(pInstance->mPlayerPitch))->SetRate(pInstance->mPlayerPitch, aPitch);
            SLresult aResult = (*(pInstance->mPlayerPitch))->SetPitch(pInstance->mPlayerPitch, aPitch);


            if(aResult != SL_RESULT_SUCCESS)
            {
                Log("Sound FAIL\n");
                Log("core_sound_instance_setPitch");
            }
        }
    }
    */


    //float attenuation = 1.0f / 1024.0f + gain * 1023.0f / 1024.0f;
    //float db = 3 * log10(attenuation) / log10(2);
    //SLmillibel setGain = (SLmillibel)(db * 1000);


    /*
    if(!aSound->oslPlayerPitchInterface)
        return;
    SLpermille pitch = aPitch * 1000.0f;
    SLresult result = (*aSound->oslPlayerPitchInterface)->SetPitch(aSound->oslPlayerPitchInterface, pitch);
    _osl_checkResult("Couldn't set audio pitch", result);
    */
}

/*
static SLVolumeItf getVolume()
{
    if (uriPlayerVolume != NULL)
        return uriPlayerVolume;
    else if (fdPlayerVolume != NULL)
        return fdPlayerVolume;
    else
        return mVolumeInterface;
}


void Java_com_example_nativeaudio_NativeAudio_setVolumeUriAudioPlayer(JNIEnv* env, jclass clazz,
                                                                      jint millibel)
{
    SLresult result;
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->SetVolumeLevel(volumeItf, millibel);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}
*/

void core_sound_instance_setVolume(FSoundInstance *pInstance, float pVolume)
{


}

void core_sound_instance_pause(FSoundInstance *pInstance)
{
    /*
    if(pInstance != 0)
    {
        if((pInstance->mObject != 0) && (pInstance->mPlayerPlay != 0) && (pInstance->mDidLoad))
        {
            SLresult aResult = (*(pInstance->mPlayerPlay))->SetPlayState(pInstance->mPlayerPlay, SL_PLAYSTATE_PAUSED);
            if(aResult != SL_RESULT_SUCCESS)
            {
                Log("Sound FAIL\n");
                Log("core_sound_instance_pause");
            }
        }
    }
    */
}

void core_sound_instance_unpause(FSoundInstance *pInstance)
{
    /*

    if(pInstance != 0)
    {
        if((pInstance->mObject != 0) && (pInstance->mPlayerPlay != 0) && (pInstance->mDidLoad))
        {
            SLresult aResult = (*(pInstance->mPlayerPlay))->SetPlayState(pInstance->mPlayerPlay, SL_PLAYSTATE_PLAYING);
        }
    }

    */
}

void core_sound_instance_loop(FSoundInstance *pInstance, float pVolume)
{

}

void core_sound_instance_stop(FSoundInstance *pInstance)
{

    /*

    if(pInstance != 0)
    {
        if((pInstance->mObject != 0) && (pInstance->mPlayerPlay != 0) && (pInstance->mDidLoad))
        {
            SLresult aResult = (*(pInstance->mPlayerPlay))->SetPlayState(pInstance->mPlayerPlay, SL_PLAYSTATE_STOPPED);
        }
    }

    */

}

bool core_sound_instance_isPlaying(FSoundInstance *pInstance)
{
    bool aReturn = false;

    FSoundInstanceAndroid *aInstance = (FSoundInstanceAndroid *)pInstance;

    if(aInstance != 0)
    {
        if(aInstance->mBuffer != 0)
        {
            aReturn = true;
        }
    }

    /*

    if(pInstance != 0)
    {
        //Log("1 - core_sound_instance_isPlaying(%d, %d, %d)\n", (pInstance->mObject != 0), (pInstance->mPlayerPlay != 0), (pInstance->mDidLoad));

        if((pInstance->mObject != 0) && (pInstance->mPlayerPlay != 0) && (pInstance->mDidLoad))
        {

            SLuint32 aPlayState = 0;
            (*(pInstance->mPlayerPlay))->GetPlayState(pInstance->mPlayerPlay, &aPlayState);

            //if(aPlayState == SL_PLAYSTATE_PAUSED)Log("2 - core_sound_instance_isPlaying(Type = PAUSED)\n");
            //else if(aPlayState == SL_PLAYSTATE_STOPPED)Log("2 - core_sound_instance_isPlaying(Type = STOPPED)\n");
            //else if(aPlayState == SL_PLAYSTATE_PLAYING)Log("2 - core_sound_instance_isPlaying(Type = PLAYING)\n");
            //else Log("2 - core_sound_instance_isPlaying(Type = UNKNOWN)\n");





            if(aPlayState == SL_PLAYSTATE_PLAYING)
            {
                aReturn = true;
            }

            //if(aPlayState == SL_PLAYSTATE_PAUSED)Log("[%d]PlayingFromState[SL_PLAYSTATE_PAUSED]\n", aIndex);
            //else if(aPlayState == SL_PLAYSTATE_STOPPED)Log("[%d]PlayingFromState[SL_PLAYSTATE_STOPPED]\n", aIndex);
            //else if(aPlayState == SL_PLAYSTATE_PLAYING)Log("[%d]PlayingFromState[SL_PLAYSTATE_PLAYING]\n", aIndex);
            //else Log("[%d]PlayingFromState[?? - %d]\n", aIndex, aPlayState);

            //if(aPlayState != SL_PLAYSTATE_PLAYING)


        }
    }

    */

    return aReturn;
}

void core_sound_instance_destroy(FSoundInstance *pInstance)
{

}






void core_sound_musicPlay(const char *pFileName, bool pLoop)
{
    Log("Playing Music[%s]\n", pFileName);

    FString aFilePath = FString(pFileName);
    aFilePath.RemoveExtension();

    FMusicBuffer *aBuffer = 0;
    EnumList (FMusicBuffer, aCheckBuffer, cMusicBufferList) {
        if (aCheckBuffer->mName == aFilePath) {
            aBuffer = aCheckBuffer;
            break;
        }
    }

    if (aBuffer == 0) {
        aBuffer = new FMusicBuffer();
        aBuffer->Initialize(pFileName);
        cMusicBufferList.Add(aBuffer);
    }

    if (aBuffer != 0) {
        if (cMusicBufferFading) {
            cMusicBufferFading->Stop();
            cMusicBufferFading = 0;
        }

        if (cMusicBuffer) {
            cMusicBufferFading = cMusicBuffer;
            cMusicBuffer = 0;
            cMusicBufferFading->Stop();
        }
        cMusicBuffer = aBuffer;
        cMusicBuffer->Play(pLoop);
    }
}

void core_sound_musicCrossFade(const char *pFileName, int pDurationTicks, bool pLoop)
{
    core_sound_musicPlay(pFileName, pLoop);

}

void core_sound_musicFadeOut(int pDurationTicks)
{
    if(cMusicBuffer)
    {
        cMusicBuffer->Stop();
    }
}

void core_sound_musicStop()
{
    if(cMusicBuffer)
    {
        cMusicBuffer->Stop();
    }
}

bool core_sound_musicIsPlaying()
{

}

void core_sound_musicSetVolume(float pVolume)
{
    gVolumeMusic = pVolume;

    Log("Setting Volume: %f [%x]\n", pVolume, (void *)cMusicBuffer);

    if(cMusicBuffer)
    {
        cMusicBuffer->SetVolume(gVolumeMusic);
    }
}

float core_sound_musicGetVolume()
{
    return gVolumeMusic;


}


void core_sound_musicResume()
{
    if(cMusicBuffer)
    {
        cMusicBuffer->Play(cMusicBuffer->mLooping);
    }

}

void core_sound_musicPause()
{
    if(cMusicBuffer)
    {
        cMusicBuffer->Pause();
    }
}


void core_sound_stopAll()
{
    core_sound_stopAllEffects();
    core_sound_musicPause();
}

void core_sound_stopAllEffects()
{

}



FSoundData *core_sound_spawn_data()
{
    return new FSoundDataAndroid();
}

void core_sound_unloadEffects()
{

}

void core_sound_reloadEffects()
{

}

void core_sound_update()
{

}

void core_sound_active()
{
    core_sound_musicResume();
}

void core_sound_inactive()
{
    core_sound_musicPause();
}



