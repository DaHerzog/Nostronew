//
//  EnemyShip.cpp
//  Nostronew
//
//  Created by David Herzog on 13.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "EnemyShip.hpp"

EnemyShip::EnemyShip() {
    
}

EnemyShip::EnemyShip(Model* p_Model) : Drawable(p_Model){
    
}

EnemyShip::EnemyShip(Vector* p_StartPos, Model* p_Model): Drawable(p_StartPos, p_Model) {
    //Ausrichtung der gegnerischen Schiffe wird in Z-Richtung umgedreht.
    Matrix RMz;
    RMz.identity();
    Matrix newMat = this->getMatrix();
    RMz.rotationY(M_PI);
    newMat = newMat * RMz;
    this->setMatrix(newMat);
}

EnemyShip::~EnemyShip() {
    
}
