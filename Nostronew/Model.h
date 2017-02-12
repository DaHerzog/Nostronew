//
//  Model.h
//  RealtimeRending
//
//  Created by Philipp Lensing on 23.10.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//

#ifndef __RealtimeRending__Model__
#define __RealtimeRending__Model__

#include <iostream>
#include "Vector.hpp"
#include "Color.hpp"
#include <string>
#include <map>
#include <vector>
#include "material.h"
#include "ShaderProgram.hpp"

struct Vertex
{
    Vertex();
    Vertex( const Vector& p, const Vector& n, float TexS, float TexT);
    Vector Position;
    Vector Normal;
    float  TexcoordS;
    float  TexcoordT;
};

struct Face
{
    unsigned int pidx[3], tidx[3], nidx[3];
};

struct Texcoord
{
    float s,t;
};

struct materialGroup {
    char name[128];
    Material* material;
    unsigned int first;
    unsigned int last;
};

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox( const Vector& min, const Vector& max);
    Vector Min;
    Vector Max;
    void drawLines() const;
    void createBox();
protected:
    Vertex* m_pVertices;
    unsigned int m_VertexCount;
    
};

class Model
{
public:
    Model();
    ~Model();
    const BoundingBox& boundingBox() const;
    void drawLines() const;
    void drawTriangles();
    ShaderProgram& getModelShader();
    void setModelShader(ShaderProgram& newShader);
    unsigned int getMaterialCount();
    void setMaterialCount(unsigned int p_Count);
    materialGroup* getMatGroupsPerformance();
    void setMatGroupsPerformance(materialGroup* newGroup);
    GLuint& getVertexBuffer();
    GLuint& getIndexBuffer();
    GLuint& getVertexAttributeBuffer();
    void setVertexCount(unsigned int p_Count);
    unsigned int getVertexCount();
    void setBoundingBox(BoundingBox& p_Box);
    BoundingBox& getBoundingBox();
    void setMatGroupCount(unsigned int p_Count);
    unsigned int getMatGroupCount();
    void setMaterials(Material* p_Materials);
    Material* getMaterials();
    void setVertices(Vertex* p_Vertices);
    Vertex* getVertices();
    void setIndices(unsigned int* p_Indices);
    unsigned int* getIndices();
    
protected:
    Vector* m_Pos;
    Vector* m_Dir;
    void createCube();
    Material* m_pMaterials;
    unsigned int m_MaterialCount;
    Vertex* m_pVertices;
    unsigned int* m_Indices;
    unsigned int m_VertexCount;
    BoundingBox m_Box;
    materialGroup* m_MatGroupsPerformance;
    unsigned int m_MatGroupCount;
    ShaderProgram m_ModelShader;
    GLuint m_VertexBuffer;
    GLuint m_IndexBuffer;
    GLuint m_VertexAttributeBuffer;
};

#endif /* defined(__RealtimeRending__Model__) */
