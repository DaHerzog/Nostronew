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

class GameManager {
public:
    GameManager();
    GameManager(PlayerShip* pShip);
    void steerPlayerShip(float p_RollLeftRight, float p_PitchUpDown, float p_ForwardBackward);
private:
    PlayerShip* playerShip;
};

#endif /* GameManager_hpp */
