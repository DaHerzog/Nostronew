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
    this->m_Acceleration = new Vector(0.0f, 0.0f, 0.0f);
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
    this->m_LeftRight = 0.0f;
    this->m_UpDown = 0.0f;
    this->m_Matrix = Matrix();
    this->m_Matrix.identity();
    this->m_Matrix.translation(*(this->m_Pos));
}

Drawable::Drawable(Model* pModel) {
    this->m_Dir = new Vector(0.0f, 0.0f, 1.0f);
    this->m_Pos = new Vector(0.0f, 0.0f, 0.0f);
    this->m_Acceleration = new Vector(0.0f, 0.0f, 0.0f);
    this->m_Model = pModel;
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
    this->m_LeftRight = 0.0f;
    this->m_UpDown = 0.0f;
    this->m_Matrix = Matrix();
    this->m_Matrix.identity();
    this->m_Matrix.translation(*(this->m_Pos));
}

Drawable::Drawable(Vector* pStartPos, Model* pModel) {
    this->m_Dir = new Vector(0.0f, 0.0f, 1.0f);
    this->m_Pos = pStartPos;
    this->m_Acceleration = new Vector(0.0f, 0.0f, 0.0f);
    this->m_Model = pModel;
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
    this->m_LeftRight = 0.0f;
    this->m_UpDown = 0.0f;
    this->m_Matrix = Matrix();
    this->m_Matrix.identity();
    this->m_Matrix.translation(*(this->m_Pos));
}

Drawable::Drawable(Vector* p_StartPos, Vector* p_Dir, Model* p_Model) {
    this->m_Dir = p_Dir;
    this->m_Pos = p_StartPos;
    this->m_Acceleration = new Vector(0.0f, 0.0f, 0.0f);
    this->m_Model = p_Model;
    this->m_RollLeftRight = 0.0f;
    this->m_PitchUpDown = 0.0f;
    this->m_PitchAngle = 0.0f;
    this->m_RollAngle = 0.0f;
    this->m_ForwardBackward = 0.0f;
    this->m_LeftRight = 0.0f;
    this->m_UpDown = 0.0f;
    this->m_Matrix = Matrix();
    this->m_Matrix.identity();
    this->m_Matrix.translation(*(this->m_Pos));
    
}

Drawable::~Drawable() {
    if (this->m_Pos)
        delete this->m_Pos;
    if (this->m_Dir)
        delete this->m_Dir;
    if (this->m_Acceleration)
        delete this->m_Acceleration;
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

void Drawable::updatePosition(float deltaTime, Vector* p_MinBoundary, Vector* p_MaxBoundary) {
    Matrix TM, RMz, RMx;
    Matrix RMDir;
    
    //*(this->m_Pos) = *(this->m_Pos) + ((*(this->m_Dir) * (float)(1/deltaTime)) * (this->m_ForwardBackward));
    
    if (this->m_Acceleration->X > 1){
        this->m_Acceleration->X = 1.0f;
    } else if (this->m_Acceleration->X < -1){
        this->m_Acceleration->X = -1.0f;
    }
    if (this->m_Acceleration->Y > 1){
        this->m_Acceleration->Y = 1.0f;
    } else if (this->m_Acceleration->Y < -1){
        this->m_Acceleration->Y = -1.0f;
    }
    
    //std::cout << "m_LeftRight " << this->m_LeftRight << std::endl;
    //std::cout << "m_UpDown " << this->m_UpDown << std::endl;
    std::cout << "m_Acc: X: " << this->m_Acceleration->X << " Y: " << this->m_Acceleration->Y << " Z: " << this->m_Acceleration->Z << std::endl;
    //std::cout << this->m_RollAngle << std::endl;
    //std::cout << deltaTime << std::endl;
    //std::cout << "m_Pos: " << this->m_Pos->X << ", " << this->m_Pos->Y << ", " << this->m_Pos->Z << ", " << std::endl;
    //std::cout << "m_Dir: " << this->m_Dir->X << ", " << this->m_Dir->Y << ", " << this->m_Dir->Z << ", " << std::endl;
    
    if(this->m_UpDown == 0.0f) {
        if (this->m_Acceleration->Y > 0.0f) {
            this->m_Acceleration->Y -= 0.01f;
        }
        if (this->m_Acceleration->Y < 0.0f) {
            this->m_Acceleration->Y += 0.01f;
        }
    }
    if (this->m_LeftRight == 0.0f) {
        if (this->m_Acceleration->X > 0.0f) {
            this->m_Acceleration->X -= 0.01f;
        }
        if (this->m_Acceleration->X < 0.0f) {
            this->m_Acceleration->X += 0.01f;
        }
    }
    
    if (this->m_Pos->X > p_MinBoundary->X && this->m_Pos->X < p_MaxBoundary->X && this->m_Pos->Y > p_MinBoundary->Y && this->m_Pos->Y < p_MaxBoundary->Y) {
        *(this->m_Acceleration) = *(this->m_Acceleration) + ((Vector(0.0f, this->m_UpDown, 0.0f) + Vector(this->m_LeftRight, 0.0f, 0.0f))*(float)(1/deltaTime));
    }
    
    if (this->m_Pos->X > p_MaxBoundary->X) {
        this->m_Acceleration->X -= 0.05f;
    } else if (this->m_Pos->X < p_MinBoundary->X) {
        this->m_Acceleration->X += 0.05f;
    }
    if (this->m_Pos->Y > p_MaxBoundary->Y) {
        this->m_Acceleration->Y -= 0.05f;
    } else if (this->m_Pos->Y < p_MinBoundary->Y) {
        this->m_Acceleration->Y += 0.05f;
    }
    
    *(this->m_Pos) = *(this->m_Pos) + *(this->m_Acceleration);
    
    if (this->m_LeftRight > 0.0f) {
        if ((this->m_RollAngle > -(M_PI/16))) {
            this->m_RollAngle -= M_PI/180;
        }
    } else if (this->m_LeftRight < 0.0f) {
        if ((this->m_RollAngle < (M_PI/16))) {
            this->m_RollAngle += M_PI/180;
        }
    }
    
    if (this->m_LeftRight == 0.0f) {
        if (this->m_RollAngle < 0.0f) {
            this->m_RollAngle += M_PI/360;
        }
        if (this->m_RollAngle > 0.0f) {
            this->m_RollAngle -= M_PI/360;
        }
    }
    
    if (this->m_UpDown > 0.0f) {
        if ((this->m_PitchAngle > -(M_PI/16))) {
            this->m_PitchAngle -= M_PI/180;
        }
    } else if (this->m_UpDown < 0.0f) {
        if ((this->m_PitchAngle < (M_PI/16))) {
            this->m_PitchAngle += M_PI/180;
        }
    }
    
    if (this->m_UpDown == 0.0f) {
        if (this->m_PitchAngle < 0.0f) {
            this->m_PitchAngle += M_PI/360;
        }
        if (this->m_PitchAngle > 0.0f) {
            this->m_PitchAngle -= M_PI/360;
        }
    }
    
    RMz.rotationZ(this->m_RollAngle);
    RMx.rotationX(this->m_PitchAngle);
    
    
    RMDir = RMz * RMx;
    this->m_Dir->X = RMDir.forward().X;
    this->m_Dir->Y = RMDir.forward().Y;
    this->m_Dir->Z = RMDir.forward().Z;
    
    this->m_Dir->normalize();
    
    TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    //Multiplikationsreihenfolge einheiltlich beachten!
    //R = Rz * Ry * Rx
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

void Drawable::setLeftRight(float p_LeftRight) {
    this->m_LeftRight = p_LeftRight;
}

void Drawable::setUpDown(float p_UpDown) {
    this->m_UpDown = p_UpDown;
}

Matrix& Drawable::getMatrix() {
    return this->m_Matrix;
}

void Drawable::setMatrix(Matrix& p_Matrix) {
    this->m_Matrix = p_Matrix;
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

float Drawable::getLeftRight() {
    return this->m_LeftRight;
}

float Drawable::getUpDown() {
    return this->m_UpDown;
}
