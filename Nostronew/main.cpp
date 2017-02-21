//
//  main.cpp
//  Nostronew
//
//  Created by David Herzog on 02.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//

#include <iostream>

#include "MyOpenGLRenderer.hpp"
#include "GameManager.hpp"
#include "Hud.hpp"

int main(int argc, char * argv[]) {
    
    //
    // Der absolute Pfad in dem die Models liegen
    //
    char* mainPath = (char*)"/Users/davidherzog/Documents/XCode/Nostronew/Models/";
    
    //
    // Der absolute Pfad zu den Shadern
    //
    char* pathToShader = (char*)"/Users/davidherzog/Documents/XCode/Nostronew/Shader/";
    
    //
    // Die Anzahl der gewünschten Gegner
    //
    int enemies = 5;
    
    
    
    
    MyWavefrontParser::setMainPath(mainPath);
    ResourceManager* resManager = new ResourceManager(pathToShader, mainPath, enemies);
    GameManager* gameManager = new GameManager(resManager);
    Hud* hud = new Hud(1024, 768, 0.045, 1000.0, GLUT_BITMAP_HELVETICA_18);
    gameManager->setBoundary(new Vector(-50.0f, 80.0f,0.0f), new Vector(50.0f, 110.0f,0.0f));
    resManager->setHud(hud);
    MyOpenGLRenderer::initialize(argc, argv);
    if (resManager->loadModels()) {
        MyOpenGLRenderer::setResourceManager(resManager);
        MyOpenGLRenderer::setGameManager(gameManager);
        MyOpenGLRenderer::startMainLoop();
    } else {
        std::cout << "Initialisierungsfehler in der loadModels() Methode!" << std::endl;
    }
    
    delete gameManager;
    delete resManager;
    return 0;
}
