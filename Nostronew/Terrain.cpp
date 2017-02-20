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
    
    //std::cout << "m_LeftRight " << this->m_LeftRight << std::endl;
    //std::cout << "m_UpDown " << this->m_UpDown << std::endl;
    //std::cout << "m_Acc: X: " << this->m_Acceleration->X << " Y: " << this->m_Acceleration->Y << " Z: " << this->m_Acceleration->Z << std::endl;
    //std::cout << this->m_RollAngle << std::endl;
    //std::cout << deltaTime << std::endl;
    //std::cout << "m_Pos: " << this->m_Pos->X << ", " << this->m_Pos->Y << ", " << this->m_Pos->Z << ", " << std::endl;
    //std::cout << "m_Dir: " << this->m_Dir->X << ", " << this->m_Dir->Y << ", " << this->m_Dir->Z << ", " << std::endl;
    
    
    
    this->m_Dir->normalize();
    
    //Multiplikationsreihenfolge einheiltlich beachten!
    //R = Rz * Ry * Rx (Rotation um die y-Achse haben wir nicht aktuell)
    //TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    //this->m_Matrix = TM * RMz * RMx;
}

