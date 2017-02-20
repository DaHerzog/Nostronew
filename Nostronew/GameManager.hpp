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
#include "EnemyShip.hpp"
#include "ResourceManager.hpp"
#include <random>

class GameManager {
public:
    GameManager();
    GameManager(ResourceManager* p_ResManager);
    GameManager(Vector* p_MinBoundary, Vector* p_MaxBoundary);
    void steerPlayerShip(int key, float p_UpDown, float p_LeftRight);
    void stopShip(int key);
    void setBoundary(Vector* p_MinBoundary, Vector* p_MaxBoundary);
    void setGameIsRunning(bool p_Bool);
    Vector* getMinBoundary();
    Vector* getMaxBoundary();
    bool getGameIsRunning();
    void moveEnemy(EnemyShip* p_Enemy);
    void calculateRandomEnemyDirection(EnemyShip* p_Enemy);
    void shootEnemyShip();
    void checkForHit();
    void updateHud();
    void restartGame();
private:
    ResourceManager* m_ResManager;
    Vector* m_MinBoundary;
    Vector* m_MaxBoundary;
    bool m_MoveEnemiesLeft;
    bool m_MoveEnemiesRight;
    bool m_MoveEnemiesUp;
    bool m_MoveEnemiesDown;
    bool m_GameIsRunning;
    
};

#endif /* GameManager_hpp */
