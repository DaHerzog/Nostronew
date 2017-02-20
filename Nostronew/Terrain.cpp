//
//  Terrain.cpp
//  Nostronew
//
//  Created by David Herzog on 12.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "Terrain.hpp"

Terrain::Terrain() {
   
}

Terrain::Terrain(Model* pModel): Drawable(pModel) {
    
}

Terrain:: ~Terrain() {
    
}

void Terrain::updatePosition(float deltaTime, Vector* p_MinBoundary, Vector* p_MaxBoundary) {
    Matrix TM, RMz, RMx;
    Matrix RMDir;
    
    //std::cout << "terrain update aufgerufen" << std::endl;
    
    
    
    
    this->m_Dir->normalize();
    
    //Multiplikationsreihenfolge einheiltlich beachten!
    //R = Rz * Ry * Rx (Rotation um die y-Achse haben wir nicht aktuell)
    //TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    //this->m_Matrix = TM * RMz * RMx;
}

