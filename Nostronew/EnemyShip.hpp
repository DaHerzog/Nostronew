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
};

#endif /* EnemyShip_hpp */
