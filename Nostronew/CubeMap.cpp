//
//  CubeMap.cpp
//  Nostronew
//
//  Created by David Herzog on 18.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#include "CubeMap.hpp"

CubeMap::CubeMap() {
    this->m_TextureFront = new Texture();
    this->m_TextureBack = new Texture();
    this->m_TextureLeft = new Texture();
    this->m_TextureRight = new Texture();
    this->m_TextureTop = new Texture();
    this->m_TextureBottom = new Texture();
}

CubeMap::CubeMap(float p_Scale) {
    this->m_TextureFront = new Texture();
    this->m_TextureBack = new Texture();
    this->m_TextureLeft = new Texture();
    this->m_TextureRight = new Texture();
    this->m_TextureTop = new Texture();
    this->m_TextureBottom = new Texture();
    this->m_Scale = p_Scale;
}



CubeMap::~CubeMap() {
    
}

/*
 * Diese Methode läd die entsprechenden Texturen für die Skybox. Zudem ruft sie die restlichen Methoen dieser Klasse
 * auf.
*/
void CubeMap::init(const char* p_PathForTextures, const char* p_PathForVertex, const char* p_PathForFragment) {
    
    char pathForFrontTex[256];
    strcpy(pathForFrontTex, p_PathForTextures);
    strcat(pathForFrontTex, "cubemap_front.bmp");
    if (this->m_TextureFront->LoadFromBMPForCubeMap(pathForFrontTex)) {
        std::cout << "Texture: " << pathForFrontTex << " succesfully loaded" << std::endl;
    } else {
        std::cout << "Failed to load Texture: " << pathForFrontTex << std::endl;
    }
    
    char pathForBackTex[256];
    strcpy(pathForBackTex, p_PathForTextures);
    strcat(pathForBackTex, "cubemap_back.bmp");
    if (this->m_TextureBack->LoadFromBMPForCubeMap(pathForBackTex)) {
        std::cout << "Texture: " << pathForBackTex << " succesfully loaded" << std::endl;
    } else {
        std::cout << "Failed to load Texture: " << pathForBackTex << std::endl;
    }
    
    char pathForLeftTex[256];
    strcpy(pathForLeftTex, p_PathForTextures);
    strcat(pathForLeftTex, "cubemap_left.bmp");
    if (this->m_TextureLeft->LoadFromBMPForCubeMap(pathForLeftTex)) {
        std::cout << "Texture: " << pathForLeftTex << " succesfully loaded" << std::endl;
    } else {
        std::cout << "Failed to load Texture: " << pathForLeftTex << std::endl;
    }
    
    char pathForRightTex[256];
    strcpy(pathForRightTex, p_PathForTextures);
    strcat(pathForRightTex, "cubemap_right.bmp");
    if (this->m_TextureRight->LoadFromBMPForCubeMap(pathForRightTex)) {
        std::cout << "Texture: " << pathForRightTex << " succesfully loaded" << std::endl;
    } else {
        std::cout << "Failed to load Texture: " << pathForRightTex << std::endl;
    }
    
    char pathForTopTex[256];
    strcpy(pathForTopTex, p_PathForTextures);
    strcat(pathForTopTex, "cubemap_top.bmp");
    if (this->m_TextureTop->LoadFromBMPForCubeMap(pathForTopTex)) {
        std::cout << "Texture: " << pathForTopTex << " succesfully loaded" << std::endl;
    } else {
        std::cout << "Failed to load Texture: " << pathForTopTex << std::endl;
    }
    
    char pathForBottomTex[256];
    strcpy(pathForBottomTex, p_PathForTextures);
    strcat(pathForBottomTex, "cubemap_bottom.bmp");
    if (this->m_TextureBottom->LoadFromBMPForCubeMap(pathForBottomTex)) {
        std::cout << "Texture: " << pathForBottomTex << " succesfully loaded" << std::endl;
    } else {
        std::cout << "Failed to load Texture: " << pathForBottomTex << std::endl;
    }
    
    this->setOpenGLParameters();
    this->initVertices();
    
    this->m_Shader = new ShaderProgram();
    this->m_Shader->load(p_PathForVertex, p_PathForFragment);
    this->m_Shader->compile();
        
    
    
}

/*
 * Die Skybox benötigt, anders als andere 2D Texturen, besondere OpenGL Parameter. Diese werden hier gesetzt.
 *
 */
void CubeMap::setOpenGLParameters() {
    
    glGenTextures(1, &this->m_TextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_TextureID);
    
    
    const RGBImage* frontImage = this->m_TextureFront->getRGBImage();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, frontImage->width(), frontImage->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_TextureFront->getData());
    
    const RGBImage* backImage = this->m_TextureBack->getRGBImage();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, backImage->width(), backImage->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_TextureBack->getData());
    
    const RGBImage* leftImage = this->m_TextureLeft->getRGBImage();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, leftImage->width(), leftImage->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_TextureLeft->getData());
    
    const RGBImage* rightImage = this->m_TextureRight->getRGBImage();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, rightImage->width(), rightImage->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_TextureRight->getData());
    
    const RGBImage* topImage = this->m_TextureTop->getRGBImage();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, topImage->width(), topImage->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_TextureTop->getData());
    
    const RGBImage* bottomImage = this->m_TextureBottom->getRGBImage();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, bottomImage->width(), bottomImage->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_TextureBottom->getData());
    
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
}

/*
 * Erstellung eines Würfels mit anschließender Skalierung. Zudem werden die Buffer für
 * die Grafikkarte erstellt.
 */
void CubeMap::initVertices() {
    
    this->m_VertexCount = 36;
    
    Vector Positions[36] =
    {
        Vector(-1.0f,  1.0f, -1.0f),
        Vector(-1.0f, -1.0f, -1.0f),
        Vector(1.0f, -1.0f, -1.0f),
        Vector(1.0f, -1.0f, -1.0f),
        Vector(1.0f,  1.0f, -1.0f),
        Vector(-1.0f,  1.0f, -1.0f),
        
        Vector(-1.0f, -1.0f,  1.0f),
        Vector(-1.0f, -1.0f, -1.0f),
        Vector(-1.0f,  1.0f, -1.0f),
        Vector(-1.0f,  1.0f, -1.0f),
        Vector(-1.0f,  1.0f,  1.0f),
        Vector(-1.0f, -1.0f,  1.0f),
        
        Vector(1.0f, -1.0f, -1.0f),
        Vector(1.0f, -1.0f,  1.0f),
        Vector(1.0f,  1.0f,  1.0f),
        Vector(1.0f,  1.0f,  1.0f),
        Vector(1.0f,  1.0f, -1.0f),
        Vector(1.0f, -1.0f, -1.0f),
        
        Vector(-1.0f, -1.0f,  1.0f),
        Vector(-1.0f,  1.0f,  1.0f),
        Vector(1.0f,  1.0f,  1.0f),
        Vector(1.0f,  1.0f,  1.0f),
        Vector(1.0f, -1.0f,  1.0f),
        Vector(-1.0f, -1.0f,  1.0f),
        
        Vector(-1.0f,  1.0f, -1.0f),
        Vector(1.0f,  1.0f, -1.0f),
        Vector(1.0f,  1.0f,  1.0f),
        Vector(1.0f,  1.0f,  1.0f),
        Vector(-1.0f,  1.0f,  1.0f),
        Vector(-1.0f,  1.0f, -1.0f),
        
        Vector(-1.0f, -1.0f, -1.0f),
        Vector(-1.0f, -1.0f,  1.0f),
        Vector(1.0f, -1.0f, -1.0f),
        Vector(1.0f, -1.0f, -1.0f),
        Vector(-1.0f, -1.0f,  1.0f),
        Vector(1.0f, -1.0f,  1.0f)
    };
    
    
    for (int k = 0; k < 36; k++) {
        Positions[k] = Positions[k]*this->m_Scale;
    }
    
    
    this->m_Vertices = new Vertex[this->m_VertexCount];
    
    for(int i=0; i<36; i++ )
    {
        this->m_Vertices[i].Position.X = Positions[i].X;
        this->m_Vertices[i].Position.Y = Positions[i].Y;
        this->m_Vertices[i].Position.Z = Positions[i].Z;
        
    }
    
    this->m_Indices = new unsigned int[36];
    
    for (int j = 0; j < 36; j++) {
        this->m_Indices[j] = j;
    }
    
    glGenBuffers( 1, &this->m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*this->m_VertexCount, this->m_Vertices, GL_STATIC_DRAW );
    
    
    
    glGenBuffers( 1, &this->m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*this->m_VertexCount, this->m_Indices, GL_STATIC_DRAW);
}

ShaderProgram* CubeMap::getShader() {
    return this->m_Shader;
}

/*
 * Diese Methode übergibt die vorher erstellte CubeMap Textur zur Anwendung an OpenGL
 *
 */
void CubeMap::applyCubeMapTextures() {
    if(this->m_TextureID==0) {
        std::cout << "Textur ID ist 0" << std::endl;
        return;
    }
    
    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_TextureID);

}

GLuint CubeMap::getVertexBuffer() {
    return this->m_VertexBuffer;
}

GLuint CubeMap::getIndexBuffer() {
    return this->m_IndexBuffer;
}

unsigned int CubeMap::getVertexCount() {
    return this->m_VertexCount;
}

GLuint CubeMap::getTextureID() {
    return this->m_TextureID;
}
