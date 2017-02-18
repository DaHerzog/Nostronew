//
//  ResourceManager.cpp
//  Nostronew
//
//  Created by David Herzog on 02.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//

#include "ResourceManager.hpp"

ResourceManager::ResourceManager() {
    this->modelsToDraw = new std::vector<Drawable*>();
    this->loadedModels = new std::vector<Drawable*>();
	this->m_Enemies = new std::vector<EnemyShip*>();
	this->m_Bullets = new std::vector<Bullet*>();
}

/*
 * Diese Methode is für das Laden aller gewünschten Modelle zuständig.
 *
 */
bool ResourceManager::loadModels() {
    Model* tmp = new Model();
    char fullPathVertexShader[256];
    strcpy(fullPathVertexShader, m_PathToShader);
    strcat(fullPathVertexShader, (const char*)"vertex_phong.glsl");
    char fullPathFragmentShader[256];
    strcpy(fullPathFragmentShader, m_PathToShader);
    strcat(fullPathFragmentShader, (const char*)"fragment_phong.glsl");
    
    /*if (MyWavefrontParser::loadModel(tmp, "sibenik/sibenik.obj", false) && tmp->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && tmp->getModelShader().compile()) {
        this->modelsToDraw->push_back(tmp);
    } else {
        std::cout << "Fehler in loadModels() beim Laden der Sibenik" << std::endl;
    }*/
    
    /*Model* sphere = new Model();
    if (MyWavefrontParser::loadModel(sphere, "coonball/coonball.obj", true) && sphere->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && sphere->getModelShader().compile()) {
        this->modelsToDraw->push_back(sphere);
    } else {
        std::cout << "Error in loadModels() while loading..." << std::endl;
    }*/
    
    
    this->m_PlayerShip = new PlayerShip(new Vector(0.0f, 100.0f, 0.0f), new Model());
    if (MyWavefrontParser::loadModel(this->m_PlayerShip->getModel(), "test/zylinderpoly.obj", true) && m_PlayerShip->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && this->m_PlayerShip->getModel()->getModelShader().compile()) {
        this->modelsToDraw->push_back(this->m_PlayerShip);
    } else {
        std::cout << "Error in loadModels() while loading..." << std::endl;
    }
    
    this->m_Terrain = new Terrain(new Model());
     if (MyWavefrontParser::loadModel(this->m_Terrain->getModel(), "landscape/landscape.obj", true) && this->m_Terrain->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && this->m_Terrain->getModel()->getModelShader().compile()) {
         this->modelsToDraw->push_back(this->m_Terrain);
     } else {
         std::cout << "Error in loadModels() while loading..." << std::endl;
     }
    
    
    for (int i = 0; i < this->m_enemyCount; i++) {
    
        EnemyShip* enemy = new EnemyShip(new Vector(((float)3*i), 90.0f+((float)2*i), 50.0f), new Model());
        if (MyWavefrontParser::loadModel(enemy->getModel(), "test/zylinderpoly.obj", true) && enemy->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && enemy->getModel()->getModelShader().compile()) {
			this->modelsToDraw->push_back(enemy);
			this->m_Enemies->push_back(enemy);
        } else {
            std::cout << "Error in loadModels() while loading..." << std::endl;
        }
    }

	for (int i = 0; i < this->m_bulletCount; i++) {

		Bullet* bullet = new Bullet(new Vector(((float)3 * i), 90.0f + ((float)2 * i), 50.0f), new Model());
		if (MyWavefrontParser::loadModel(bullet->getModel(), "test/zylinderpoly.obj", true) && bullet->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && bullet->getModel()->getModelShader().compile()) {
			this->modelsToDraw->push_back(bullet);
			this->m_Bullets->push_back(bullet);
		}
		else {
			std::cout << "Error in loadModels() while loading..." << std::endl;
		}
	}
    return true;
}

std::vector<Drawable*>* ResourceManager::getModelsToDraw() {
    return this->modelsToDraw;
}

std::vector<Drawable*>* ResourceManager::getLoadedModels() {
    return this->loadedModels;
}

PlayerShip* ResourceManager::getPlayerShip() {
    return this->m_PlayerShip;
}

Terrain* ResourceManager::getTerrain() {
    return this->m_Terrain;
}

EnemyShip * ResourceManager::getEnemy(int index) {
	if (index < this->m_enemyCount) {
		return this->m_Enemies->at(index);
	} else {
		std::cout << "Error in getEnemy" << std::endl;
		return NULL;
	}
}

Bullet * ResourceManager::getBullet(int index) {
	if (index < this->m_bulletCount) {
		return this->m_Bullets->at(index);
	} else {
		std::cout << "Error in getBullet" << std::endl;
		return NULL;
	}
}

int ResourceManager::getEnemyCount() {
	return this->m_enemyCount;
}

int ResourceManager::getBulletCount() {
	return this->m_bulletCount;
}


