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
    char* m_PathToShader;
    char* m_PathToCubeMap;
    int m_EnemyCount;
    int m_InitialEnemyCount;
    std::vector<Drawable*>* modelsToDraw;
    std::vector<Drawable*>* loadedModels;
    PlayerShip* m_PlayerShip;
    Terrain* m_Terrain;
    CubeMap* m_CubeMap;
    Bullet* m_BulletBluePrint;
    EnemyShip* m_EnemyShipBluePrint;
    std::vector<EnemyShip*>* m_Enemies;
    std::vector<Bullet*>* m_Bullets;
    Hud* m_Hud;
public:
    ResourceManager();
    ResourceManager(char* p_PathToShader, char* p_PathToCubeMap, int p_EnemyCount);
    bool loadModels();
    std::vector<Drawable*>* getModelsToDraw();
    std::vector<Drawable*>* getLoadedModels();
    std::vector<Bullet*>* getBullets();
    PlayerShip* getPlayerShip();
    Terrain* getTerrain();
    CubeMap* getCubeMap();
    EnemyShip* getEnemy(int index);
    Hud* getHud();
    void setHud(Hud* p_Hud);
    int getEnemyCount();
    void setEnemyCount(int p_NewValue);
    Bullet* getBulletBluePrint();
    EnemyShip* getEnemyShipBluePrint();
    int getInitialEnemyCount();
};

#endif /* ResourceManager_hpp */
