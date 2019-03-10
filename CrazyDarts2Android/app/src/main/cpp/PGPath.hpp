//
//  PGPath.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/7/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef PGPath_hpp
#define PGPath_hpp

#include "FPointList.h"

class PGPath {
public:
    PGPath();
    ~PGPath();

    void                        Update();
    void                        Draw();

    FPointList                  mPointListBase;
    FPointList                  mPointList;


};


#endif /* PGPath_hpp */
