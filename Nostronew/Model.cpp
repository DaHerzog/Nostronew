//
//  Model.cpp
//  RealtimeRending
//
//  Created by Philipp Lensing on 23.10.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//
//  Diese Klasse verfügt nach dem neuen Design nicht mehr über eine load() Methode.
//
//  Siehe MyWavefrontParser.hpp
//

#ifdef WIN32
	#include <Windows.h>
	#include <GL/glew.h>
	#include <GL/GLUT.h>
	#include <GL/GL.h>
#else
	#include <OpenGL/OpenGL.h>
	#include <GLUT/GLUT.h>
#endif

#include "Model.h"
#include <vector>
#include <assert.h>
#include <math.h>
#include <map>
#include <float.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>


Vertex::Vertex()
{
    
}

Vertex::Vertex( const Vector& p, const Vector& n, float TexS, float TexT)
{
    Position = p;
    Normal = n;
    TexcoordS = TexS;
    TexcoordT = TexT;
}

BoundingBox::BoundingBox()
{
}
BoundingBox::BoundingBox( const Vector& min, const Vector& max) : Min(min), Max(max)
{
}

Model::Model() : m_pVertices(NULL), m_pMaterials(NULL), m_MaterialCount(0), m_VertexCount(0)
{
    
}

Model::~Model()
{
    if( m_pVertices)
        delete [] m_pVertices;
    if(m_pMaterials)
        delete [] m_pMaterials;
}

void Model::createCube()
{
    Vector PositionsFromFile[8] =
    {
        Vector(-1, -1, 1),
        Vector(-1,  1, 1),
        Vector( 1, -1, 1),
        Vector( 1,  1, 1),
        Vector( 1, -1, -1),
        Vector( 1,  1, -1),
        Vector(-1, -1, -1),
        Vector(-1, 1, -1)
    };
    
    Texcoord TexcoordFromFile[20] =
    {
        { 0, 1 },
        { 1, 0 },
        { 0, 0 },
        { 0, 0 },
        { 1, 1 },
        { 0, 1 },
        { 1, 1 },
        { 0, 0 },
        { 1, 0 },
        { 1, 0 },
        { 0, 1 },
        { 1, 1 },
        { 1, 0 },
        { 0, 0 },
        { 1, 1 },
        { 0, 1 },
        { 0, 0 },
        { 1, 0 },
        { 0, 1 },
        { 1, 1 }
    };
    
    Face FacesFromFile[12]
    {
        //face 1
        {3,4,2,   9, 12, 6},
        {3,2,1,   9, 6, 3},
        //face 2
        {5,6,4,   13,15,11},
        {5,4,3,   13,11,8},
        //face 3
        {7,8,6,   18,20,16},
        {7,6,5,   18,16,14},
        //face 4
        {1,2,8,   2,5,19},
        {1,8,7,   2,19,17},
        //face 5
        {4,6,8,   10,15,19},
        {4,8,2,   10,19,4},
        //face 6
        {5,3,1,   13,7,1},
        {5,1,7,   13,1,17}
        
    };
    
    
    m_pVertices = new Vertex[12*3];
    m_VertexCount = 12*3;
    for(int i=0; i<12; i++ )
    {
        unsigned int PosIdx0 = FacesFromFile[i].pidx[0]-1;
        unsigned int PosIdx1 = FacesFromFile[i].pidx[1]-1;
        unsigned int PosIdx2 = FacesFromFile[i].pidx[2]-1;
        
        unsigned int TexIdx0 = FacesFromFile[i].tidx[0]-1;
        unsigned int TexIdx1 = FacesFromFile[i].tidx[1]-1;
        unsigned int TexIdx2 = FacesFromFile[i].tidx[2]-1;
        
        Vector a = m_pVertices[i*3].Position = PositionsFromFile[ PosIdx0];
        Vector b = m_pVertices[i*3+1].Position = PositionsFromFile[ PosIdx1];
        Vector c = m_pVertices[i*3+2].Position = PositionsFromFile[ PosIdx2];
        
        m_pVertices[i*3].TexcoordS = TexcoordFromFile[TexIdx0].s;
        m_pVertices[i*3+1].TexcoordS = TexcoordFromFile[TexIdx1].s;
        m_pVertices[i*3+2].TexcoordS = TexcoordFromFile[TexIdx2].s;
        
        m_pVertices[i*3].TexcoordT = TexcoordFromFile[TexIdx0].t;
        m_pVertices[i*3+1].TexcoordT = TexcoordFromFile[TexIdx1].t;
        m_pVertices[i*3+2].TexcoordT = TexcoordFromFile[TexIdx2].t;
        
        Vector normal = (b-a).cross(c-a);
        normal.normalize();
        
        m_pVertices[i*3].Normal =
        m_pVertices[i*3+1].Normal =
        m_pVertices[i*3+2].Normal = normal;
    }
    
    printf( "Vertices:\n");
    for( unsigned int i=0; i<m_VertexCount; i++)
    {
        printf( "%2i: ", i);
        printf( "p(%2.1f, %2.1f, %2.1f) ", m_pVertices[i].Position.X, m_pVertices[i].Position.Y, m_pVertices[i].Position.Z );
        printf( "n(%2.1f, %2.1f, %2.1f) ", m_pVertices[i].Normal.X, m_pVertices[i].Normal.Y, m_pVertices[i].Normal.Z );
        printf( "t(%2.1f, %2.1f)\n", m_pVertices[i].TexcoordS, m_pVertices[i].TexcoordT );
        
    }
}

void BoundingBox::createBox() {
    
    //Erstellung der Vektoren für die achsenausgerichtete Bounding Box
    Vector positionsForBB[8] = {
        Vector(Min.X, Min.Y, Min.Z),
        Vector(Max.X, Min.Y, Min.Z),
        Vector(Max.X, Max.Y, Min.Z),
        Vector(Min.X, Max.Y, Min.Z),
        
        Vector(Min.X, Min.Y, Max.Z),
        Vector(Max.X, Min.Y, Max.Z),
        Vector(Max.X, Max.Y, Max.Z),
        Vector(Min.X, Max.Y, Max.Z),
    };
    
    //Erstellung der Faces
    Face facesForBB[12] {
        {4,3,1,  0,0,0},
        {3,2,1,  0,0,0},
        
        {3,7,2,  0,0,0},
        {7,6,2,  0,0,0},
        
        {7,8,6,  0,0,0},
        {8,5,6,  0,0,0},
        
        {8,4,5,  0,0,0},
        {4,1,5,  0,0,0},
        
        {8,7,4,  0,0,0},
        {7,3,4,  0,0,0},
        
        {5,6,1,  0,0,0},
        {6,2,1,  0,0,0},
    };
    
    //Speicherung der Vertices in der richtigen Reihenfolge im m_pVertices Array
    m_VertexCount = 12*3;
    m_pVertices = new Vertex[m_VertexCount];
    for(int k=0; k<12; k++ )
    {
        unsigned int PosIdx0 = facesForBB[k].pidx[0]-1;
        unsigned int PosIdx1 = facesForBB[k].pidx[1]-1;
        unsigned int PosIdx2 = facesForBB[k].pidx[2]-1;
        
        Vector a = m_pVertices[(k)*3].Position = positionsForBB[PosIdx0];
        Vector b = m_pVertices[(k)*3+1].Position = positionsForBB[PosIdx1];
        Vector c = m_pVertices[(k)*3+2].Position = positionsForBB[PosIdx2];
        
        Vector normal = (b-a).cross(c-a);
        normal.normalize();
        
        m_pVertices[k*3].Normal =
        m_pVertices[k*3+1].Normal =
        m_pVertices[k*3+2].Normal = normal;
    }

    
}

void BoundingBox::drawLines() const {
    
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < m_VertexCount; i++) {
        
        glVertex3f(m_pVertices[i].Position.X, m_pVertices[i].Position.Y, m_pVertices[i].Position.Z);
        glVertex3f(m_pVertices[i+1].Position.X, m_pVertices[i+1].Position.Y, m_pVertices[i+1].Position.Z);
        
        glVertex3f(m_pVertices[i+1].Position.X, m_pVertices[i+1].Position.Y, m_pVertices[i+1].Position.Z);
        glVertex3f(m_pVertices[i+2].Position.X, m_pVertices[i+2].Position.Y, m_pVertices[i+2].Position.Z);
        
        glVertex3f(m_pVertices[i+2].Position.X, m_pVertices[i+2].Position.Y, m_pVertices[i+2].Position.Z);
        glVertex3f(m_pVertices[i].Position.X, m_pVertices[i].Position.Y, m_pVertices[i].Position.Z);
        
        i= i+2;
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

const BoundingBox& Model::boundingBox() const
{
    return m_Box;
}

void Model::drawLines() const
{
    // Aufgabe 1

    glBegin(GL_LINES);
    for (int i = 0; i < m_VertexCount; i+=3) {
        
        glVertex3f(m_pVertices[i].Position.X, m_pVertices[i].Position.Y, m_pVertices[i].Position.Z);
        glVertex3f(m_pVertices[i+1].Position.X, m_pVertices[i+1].Position.Y, m_pVertices[i+1].Position.Z);
        
        glVertex3f(m_pVertices[i+1].Position.X, m_pVertices[i+1].Position.Y, m_pVertices[i+1].Position.Z);
        glVertex3f(m_pVertices[i+2].Position.X, m_pVertices[i+2].Position.Y, m_pVertices[i+2].Position.Z);
        
        glVertex3f(m_pVertices[i+2].Position.X, m_pVertices[i+2].Position.Y, m_pVertices[i+2].Position.Z);
        glVertex3f(m_pVertices[i].Position.X, m_pVertices[i].Position.Y, m_pVertices[i].Position.Z);
        
        
    }
    glEnd();
    
}

void Model::drawTriangles()
{
    
    
    // Aufgabe 1
    if (m_MatGroupCount > 0) {
        for (int j = 0; j < m_MatGroupCount; j++) {
            
            this->m_ModelShader.activate();
            
            this->m_ModelShader.setParameter(this->m_ModelShader.getParameterId("LightPos"), Vector(0.0, 4.0, 0.0));
            this->m_ModelShader.setParameter(this->m_ModelShader.getParameterId("LightColor"), Color(1.0, 1.0, 1.0));
            this->m_ModelShader.setParameter(this->m_ModelShader.getParameterId("DiffColor"), Color(m_MatGroupsPerformance[j].material->getDiffuseColor().R, m_MatGroupsPerformance[j].material->getDiffuseColor().G, m_MatGroupsPerformance[j].material->getDiffuseColor().B));
            this->m_ModelShader.setParameter(this->m_ModelShader.getParameterId("SpecColor"), Color(m_MatGroupsPerformance[j].material->getSpecularColor().R, m_MatGroupsPerformance[j].material->getSpecularColor().G, m_MatGroupsPerformance[j].material->getSpecularColor().B));
            this->m_ModelShader.setParameter(this->m_ModelShader.getParameterId("AmbientColor"), Color(m_MatGroupsPerformance[j].material->getAmbientColor().R, m_MatGroupsPerformance[j].material->getAmbientColor().G, m_MatGroupsPerformance[j].material->getAmbientColor().B));
            this->m_ModelShader.setParameter(this->m_ModelShader.getParameterId("SpecExp"), m_MatGroupsPerformance[j].material->getSpecularExponent());
            
            
            m_MatGroupsPerformance[j].material->getTexture().apply();
            this->m_ModelShader.setParameter(this->m_ModelShader.getParameterId("DiffuseTexture"), 0);
            
            glBegin(GL_TRIANGLES);
            
            for (int i = m_MatGroupsPerformance[j].first; i <= m_MatGroupsPerformance[j].last; i+=3) {
                
                
                glNormal3f(m_pVertices[i].Normal.X, m_pVertices[i].Normal.Y, m_pVertices[i].Normal.Z);
                glTexCoord2f(m_pVertices[i].TexcoordS, m_pVertices[i].TexcoordT);
                glVertex3f(m_pVertices[i].Position.X, m_pVertices[i].Position.Y, m_pVertices[i].Position.Z);
                
                glNormal3f(m_pVertices[i+1].Normal.X, m_pVertices[i+1].Normal.Y, m_pVertices[i+1].Normal.Z);
                glTexCoord2f(m_pVertices[i+1].TexcoordS, m_pVertices[i+1].TexcoordT);
                glVertex3f(m_pVertices[i+1].Position.X, m_pVertices[i+1].Position.Y, m_pVertices[i+1].Position.Z);
                
                glNormal3f(m_pVertices[i+2].Normal.X, m_pVertices[i+2].Normal.Y, m_pVertices[i+2].Normal.Z);
                glTexCoord2f(m_pVertices[i+2].TexcoordS, m_pVertices[i+2].TexcoordT);
                glVertex3f(m_pVertices[i+2].Position.X, m_pVertices[i+2].Position.Y, m_pVertices[i+2].Position.Z);
                
            }
            glEnd();
            this->m_ModelShader.deactivate();
        }
    } else {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < m_VertexCount; i+=3) {
            
            glNormal3f(m_pVertices[i].Normal.X, m_pVertices[i].Normal.Y, m_pVertices[i].Normal.Z);
            glTexCoord2f(m_pVertices[i].TexcoordS, m_pVertices[i].TexcoordT);
            glVertex3f(m_pVertices[i].Position.X, m_pVertices[i].Position.Y, m_pVertices[i].Position.Z);
            
            glNormal3f(m_pVertices[i+1].Normal.X, m_pVertices[i+1].Normal.Y, m_pVertices[i+1].Normal.Z);
            glTexCoord2f(m_pVertices[i+1].TexcoordS, m_pVertices[i+1].TexcoordT);
            glVertex3f(m_pVertices[i+1].Position.X, m_pVertices[i+1].Position.Y, m_pVertices[i+1].Position.Z);
            
            glNormal3f(m_pVertices[i+2].Normal.X, m_pVertices[i+2].Normal.Y, m_pVertices[i+2].Normal.Z);
            glTexCoord2f(m_pVertices[i+2].TexcoordS, m_pVertices[i+2].TexcoordT);
            glVertex3f(m_pVertices[i+2].Position.X, m_pVertices[i+2].Position.Y, m_pVertices[i+2].Position.Z);
            
        }
        glEnd();
    }
    
}

ShaderProgram& Model::getModelShader() {
    return this->m_ModelShader;
}

void Model::setModelShader(ShaderProgram &newShader) {
    this->m_ModelShader = newShader;
}

void Model::setMatGroupCount(unsigned int p_Count) {
    this->m_MatGroupCount = p_Count;
}

unsigned int Model::getMaterialCount() {
    return this->m_MaterialCount;
}

void Model::setMaterialCount(unsigned int p_Count) {
    this->m_MaterialCount = p_Count;
}

materialGroup* Model::getMatGroupsPerformance() {
    return this->m_MatGroupsPerformance;
}

void Model::setMatGroupsPerformance(materialGroup* newGroup) {
    this->m_MatGroupsPerformance = newGroup;
}

GLuint& Model::getVertexBuffer() {
    return this->m_VertexBuffer;
}

GLuint& Model::getIndexBuffer() {
    return this->m_IndexBuffer;
}

GLuint& Model::getVertexAttributeBuffer() {
    return this->m_VertexAttributeBuffer;
}

void Model::setVertexCount(unsigned int p_Count) {
    this->m_VertexCount = p_Count;
}

unsigned int Model::getVertexCount() {
    return this->m_VertexCount;
}

void Model::setBoundingBox(BoundingBox& p_Box) {
    this->m_Box = p_Box;
}

BoundingBox& Model::getBoundingBox() {
    return this->m_Box;
}

unsigned int Model::getMatGroupCount() {
    return this->m_MatGroupCount;
}

void Model::setMaterials(Material* p_Materials) {
    this->m_pMaterials = p_Materials;
}

Material* Model::getMaterials() {
    return this->m_pMaterials;
}

void Model::setVertices(Vertex* p_Vertices) {
    this->m_pVertices = p_Vertices;
}

Vertex* Model::getVertices() {
    return this->m_pVertices;
}

void Model::setIndices(unsigned int* p_Indices) {
    this->m_Indices = p_Indices;
}

unsigned int* Model::getIndices() {
    return this->m_Indices;
}

