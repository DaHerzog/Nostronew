//
//  Drawable.cpp
//  Nostronew
//
//  Created by David Herzog on 12.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "Drawable.hpp"

Drawable::Drawable() {
    this->m_Dir = new Vector(0.0f, 0.0f, 1.0f);
    this->m_Pos = new Vector(0.0f, 0.0f, 0.0f);
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
}

Drawable::Drawable(Model* pModel) {
    this->m_Dir = new Vector(0.0f, 0.0f, 1.0f);
    this->m_Pos = new Vector(0.0f, 0.0f, 0.0f);
    this->m_Model = pModel;
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
}

Drawable::Drawable(Vector* pStartPos, Model* pModel) {
    this->m_Dir = new Vector(0.0f, 0.0f, 1.0f);
    this->m_Pos = pStartPos;
    this->m_Model = pModel;
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
}

Drawable::~Drawable() {
    if (this->m_Pos)
        delete this->m_Pos;
    if (this->m_Dir)
        delete this->m_Dir;
}

void Drawable::setPos(Vector *newPos) {
    delete this->m_Pos;
    this->m_Pos = newPos;
}

Vector* Drawable::getPos() {
    return this->m_Pos;
}

void Drawable::setDir(Vector* newDir) {
    delete this->m_Dir;
    this->m_Dir = newDir;
}

Vector* Drawable::getDir() {
    return this->m_Dir;
}

void Drawable::updatePosition(float deltaTime) {
    Matrix TM, RMz, RMx;
    Matrix RMDir;
    
    
    *(this->m_Pos) = *(this->m_Pos) + ((*(this->m_Dir) * (float)(1/deltaTime)) * (this->m_ForwardBackward));
    
    //std::cout << deltaTime << std::endl;
    //std::cout << "m_Pos: " << this->m_Pos->X << ", " << this->m_Pos->Y << ", " << this->m_Pos->Z << ", " << std::endl;
    //std::cout << "m_Dir: " << this->m_Dir->X << ", " << this->m_Dir->Y << ", " << this->m_Dir->Z << ", " << std::endl;
    
    this->m_RollAngle += this->m_RollLeftRight * (2*M_PI)/90;
    this->m_PitchAngle += this->m_PitchUpDown * (2*M_PI)/90;
    
    
    RMz.rotationZ(this->m_RollAngle);
    RMx.rotationX(this->m_PitchAngle);
    
    RMDir = RMz * RMx;
    this->m_Dir->X = RMDir.forward().X;
    this->m_Dir->Y = RMDir.forward().Y;
    this->m_Dir->Z = RMDir.forward().Z;
    
    this->m_Dir->normalize();
    
    //Multiplikationsreihenfolge einheiltlich beachten!
    //R = Rz * Ry * Rx (Rotation um die y-Achse haben wir nicht aktuell)
    TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    this->m_Matrix = TM * RMz * RMx;
}

void Drawable::applyMatrices() {
    glPushMatrix();
    glMultMatrixf(this->m_Matrix);
}

void Drawable::discardMatrix() {
    glPopMatrix();
}

void Drawable::setRollLeftRight(float p_RollLeftRight) {
    this->m_RollLeftRight = p_RollLeftRight;
}

void Drawable::setPitchUpDown(float p_PitchUpDown) {
    this->m_PitchUpDown = p_PitchUpDown;
}

void Drawable::setForwardBackward(float p_ForwardBackward) {
    this->m_ForwardBackward = p_ForwardBackward;
}

Matrix& Drawable::getMatrix() {
    return this->m_Matrix;
}

Model* Drawable::getModel() {
    return this->m_Model;
}

void Drawable::setModel(Model *pModel) {
    delete this->m_Model;
    this->m_Model = pModel;
}

void Drawable::drawAxis() {
    //right, up, forward Vektoren der Transformationsmatrix anzeigen lassen
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    glVertex3f(this->m_Pos->X+this->m_Matrix.right().X, this->m_Pos->Y+this->m_Matrix.right().Y, this->m_Pos->Z+this->m_Matrix.right().Z);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    glVertex3f(this->m_Pos->X+this->m_Matrix.up().X, this->m_Pos->Y+this->m_Matrix.up().Y, this->m_Pos->Z+this->m_Matrix.up().Z);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    glVertex3f(this->m_Pos->X+this->m_Matrix.forward().X, this->m_Pos->Y+this->m_Matrix.forward().Y, this->m_Pos->Z+this->m_Matrix.forward().Z);
    glEnd();
    glEnable(GL_LIGHTING);
}
