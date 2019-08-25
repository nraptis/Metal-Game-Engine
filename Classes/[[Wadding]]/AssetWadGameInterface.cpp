//
//  AssetWadGameInterface.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetWadGameInterface.hpp"


AssetWadGameInterface::AssetWadGameInterface() {
    
}

AssetWadGameInterface::~AssetWadGameInterface() {
    
}


void AssetWadGameInterface::Load() {
    
    QuickLoad("demo_sprite", &mSpriteTest);
    
    
}

void AssetWadGameInterface::Unload() {
    
    mSpriteTest.Kill();
    
}

