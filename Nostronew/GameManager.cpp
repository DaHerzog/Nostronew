//
//  GameManager.cpp
//  Nostronew
//
//  Created by David Herzog on 07.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "GameManager.hpp"


GameManager::GameManager() {
    
}

GameManager::GameManager(PlayerShip* pShip) {
    this->playerShip = pShip;
}

void GameManager::steerPlayerShip(float p_RollLeftRight, float p_PitchUpDown, float p_ForwardBackward) {
    
}
