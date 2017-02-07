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
    PlayerShip(Vector* pos);
    
    void setPos(Vector* newPos);
    Vector* getPos();
protected:
    Vector* m_Pos;
};
