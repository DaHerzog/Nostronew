//
//  Bullet.hpp
//  Nostronew
//
//  Created by David Herzog on 13.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Drawable.hpp"

class Bullet : public Drawable {
public:
	Bullet();
	Bullet(Model* p_Model);
	Bullet(Vector* p_StartPos, Model* p_Model);
	virtual~Bullet();
	void updatePosition(float deltaTime);
};

#endif /* Bullet_hpp */
