//
//  MyOpenGLRenderer.cpp
//  Nostronew
//
//  Created by David Herzog on 02.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//

#include "MyOpenGLRenderer.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

double MyOpenGLRenderer::m_WindowWidth = 1024;
double MyOpenGLRenderer::m_WindowHeight = 768;
Vector* MyOpenGLRenderer::m_LightPos = new Vector(0,10,0);
Camera* MyOpenGLRenderer::m_Camera = new Camera();
ResourceManager* MyOpenGLRenderer::m_ResManager = nullptr;
int MyOpenGLRenderer::m_MouseState = 0;
int MyOpenGLRenderer::m_MouseButton = 0;
int MyOpenGLRenderer::m_LastFrameTime = 0;


MyOpenGLRenderer::MyOpenGLRenderer(){
    
}

void MyOpenGLRenderer::setupDefaultOpenGLSettings() {
    
    glClearColor(0, 0, 0, 255);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, (double)m_WindowWidth/(double)m_WindowHeight, 0.045f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Setup Light Color
    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 0.0f };
    GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    
    // Setup default material
    float diff[4] = {1,1,1,1};
    float amb[4]  = {0.2f,0.2f,0.2f,1};
    float spec[4] = {0.5f,0.5f,0.5f,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMateriali(GL_FRONT, GL_SHININESS, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    std::cout << "OpenGL default settings initialized successfully!" << std::endl;
}

/*
 *  Falls das Model mehrere Texturen (Materials) besitzt, werden
 *  diese nacheinander in Paketen gezeichnet. Jeweils pro MaterialGroup
 *  einen DrawCall per glDrawElements. Hat das Model kein Material,
 *  wird es einfach komplett ohne Unterteilung gezeichnet.
*/
void MyOpenGLRenderer::drawModel(Model *p_ModelToDraw) {
    
    if (p_ModelToDraw->getMaterialCount() > 0) {
        for (int j = 0; j < p_ModelToDraw->getMatGroupCount(); j++) {
            
            p_ModelToDraw->getModelShader().activate();
            
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("LightPos"), *m_LightPos);
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("LightColor"), Color(1.0, 1.0, 1.0));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("DiffColor"), Color(p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().R, p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().G, p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().B));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("SpecColor"), Color(p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().R, p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().G, p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().B));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("AmbientColor"), Color(p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().R, p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().G, p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().B));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("SpecExp"), p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularExponent());
            
            
            p_ModelToDraw->getMatGroupsPerformance()[j].material->getTexture().apply();
            
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("DiffuseTexture"), 0);
            
            /*std::cout << "DiffColor R: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().R << ", G: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().G << ", B: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().B << std::endl;
            std::cout << "SpecColor R: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().R << ", G: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().G << ", B: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().B << std::endl;
            std::cout << "AmbientColor R: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().R << ", G: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().G << ", B: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().B << std::endl;
            std::cout << "SpecExp: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularExponent() << std::endl;*/
            
            //draw via Array Buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_ModelToDraw->getIndexBuffer());
            glBindBuffer(GL_ARRAY_BUFFER, p_ModelToDraw->getVertexBuffer());
            //glBindVertexArrayAPPLE(p_ModelToDraw->getVertexAttributeBuffer());
            
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            
            glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
            glNormalPointer( GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
            glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
            
            glDrawElements( GL_TRIANGLES, p_ModelToDraw->getMatGroupsPerformance()[j].last-p_ModelToDraw->getMatGroupsPerformance()[j].first+1, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(unsigned int)*p_ModelToDraw->getMatGroupsPerformance()[j].first) );
            
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            p_ModelToDraw->getModelShader().deactivate();
            
            p_ModelToDraw->getBoundingBox().drawLines();
            
        }
    } else {
        // draw via Array Buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_ModelToDraw->getIndexBuffer());
        glBindBuffer(GL_ARRAY_BUFFER, p_ModelToDraw->getVertexBuffer());
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        
        glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
        glNormalPointer( GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
        
        glDrawElements( GL_TRIANGLES, p_ModelToDraw->getVertexCount() , GL_UNSIGNED_INT, BUFFER_OFFSET(0) );
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        
    }
    
}

void MyOpenGLRenderer::initialize(int argc, char* argv[]) {
    
    // initialize the glut system and create a window
    glutInitWindowSize(m_WindowWidth, m_WindowHeight);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("CG Hausarbeit");
    
#ifdef WIN32
    glewInit();
#endif
    
    setupDefaultOpenGLSettings();
    m_Camera->setWindowWidthHeight(m_WindowWidth, m_WindowHeight);
    
    glutDisplayFunc(drawScene);
    glutMouseFunc(mouseCallback);
    glutKeyboardFunc(keyboardCallback);
    glutKeyboardUpFunc(keyboardUpCallback);
    glutMotionFunc(mouseMoveCallback);
    glutSpecialFunc(specialKeyboardCallback);
    glutSpecialUpFunc(specialKeyboardUpCallback);
    
    
}

void MyOpenGLRenderer::startMainLoop() {
    glutMainLoop();
}

void MyOpenGLRenderer::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    m_Camera->apply();
    
    //drawGroundGrid();
    
    int deltaTimeInt = glutGet(GLUT_ELAPSED_TIME) - m_LastFrameTime;
    m_LastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (float)deltaTimeInt;
    
    m_ResManager->getPlayerShip()->updatePosition(deltaTime);
    m_ResManager->getPlayerShip()->applyMatrices();
    
    for (Model* currModel : *(m_ResManager->getModelsToDraw())) {
        //Das C++ Äquivalent zu dem "instanceof" Operator
        //Ist das Model keine Instanz vom zu prüfenden Objekt, wird
        //ein nullptr zurückgegeben.
        //if (PlayerShip* plShip = dynamic_cast<PlayerShip*>(currModel)) {
        //    plShip->updatePosition(deltaTime);
            
        //}
        drawModel(currModel);
        if (PlayerShip* plShip = dynamic_cast<PlayerShip*>(currModel)) {
            //plShip->discardMatrix();
            //right, up, forward Vektoren der Transformationsmatrix anzeigen lassen
            glDisable(GL_LIGHTING);
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(plShip->getPos()->X, plShip->getPos()->Y, plShip->getPos()->Z);
            glVertex3f(plShip->getPos()->X+plShip->getMatrix().right().X, plShip->getPos()->Y+plShip->getMatrix().right().Y, plShip->getPos()->Z+plShip->getMatrix().right().Z);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(plShip->getPos()->X, plShip->getPos()->Y, plShip->getPos()->Z);
            glVertex3f(plShip->getPos()->X+plShip->getMatrix().up().X, plShip->getPos()->Y+plShip->getMatrix().up().Y, plShip->getPos()->Z+plShip->getMatrix().up().Z);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(plShip->getPos()->X, plShip->getPos()->Y, plShip->getPos()->Z);
            glVertex3f(plShip->getPos()->X+plShip->getMatrix().forward().X, plShip->getPos()->Y+plShip->getMatrix().forward().Y, plShip->getPos()->Z+plShip->getMatrix().forward().Z);
            glEnd();
            glEnable(GL_LIGHTING);
            
        }
    }
    
    m_ResManager->getPlayerShip()->discardMatrix();
    
    GLfloat lpos[4];
    lpos[0]=m_LightPos->X;
    lpos[1]=m_LightPos->Y;
    lpos[2]=m_LightPos->Z;
    lpos[3]=1;
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    
    checkForErrors();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void MyOpenGLRenderer::mouseCallback(int p_Button, int p_State, int p_X, int p_Y) {
    
    m_MouseButton = p_Button;
    m_MouseState = p_State;
    m_Camera->mouseInput(p_X, p_Y, p_Button, p_State);
    
    
}

void MyOpenGLRenderer::keyboardCallback(unsigned char p_Key, int p_X, int p_Y) {
    
    switch (p_Key) {
        case 'a':
            //std::cout << "a pressed" << std::endl;
            m_ResManager->getPlayerShip()->setForwardBackward(-1.0f);
            break;
        case 'y':
            //std::cout << "y pressed" << std::endl;
            m_ResManager->getPlayerShip()->setForwardBackward(1.0f);
            break;
        default:
            break;
    }
    
}

void MyOpenGLRenderer::keyboardUpCallback(unsigned char p_Key, int p_X, int p_Y) {
    
    switch (p_Key) {
        case 'a':
            //std::cout << "a up" << std::endl;
            m_ResManager->getPlayerShip()->setForwardBackward(0.0f);
            break;
        case 'y':
            //std::cout << "y up" << std::endl;
            m_ResManager->getPlayerShip()->setForwardBackward(0.0f);
            break;
        default:
            break;
    }
    
}

void MyOpenGLRenderer::specialKeyboardCallback(int key, int x, int y)
{
    // function is called if a special keyboard button is pressed (e. g. Up-arrow-Key)
    
    switch (key) {
        case GLUT_KEY_UP:
            //std::cout << "Up Key Pressed" << std::endl;
            m_ResManager->getPlayerShip()->setPitchUpDown(-1.0f);
            break;
            
        case GLUT_KEY_DOWN:
            //std::cout << "Down Key Pressed" << std::endl;
            m_ResManager->getPlayerShip()->setPitchUpDown(1.0f);
            break;
            
        case GLUT_KEY_LEFT:
            //std::cout << "Left Key Pressed" << std::endl;
            m_ResManager->getPlayerShip()->setRollLeftRight(1.0f);
            break;
            
        case GLUT_KEY_RIGHT:
            //std::cout << "Right Key Pressed" << std::endl;
            m_ResManager->getPlayerShip()->setRollLeftRight(-1.0f);
            break;
            
        default:
            break;
    }
}

void MyOpenGLRenderer::specialKeyboardUpCallback(int key, int x, int y)
{
    // function is called if a special keyboard button is released
    
    switch (key) {
        case GLUT_KEY_UP:
            //std::cout << "Up Key Released" << std::endl;
            m_ResManager->getPlayerShip()->setPitchUpDown(0.0f);
            break;
            
        case GLUT_KEY_DOWN:
            //std::cout << "Down Key Released" << std::endl;
            m_ResManager->getPlayerShip()->setPitchUpDown(0.0f);
            break;
            
        case GLUT_KEY_LEFT:
            //std::cout << "Left Key Released" << std::endl;
            m_ResManager->getPlayerShip()->setRollLeftRight(0.0f);
            break;
            
        case GLUT_KEY_RIGHT:
            //std::cout << "Right Key Releaed" << std::endl;
            m_ResManager->getPlayerShip()->setRollLeftRight(0.0f);
            break;
            
        default:
            break;
    }
    
}

void MyOpenGLRenderer::mouseMoveCallback(int p_X, int p_Y) {
    m_Camera->mouseInput(p_X, p_Y, m_MouseButton,m_MouseState);
}

void MyOpenGLRenderer::drawGroundGrid() {
    const float GridSize=10.0f;
    const unsigned int GridSegments=20;
    const float GridStep=GridSize/(float)GridSegments;
    const float GridOrigin=-GridSize*0.5f;
    
    glDisable( GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    for( unsigned int i=0; i<GridSegments+1; i++)
    {
        float itpos=GridOrigin + GridStep*(float)i;
        glVertex3f(itpos, 0, GridOrigin);
        glVertex3f(itpos, 0, GridOrigin+GridSize);
        
        glVertex3f(GridOrigin, 0, itpos);
        glVertex3f(GridOrigin+GridSize, 0, itpos);
        
    }
    
    glEnd();
    glEnable( GL_LIGHTING);
}

void MyOpenGLRenderer::checkForErrors() {
    
    GLenum myError = glGetError();
    std::string* error;
    if (myError != GL_NO_ERROR) {
        error = new std::string(reinterpret_cast<const char*>(gluErrorString(myError)));
        std::cout << *error << std::endl;
    } else {
        //std::cout << "Errors were checked, nothing's wrong" << std::endl;
    }
    
    
}

void MyOpenGLRenderer::setResourceManager(ResourceManager* p_ResManager) {
    m_ResManager = p_ResManager;
}
