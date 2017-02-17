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
    
    
    for (int i = 0; i < 5; i++) {
    
        EnemyShip* enemy = new EnemyShip(new Vector(((float)3*i), 90.0f+((float)2*i), 50.0f), new Model());
        if (MyWavefrontParser::loadModel(enemy->getModel(), "test/zylinderpoly.obj", true) && enemy->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && enemy->getModel()->getModelShader().compile()) {
			this->m_Enemies->push_back(enemy);
        } else {
            std::cout << "Error in loadModels() while loading..." << std::endl;
        }
    }
    
    
    return true;
}

std::vector<Drawable*>* ResourceManager::getModelsToDraw() {

	//erlaubt es später Gegner zu töten und neue zu spawnen
	for (int i = 0; i < this->m_Enemies->size(); i++) {
		this->modelsToDraw->push_back(this->m_Enemies->at(i));
	}
	//erlaubt es Kugeln zu erstellen und zu entfernen TODO
	for (int i = 0; i < this->m_Bullets->size(); i++) {
		this->modelsToDraw->push_back(this->m_Bullets->back());
	}
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

void ResourceManager::createBullet() {

	//temporär ein spezieller Shader muss noch ergänzt werden
	char fullPathVertexShader[256];
	strcpy(fullPathVertexShader, m_PathToShader);
	strcat(fullPathVertexShader, (const char*)"vertex_phong.glsl");
	char fullPathFragmentShader[256];
	strcpy(fullPathFragmentShader, m_PathToShader);
	strcat(fullPathFragmentShader, (const char*)"fragment_phong.glsl");

	Vector* tmp = this->m_PlayerShip->getPos();
	Bullet* bullet = new Bullet(tmp, new Model());
	if (MyWavefrontParser::loadModel(bullet->getModel(), "test/zylinderpoly.obj", true) && bullet->getModel()->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && bullet->getModel()->getModelShader().compile()) {
		this->m_Bullets->push(bullet);
	}
	else {
		std::cout << "Error in loadModels() while loading..." << std::endl;
	}
}

void ResourceManager::deleteBullet() {

	//Schuss hat begrenzte Lebenszeit -> erster abgebeuerter Schuss muss zuerst wieder gelöscht werden
	std::queue<Bullet*> *tmp = this->m_Bullets;
	tmp->pop();
}

