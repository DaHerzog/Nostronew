#include "Bullet.hpp"



Bullet::Bullet() {
}

Bullet::Bullet(Model * p_Model) : Drawable(p_Model) {
}

Bullet::Bullet(Vector * p_StartPos, Model * p_Model): Drawable(p_StartPos, p_Model) {
}


Bullet::~Bullet() {
}

void Bullet::updatePosition(float deltaTime) {
}
