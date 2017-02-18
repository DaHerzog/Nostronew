//
//  EnemyShip.hpp
//  Nostronew
//
//  Created by David Herzog on 13.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef EnemyShip_hpp
#define EnemyShip_hpp

#include <stdio.h>
#include "Drawable.hpp"

class EnemyShip: public Drawable {

public:
    EnemyShip();
    EnemyShip(Model* p_Model);
    EnemyShip(Vector* p_StartPos, Model* p_Model);
    virtual~EnemyShip();
    void updatePosition(float deltaTime, Vector* p_MinBoundary, Vector* p_MaxBoundary);
    void setMoveEnemiesLeft(bool p_Bool);
    void setMoveEnemiesRight(bool p_Bool);
    void setMoveEnemiesDown(bool p_Bool);
    void setMoveEnemiesUp(bool p_Bool);
	void setStatus(bool p_Bool);
    bool getMoveEnemiesLeft();
    bool getMoveEnemiesRight();
    bool getMoveEnemiesDown();
    bool getMoveEnemiesUp();
	bool getStatus();

protected:
    bool m_MoveEnemiesLeft;
    bool m_MoveEnemiesRight;
    bool m_MoveEnemiesDown;
    bool m_MoveEnemiesUp;
	bool m_status;
};

#endif /* EnemyShip_hpp */
