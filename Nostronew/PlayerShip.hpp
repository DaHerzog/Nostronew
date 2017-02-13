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

#include "Drawable.hpp"



class PlayerShip: public Drawable {
public:
    PlayerShip();
    PlayerShip(Vector* startPos);
    PlayerShip(Model* pModel);
    PlayerShip(Vector* pStartPos, Model* pModel);
    virtual ~PlayerShip();
    
    
protected:
    
};

#endif /* PlayerShip_hpp */
