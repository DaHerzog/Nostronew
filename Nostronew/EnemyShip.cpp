//
//  EnemyShip.cpp
//  Nostronew
//
//  Created by David Herzog on 13.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "EnemyShip.hpp"

EnemyShip::EnemyShip() {
    
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesDown = false;;
    this->m_MoveEnemiesUp = false;
    this->m_Status = true;
    
}

EnemyShip::EnemyShip(Model* p_Model) : Drawable(p_Model){
    
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesDown = false;;
    this->m_MoveEnemiesUp = false;
    this->m_Status = true;
    
}

EnemyShip::EnemyShip(Vector* p_StartPos, Model* p_Model): Drawable(p_StartPos, p_Model) {
    //Ausrichtung der gegnerischen Schiffe wird in Z-Richtung umgedreht.
    Matrix RMz;
    RMz.identity();
    Matrix newMat = this->getMatrix();
    RMz.rotationY(M_PI);
    newMat = newMat * RMz;
    this->setMatrix(newMat);
    
    this->m_MoveEnemiesLeft = true;
    this->m_MoveEnemiesRight = false;
    this->m_MoveEnemiesDown = false;;
    this->m_MoveEnemiesUp = false;
    this->m_Status = true;
}

EnemyShip::~EnemyShip() {
    
}

void EnemyShip::updatePosition(float deltaTime, Vector* p_MinBoundary, Vector* p_MaxBoundary) {
    Matrix TM, RMz, RMx, RMy;
    Matrix RMDir;
    
    //std::cout << "Funktion des EnemyShips" << std::endl;
    //*(this->m_Pos) = *(this->m_Pos) + ((*(this->m_Dir) * (float)(1/deltaTime)) * (this->m_ForwardBackward));
    
    if (this->getLeftRight() < -0.2f) {
        this->setLeftRight(-0.2f);
    }
    if (this->getLeftRight() > 0.2f) {
        this->setLeftRight(0.2f);
    }
    if (this->getUpDown() < -0.2f) {
        this->setUpDown(-0.2f);
    }
    if (this->getUpDown() > 0.2f) {
        this->setUpDown(0.2f);
    }
    
    if (this->m_Acceleration->X > 0.2f){
        this->m_Acceleration->X = 0.2f;
    } else if (this->m_Acceleration->X < -0.2f){
        this->m_Acceleration->X = -0.2f;
    }
    if (this->m_Acceleration->Y > 0.2f){
        this->m_Acceleration->Y = 0.2f;
    } else if (this->m_Acceleration->Y < -0.2f){
        this->m_Acceleration->Y = -0.2f;
    }
    
    //std::cout << "m_LeftRight " << this->m_LeftRight << std::endl;
    //std::cout << "m_UpDown " << this->m_UpDown << std::endl;
    //std::cout << "m_Acc: X: " << this->m_Acceleration->X << " Y: " << this->m_Acceleration->Y << " Z: " << this->m_Acceleration->Z << std::endl;
    //std::cout << this->m_RollAngle << std::endl;
    //std::cout << deltaTime << std::endl;
    //std::cout << "m_Pos: " << this->m_Pos->X << ", " << this->m_Pos->Y << ", " << this->m_Pos->Z << ", " << std::endl;
    //std::cout << "m_Dir: " << this->m_Dir->X << ", " << this->m_Dir->Y << ", " << this->m_Dir->Z << ", " << std::endl;
    
    if(this->m_UpDown == 0.0f) {
        if (this->m_Acceleration->Y > 0.0f) {
            this->m_Acceleration->Y -= 0.01f;
        }
        if (this->m_Acceleration->Y < 0.0f) {
            this->m_Acceleration->Y += 0.01f;
        }
    }
    if (this->m_LeftRight == 0.0f) {
        if (this->m_Acceleration->X > 0.0f) {
            this->m_Acceleration->X -= 0.01f;
        }
        if (this->m_Acceleration->X < 0.0f) {
            this->m_Acceleration->X += 0.01f;
        }
    }
    
    //Bei einer sehr geringen Beschleunigung wird der Vektor wieder auf 0.0f gesetzt.
    if (this->m_Acceleration->X > 0.0f && this->m_Acceleration->X < 0.01f) {
        this->m_Acceleration->X = 0.0f;
    } else if (this->m_Acceleration->X < 0.0f && this->m_Acceleration->X > -0.01f) {
        this->m_Acceleration->X = 0.0f;
    }
    
    if (this->m_Acceleration->Y > 0.0f && this->m_Acceleration->Y < 0.01f) {
        this->m_Acceleration->Y = 0.0f;
    } else if (this->m_Acceleration->Y < 0.0f && this->m_Acceleration->Y > -0.01f) {
        this->m_Acceleration->Y = 0.0f;
    }
    
    if (this->m_Pos->X > p_MinBoundary->X && this->m_Pos->X < p_MaxBoundary->X && this->m_Pos->Y > p_MinBoundary->Y && this->m_Pos->Y < p_MaxBoundary->Y) {
        *(this->m_Acceleration) = *(this->m_Acceleration) + ((Vector(0.0f, this->m_UpDown, 0.0f) + Vector(this->m_LeftRight, 0.0f, 0.0f))*(float)(1/deltaTime));
    }
    
    if (this->m_Pos->X > p_MaxBoundary->X) {
        this->m_Acceleration->X -= 0.05f;
    } else if (this->m_Pos->X < p_MinBoundary->X) {
        this->m_Acceleration->X += 0.05f;
    }
    if (this->m_Pos->Y > p_MaxBoundary->Y) {
        this->m_Acceleration->Y -= 0.05f;
    } else if (this->m_Pos->Y < p_MinBoundary->Y) {
        this->m_Acceleration->Y += 0.05f;
    }
    
    *(this->m_Pos) = *(this->m_Pos) + *(this->m_Acceleration);
    
    if (this->m_LeftRight > 0.0f) {
        if ((this->m_RollAngle > -(M_PI/16))) {
            this->m_RollAngle -= M_PI/180;
        }
    } else if (this->m_LeftRight < 0.0f) {
        if ((this->m_RollAngle < (M_PI/16))) {
            this->m_RollAngle += M_PI/180;
        }
    }
    
    if (this->m_LeftRight == 0.0f) {
        if (this->m_RollAngle < 0.0f) {
            this->m_RollAngle += M_PI/360;
        }
        if (this->m_RollAngle > 0.0f) {
            this->m_RollAngle -= M_PI/360;
        }
    }
    
    if (this->m_UpDown > 0.0f) {
        if ((this->m_PitchAngle > -(M_PI/16))) {
            this->m_PitchAngle -= M_PI/180;
        }
    } else if (this->m_UpDown < 0.0f) {
        if ((this->m_PitchAngle < (M_PI/16))) {
            this->m_PitchAngle += M_PI/180;
        }
    }
    
    if (this->m_UpDown == 0.0f) {
        if (this->m_PitchAngle < 0.0f) {
            this->m_PitchAngle += M_PI/360;
        }
        if (this->m_PitchAngle > 0.0f) {
            this->m_PitchAngle -= M_PI/360;
        }
    }
    
    
    
    //this->m_RollAngle += this->m_RollLeftRight * (2*M_PI)/90;
    //this->m_PitchAngle += this->m_PitchUpDown * (2*M_PI)/90;
    
    
    RMz.rotationZ(this->m_RollAngle);
    RMx.rotationX(this->m_PitchAngle);
    
    //Rotation um 180 Grad um die Y-Achse. Damit die Gegner uns auch anschauen.
    RMy.rotationY(M_PI);
    
    
    RMDir = RMz * RMx;
    this->m_Dir->X = RMDir.forward().X;
    this->m_Dir->Y = RMDir.forward().Y;
    this->m_Dir->Z = RMDir.forward().Z;
    
    this->m_Dir->normalize();
    
    //Multiplikationsreihenfolge einheiltlich beachten!
    //R = Rz * Ry * Rx (Rotation um die y-Achse haben wir nicht aktuell)
    TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    this->m_Matrix = TM * RMz * RMy * RMx;
}

void EnemyShip::setMoveEnemiesLeft(bool p_Bool) {
    this->m_MoveEnemiesLeft = p_Bool;
}

void EnemyShip::setMoveEnemiesRight(bool p_Bool) {
    this->m_MoveEnemiesRight = p_Bool;
}

void EnemyShip::setMoveEnemiesDown(bool p_Bool) {
    this->m_MoveEnemiesDown = p_Bool;
}

void EnemyShip::setMoveEnemiesUp(bool p_Bool) {
    this->m_MoveEnemiesUp = p_Bool;
}

void EnemyShip::setStatus(bool p_Bool) {
    this->m_Status = p_Bool;
}

bool EnemyShip::getMoveEnemiesLeft() {
    return this->m_MoveEnemiesLeft;
}

bool EnemyShip::getMoveEnemiesRight() {
    return this->m_MoveEnemiesRight;
}

bool EnemyShip::getMoveEnemiesDown() {
    return this->m_MoveEnemiesDown;
}

bool EnemyShip::getMoveEnemiesUp() {
    return this->m_MoveEnemiesUp;
}

bool EnemyShip::getStatus() {
    return this->m_Status;
}
