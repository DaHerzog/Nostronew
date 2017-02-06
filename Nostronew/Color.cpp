//
//  Color.cpp
//  CGPrak1
//
//  Created by David Herzog on 22.03.16.
//  Copyright © 2016 David Herzog. All rights reserved.
//

#include "Color.hpp"

Color::Color() {
    this->R = 0.0f;
    this->G = 0.0f;
    this->B = 0.0f;
}

Color::Color(float r, float g, float b) {
    this->R = r;
    this->G = g;
    this->B = b;
}

Color Color::operator* (const Color& c) const {
    Color tempCol;
    tempCol.R = this->R*c.R;
    tempCol.G = this->G*c.G;
    tempCol.B = this->B*c.B;
    return tempCol;
}

Color Color::operator* (const float Factor) const {
    Color tempCol;
    tempCol.R = this->R*Factor;
    tempCol.G = this->G*Factor;
    tempCol.B = this->B*Factor;
    return tempCol;
}

Color Color::operator* (const double Factor) const {
    Color tempCol;
    tempCol.R = this->R*Factor;
    tempCol.G = this->G*Factor;
    tempCol.B = this->B*Factor;
    return tempCol;
}

Color Color::operator+(const Color &c) const {
    Color tempCol;
    tempCol.R = this->R+c.R;
    tempCol.G = this->G+c.G;
    tempCol.B = this->B+c.B;
    return tempCol;
}

Color& Color::operator+= (const Color& c) {
    this->R = this->R+c.R;
    this->G = this->G+c.G;
    this->B = this->B+c.B;
    return (*this);
}