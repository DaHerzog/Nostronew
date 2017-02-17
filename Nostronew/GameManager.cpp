//
//  GameManager.cpp
//  Nostronew
//
//  Created by David Herzog on 07.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "GameManager.hpp"


GameManager::GameManager() {
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesUp = false;
    this->m_MoveEnemiesDown = false;
}

GameManager::GameManager(Vector* p_MinBoundary, Vector* p_MaxBoundary) {
    this->m_MinBoundary = p_MinBoundary;
    this->m_MaxBoundary = p_MaxBoundary;
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesUp = false;
    this->m_MoveEnemiesDown = false;
}

GameManager::GameManager(ResourceManager* p_ResManager) {
    this->m_ResManager = p_ResManager;
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesUp = false;
    this->m_MoveEnemiesDown = false;
}

void GameManager::steerPlayerShip(int key, float p_UpDown, float p_LeftRight) {
    switch (key) {
        case GLUT_KEY_UP:
            //std::cout << "Up Key Pressed" << std::endl;
            //m_ResManager->getPlayerShip()->setUpDown(1.0f);
            if (this->m_ResManager->getPlayerShip()->getPos()->Y < this->m_MaxBoundary->Y) {
                this->m_ResManager->getPlayerShip()->setUpDown(1.0f);
                
            } else {
                this->m_ResManager->getPlayerShip()->setUpDown(0.0f);
            }
            break;
            
        case GLUT_KEY_DOWN:
            //std::cout << "Down Key Pressed" << std::endl;
            if (this->m_ResManager->getPlayerShip()->getPos()->Y > this->m_MinBoundary->Y) {
                this->m_ResManager->getPlayerShip()->setUpDown(-1.0f);
                
            } else {
                this->m_ResManager->getPlayerShip()->setUpDown(0.0f);
            }
            break;
            
        case GLUT_KEY_LEFT:
            //std::cout << "Left Key Pressed" << std::endl;
            if (this->m_ResManager->getPlayerShip()->getPos()->X < this->m_MaxBoundary->X) {
                this->m_ResManager->getPlayerShip()->setLeftRight(1.0f);
                
            } else {
                this->m_ResManager->getPlayerShip()->setLeftRight(0.0f);
            }
            break;
            
        case GLUT_KEY_RIGHT:
            //std::cout << "Right Key Pressed" << std::endl;
            if (this->m_ResManager->getPlayerShip()->getPos()->X > this->m_MinBoundary->X) {
                this->m_ResManager->getPlayerShip()->setLeftRight(-1.0f);
            } else {
                this->m_ResManager->getPlayerShip()->setLeftRight(0.0f);
            }
            break;
            
        default:
            break;
    }
}

void GameManager::stopShip(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            //std::cout << "Up Key Released" << std::endl;
            //m_ResManager->getPlayerShip()->setUpDown(0.0f);
            this->m_ResManager->getPlayerShip()->setUpDown(0.0f);
            break;
            
        case GLUT_KEY_DOWN:
            //std::cout << "Down Key Released" << std::endl;
            this->m_ResManager->getPlayerShip()->setUpDown(0.0f);
            break;
            
        case GLUT_KEY_LEFT:
            this->m_ResManager->getPlayerShip()->setLeftRight(0.0f);
            break;
            
        case GLUT_KEY_RIGHT:
            //std::cout << "Right Key Releaed" << std::endl;
            this->m_ResManager->getPlayerShip()->setLeftRight(0.0f);
            break;

        default:
            break;
    }
}

void GameManager::setBoundary(Vector *p_MinBoundary, Vector *p_MaxBoundary) {
    this->m_MinBoundary = p_MinBoundary;
    this->m_MaxBoundary = p_MaxBoundary;
}

Vector* GameManager::getMinBoundary() {
    return m_MinBoundary;
}

Vector* GameManager::getMaxBoundary() {
    return this->m_MaxBoundary;
}

void GameManager::moveEnemy(EnemyShip* p_Enemy) {
    if ( (p_Enemy->getPos()->X < this->m_MaxBoundary->X) && p_Enemy->getMoveEnemiesLeft()) {
        p_Enemy->setLeftRight(1.0f);
        //std::cout << "Enemies Left" << std::endl;
        if (p_Enemy->getPos()->X > (this->m_MaxBoundary->X-10.0f)) {
            p_Enemy->setLeftRight(0.0f);
            p_Enemy->setMoveEnemiesRight(false);
            p_Enemy->setMoveEnemiesLeft(false);
            p_Enemy->setMoveEnemiesDown(true);
            p_Enemy->setMoveEnemiesUp(false);
        }
    }
    
    if ( (p_Enemy->getPos()->X > this->m_MinBoundary->X) && p_Enemy->getMoveEnemiesRight()) {
        p_Enemy->setLeftRight(-1.0f);
        //std::cout << "Enemies Right" << std::endl;
        if (p_Enemy->getPos()->X < (this->m_MinBoundary->X+10.0f)) {
            p_Enemy->setLeftRight(0.0f);
            p_Enemy->setMoveEnemiesRight(false);
            p_Enemy->setMoveEnemiesLeft(false);
            p_Enemy->setMoveEnemiesDown(false);
            p_Enemy->setMoveEnemiesUp(true);
        }
    }
    
    if ( (p_Enemy->getPos()->Y > this->m_MinBoundary->Y) && p_Enemy->getMoveEnemiesDown()) {
        p_Enemy->setUpDown(-1.0f);
        //std::cout << "Enemies Down" << std::endl;
        if (p_Enemy->getPos()->Y < (this->m_MinBoundary->Y+10.0f)) {
            p_Enemy->setUpDown(0.0f);
            p_Enemy->setMoveEnemiesRight(true);
            p_Enemy->setMoveEnemiesLeft(false);
            p_Enemy->setMoveEnemiesDown(false);
            p_Enemy->setMoveEnemiesUp(false);
        }
    }
    
    if ( (p_Enemy->getPos()->Y < this->m_MaxBoundary->Y) && p_Enemy->getMoveEnemiesUp()) {
        p_Enemy->setUpDown(1.0f);
        //std::cout << "Enemies Up" << std::endl;
        if (p_Enemy->getPos()->Y > (this->m_MaxBoundary->Y-10.0f)) {
            p_Enemy->setUpDown(0.0f);
            p_Enemy->setMoveEnemiesRight(false);
            p_Enemy->setMoveEnemiesLeft(true);
            p_Enemy->setMoveEnemiesDown(false);
            p_Enemy->setMoveEnemiesUp(false);
        }
    }
}

void GameManager::shootEnemyShip() {
	//TODO
}

