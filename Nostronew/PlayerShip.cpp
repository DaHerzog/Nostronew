//
//  PlayerShip.cpp
//  Nostronew
//
//  Created by David Herzog on 07.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(): Model() {
    this->m_Dir = new Vector();
    this->m_Pos = new Vector();
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
}

PlayerShip::PlayerShip(Vector* startPos): Model() {
    this->m_Dir = new Vector();
    this->m_Pos = new Vector();
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
}

PlayerShip::~PlayerShip() {
    if (this->m_Pos)
        delete this->m_Pos;
    if (this->m_Dir)
        delete this->m_Dir;
}

void PlayerShip::setPos(Vector *newPos) {
    delete this->m_Pos;
    this->m_Pos = newPos;
}

Vector* PlayerShip::getPos() {
    return this->m_Pos;
}

void PlayerShip::setDir(Vector* newDir) {
    delete this->m_Dir;
    this->m_Dir = newDir;
}

Vector* PlayerShip::getDir() {
    return this->m_Dir;
}

void PlayerShip::updatePosition(float deltaTime) {
    Matrix TM, RM;
    
    *(this->m_Pos) = *(this->m_Pos) + ((*(this->m_Dir) * (float)(deltaTime/0.15)) * (this->m_ForwardBackward));
    
    this->m_RollAngle += this->m_RollLeftRight * (2*M_PI)/90;
    
    this->m_Dir->X = cosf(-this->m_RollAngle);
    this->m_Dir->Y = sinf(-this->m_RollAngle);
    
    RM.rotationZ(this->m_RollAngle);
    TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    this->m_Matrix = TM * RM;
}

void PlayerShip::applyMatrices() {
    glPushMatrix();
    glMultMatrixf(this->m_Matrix);
}

void PlayerShip::discardMatrix() {
    glPopMatrix();
}

