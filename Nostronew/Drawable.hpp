//
//  Drawable.hpp
//  Nostronew
//
//  Created by David Herzog on 12.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include <stdio.h>
#include "Model.h"

class Drawable {
public:
    Drawable();
    Drawable(Model* pModel);
    Drawable(Vector* pStartPos, Model* pModel);
    ~Drawable();
    
    void setPos(Vector* newPos);
    Vector* getPos();
    void setDir(Vector* newDir);
    Vector* getDir();
    Matrix& getMatrix();
    void updatePosition(float deltaTime);
    void applyMatrices();
    void discardMatrix();
    void setRollLeftRight(float p_RollLeftRight);
    void setPitchUpDown(float p_PitchUpDown);
    void setForwardBackward(float p_ForwardBackward);
    Model* getModel();
    void setModel(Model* pModel);
    void drawAxis();
protected:
    Model* m_Model;
    Vector* m_Pos;
    Vector* m_Dir;
    Matrix m_Matrix;
    float m_RollAngle;
    float m_PitchAngle;
    float m_RollLeftRight;
    float m_PitchUpDown;
    float m_ForwardBackward;
};

#endif /* Drawable_hpp */
