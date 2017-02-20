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

/*
 * Löst einen Schuss aus
 *
 */
void GameManager::shootEnemyShip() {
    ResourceManager* res = this->m_ResManager;
    Vector* vec = new Vector(*res->getPlayerShip()->getPos());
    Bullet* newBullet = new Bullet(vec, res->getBulletBluePrint()->getModel());
    res->getModelsToDraw()->push_back(newBullet);
}

/*
 * Prüft, wie lange eine "Bullet" schon in der Luft war und loescht sie aus dem
 * modelsToDraw Array wenn sie ihren Lebenszyklus durchlaufen hat.
 */
bool GameManager::checkBulletsLifecylce(Bullet *p_Bullet, int p_BulletIdx) {
    if (!p_Bullet->getStatus()) {
        m_ResManager->getModelsToDraw()->erase(m_ResManager->getModelsToDraw()->begin()+p_BulletIdx);
        delete p_Bullet;
        return false;
    }
    return true;
}

/*
 * Kolllisionsabfrage für die übergebene "Bullet"
 *
 */
void GameManager::checkForHit(Bullet *p_Bullet, int p_BulletIdx) {
    
    ResourceManager* res = this->m_ResManager;
    int p_enemyCount = res->getEnemyCount();
    
    for (int i = 0; i < res->getModelsToDraw()->size(); i++) {
        
        if (EnemyShip* e = dynamic_cast<EnemyShip*>(res->getModelsToDraw()->at(i))) {
        
            Vector bullet_max = p_Bullet->getModel()->getBoundingBox().Max + *p_Bullet->getPos();
            Vector bullet_min = p_Bullet->getModel()->getBoundingBox().Min + *p_Bullet->getPos();
            Vector enemy_max = e->getModel()->getBoundingBox().Max + *e->getPos();
            Vector enemy_min = e->getModel()->getBoundingBox().Min + *e->getPos();
            
            //prüfung ob wert infrage kommt
            if (bullet_max.Z > enemy_min.Z) {
                if ((bullet_min.Y <= enemy_max.Y) && (bullet_max.Y >= enemy_min.Y)) {
                    if((bullet_max.X >= enemy_min.X) && (bullet_min.X <= enemy_max.X)) {
                        res->getModelsToDraw()->erase(res->getModelsToDraw()->begin()+i);
                        res->setEnemyCount(res->getEnemyCount()-1);
                        delete e;
                        res->getModelsToDraw()->erase(res->getModelsToDraw()->begin()+p_BulletIdx-1);
                        delete p_Bullet;
                        this->m_ShipsDestroyedCounter++;
                        if(res->getEnemyCount() == 0) {
                            this->m_GameIsRunning = false;
                        }
                    }
                }
            }
        }
    }
}
/*
 * Aktualisiert das HUD
 *
 */
void GameManager::updateHud() {
    m_ResManager->getHud()->setupFor2DRendering();
    if (m_GameIsRunning) {
        std::string s = std::to_string(this->m_ShipsDestroyedCounter);
        char const *counterChar = s.c_str();
        char text[256] = "Insgesamt zerstoerte Schiffe: ";
        strcat(text, counterChar);
        m_ResManager->getHud()->drawText(50, 50, text);
    } else {
        m_ResManager->getHud()->drawText((m_ResManager->getHud()->getDisplayWidth()/2)-10, m_ResManager->getHud()->getDisplayHeight()/2, "Game Over!");
        m_ResManager->getHud()->drawText((m_ResManager->getHud()->getDisplayWidth()/2)-40, (m_ResManager->getHud()->getDisplayHeight()/2)-40, "Press R for Restart!");
    }
    m_ResManager->getHud()->setupFor3DRendering();
}


/*
 * Startet das Spiel neu, sobald alle Gegner erledigt wurden
 *
 */
void GameManager::restartGame() {
    
    m_ResManager->setEnemyCount(5);
    for (int i = 0; i < m_ResManager->getEnemyCount(); i++) {
        EnemyShip* tmpEnemy = new EnemyShip(new Vector((float)(i * 4.0f), (float)(90+i), 50.0f), m_ResManager->getEnemyShipBluePrint()->getModel());
        m_ResManager->getModelsToDraw()->push_back(tmpEnemy);
    }
    
    this->m_GameIsRunning = true;
}
