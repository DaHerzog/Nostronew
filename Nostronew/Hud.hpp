//
//  Hud.hpp
//  Nostronew
//
//  Created by David Herzog on 20.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef Hud_hpp
#define Hud_hpp

#include <stdio.h>
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

class Hud {
public:
    Hud();
    Hud(unsigned int p_DisplayWidth, unsigned int p_DisplayHeight, GLdouble p_NearClippingPlane, GLdouble p_FarClippingPlane, void* font);
    ~Hud();
    void setupFor2DRendering();
    void setupFor3DRendering();
    void drawText(unsigned int p_PosX, unsigned int p_PoxY, char* p_Text);
    unsigned int getDisplayWidth();
    unsigned int getDisplayHeight();
protected:
    unsigned int m_DisplayWidth;
    unsigned int m_DisplayHeight;
    GLdouble m_NearClippingPlane;
    GLdouble m_FarClippingPlane;
    void* m_Font;
};

#endif /* Hud_hpp */
