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
    
    char fullPathVertexShader[256];
    strcpy(fullPathVertexShader, m_PathToShader);
    strcat(fullPathVertexShader, (const char*)"vertex_phong.glsl");
    char fullPathFragmentShader[256];
    strcpy(fullPathFragmentShader, m_PathToShader);
    strcat(fullPathFragmentShader, (const char*)"fragment_phong.glsl");
    
    char fullPathVertexShaderCubeMap[256];
    strcpy(fullPathVertexShaderCubeMap, m_PathToShader);
    strcat(fullPathVertexShaderCubeMap, (const char*)"cubemap_vertex.glsl");
    char fullPathFragmentShaderCubeMap[256];
    strcpy(fullPathFragmentShaderCubeMap, m_PathToShader);
    strcat(fullPathFragmentShaderCubeMap, (const char*)"cubemap_fragment.glsl");
    
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
    
    

    
    this->m_EnemyShipBluePrint = new EnemyShip(new Model());
    if (MyWavefrontParser::loadModel(this->m_EnemyShipBluePrint->getModel(), "test/zylinderpoly.obj", true) && this->m_EnemyShipBluePrint->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && this->m_EnemyShipBluePrint->getModel()->getModelShader().compile()) {
    } else {
        std::cout << "Error in loadModels() while loading..." << std::endl;
    }
    
    for (int i = 0; i < this->m_EnemyCount; i++) {
        EnemyShip* tmpEnemy = new EnemyShip(new Vector((float)(i * 4.0f), (float)(90+i), 50.0f), this->m_EnemyShipBluePrint->getModel());
        this->modelsToDraw->push_back(tmpEnemy);
    }
    
    
    
    this->m_BulletBluePrint = new Bullet(new Model());
    if (MyWavefrontParser::loadModel(this->m_BulletBluePrint->getModel(), "test/zylinderpoly.obj", true) && this->m_BulletBluePrint->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && this->m_BulletBluePrint->getModel()->getModelShader().compile()) {
    }
    else {
        std::cout << "Error in loadModels() while loading..." << std::endl;
    }
    
    this->m_CubeMap = new CubeMap(300.0f);
    this->m_CubeMap->init(m_PathToCubeMap, fullPathVertexShaderCubeMap, fullPathFragmentShaderCubeMap);
    
    
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

CubeMap* ResourceManager::getCubeMap() {
    return this->m_CubeMap;
}

EnemyShip * ResourceManager::getEnemy(int index) {
    if (index < this->m_EnemyCount) {
        return this->m_Enemies->at(index);
    } else {
        std::cout << "Error in getEnemy" << std::endl;
        return NULL;
    }
}

Bullet * ResourceManager::getBullet(int index) {
    if (index < this->m_BulletCount) {
        return this->m_Bullets->at(index);
    } else {
        std::cout << "Error in getBullet" << std::endl;
        return NULL;
    }
}

int ResourceManager::getEnemyCount() {
    return this->m_EnemyCount;
}

int ResourceManager::getBulletCount() {
    return this->m_BulletCount;
}

std::vector<Bullet*>* ResourceManager::getBullets() {
    return this->m_Bullets;
}

void ResourceManager::setHud(Hud *p_Hud) {
    this->m_Hud = p_Hud;
}

Hud* ResourceManager::getHud() {
    return this->m_Hud;
}

void ResourceManager::setEnemyCount(int p_NewValue) {
    this->m_EnemyCount = p_NewValue;
}

Bullet* ResourceManager::getBulletBluePrint() {
    return this->m_BulletBluePrint;
}

EnemyShip* ResourceManager::getEnemyShipBluePrint() {
    return this->m_EnemyShipBluePrint;
}

