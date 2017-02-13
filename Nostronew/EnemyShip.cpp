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
    
}

EnemyShip::~EnemyShip() {
    
}
