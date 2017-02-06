//
//  Vector.hpp
//  CGPrak1
//
//  Created by David Herzog on 16.03.16.
//  Copyright © 2016 David Herzog. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>

class Vector {

public:
    float X;
    float Y;
    float Z;
    
    Vector();
    Vector(float x, float y, float z);
    
    float dot(const Vector& v) const;
    Vector cross(const Vector& v) const;
    Vector operator +(const Vector& v) const;
    Vector operator -(const Vector& v) const;
    Vector& operator +=(const Vector& v);
    Vector operator *(float c) const;
    Vector operator -() const;
    Vector& normalize();
    float length() const;
    float lengthSquared() const;
    Vector reflection(const Vector& normal) const;
    bool triangleIntersection(const Vector& d, const Vector& a, const Vector& b,
                              const Vector& c, float &s) const;
    
};

#endif /* Vector_hpp */
