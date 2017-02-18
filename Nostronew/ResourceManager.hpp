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
#include "EnemyShip.hpp"
#include "Terrain.hpp"
#include "MyWavefrontParser.hpp"
#include "CubeMap.hpp"

class ResourceManager {

private:
    const char* m_PathToShader = "/Users/davidherzog/Documents/XCode/Nostronew/Shader/";
    const char* m_PathToCubeMap = "/Users/davidherzog/Documents/XCode/Nostronew/Models/cubemap/";
    std::vector<Drawable*>* modelsToDraw;
    std::vector<Drawable*>* loadedModels;
    PlayerShip* m_PlayerShip;
    Terrain* m_Terrain;
    CubeMap* m_CubeMap;
public:
    ResourceManager();
    bool loadModels();
    std::vector<Drawable*>* getModelsToDraw();
    std::vector<Drawable*>* getLoadedModels();
    PlayerShip* getPlayerShip();
    Terrain* getTerrain();
    CubeMap* getCubeMap();
};

#endif /* ResourceManager_hpp */
