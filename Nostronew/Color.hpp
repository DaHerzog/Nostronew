//
//  Color.hpp
//  CGPrak1
//
//  Created by David Herzog on 22.03.16.
//  Copyright © 2016 David Herzog. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <stdio.h>

class Color {

public:
    float R;
    float G;
    float B;
    
    Color();
    Color(float r, float g, float b);
    Color operator* (const Color& c) const;
    Color operator* (const float Factor) const;
    Color operator* (const double Factor) const;
    Color operator+ (const Color& c) const;
    Color& operator+= (const Color& c);
    
};

#endif /* Color_hpp */
