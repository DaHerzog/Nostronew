//
//  CubeMap.hpp
//  Nostronew
//
//  Created by David Herzog on 18.02.17.
//  Copyright © 2017 HS Osnabrueck. All rights reserved.
//

#ifndef CubeMap_hpp
#define CubeMap_hpp

#include <stdio.h>
#include "Texture.h"
#include "Model.h"
#include "RGBImage.hpp"


class CubeMap {
public:
    CubeMap();
    ~CubeMap();
    void init(const char* p_PathForTextures, const char* p_PathForVertex, const char* p_PathForFragment);
    ShaderProgram* getShader();
    void applyCubeMapTextures();
    GLuint getVertexBuffer();
    GLuint getIndexBuffer();
    unsigned int getVertexCount();
protected:
    void setOpenGLParameters();
    void initVertices();
    Texture* m_TextureFront;
    Texture* m_TextureBack;
    Texture* m_TextureLeft;
    Texture* m_TextureRight;
    Texture* m_TextureTop;
    Texture* m_TextureBottom;
    Vertex* m_Vertices;
    unsigned int* m_Indices;
    unsigned int m_VertexCount;
    ShaderProgram* m_Shader;
    GLuint m_TextureID;
    GLuint m_VertexBuffer;
    GLuint m_IndexBuffer;
};

#endif /* CubeMap_hpp */
