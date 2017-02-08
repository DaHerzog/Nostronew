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
    void discardMatrix();
    void setRollLeftRight(float p_RollLeftRight);
    void setPitchUpDown(float p_PitchUpDown);
    void setForwardBackward(float p_ForwardBackward);
protected:
    Vector* m_Pos;
    Vector* m_Dir;
    Matrix m_Matrix;
    float m_RollAngle;
    float m_PitchAngle;
    float m_RollLeftRight;
    float m_PitchUpDown;
    float m_ForwardBackward;
};

#endif /* PlayerShip_hpp */
