//
//  PlayerShip.cpp
//  Nostronew
//
//  Created by David Herzog on 07.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(): Model() {
    this->m_Dir = new Vector(0.0f, 0.0f, 1.0f);
    this->m_Pos = new Vector(0.0f, 0.0f, 0.0f);
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
}

PlayerShip::PlayerShip(Vector* startPos): Model() {
    this->m_Dir = new Vector();
    this->m_Pos = startPos;
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
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
    Matrix TM, RMz, RMx;
    Matrix RMDir;
    
    
    *(this->m_Pos) = *(this->m_Pos) + ((*(this->m_Dir) * (float)(1/deltaTime)) * (this->m_ForwardBackward));
    
    //std::cout << deltaTime << std::endl;
    //std::cout << "m_Pos: " << this->m_Pos->X << ", " << this->m_Pos->Y << ", " << this->m_Pos->Z << ", " << std::endl;
    //std::cout << "m_Dir: " << this->m_Dir->X << ", " << this->m_Dir->Y << ", " << this->m_Dir->Z << ", " << std::endl;
    
    this->m_RollAngle += this->m_RollLeftRight * (2*M_PI)/90;
    this->m_PitchAngle += this->m_PitchUpDown * (2*M_PI)/90;
    
    //this->m_Dir->Y = sinf(this->m_RollAngle);
    //this->m_Dir->Y = sinf(-this->m_PitchAngle);
    
    
    
    RMz.rotationZ(this->m_RollAngle);
    RMx.rotationX(this->m_PitchAngle);
    
    RMDir = RMz * RMx;
    this->m_Dir->X = RMDir.forward().X;
    this->m_Dir->Y = RMDir.forward().Y;
    this->m_Dir->Z = RMDir.forward().Z;
    
    this->m_Dir->normalize();
    
    //Multiplikationsreihenfolge einheiltlich beachten!
    //R = Rz * Ry * Rx (Rotation um die y-Achse haben wir nicht aktuell)
    TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    this->m_Matrix = TM * RMz * RMx;
}

void PlayerShip::applyMatrices() {
    glPushMatrix();
    glMultMatrixf(this->m_Matrix);
}

void PlayerShip::discardMatrix() {
    glPopMatrix();
}

void PlayerShip::setRollLeftRight(float p_RollLeftRight) {
    this->m_RollLeftRight = p_RollLeftRight;
}

void PlayerShip::setPitchUpDown(float p_PitchUpDown) {
    this->m_PitchUpDown = p_PitchUpDown;
}

void PlayerShip::setForwardBackward(float p_ForwardBackward) {
    this->m_ForwardBackward = p_ForwardBackward;
}

Matrix& PlayerShip::getMatrix() {
    return this->m_Matrix;
}
