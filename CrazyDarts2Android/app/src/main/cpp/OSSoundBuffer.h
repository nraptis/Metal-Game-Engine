//
//  OSSoundBuffer.h
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#ifndef FRAMEWORK_SOUND_BUFFER_ANDROID_H
#define FRAMEWORK_SOUND_BUFFER_ANDROID_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>


class OSSoundBuffer {
public:
    OSSoundBuffer();
    ~OSSoundBuffer();



    SLObjectItf bqPlayerObject;
    SLPlayItf bqPlayerPlay ;
    SLAndroidSimpleBufferQueueItf       bqPlayerBufferQueue;
    SLEffectSendItf                     bqPlayerEffectSend;
    SLPlaybackRateItf                   bqPlayerPlaybackRate;
    SLVolumeItf                         bqPlayerVolume;
    SLmilliHertz                        bqPlayerSampleRate;
    SLpermille                          bqPlaybackRateMin;
    SLpermille                          bqPlaybackRateMax;
};



#endif


