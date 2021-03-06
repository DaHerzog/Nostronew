//
//  Camera.h
//  RealtimeRending
//
//  Created by Philipp Lensing on 22.10.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//

#ifndef __RealtimeRending__Camera__
#define __RealtimeRending__Camera__

#include <iostream>

#include "Vector.hpp"
#include "PlayerShip.hpp"

//extern const unsigned int g_WindowWidth;
//extern const unsigned int g_WindowHeight;

class Camera
{
public:
    Camera();
    Camera(Vector& Pos, Vector& Target, Vector& Up);
    
    Vector getPosition();
    Vector getTarget();
    Vector getUp();
    
    void setPosition( const Vector& Pos);
    void setTarget( const Vector& Target);
    void setUp( const Vector& Up);
    Matrix* getInverseViewMatrix(const Vector& Target, const Vector& Up, const Vector& Position);

    void mouseInput( int x, int y, int Button, int State);
    
    void apply();
    void setWindowWidthHeight(unsigned int p_Width, unsigned int p_Height);
protected:
    void pan( float dx, float dy);
    void zoom( float dz);
    void rotate( float x, float y );
    Vector getVSpherePos( float x, float y);
    Vector rotateAxisAngle( Vector v, Vector n, float a);
    
    unsigned int m_WindowWidth;
    unsigned int m_WindowHeight;
    Vector m_Position;
    Vector m_Target;
    Vector m_Up;
    Vector m_Panning;
    Vector m_Zoom;
    Vector m_Rotation;
    int m_LastMouseX;
    int m_LastMouseY;
};


#endif /* defined(__RealtimeRending__Camera__) */
