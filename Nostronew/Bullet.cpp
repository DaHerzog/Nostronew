#include "Bullet.hpp"



Bullet::Bullet() {
	this->m_status = false;
	this->m_lifetime = 0.0f;
}

Bullet::Bullet(Model * p_Model) : Drawable(p_Model) {
}

Bullet::Bullet(Vector * p_StartPos, Model * p_Model): Drawable(p_StartPos, p_Model) {
}


Bullet::~Bullet() {
}

void Bullet::updatePosition(float deltaTime, Vector* p_MinBoundary, Vector* p_MaxBoundary, Vector* p_shipPosition) {
	Matrix TM;

	//Zeit um Bullet nach festgelegter Zeit zu zerstören
	this->m_lifetime += (float)(1 / deltaTime);

	if (this->m_lifetime > this->destructTime) {
		this->setStatus(false);
		this->m_lifetime = 0.0f;
	}
	this->m_Pos->Z += this->speed * (float)(1 / deltaTime);
	
	//Multiplikationsreihenfolge einheiltlich beachten!
	//R = Rz * Ry * Rx (Rotation um die y-Achse haben wir nicht aktuell)
	TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);

	this->m_Matrix = TM;
}

bool Bullet::getStatus() {
	return this->m_status;
}

void Bullet::setStatus(bool status) {
	this->m_status = status;
}

