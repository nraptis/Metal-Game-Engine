//
//  LevelFormationConfiguration.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelFormationConfiguration.hpp"
#include "LevelFormation.hpp"
#include "LevelPath.hpp"

LevelFormationConfiguration::LevelFormationConfiguration() {
    
    mTracerSpeedGlobal = SPEED_CLASS_DEFAULT;
    mTracerSpeed1 = SPEED_CLASS_DEFAULT;
    mTracerSpeed2 = SPEED_CLASS_DEFAULT;
    mTracerSpeed3 = SPEED_CLASS_DEFAULT;
    mTracerSpeed4 = SPEED_CLASS_DEFAULT;
    mTracerSpeed5 = SPEED_CLASS_DEFAULT;
    mTracerSpeed6 = SPEED_CLASS_DEFAULT;
    mTracerSpeed7 = SPEED_CLASS_DEFAULT;
    mTracerSpeed8 = SPEED_CLASS_DEFAULT;
    
}

LevelFormationConfiguration::~LevelFormationConfiguration() {
    
}

void LevelFormationConfiguration::Reset() {
    
    mTracerSpeedGlobal = SPEED_CLASS_DEFAULT;
    mTracerSpeed1 = SPEED_CLASS_DEFAULT;
    mTracerSpeed2 = SPEED_CLASS_DEFAULT;
    mTracerSpeed3 = SPEED_CLASS_DEFAULT;
    mTracerSpeed4 = SPEED_CLASS_DEFAULT;
    mTracerSpeed5 = SPEED_CLASS_DEFAULT;
    mTracerSpeed6 = SPEED_CLASS_DEFAULT;
    mTracerSpeed7 = SPEED_CLASS_DEFAULT;
    mTracerSpeed8 = SPEED_CLASS_DEFAULT;
    
}

void LevelFormationConfiguration::Apply(LevelFormation *pFormation) {
    
    if (pFormation == NULL) { return; }
    
    if (mTracerSpeedGlobal != SPEED_CLASS_DEFAULT) {
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            aTracer->SetSpeedClass(mTracerSpeedGlobal);
        }
    }
    
    if (mTracerSpeed1 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 0) {
                aTracer->SetSpeedClass(mTracerSpeed1);
                break;
            }
            aIndex++;
        }
    }
    
    if (mTracerSpeed2 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 1) {
                aTracer->SetSpeedClass(mTracerSpeed2);
                break;
            }
            aIndex++;
        }
    }
    
    if (mTracerSpeed3 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 2) {
                aTracer->SetSpeedClass(mTracerSpeed3);
                break;
            }
            aIndex++;
        }
    }
    
    if (mTracerSpeed4 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 3) {
                aTracer->SetSpeedClass(mTracerSpeed4);
                break;
            }
            aIndex++;
        }
    }
    
    if (mTracerSpeed5 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 4) {
                aTracer->SetSpeedClass(mTracerSpeed5);
                break;
            }
            aIndex++;
        }
    }
    
    if (mTracerSpeed6 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 5) {
                aTracer->SetSpeedClass(mTracerSpeed6);
                break;
            }
            aIndex++;
        }
    }
    
    if (mTracerSpeed7 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 6) {
                aTracer->SetSpeedClass(mTracerSpeed7);
                break;
            }
            aIndex++;
        }
    }
    
    if (mTracerSpeed8 != SPEED_CLASS_DEFAULT) {
        int aIndex = 0;
        EnumList(LevelFormationTracer, aTracer, pFormation->mTracerList) {
            if (aIndex == 7) {
                aTracer->SetSpeedClass(mTracerSpeed8);
                break;
            }
            aIndex++;
        }
    }
    
}
