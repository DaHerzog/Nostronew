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
    std::vector<Model*>* modelsToDraw;
    const char* m_PathToShader = "/Users/davidherzog/Documents/XCode/Nostronew/Shader/";
public:
    ResourceManager();
    bool loadModels();
    std::vector<Model*>* getModelsToDraw();
};

#endif /* ResourceManager_hpp */
