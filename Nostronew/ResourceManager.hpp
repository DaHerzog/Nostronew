//
//  ResourceManager.hpp
//  Nostronew
//
//  Created by David Herzog on 02.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>

#include "PlayerShip.hpp"
#include "Terrain.hpp"
#include "MyWavefrontParser.hpp"

class ResourceManager {

private:
    const char* m_PathToShader = "/Users/davidherzog/Documents/XCode/Nostronew/Shader/";
    std::vector<Drawable*>* modelsToDraw;
    std::vector<Drawable*>* loadedModels;
    PlayerShip* m_PlayerShip;
    Terrain* m_Terrain;
public:
    ResourceManager();
    bool loadModels();
    std::vector<Drawable*>* getModelsToDraw();
    std::vector<Drawable*>* getLoadedModels();
    PlayerShip* getPlayerShip();
    Terrain* getTerrain();
};

#endif /* ResourceManager_hpp */
