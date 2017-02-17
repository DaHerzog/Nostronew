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

//#include "Model.h"
#include "PlayerShip.hpp"
#include "MyWavefrontParser.hpp"

class ResourceManager {

private:
#ifdef WIN32
	const char* m_PathToShader = "E:/ComputerGrafik/PraktikumProjekte/Projekt/CG_Nostronew/Shader/";
#else
	const char* m_PathToShader = "/Users/davidherzog/Documents/XCode/Nostronew/Shader/";
#endif
    std::vector<Model*>* modelsToDraw;
    std::vector<Model*>* loadedModels;
    PlayerShip* playerShip;
public:
    ResourceManager();
    bool loadModels();
    std::vector<Model*>* getModelsToDraw();
    std::vector<Model*>* getLoadedModels();
    PlayerShip* getPlayerShip();
};

#endif /* ResourceManager_hpp */
