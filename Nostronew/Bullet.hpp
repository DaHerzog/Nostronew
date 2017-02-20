//
//  Bullet.hpp
//  Nostronew
//
//  Created by David Herzog on 20.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Drawable.hpp"

class Bullet : public Drawable {
public:
    const float speed = 100.0f;
    const float destructTime = 0.5f;
    
    Bullet();
    Bullet(Model* p_Model);
    Bullet(Vector* p_StartPos, Model* p_Model);
    virtual~Bullet();
    void updatePosition(float deltaTime, Vector* p_MinBoundary, Vector* p_MaxBoundary, Vector* p_shipPosition);
    bool getStatus();
    void setStatus(bool status);
protected:
    bool m_status;
    float m_lifetime;
};

#endif /* Bullet_hpp */
