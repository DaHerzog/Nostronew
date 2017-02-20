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
#include "Bullet.hpp"
#include "Hud.hpp"

class ResourceManager {

private:
    const char* m_PathToShader = "/Users/davidherzog/Documents/XCode/Nostronew/Shader/";
    const char* m_PathToCubeMap = "/Users/davidherzog/Documents/XCode/Nostronew/Models/cubemap/";
    const int m_enemyCount = 5;
    const int m_bulletCount = 10;
    std::vector<Drawable*>* modelsToDraw;
    std::vector<Drawable*>* loadedModels;
    PlayerShip* m_PlayerShip;
    Terrain* m_Terrain;
    CubeMap* m_CubeMap;
    std::vector<EnemyShip*>* m_Enemies;
    std::vector<Bullet*>* m_Bullets;
    Hud* m_Hud;
public:
    ResourceManager();
    bool loadModels();
    std::vector<Drawable*>* getModelsToDraw();
    std::vector<Drawable*>* getLoadedModels();
    std::vector<Bullet*>* getBullets();
    PlayerShip* getPlayerShip();
    Terrain* getTerrain();
    CubeMap* getCubeMap();
    EnemyShip* getEnemy(int index);
    Bullet* getBullet(int index);
    Hud* getHud();
    void setHud(Hud* p_Hud);
    int getEnemyCount();
    int getBulletCount();
};

#endif /* ResourceManager_hpp */
