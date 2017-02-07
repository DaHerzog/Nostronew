//
//  PlayerShip.hpp
//  Nostronew
//
//  Created by David Herzog on 07.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef PlayerShip_hpp
#define PlayerShip_hpp

#include <stdio.h>

#include "Model.h"

#endif /* PlayerShip_hpp */

class PlayerShip : public Model {
public:
    PlayerShip();
    PlayerShip(Vector* startPos);
    virtual ~PlayerShip();
    
    void setPos(Vector* newPos);
    Vector* getPos();
    void setDir(Vector* newDir);
    Vector* getDir();
    void updatePosition(float deltaTime);
    void applyMatrices();
protected:
    Vector* m_Pos;
    Vector* m_Dir;
    Matrix m_Matrix;
    float m_RollLeftRight;
    float m_RollAngle;
    float m_PitchUpDown;
    float m_ForwardBackward;
};
