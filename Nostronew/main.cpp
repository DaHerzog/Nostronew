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

int main(int argc, char * argv[]) {
    
    ResourceManager* resManager = new ResourceManager();
    GameManager* gameManager = new GameManager(resManager);
    gameManager->setBoundary(new Vector(-50.0f, 50.0f,0.0f), new Vector(50.0f, 200.0f,0.0f));
    MyOpenGLRenderer::initialize(argc, argv);
    if (resManager->loadModels()) {
        MyOpenGLRenderer::setResourceManager(resManager);
        MyOpenGLRenderer::setGameManager(gameManager);
        MyOpenGLRenderer::startMainLoop();
    } else {
        std::cout << "Initialisierungsfehler in der loadModels() Methode!" << std::endl;
    }
    return 0;
}
