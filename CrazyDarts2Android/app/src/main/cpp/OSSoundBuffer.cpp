//
//  OSSoundBuffer.cpp
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#include <assert.h>

#include "OSSoundBuffer.h"
#include "os_core_sound.h"
#include "os_core_includes.h"
#include "core_includes.h"


OSSoundBuffer::OSSoundBuffer() {
    bqPlayerObject = NULL;
    bqPlayerPlay = NULL;
    bqPlayerBufferQueue = NULL;
    bqPlayerEffectSend = NULL;
    bqPlayerPlaybackRate = NULL;
    bqPlayerVolume = NULL;
    bqPlayerSampleRate = NULL;
    bqPlaybackRateMin = 1000;
    bqPlaybackRateMax = 1000;
}

OSSoundBuffer::~OSSoundBuffer() {

}

