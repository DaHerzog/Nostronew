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
    
    GameManager* gameManager = new GameManager();
    ResourceManager* resManager = new ResourceManager();
    MyOpenGLRenderer::initialize(argc, argv);
    if (resManager->loadModels()) {
        MyOpenGLRenderer::setResourceManager(resManager);
        MyOpenGLRenderer::startMainLoop();
    } else {
        std::cout << "Initialisierungsfehler in der loadModels() Methode!" << std::endl;
    }
    return 0;
}
