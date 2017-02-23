//
//  Hud.cpp
//  Nostronew
//
//  Created by David Herzog on 20.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "Hud.hpp"


Hud::Hud() {
    
}

Hud::Hud(unsigned int p_DisplayWidth, unsigned int p_DisplayHeight, GLdouble p_NearClippingPlane, GLdouble p_FarClippingPlane, void* p_Font) {
    this->m_DisplayWidth = p_DisplayWidth;
    this->m_DisplayHeight = p_DisplayHeight;
    this->m_Font = p_Font;
    this->m_NearClippingPlane = p_NearClippingPlane;
    this->m_FarClippingPlane = p_FarClippingPlane;
}

Hud::~Hud() {
    
}

/*
 * Bereitet OpenGL auf das Zeichnen von 2D vor
 *
 */
void Hud::setupFor2DRendering() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, this->m_DisplayWidth, 0.0, this->m_DisplayHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
}

/*
 * Löscht die zuvor erstellten Matrizen vom OpenGL Matrix-Stack, damit
 * wieder 3D gezeichnet werden kann.
 */
void Hud::setupFor3DRendering() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
}

/*
 * Zeichnet den gewünschten Text an die Stelle der X- und Y-Koordinaten
 * (im Fensterraum)
 */
void Hud::drawText(unsigned int p_PosX, unsigned int p_PoxY, char *p_Text) {
    
    glColor3f(0.0f, 1.0f, 1.0f);
    
    glDisable(GL_LIGHTING);
    glRasterPos2i(p_PosX, p_PoxY);
    for (char* c = p_Text; *c != '\0'; c++) {
        glutBitmapCharacter(this->m_Font, *c);
    }
    glEnable(GL_LIGHTING);
}

unsigned int Hud::getDisplayWidth() {
    return this->m_DisplayWidth;
}

unsigned int Hud::getDisplayHeight() {
    return this->m_DisplayHeight;
}

