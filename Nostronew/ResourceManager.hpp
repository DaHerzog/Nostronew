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
#include <queue>

#include "PlayerShip.hpp"
#include "EnemyShip.hpp"
#include "Terrain.hpp"
#include "Bullet.hpp"
#include "MyWavefrontParser.hpp"

class ResourceManager {

private:
 
#ifdef WIN32
	const char* m_PathToShader = "E:/ComputerGrafik/PraktikumProjekte/Projekt/CG_Nostronew/Shader/";
#else
	const char* m_PathToShader = "/Users/davidherzog/Documents/XCode/Nostronew/Shader/";
#endif
	const int m_enemyCount = 5;
	const int m_bulletCount = 10;

    std::vector<Drawable*>* modelsToDraw;
    std::vector<Drawable*>* loadedModels;
    PlayerShip* m_PlayerShip;
    Terrain* m_Terrain;
	std::vector<EnemyShip*>* m_Enemies;
	std::vector<Bullet*>* m_Bullets;
public:
    ResourceManager();
    bool loadModels();
    std::vector<Drawable*>* getModelsToDraw();
    std::vector<Drawable*>* getLoadedModels();
    PlayerShip* getPlayerShip();
    Terrain* getTerrain();
	EnemyShip* getEnemy(int index);
	Bullet* getBullet(int index);
	int getEnemyCount();
	int getBulletCount();
};

#endif /* ResourceManager_hpp */
