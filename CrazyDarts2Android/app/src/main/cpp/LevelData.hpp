//
//  LevelData.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelData_hpp
#define LevelData_hpp

class LevelData {
public:
    LevelData();
    virtual ~LevelData();
    
    virtual void                    Update();
    virtual void                    Dispose();
    virtual void                    Print(const char *pName);
    
    
    
};

#endif /* LevelData_hpp */
