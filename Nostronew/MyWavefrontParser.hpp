//
//  MyWavefrontParser.hpp
//  Nostronew
//
//  Created by David Herzog on 16.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//
//  Diese Klasse dient dem Laden eines Models. In der loadModel() Methode wird entschieden,
//  von welcher Quelle die Wavefront Datei stammt. Dementsprechend wird die jeweilige private
//  Methode aufgerufen.
//
//  Die Klasse "Model" verfügt nicht mehr über eine load() Methode.
//

#ifndef MyWavefrontParser_hpp
#define MyWavefrontParser_hpp

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "Model.h"

enum ImportType {
    CINEMA, PRAKTIKUM
};

class MyWavefrontParser {
public:
    static ImportType m_UsedProgram;
    static const char* m_MainPath;
    static float m_Scale;
    static bool loadModel(Model* p_Model, const char* p_Filename, bool p_Fitsize);
private:
    static bool loadFromCinema(Model* p_Model, const char* p_Filename, bool p_Fitsize);
    static bool loadFromPraktikum(Model* p_Model, const char* p_Filename, bool p_Fitsize);
    static void checkForErrors();
};

#endif /* MyWavefrontParser_hpp */
