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
Vector* MyOpenGLRenderer::m_LightPos = new Vector(-10.0f ,100.0f ,20.0f);
Camera* MyOpenGLRenderer::m_Camera = new Camera();
ResourceManager* MyOpenGLRenderer::m_ResManager = nullptr;
GameManager* MyOpenGLRenderer::m_GameManager = nullptr;
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
    /*float diff[4] = {1,1,1,1};
    float amb[4]  = {0.2f,0.2f,0.2f,1};
    float spec[4] = {0.5f,0.5f,0.5f,1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMateriali(GL_FRONT, GL_SHININESS, 30);
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);*/
    
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
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("EyePos"), m_Camera->getPosition());
            //std::cout << "Kamera X: " << m_Camera->getPosition().X << "Kamera Y: " << m_Camera->getPosition().Y << "Kamera Z: " << m_Camera->getPosition().Z << std::endl;
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("LightColor"), Color(1.0, 1.0, 1.0));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("DiffColor"), Color(p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().R, p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().G, p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().B));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("SpecColor"), Color(p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().R, p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().G, p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().B));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("AmbientColor"), Color(p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().R, p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().G, p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().B));
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("SpecExp"), p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularExponent());
            
            
            p_ModelToDraw->getMatGroupsPerformance()[j].material->getTexture().apply();
            
            p_ModelToDraw->getModelShader().setParameter(p_ModelToDraw->getModelShader().getParameterId("DiffuseTexture"), 0);
            
//            std::cout << "DiffColor R: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().R << ", G: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().G << ", B: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getDiffuseColor().B << std::endl;
//            std::cout << "SpecColor R: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().R << ", G: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().G << ", B: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularColor().B << std::endl;
//            std::cout << "AmbientColor R: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().R << ", G: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().G << ", B: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getAmbientColor().B << std::endl;
//            std::cout << "SpecExp: " << p_ModelToDraw->getMatGroupsPerformance()[j].material->getSpecularExponent() << std::endl;
            
            //draw via Array Buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_ModelToDraw->getIndexBuffer());
            glBindBuffer(GL_ARRAY_BUFFER, p_ModelToDraw->getVertexBuffer());
            
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            
            glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
            glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
            glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
            
            glDrawElements( GL_TRIANGLES, p_ModelToDraw->getMatGroupsPerformance()[j].last-p_ModelToDraw->getMatGroupsPerformance()[j].first+1, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(unsigned int)*p_ModelToDraw->getMatGroupsPerformance()[j].first) );
            
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            p_ModelToDraw->getModelShader().deactivate();
            
            glBindTexture(GL_TEXTURE_2D, 0);
            
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

void MyOpenGLRenderer::drawCubeMap() {
    CubeMap* cubeMap = m_ResManager->getCubeMap();
    
    cubeMap->getShader()->activate();
    
    cubeMap->applyCubeMapTextures();
    cubeMap->getShader()->setParameter(cubeMap->getShader()->getParameterId("cubeMap"), 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeMap->getIndexBuffer());
    glBindBuffer(GL_ARRAY_BUFFER, cubeMap->getVertexBuffer());
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
    
    glDrawElements( GL_TRIANGLES, cubeMap->getVertexCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0) );
    
    glDisableClientState(GL_VERTEX_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    m_ResManager->getCubeMap()->getShader()->deactivate();
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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
    
    PlayerShip* pShip = m_ResManager->getPlayerShip();
    glLoadIdentity();
    
//    std::cout << "Forward X: " << pShip->getMatrix().forward().X << " Y: " << pShip->getMatrix().forward().Y << " Z: " << pShip->getMatrix().forward().Z << std::endl;
//    std::cout << "Right X: " << pShip->getMatrix().right().X << " Y: " << pShip->getMatrix().right().Y << " Z: " << pShip->getMatrix().right().Z << std::endl;
//    std::cout << "Up X: " << pShip->getMatrix().up().X << " Y: " << pShip->getMatrix().up().Y << " Z: " << pShip->getMatrix().up().Z << std::endl;
//    std::cout << "Translation X: " << pShip->getMatrix().translation().X << " Y: " << pShip->getMatrix().translation().Y << " Z: " << pShip->getMatrix().translation().Z << std::endl;
    
    if (!m_GameManager->checkForHit()) {
        m_GameManager->checkBulletsLifecylce();
    }
    
    m_Camera->setPosition(*(pShip->getPos()) + pShip->getMatrix().up()*3.0f - *(pShip->getDir())*5.0f);
    m_Camera->setTarget(*(pShip->getPos()) + *(pShip->getDir()));
    m_Camera->apply();
    
    
    //drawGroundGrid();
    
    int deltaTimeInt = glutGet(GLUT_ELAPSED_TIME) - m_LastFrameTime;
    m_LastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (float)deltaTimeInt;
    
    
    
    
    for (Drawable* currDrawable : *(m_ResManager->getModelsToDraw())) {
        
        if (PlayerShip* pShipCast = dynamic_cast<PlayerShip*>(currDrawable)) {
            //std::cout << "PlayerShip m_Pos: " << pShip->getPos()->X << ", " << pShip->getPos()->Y << ", " << pShip->getPos()->Z << ", " << std::endl;
            //std::cout << "PlayerShip m_Dir: " << pShip->getDir()->X << ", " << pShip->getDir()->Y << ", " << pShip->getDir()->Z << ", " << std::endl;
            //std::cout << "Forward X: " << pShip->getMatrix().forward().X << " Y: " << pShip->getMatrix().forward().Y << " Z: " << pShip->getMatrix().forward().Z << std::endl;
            //std::cout << "Right X: " << pShip->getMatrix().right().X << " Y: " << pShip->getMatrix().right().Y << " Z: " << pShip->getMatrix().right().Z << std::endl;
            //std::cout << "Up X: " << pShip->getMatrix().up().X << " Y: " << pShip->getMatrix().up().Y << " Z: " << pShip->getMatrix().up().Z << std::endl;
            //std::cout << "Translation X: " << pShip->getMatrix().translation().X << " Y: " << pShip->getMatrix().translation().Y << " Z: " << pShip->getMatrix().translation().Z << std::endl;
            
            pShip->updatePosition(deltaTime, m_GameManager->getMinBoundary(), m_GameManager->getMaxBoundary());
            
        } else if (Terrain* terrain = dynamic_cast<Terrain*>(currDrawable)) {
            //std::cout << "Terrain m_Pos: " << currDrawable->getPos()->X << ", " << currDrawable->getPos()->Y << ", " << currDrawable->getPos()->Z << ", " << std::endl;
            //std::cout << "Terrain m_Dir: " << currDrawable->getDir()->X << ", " << currDrawable->getDir()->Y << ", " << currDrawable->getDir()->Z << ", " << std::endl;
            //terrain->updateTerrainMovement(deltaTime);
        } else if (EnemyShip* pEnemy = dynamic_cast<EnemyShip*>(currDrawable)) {
            
            //std::cout << "EnemyShip m_Pos: " << pEnemy->getPos()->X << ", " << pEnemy->getPos()->Y << ", " << pEnemy->getPos()->Z << ", " << std::endl;
            m_GameManager->moveEnemy(pEnemy);
            pEnemy->updatePosition(deltaTime, m_GameManager->getMinBoundary(), m_GameManager->getMaxBoundary());
            
        } else if (Bullet* pBullet = dynamic_cast<Bullet*>(currDrawable)) {
            pBullet->updatePosition(deltaTime * 10.0f, m_GameManager->getMinBoundary(), m_GameManager->getMaxBoundary(), pShip->getPos());
        }
        
        currDrawable->applyMatrices();
        drawModel(currDrawable->getModel());
        //currDrawable->getModel()->getBoundingBox().drawLines();
        currDrawable->discardMatrix();
        //currDrawable->drawAxis();
    }
    
    
    
    drawCubeMap();
    
    m_GameManager->updateHud();
    
    
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
        case 'o':
            m_GameManager->setGameIsRunning(false);
            break;
        case 'r':
            if (!m_GameManager->getGameIsRunning()) {
                m_GameManager->restartGame();
            }
            break;
        case ' ':
            if(m_GameManager->getGameIsRunning()) {
                m_GameManager->shootEnemyShip();
            }
            break;
        default:
            break;
    }
    
}

void MyOpenGLRenderer::keyboardUpCallback(unsigned char p_Key, int p_X, int p_Y) {
    
    switch (p_Key) {
        case 'd':
            //std::cout << "d up" << std::endl;
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
            //m_ResManager->getPlayerShip()->setUpDown(1.0f);
            m_GameManager->steerPlayerShip(GLUT_KEY_UP, 1.0f, 0.0f);
            break;
            
        case GLUT_KEY_DOWN:
            //std::cout << "Down Key Pressed" << std::endl;
            m_GameManager->steerPlayerShip(GLUT_KEY_DOWN,-1.0f, 0.0f);
            break;
            
        case GLUT_KEY_LEFT:
            //std::cout << "Left Key Pressed" << std::endl;
            m_GameManager->steerPlayerShip(GLUT_KEY_LEFT,0.0f, 1.0f);
            break;
            
        case GLUT_KEY_RIGHT:
            //std::cout << "Right Key Pressed" << std::endl;
            m_GameManager->steerPlayerShip(GLUT_KEY_RIGHT, 0.0f, -1.0f);
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
            //m_ResManager->getPlayerShip()->setUpDown(0.0f);
            //m_GameManager->steerPlayerShip(GLUT_KEY_UP, 0.0f, 0.0f);
            m_GameManager->stopShip(GLUT_KEY_UP);
            break;
            
        case GLUT_KEY_DOWN:
            //std::cout << "Down Key Released" << std::endl;
            //m_GameManager->steerPlayerShip(GLUT_KEY_DOWN, 0.0f, 0.0f);
            m_GameManager->stopShip(GLUT_KEY_DOWN);
            break;
            
        case GLUT_KEY_LEFT:
            //m_GameManager->steerPlayerShip(GLUT_KEY_LEFT, 0.0f, 0.0f);
            m_GameManager->stopShip(GLUT_KEY_LEFT);
            break;
            
        case GLUT_KEY_RIGHT:
            //std::cout << "Right Key Releaed" << std::endl;
            //m_GameManager->steerPlayerShip(GLUT_KEY_RIGHT, 0.0f, 0.0f);
            m_GameManager->stopShip(GLUT_KEY_RIGHT);
            
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

void MyOpenGLRenderer::setGameManager(GameManager* p_GameManager) {
    m_GameManager = p_GameManager;
}
