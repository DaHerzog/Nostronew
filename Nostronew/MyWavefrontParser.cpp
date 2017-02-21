//
//  MyWavefrontParser.cpp
//  Nostronew
//
//  Created by David Herzog on 16.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//

#include "MyWavefrontParser.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//
//  Hier die gewünschte Quelle eintragen. PRAKTIKUM, CINEMA
//
ImportType MyWavefrontParser::m_UsedProgram = CINEMA;

//
//  Hier wird der Hauptpfad angegeben in dem die Models liegen.
//
char* MyWavefrontParser::m_MainPath = "";

//
//  Skalierungsfaktor, falls gewünscht.
//
float MyWavefrontParser::m_Scale = 0.09f;


bool MyWavefrontParser::loadModel(Model* p_Model, const char* p_Filename, bool p_Fitsize) {
    switch (m_UsedProgram) {
        case PRAKTIKUM:
            if (!MyWavefrontParser::loadFromPraktikum(p_Model, p_Filename, p_Fitsize)) {
                return false;
            }
            break;
        case CINEMA:
            if (!MyWavefrontParser::loadFromCinema(p_Model, p_Filename, p_Fitsize)) {
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

//
//  Cinema 4D hat die f v/vt/vn Syntax. Die Normale, welche wir für den Phong Shader benutzen,
//  wird von Cinema 4D schon berechnet. Diese Methode wurde somit für die Verwendung dieser Normalen
//  angepasst.
//
bool MyWavefrontParser::loadFromCinema(Model *p_Model, const char* p_Filename, bool p_Fitsize) {
    
    std::cout << "Loading " << p_Filename << "..." << std::endl;
    
    char pathForModel[256];
    char pathForMaterial[256];
    std::ifstream inputStream;
    strcpy(pathForModel, m_MainPath);
    strcpy(pathForMaterial, m_MainPath);
    
    strcat(pathForModel, p_Filename);
    inputStream.open(pathForModel);
    
    std::string directory;
    std::stringstream streamForMaterialPath(p_Filename);
    getline(streamForMaterialPath, directory, '/');
    strcat(pathForMaterial, directory.c_str());
    strcat(pathForMaterial, "/");
    
    char directoryForBmps[256];
    strcpy(directoryForBmps, pathForMaterial);
    
    bool faceIdxCounterActive = false;
    char buffer[256];
    char bufferForMat[256];
    char materialName[64];
    std::string tempForLineCut;
    std::string tempForNumber;
    std::vector<Vector>* positionsFromFile = new std::vector<Vector>();
    std::vector<Vector>* normalsFromFile = new std::vector<Vector>();
    std::vector<Texcoord>* texcoordFromFile = new std::vector<Texcoord>();
    std::vector<Face>* facesFromFile = new std::vector<Face>();
    
    std::vector<materialGroup>* matGroups = new std::vector<materialGroup>();
    int faceIdxForMat = 0;
    int materialIdx = -1;
    
    if (inputStream.is_open()) {
        
        while(!inputStream.eof()) {
            inputStream.getline(buffer, sizeof(buffer));
            std::string tempLine(buffer);
            if (buffer[0] == 'm' && buffer[1] == 't' && buffer[2] == 'l') {
                sscanf(tempLine.c_str(), "mtllib ./%s", materialName);
                strcat(pathForMaterial, materialName);
                //Material Datei einlesen
                std::ifstream inputStreamForMat;
                inputStreamForMat.open(pathForMaterial);
                if (inputStreamForMat.is_open()) {
                    while(!inputStreamForMat.eof()) {
                        inputStreamForMat.getline(bufferForMat, sizeof(bufferForMat));
                        if (bufferForMat[0] == 'n' && bufferForMat[1] == 'e' && bufferForMat[2] == 'w' && bufferForMat[3] == 'm') {
                            p_Model->setMaterialCount(p_Model->getMaterialCount()+1);
                        }
                    }
                    
                    inputStreamForMat.clear();
                    inputStreamForMat.seekg(0, std::ios::beg);
                    
                    p_Model->setMaterials(new Material[p_Model->getMaterialCount()]);
                    
                    while(!inputStreamForMat.eof()) {
                        inputStreamForMat.getline(bufferForMat, sizeof(bufferForMat));
                        std::string tempLineForMat(bufferForMat);
                        
                        if (bufferForMat[0] == 'n' && bufferForMat[1] == 'e' && bufferForMat[2] == 'w' && bufferForMat[3] == 'm') {
                            materialIdx++;
                            p_Model->getMaterials()[materialIdx] = Material();
                            char tmpName[128];
                            sscanf(tempLineForMat.c_str(), "newmtl %s", tmpName);
                            p_Model->getMaterials()[materialIdx].setName(std::string(tmpName));
                        } else if (bufferForMat[0] == 'N' && bufferForMat[1] == 's') {
                            float tmpNs;
                            sscanf(tempLineForMat.c_str(), "Ns %f", &tmpNs);
                            p_Model->getMaterials()[materialIdx].setSpecularExponent(tmpNs);
                        } else if (bufferForMat[0] == 'K' && bufferForMat[1] == 'a') {
                            float tmpR, tmpG, tmpB;
                            sscanf(tempLineForMat.c_str(), "Ka %f %f %f", &tmpR, &tmpG, &tmpB);
                            p_Model->getMaterials()[materialIdx].setAmbientColor(Color(tmpR, tmpG, tmpB));
                        } else if(bufferForMat[0] == 'K' && bufferForMat[1] == 'd') {
                            float tmpR, tmpG, tmpB;
                            sscanf(tempLineForMat.c_str(), "Kd %f %f %f", &tmpR, &tmpG, &tmpB);
                            p_Model->getMaterials()[materialIdx].setDiffuseColor(Color(tmpR, tmpG, tmpB));
                        } else if (bufferForMat[0] == 'K' && bufferForMat[1] == 's') {
                            float tmpR, tmpG, tmpB;
                            sscanf(tempLineForMat.c_str(), "Ks %f %f %f", &tmpR, &tmpG, &tmpB);
                            p_Model->getMaterials()[materialIdx].setSpecularColor(Color(tmpR, tmpG, tmpB));
                            
                        } else if (bufferForMat[0] == 'm' && bufferForMat[1] == 'a' && bufferForMat[2] == 'p' && bufferForMat[3] == '_' && bufferForMat[4] == 'K' && bufferForMat[5] == 'd') {
                            char texName[128];
                            char texPath[256];
                            sscanf(tempLineForMat.c_str(), "map_Kd %s", texName);
                            strcpy(texPath, directoryForBmps);
                            strcat(texPath, texName);
                            p_Model->getMaterials()[materialIdx].setDiffuseTexture(texPath);
                            
                        }
                    }
                } else {
                    std::cout << "Material Datei nicht gefunden!" << std::endl;
                    std::cout << "Pfad: " << pathForMaterial << std::endl;
                }
                
            } else if (buffer[0] == 'v' && buffer[1] == ' ') {
                float tmpPosX, tmpPosY, tmpPosZ;
                sscanf(tempLine.c_str(), "v %f %f %f", &tmpPosX, &tmpPosY, &tmpPosZ);
                Vector tempPos(tmpPosX, tmpPosY, tmpPosZ);
                positionsFromFile->push_back(tempPos);
            } else if (buffer[0] == 'v' && buffer[1] == 't') {
                float tmpTexS, tmpTexT, tmpTexIgnore;
                //Die letzte Koordinate von den Texturen wird ignoriert
                sscanf(tempLine.c_str(), "vt %f %f %f", &tmpTexS, &tmpTexT, &tmpTexIgnore);
                Texcoord tempTexCoord;
                tempTexCoord.s = tmpTexS;
                tempTexCoord.t = tmpTexT;
                texcoordFromFile->push_back(tempTexCoord);
            } else if(buffer[0] == 'v' && buffer[1] == 'n') {
                float tmpNormX, tmpNormY, tmpNormZ;
                sscanf(tempLine.c_str(), "vn %f %f %f", &tmpNormX, &tmpNormY, &tmpNormZ);
                //std::cout << "Normale X: " << tmpNormX << " Y: " << tmpNormY << " Z: " << tmpNormZ << std::endl;
                Vector tmpNorm(tmpNormX, tmpNormY, tmpNormZ);
                normalsFromFile->push_back(tmpNorm);
            } else if (buffer[0] == 'f') {
                if (std::count(tempLine.begin(), tempLine.end(), ' ') == 4) {
                    if (faceIdxCounterActive) {
                        faceIdxForMat += 6;
                    }
                    Face tempFace;
                    unsigned int tmpPidx;
                    unsigned int tmpTidx;
                    unsigned int tmpNormal;
                    sscanf(tempLine.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u %u/%u/%u", &tempFace.pidx[0], &tempFace.tidx[0], &tempFace.nidx[0], &tempFace.pidx[1], &tempFace.tidx[1], &tempFace.nidx[1], &tempFace.pidx[2], &tempFace.tidx[2], &tempFace.nidx[2], &tmpPidx, &tmpTidx, &tmpNormal);
                    
                    // Aus einem Quadrat zwei Dreiecke machen....
                    Face tempFace2;
                    tempFace2.pidx[0] = tempFace.pidx[0];
                    tempFace2.pidx[1] = tempFace.pidx[2];
                    tempFace2.pidx[2] = tmpPidx;
                    
                    tempFace2.tidx[0] = tempFace.tidx[0];
                    tempFace2.tidx[1] = tempFace.tidx[2];
                    tempFace2.tidx[2] = tmpTidx;
                    
                    tempFace2.nidx[0] = tempFace.nidx[0];
                    tempFace2.nidx[1] = tempFace.nidx[2];
                    tempFace2.nidx[2] = tmpNormal;
                    
                    facesFromFile->push_back(tempFace);
                    facesFromFile->push_back(tempFace2);
                    
                } else if (std::count(tempLine.begin(), tempLine.end(), ' ') == 3) {
                    if (faceIdxCounterActive) {
                        faceIdxForMat+=3;
                    }
                    
                    Face tempFace;
                    sscanf(tempLine.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u", &tempFace.pidx[0], &tempFace.tidx[0], &tempFace.nidx[0], &tempFace.pidx[1], &tempFace.tidx[1], &tempFace.nidx[1], &tempFace.pidx[2], &tempFace.tidx[2], &tempFace.nidx[2]);
                    facesFromFile->push_back(tempFace);
                    
                }
            } else if (buffer[0] == 'u' && buffer[1] == 's' && buffer[2] == 'e' && buffer[3] == 'm' && buffer[4] == 't' && buffer[5] == 'l') {
                if (!matGroups->empty()) {
                    matGroups->back().last = faceIdxForMat-1;
                }
                matGroups->push_back(materialGroup());
                matGroups->back().first = faceIdxForMat;
                sscanf(tempLine.c_str(), "usemtl %s", matGroups->back().name);
                
                faceIdxCounterActive = true;
            }
        }
        //setzen des Index für das letzte Material
        if (!matGroups->empty()) {
            matGroups->back().last = faceIdxForMat;
        }
        
        for (int y = 0; y < matGroups->size(); y++) {
            
            for (int z = 0; z < p_Model->getMaterialCount(); z++) {
                if (strcmp(matGroups->at(y).name, p_Model->getMaterials()[z].getName().c_str()) == 0) {
                    matGroups->at(y).material = &(p_Model->getMaterials()[z]);
                }
            }
            
        }
        
        
        //kopieren der matGroups ins dafür vorgesehene Array (aus Performancegründen)
        p_Model->setMatGroupCount(matGroups->size());
        p_Model->setMatGroupsPerformance(new materialGroup[p_Model->getMatGroupCount()]);
        for (int ctr = 0; ctr < p_Model->getMatGroupCount(); ctr++) {
            strcpy(p_Model->getMatGroupsPerformance()[ctr].name, matGroups->at(ctr).name);
            p_Model->getMatGroupsPerformance()[ctr].first = matGroups->at(ctr).first;
            //std::cout << "First: " << matGroupsPerformance[ctr].first << std::endl;
            p_Model->getMatGroupsPerformance()[ctr].last = matGroups->at(ctr).last;
            //std::cout << "Last: " << matGroupsPerformance[ctr].last << std::endl;
            p_Model->getMatGroupsPerformance()[ctr].material = matGroups->at(ctr).material;
        }
        
        
        
        p_Model->setVertices(new Vertex[facesFromFile->size()*3]);
        p_Model->setVertexCount(facesFromFile->size()*3);
        
        
        int i = 0;
        for(i=0; i<facesFromFile->size(); i++ )
        {
            unsigned int PosIdx0 = facesFromFile->at(i).pidx[0]-1;
            unsigned int PosIdx1 = facesFromFile->at(i).pidx[1]-1;
            unsigned int PosIdx2 = facesFromFile->at(i).pidx[2]-1;
            
            unsigned int TexIdx0 = facesFromFile->at(i).tidx[0]-1;
            unsigned int TexIdx1 = facesFromFile->at(i).tidx[1]-1;
            unsigned int TexIdx2 = facesFromFile->at(i).tidx[2]-1;
            
            unsigned int NormIdx0 = facesFromFile->at(i).nidx[0]-1;
            unsigned int NormIdx1 = facesFromFile->at(i).nidx[1]-1;
            unsigned int NormIdx2 = facesFromFile->at(i).nidx[2]-1;
            
            p_Model->getVertices()[i*3].Position = positionsFromFile->at(PosIdx0);
            p_Model->getVertices()[i*3+1].Position = positionsFromFile->at(PosIdx1);
            p_Model->getVertices()[i*3+2].Position = positionsFromFile->at(PosIdx2);
            
            p_Model->getVertices()[i*3].Normal = normalsFromFile->at(NormIdx0);
            p_Model->getVertices()[i*3+1].Normal = normalsFromFile->at(NormIdx1);
            p_Model->getVertices()[i*3+2].Normal = normalsFromFile->at(NormIdx2);
            
            p_Model->getVertices()[i*3].TexcoordS = texcoordFromFile->at(TexIdx0).s;
            p_Model->getVertices()[i*3+1].TexcoordS = texcoordFromFile->at(TexIdx1).s;
            p_Model->getVertices()[i*3+2].TexcoordS = texcoordFromFile->at(TexIdx2).s;
            
            p_Model->getVertices()[i*3].TexcoordT = texcoordFromFile->at(TexIdx0).t;
            p_Model->getVertices()[i*3+1].TexcoordT = texcoordFromFile->at(TexIdx1).t;
            p_Model->getVertices()[i*3+2].TexcoordT = texcoordFromFile->at(TexIdx2).t;
            
        }
        
        p_Model->setIndices(new unsigned int[p_Model->getVertexCount()]);
        //Erstellung des Indices Array für die Array Buffer der Grafikkarte
        //Das die Vertices schon sortiert wurden, kann diese einfache Reienfolge gewählt werden
        for (i = 0; i < p_Model->getVertexCount(); i++) {
            p_Model->getIndices()[i] = i;
        }
        
        //Skalierung des gesamten Models, falls gewünscht.
        if (p_Fitsize) {
            for (int i = 0; i < p_Model->getVertexCount(); i++) {
                p_Model->getVertices()[i].Position = p_Model->getVertices()[i].Position * m_Scale;
            }
        }
        
        
        //Erstellung der Bounding Box
        float minX, minY, minZ, maxX, maxY, maxZ;
        
        minX = maxX = 0;
        minY = maxY = 0;
        minZ = maxZ = 0;
        
        //Ermittlung der Minima und Maxima
        for (int j = 0; j < p_Model->getVertexCount(); j++) {
            if (p_Model->getVertices()[j].Position.X < minX) {
                minX = p_Model->getVertices()[j].Position.X;
            }
            if (p_Model->getVertices()[j].Position.Y < minY) {
                minY = p_Model->getVertices()[j].Position.Y;
            }
            if (p_Model->getVertices()[j].Position.Z < minZ) {
                minZ = p_Model->getVertices()[j].Position.Z;
            }
            if (p_Model->getVertices()[j].Position.X > maxX) {
                maxX = p_Model->getVertices()[j].Position.X;
            }
            if (p_Model->getVertices()[j].Position.Y > maxY) {
                maxY = p_Model->getVertices()[j].Position.Y;
            }
            if (p_Model->getVertices()[j].Position.Z > maxZ) {
                maxZ = p_Model->getVertices()[j].Position.Z;
            }
        }
        
        BoundingBox BBox(Vector(minX, minY, minZ), Vector(maxX, maxY, maxZ));
        p_Model->setBoundingBox(BBox);
        p_Model->getBoundingBox().createBox();
        
    } else {
        std::cout << "Datei wurde nicht gefunden!" << std::endl;
        return false;
    }
    
    //createCube();
    inputStream.close();
    
    glGenBuffers( 1, &p_Model->getVertexBuffer());
    glBindBuffer(GL_ARRAY_BUFFER, p_Model->getVertexBuffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*p_Model->getVertexCount(), p_Model->getVertices(), GL_STATIC_DRAW );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers( 1, &p_Model->getIndexBuffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_Model->getIndexBuffer());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*p_Model->getVertexCount(), p_Model->getIndices(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    
    delete positionsFromFile;
    delete texcoordFromFile;
    delete facesFromFile;
    
    std::cout << "Finished loading " << p_Filename << "..." << std::endl;
    
    return true;
}

bool MyWavefrontParser::loadFromPraktikum(Model *p_Model, const char* p_Filename, bool p_Fitsize) {
    
    char pathForModel[256];
    char pathForMaterial[256];
    std::ifstream inputStream;
    strcpy(pathForModel, m_MainPath);
    strcpy(pathForMaterial, m_MainPath);
    
    strcat(pathForModel, p_Filename);
    inputStream.open(pathForModel);
    
    std::string directory;
    std::stringstream streamForMaterialPath(p_Filename);
    getline(streamForMaterialPath, directory, '/');
    strcat(pathForMaterial, directory.c_str());
    strcat(pathForMaterial, "/");
    
    char directoryForBmps[256];
    strcpy(directoryForBmps, pathForMaterial);
    
    bool faceIdxCounterActive = false;
    char buffer[256];
    char bufferForMat[256];
    char materialName[64];
    std::string tempForLineCut;
    std::string tempForNumber;
    std::vector<Vector>* positionsFromFile = new std::vector<Vector>();
    std::vector<Texcoord>* texcoordFromFile = new std::vector<Texcoord>();
    std::vector<Face>* facesFromFile = new std::vector<Face>();
    
    std::vector<materialGroup>* matGroups = new std::vector<materialGroup>();
    int faceIdxForMat = 0;
    int materialIdx = -1;
    
    if (inputStream.is_open()) {
        
        while(!inputStream.eof()) {
            inputStream.getline(buffer, sizeof(buffer));
            std::string tempLine(buffer);
            if (buffer[0] == 'm' && buffer[1] == 't' && buffer[2] == 'l') {
                sscanf(tempLine.c_str(), "mtllib %s", materialName);
                strcat(pathForMaterial, materialName);
                
                std::cout << materialName << std::endl;
                //Material Datei einlesen
                std::ifstream inputStreamForMat;
                inputStreamForMat.open(pathForMaterial);
                if (inputStreamForMat.is_open()) {
                    while(!inputStreamForMat.eof()) {
                        inputStreamForMat.getline(bufferForMat, sizeof(bufferForMat));
                        if (bufferForMat[0] == 'n' && bufferForMat[1] == 'e' && bufferForMat[2] == 'w' && bufferForMat[3] == 'm') {
                            p_Model->setMaterialCount(p_Model->getMaterialCount()+1);
                        }
                    }
                    
                    inputStreamForMat.clear();
                    inputStreamForMat.seekg(0, std::ios::beg);
                    
                    p_Model->setMaterials(new Material[p_Model->getMaterialCount()]);
                    
                    while(!inputStreamForMat.eof()) {
                        inputStreamForMat.getline(bufferForMat, sizeof(bufferForMat));
                        std::string tempLineForMat(bufferForMat);
                        
                        if (bufferForMat[0] == 'n' && bufferForMat[1] == 'e' && bufferForMat[2] == 'w' && bufferForMat[3] == 'm') {
                            materialIdx++;
                            p_Model->getMaterials()[materialIdx] = Material();
                            char tmpName[128];
                            sscanf(tempLineForMat.c_str(), "newmtl %s", tmpName);
                            p_Model->getMaterials()[materialIdx].setName(std::string(tmpName));
                        } else if (bufferForMat[0] == '\t' && bufferForMat[1] == 'N' && bufferForMat[2] == 's') {
                            float tmpNs;
                            sscanf(tempLineForMat.c_str(), "\tNs %f", &tmpNs);
                            p_Model->getMaterials()[materialIdx].setSpecularExponent(tmpNs);
                        } else if (bufferForMat[0] == '\t' && bufferForMat[1] == 'K' && bufferForMat[2] == 'a') {
                            float tmpR, tmpG, tmpB;
                            sscanf(tempLineForMat.c_str(), "\tKa %f %f %f", &tmpR, &tmpG, &tmpB);
                            p_Model->getMaterials()[materialIdx].setAmbientColor(Color(tmpR, tmpG, tmpB));
                        } else if(bufferForMat[0] == '\t' && bufferForMat[1] == 'K' && bufferForMat[2] == 'd') {
                            float tmpR, tmpG, tmpB;
                            sscanf(tempLineForMat.c_str(), "\tKd %f %f %f", &tmpR, &tmpG, &tmpB);
                            p_Model->getMaterials()[materialIdx].setDiffuseColor(Color(tmpR, tmpG, tmpB));
                        } else if (bufferForMat[0] == '\t' && bufferForMat[1] == 'K' && bufferForMat[2] == 's') {
                            float tmpR, tmpG, tmpB;
                            sscanf(tempLineForMat.c_str(), "\tKs %f %f %f", &tmpR, &tmpG, &tmpB);
                            p_Model->getMaterials()[materialIdx].setSpecularColor(Color(tmpR, tmpG, tmpB));
                            
                        } else if (bufferForMat[0] == '\t' && bufferForMat[1] == 'm' && bufferForMat[2] == 'a' && bufferForMat[3] == 'p' && bufferForMat[4] == '_' && bufferForMat[5] == 'K' && bufferForMat[6] == 'd') {
                            char texName[128];
                            char texPath[256];
                            sscanf(tempLineForMat.c_str(), "\tmap_Kd %s", texName);
                            strcpy(texPath, directoryForBmps);
                            strcat(texPath, texName);
                            p_Model->getMaterials()[materialIdx].setDiffuseTexture(texPath);
                            
                        }
                    }
                } else {
                    std::cout << "Material Datei nicht gefunden!" << std::endl;
                    std::cout << "Pfad: " << pathForMaterial << std::endl;
                }
                
            } else if (buffer[0] == 'v' && buffer[1] == ' ') {
                float tmpPosX, tmpPosY, tmpPosZ;
                sscanf(tempLine.c_str(), "v %f %f %f", &tmpPosX, &tmpPosY, &tmpPosZ);
                Vector tempPos(tmpPosX, tmpPosY, tmpPosZ);
                positionsFromFile->push_back(tempPos);
            } else if (buffer[0] == 'v' && buffer[1] == 't') {
                float tmpTexS, tmpTexT, tmpTexIgnore;
                //Die letzte Koordinate von den Texturen wird ignoriert
                sscanf(tempLine.c_str(), "vt %f %f %f", &tmpTexS, &tmpTexT, &tmpTexIgnore);
                Texcoord tempTexCoord;
                tempTexCoord.s = tmpTexS;
                tempTexCoord.t = tmpTexT;
                texcoordFromFile->push_back(tempTexCoord);
            } else if (buffer[0] == 'f') {
                if (std::count(tempLine.begin(), tempLine.end(), ' ') == 5) {
                    if (faceIdxCounterActive) {
                        faceIdxForMat += 6;
                    }
                    Face tempFace;
                    unsigned int tmpPidx;
                    unsigned int tmpTidx;
                    sscanf(tempLine.c_str(), "f %u/%u %u/%u %u/%u %u/%u", &tempFace.pidx[0], &tempFace.tidx[0], &tempFace.pidx[1], &tempFace.tidx[1], &tempFace.pidx[2], &tempFace.tidx[2], &tmpPidx, &tmpTidx);
                    
                    // Aus einem Quadrat zwei Dreiecke machen....
                    Face tempFace2;
                    tempFace2.pidx[0] = tempFace.pidx[0];
                    tempFace2.pidx[1] = tempFace.pidx[2];
                    tempFace2.pidx[2] = tmpPidx;
                    
                    tempFace2.tidx[0] = tempFace.tidx[0];
                    tempFace2.tidx[1] = tempFace.tidx[2];
                    tempFace2.tidx[2] = tmpTidx;
                    
                    facesFromFile->push_back(tempFace);
                    facesFromFile->push_back(tempFace2);
                    
                } else if (std::count(tempLine.begin(), tempLine.end(), ' ') == 4) {
                    if (faceIdxCounterActive) {
                        faceIdxForMat+=3;
                    }
                    Face tempFace;
                    sscanf(tempLine.c_str(), "f %u/%u %u/%u %u/%u", &tempFace.pidx[0], &tempFace.tidx[0], &tempFace.pidx[1], &tempFace.tidx[1], &tempFace.pidx[2], &tempFace.tidx[2]);
                    facesFromFile->push_back(tempFace);
                }
            } else if (buffer[0] == 'u' && buffer[1] == 's' && buffer[2] == 'e' && buffer[3] == 'm' && buffer[4] == 't' && buffer[5] == 'l') {
                if (!matGroups->empty()) {
                    matGroups->back().last = faceIdxForMat-1;
                }
                matGroups->push_back(materialGroup());
                matGroups->back().first = faceIdxForMat;
                sscanf(tempLine.c_str(), "usemtl %s", matGroups->back().name);
                
                faceIdxCounterActive = true;
            }
        }
        //setzen des Index für das letzte Material
        if (!matGroups->empty()) {
            matGroups->back().last = faceIdxForMat;
        }
        
        for (int y = 0; y < matGroups->size(); y++) {
            
            for (int z = 0; z < p_Model->getMaterialCount(); z++) {
                if (strcmp(matGroups->at(y).name, p_Model->getMaterials()[z].getName().c_str()) == 0) {
                    matGroups->at(y).material = &(p_Model->getMaterials()[z]);
                }
            }
            
        }
        
        
        //kopieren der matGroups ins dafür vorgesehene Array (aus Performancegründen)
        p_Model->setMatGroupCount(matGroups->size());
        p_Model->setMatGroupsPerformance(new materialGroup[p_Model->getMatGroupCount()]);
        for (int ctr = 0; ctr < p_Model->getMatGroupCount(); ctr++) {
            strcpy(p_Model->getMatGroupsPerformance()[ctr].name, matGroups->at(ctr).name);
            p_Model->getMatGroupsPerformance()[ctr].first = matGroups->at(ctr).first;
            //std::cout << "First: " << matGroupsPerformance[ctr].first << std::endl;
            p_Model->getMatGroupsPerformance()[ctr].last = matGroups->at(ctr).last;
            //std::cout << "Last: " << matGroupsPerformance[ctr].last << std::endl;
            p_Model->getMatGroupsPerformance()[ctr].material = matGroups->at(ctr).material;
        }
        
        
        
        
        p_Model->setVertices(new Vertex[facesFromFile->size()*3]);
        p_Model->setVertexCount(facesFromFile->size()*3);
        int i = 0;
        for(i=0; i<facesFromFile->size(); i++ )
        {
            unsigned int PosIdx0 = facesFromFile->at(i).pidx[0]-1;
            unsigned int PosIdx1 = facesFromFile->at(i).pidx[1]-1;
            unsigned int PosIdx2 = facesFromFile->at(i).pidx[2]-1;
            
            unsigned int TexIdx0 = facesFromFile->at(i).tidx[0]-1;
            unsigned int TexIdx1 = facesFromFile->at(i).tidx[1]-1;
            unsigned int TexIdx2 = facesFromFile->at(i).tidx[2]-1;
            
            Vector a = p_Model->getVertices()[i*3].Position = positionsFromFile->at(PosIdx0);
            Vector b = p_Model->getVertices()[i*3+1].Position = positionsFromFile->at(PosIdx1);
            Vector c = p_Model->getVertices()[i*3+2].Position = positionsFromFile->at(PosIdx2);
            
            p_Model->getVertices()[i*3].TexcoordS = texcoordFromFile->at(TexIdx0).s;
            p_Model->getVertices()[i*3+1].TexcoordS = texcoordFromFile->at(TexIdx1).s;
            p_Model->getVertices()[i*3+2].TexcoordS = texcoordFromFile->at(TexIdx2).s;
            
            p_Model->getVertices()[i*3].TexcoordT = texcoordFromFile->at(TexIdx0).t;
            p_Model->getVertices()[i*3+1].TexcoordT = texcoordFromFile->at(TexIdx1).t;
            p_Model->getVertices()[i*3+2].TexcoordT = texcoordFromFile->at(TexIdx2).t;
            
            Vector normal = (b-a).cross(c-a);
            normal.normalize();
            
            p_Model->getVertices()[i*3].Normal =
            p_Model->getVertices()[i*3+1].Normal =
            p_Model->getVertices()[i*3+2].Normal = normal;
        }
        
        p_Model->setIndices(new unsigned int[p_Model->getVertexCount()]);
        //Erstellung des Indices Array für die Array Buffer der Grafikkarte
        //Das die Vertices schon sortiert wurden, kann diese einfache Reienfolge gewählt werden
        for (i = 0; i < p_Model->getVertexCount(); i++) {
            p_Model->getIndices()[i] = i;
        }
        
        
        
        //Skalierung des gesamten Models
        if (p_Fitsize) {
            for (int i = 0; i < p_Model->getVertexCount(); i++) {
                p_Model->getVertices()[i].Position = p_Model->getVertices()[i].Position * m_Scale;
            }
        }
        
        
        //Erstellung der Bounding Box
        float minX, minY, minZ, maxX, maxY, maxZ;
        
        minX = maxX = 0;
        minY = maxY = 0;
        minZ = maxZ = 0;
        
        //Ermittlung der Minima und Maxima
        for (int j = 0; j < p_Model->getVertexCount(); j++) {
            if (p_Model->getVertices()[j].Position.X < minX) {
                minX = p_Model->getVertices()[j].Position.X;
            }
            if (p_Model->getVertices()[j].Position.Y < minY) {
                minY = p_Model->getVertices()[j].Position.Y;
            }
            if (p_Model->getVertices()[j].Position.Z < minZ) {
                minZ = p_Model->getVertices()[j].Position.Z;
            }
            if (p_Model->getVertices()[j].Position.X > maxX) {
                maxX = p_Model->getVertices()[j].Position.X;
            }
            if (p_Model->getVertices()[j].Position.Y > maxY) {
                maxY = p_Model->getVertices()[j].Position.Y;
            }
            if (p_Model->getVertices()[j].Position.Z > maxZ) {
                maxZ = p_Model->getVertices()[j].Position.Z;
            }
        }
        
        BoundingBox BBox(Vector(minX, minY, minZ), Vector(maxX, maxY, maxZ));
        p_Model->setBoundingBox(BBox);
        p_Model->getBoundingBox().createBox();
        
    } else {
        std::cout << "Datei wurde nicht gefunden!" << std::endl;
        return false;
    }
    
    //createCube();
    inputStream.close();
    
    glGenBuffers( 1, &p_Model->getVertexBuffer());
    glBindBuffer(GL_ARRAY_BUFFER, p_Model->getVertexBuffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*p_Model->getVertexCount(), p_Model->getVertices(), GL_STATIC_DRAW );
    
    glGenBuffers( 1, &p_Model->getIndexBuffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_Model->getIndexBuffer());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*p_Model->getVertexCount(), p_Model->getIndices(), GL_STATIC_DRAW);
    
    
    
    delete positionsFromFile;
    delete texcoordFromFile;
    delete facesFromFile;
    
    return true;
}

void MyWavefrontParser::checkForErrors() {
    
    GLenum myError = glGetError();
    std::string* error;
    if (myError != GL_NO_ERROR) {
        error = new std::string(reinterpret_cast<const char*>(gluErrorString(myError)));
        std::cout << *error << std::endl;
    } else {
        std::cout << "Errors were checked, nothing's wrong" << std::endl;
    }
    
    
}

void MyWavefrontParser::setMainPath(char *p_MainPath) {
    m_MainPath = p_MainPath;
}
