//
//  Terrain.hpp
//  Nostronew
//
//  Created by David Herzog on 12.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp

#include <stdio.h>
#include "Drawable.hpp"

class Terrain : public Drawable {
public:
    Terrain();
    Terrain(Model* pModel);
    virtual ~Terrain();
    void updateTerrainMovement(float pDeltaTime);
};

#endif /* Terrain_hpp */
