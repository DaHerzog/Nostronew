//
//  GameManager.hpp
//  Nostronew
//
//  Created by David Herzog on 07.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>

#include "PlayerShip.hpp"
#include "ResourceManager.hpp"

class GameManager {
public:
    GameManager();
    GameManager(ResourceManager* p_ResManager);
    GameManager(Vector* p_MinBoundary, Vector* p_MaxBoundary);
    void steerPlayerShip(int key, float p_UpDown, float p_LeftRight);
    void stopShip(int key);
    void setBoundary(Vector* p_MinBoundary, Vector* p_MaxBoundary);
private:
    ResourceManager* m_ResManager;
    Vector* m_MinBoundary;
    Vector* m_MaxBoundary;
    
};

#endif /* GameManager_hpp */
