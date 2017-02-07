//
//  ResourceManager.cpp
//  Nostronew
//
//  Created by David Herzog on 02.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//

#include "ResourceManager.hpp"

ResourceManager::ResourceManager() {
    this->modelsToDraw = new std::vector<Model*>();
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
    
    PlayerShip* sphere = new PlayerShip();
    if (MyWavefrontParser::loadModel(sphere, "coonball/coonball.obj", true) && sphere->getModelShader().load(fullPathVertexShader, fullPathFragmentShader) && sphere->getModelShader().compile()) {
        this->modelsToDraw->push_back(sphere);
    } else {
        std::cout << "Error in loadModels() while loading..." << std::endl;
    }
    
    return true;
}

std::vector<Model*>* ResourceManager::getModelsToDraw() {
    return this->modelsToDraw;
}
