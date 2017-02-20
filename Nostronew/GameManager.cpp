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
    this->m_GameIsRunning = true;
}

GameManager::GameManager(Vector* p_MinBoundary, Vector* p_MaxBoundary) {
    this->m_MinBoundary = p_MinBoundary;
    this->m_MaxBoundary = p_MaxBoundary;
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesUp = false;
    this->m_MoveEnemiesDown = false;
    this->m_GameIsRunning = true;
}

GameManager::GameManager(ResourceManager* p_ResManager) {
    this->m_ResManager = p_ResManager;
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesUp = false;
    this->m_MoveEnemiesDown = false;
    this->m_GameIsRunning = true;
}

/*
 * Diese Metohde nimmt die gedrückte Taste der MyOpenGLRenderer Klasse entgegen und reagiert
 * entsprechend. Vor allem prüft sie die Grenzen des "Spielfeldes" und verhindert eine Bewegung,
 * wenn diese überschritten wurde.
 */
void GameManager::steerPlayerShip(int key, float p_UpDown, float p_LeftRight) {
    if (m_GameIsRunning) {
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

void GameManager::setGameIsRunning(bool p_Bool) {
    this->m_GameIsRunning = p_Bool;
}

Vector* GameManager::getMinBoundary() {
    return m_MinBoundary;
}

Vector* GameManager::getMaxBoundary() {
    return this->m_MaxBoundary;
}

bool GameManager::getGameIsRunning() {
    return this->m_GameIsRunning;
}

/*
 * Diese Methode bewegt die gegnerischen Schiffe. Sie berücksichtigt ebenfalls die gegebenen Grenzen.
 *
 */
void GameManager::moveEnemy(EnemyShip* p_Enemy) {
    if (this->m_GameIsRunning) {
        if ( (p_Enemy->getPos()->X < this->m_MaxBoundary->X) && p_Enemy->getMoveEnemiesLeft()) {
            p_Enemy->setLeftRight(1.0f);
            //std::cout << "Enemies Left" << std::endl;
            if (p_Enemy->getPos()->X > (this->m_MaxBoundary->X-10.0f)) {
                p_Enemy->setLeftRight(0.0f);
                this->calculateRandomEnemyDirection(p_Enemy);
            }
        }
        
        if ( (p_Enemy->getPos()->X > this->m_MinBoundary->X) && p_Enemy->getMoveEnemiesRight()) {
            p_Enemy->setLeftRight(-1.0f);
            //std::cout << "Enemies Right" << std::endl;
            if (p_Enemy->getPos()->X < (this->m_MinBoundary->X+10.0f)) {
                p_Enemy->setLeftRight(0.0f);
                this->calculateRandomEnemyDirection(p_Enemy);
            }
        }
        
        if ( (p_Enemy->getPos()->Y > this->m_MinBoundary->Y) && p_Enemy->getMoveEnemiesDown()) {
            p_Enemy->setUpDown(-1.0f);
            //std::cout << "Enemies Down" << std::endl;
            if (p_Enemy->getPos()->Y < (this->m_MinBoundary->Y+10.0f)) {
                p_Enemy->setUpDown(0.0f);
                this->calculateRandomEnemyDirection(p_Enemy);
            }
        }
        
        if ( (p_Enemy->getPos()->Y < this->m_MaxBoundary->Y) && p_Enemy->getMoveEnemiesUp()) {
            p_Enemy->setUpDown(1.0f);
            //std::cout << "Enemies Up" << std::endl;
            if (p_Enemy->getPos()->Y > (this->m_MaxBoundary->Y-10.0f)) {
                p_Enemy->setUpDown(0.0f);
                this->calculateRandomEnemyDirection(p_Enemy);
            }
        }
    } else {
        p_Enemy->setLeftRight(0.0f);
        p_Enemy->setUpDown(0.0f);
    }
}


/*
 * Diese Methode berechnet eine zufällige Bewegungsrichtung.
 *
 */
void GameManager::calculateRandomEnemyDirection(EnemyShip *p_Enemy) {
    
    //Initialisierung eines echten Zufallsgenerators für Integer Werte zwischen 1 und 3
    std::random_device randomDev;
    std::default_random_engine randEng(randomDev());
    std::uniform_int_distribution<int> uniformDist(1,3);
    int randomNr;

    
    if (p_Enemy->getMoveEnemiesDown()) {
        randomNr = uniformDist(randEng);
        switch (randomNr) {
            case 1:
                p_Enemy->setMoveEnemiesDown(false);
                p_Enemy->setMoveEnemiesUp(true);
                break;
            case 2:
                p_Enemy->setMoveEnemiesDown(false);
                p_Enemy->setMoveEnemiesLeft(true);
                break;
            case 3:
                p_Enemy->setMoveEnemiesDown(false);
                p_Enemy->setMoveEnemiesRight(true);
                break;
            default:
                break;
        }
    } else if (p_Enemy->getMoveEnemiesUp()) {
        randomNr = uniformDist(randEng);
        switch (randomNr) {
            case 1:
                p_Enemy->setMoveEnemiesUp(false);
                p_Enemy->setMoveEnemiesDown(true);
                break;
            case 2:
                p_Enemy->setMoveEnemiesUp(false);
                p_Enemy->setMoveEnemiesLeft(true);
                break;
            case 3:
                p_Enemy->setMoveEnemiesUp(false);
                p_Enemy->setMoveEnemiesRight(true);
                break;
            default:
                break;
        }
    } else if (p_Enemy->getMoveEnemiesLeft()) {
        randomNr = uniformDist(randEng);
        switch (randomNr) {
            case 1:
                p_Enemy->setMoveEnemiesLeft(false);
                p_Enemy->setMoveEnemiesRight(true);
                break;
            case 2:
                p_Enemy->setMoveEnemiesLeft(false);
                p_Enemy->setMoveEnemiesUp(true);
                break;
            case 3:
                p_Enemy->setMoveEnemiesLeft(false);
                p_Enemy->setMoveEnemiesDown(true);
                break;
            default:
                break;
        }
    } else if (p_Enemy->getMoveEnemiesRight()) {
        randomNr = uniformDist(randEng);
        switch (randomNr) {
            case 1:
                p_Enemy->setMoveEnemiesRight(false);
                p_Enemy->setMoveEnemiesDown(true);
                break;
            case 2:
                p_Enemy->setMoveEnemiesRight(false);
                p_Enemy->setMoveEnemiesLeft(true);
                break;
            case 3:
                p_Enemy->setMoveEnemiesRight(false);
                p_Enemy->setMoveEnemiesUp(true);
                break;
            default:
                break;
        }
    }
    
}

void GameManager::shootEnemyShip() {
    ResourceManager* res = this->m_ResManager;
    for (int i = 0; i < res->getBulletCount(); i++) {
        Bullet* bullet = res->getBullet(i);
        if (!bullet->getStatus()) {
            //schiessen wenn status == false -> bullet noch nicht geschossen
            bullet->setStatus(true);
            Vector* vec = new Vector(*res->getPlayerShip()->getPos());
            bullet->setPos(vec);
            res->getModelsToDraw()->push_back(bullet);
            break;
        } else if(i == res->getBulletCount()-1) {
            //alle Shüsse werden gezeichnet  -> spieler muss warten bis schuss zerstört wird
            std::cout << "Waffe überhitzt" << std::endl;
        }
    }
}

void GameManager::checkForHit() {
    
    ResourceManager* res = this->m_ResManager;
    int p_bulletCount = res->getBulletCount();
    int p_enemyCount = res->getEnemyCount();
    
    for (int p_bulletIndex = 0; p_bulletIndex < p_bulletCount; p_bulletIndex++) {
        for (int p_enemyIndex = 0; p_enemyIndex < p_enemyCount; p_enemyIndex++) {
            Bullet* b = res->getBullet(p_bulletIndex);
            EnemyShip* e = res->getEnemy(p_enemyIndex);
            
            b->getModel()->getBoundingBox();
            
            
        }
    }
}

void GameManager::updateHud() {
    m_ResManager->getHud()->setupFor2DRendering();
    if (m_GameIsRunning) {
        m_ResManager->getHud()->drawText(50, 50, "Das ist ein Test!");
    } else {
        m_ResManager->getHud()->drawText((m_ResManager->getHud()->getDisplayWidth()/2)-10, m_ResManager->getHud()->getDisplayHeight()/2, "Game Over!");
    }
    m_ResManager->getHud()->setupFor3DRendering();
}
