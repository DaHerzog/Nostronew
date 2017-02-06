//
//  Vector.cpp
//  CGPrak1
//
//  Created by David Herzog on 16.03.16.
//  Copyright © 2016 David Herzog. All rights reserved.
//

#include "Vector.hpp"

#define EPSILON 1e-6;

Vector::Vector() {
    
}

Vector::Vector(float x, float y, float z) {
    this->X = x;
    this->Y = y;
    this->Z = z;
}

float Vector::dot(const Vector& v) const{
    return this->X*v.X + this->Y*v.Y + this->Z*v.Z;
}

Vector Vector::cross(const Vector& v) const {
    Vector tempVec;
    tempVec.X = this->Y*v.Z - this->Z*v.Y;
    tempVec.Y = this->Z*v.X - this->X*v.Z;
    tempVec.Z = this->X*v.Y - this->Y*v.X;
    return tempVec;
}

Vector Vector::operator +(const Vector& v) const {
    Vector tempVec;
    tempVec.X = this->X + v.X;
    tempVec.Y = this->Y + v.Y;
    tempVec.Z = this->Z + v.Z;
    return tempVec;
}

Vector Vector::operator -(const Vector& v) const {
    Vector tempVec;
    tempVec.X = this->X - v.X;
    tempVec.Y = this->Y - v.Y;
    tempVec.Z = this->Z - v.Z;
    return tempVec;
}

Vector& Vector::operator +=(const Vector& v) {
    this->X = this->X + v.X;
    this->Y = this->Y + v.Y;
    this->Z = this->Z + v.Z;
    return *this;
}

Vector Vector::operator *(float c) const {
    Vector tempVec;
    tempVec.X = this->X * c;
    tempVec.Y = this->Y * c;
    tempVec.Z = this->Z * c;
    return tempVec;
}

Vector Vector::operator -() const {
    Vector tempVec;
    tempVec.X = this->X*-1;
    tempVec.Y = this->Y*-1;
    tempVec.Z = this->Z*-1;
    return tempVec;
}

Vector& Vector::normalize() {
    float length = this->length();
    this->X = this->X / length;
    this->Y = this->Y / length;
    this->Z = this->Z / length;
    return *this;
}


float Vector::length() const{
    return sqrtf(this->lengthSquared());
}

float Vector::lengthSquared() const {
    return powf(this->X, 2) + powf(this->Y, 2) + powf(this->Z, 2);
}

Vector Vector::reflection(const Vector& normal) const {
    Vector t;
    float negativeScalar = -2 * this->dot(normal);
    t = normal*negativeScalar;
    Vector tempVec = *this+t;
    return tempVec;
}

bool Vector::triangleIntersection(const Vector& d, const Vector& a, const Vector& b,
                                  const Vector& c, float &s) const {
    
    Vector bMinusA = b-a;
    Vector cMinusA = c-a;
    Vector normOfPlane = bMinusA.cross(cMinusA).normalize();
    float smallD = normOfPlane.dot(a);
    
    s = (smallD - normOfPlane.dot(*this)) / (normOfPlane.dot(d));
    if (s < 1e-4) {
        return false;
    }
    Vector p = (*this)+(d*s);
    
    
    float areaOfABP = (p-a).cross(b-a).length()/2;
    float areaOfBCP = (c-p).cross(b-p).length()/2;
    float areaOfACP = (c-a).cross(p-a).length()/2;
    float areaOfABC = (b-a).cross(c-a).length()/2;
    float areaOfAbcWithTolerance = areaOfABC+EPSILON;
    
    if (areaOfAbcWithTolerance >= (areaOfABP+areaOfACP+areaOfBCP)) {
        return true;
    } else {
        return false;
    }
        
    
    
}
