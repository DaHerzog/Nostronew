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

void Terrain::updateTerrainMovement(float pDeltaTime) {
    Matrix TM, RMz, RMx;
    Matrix RMDir;
    
    
    *(this->m_Pos) = *(this->m_Pos) + ((*(this->m_Dir) * (float)(1/pDeltaTime)) * (this->m_ForwardBackward));
    
    //std::cout << deltaTime << std::endl;
    //std::cout << "m_Pos: " << this->m_Pos->X << ", " << this->m_Pos->Y << ", " << this->m_Pos->Z << ", " << std::endl;
    //std::cout << "m_Dir: " << this->m_Dir->X << ", " << this->m_Dir->Y << ", " << this->m_Dir->Z << ", " << std::endl;
    
    this->m_RollAngle += this->m_RollLeftRight * (2*M_PI)/90;
    this->m_PitchAngle += this->m_PitchUpDown * (2*M_PI)/90;
    
    
    RMz.rotationZ(this->m_RollAngle);
    RMx.rotationX(this->m_PitchAngle);
    
    /*RMDir = RMz * RMx;
    this->m_Dir->X = RMDir.forward().X;
    this->m_Dir->Y = RMDir.forward().Y;
    this->m_Dir->Z = RMDir.forward().Z;*/
    
    this->m_Dir->normalize();
    
    //Multiplikationsreihenfolge einheiltlich beachten!
    //R = Rz * Ry * Rx (Rotation um die y-Achse haben wir nicht aktuell)
    TM.translation(this->m_Pos->X, this->m_Pos->Y, this->m_Pos->Z);
    
    this->m_Matrix = RMz * RMx * TM;
}

