//
//  MyOpenGLRenderer.hpp
//  Nostronew
//
//  Created by David Herzog on 02.09.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//
//  Diese Klasse stellt die Methoden für OpenGL zum Rendern zur Verfügung. OpenGL ist eine sehr c-nahe
//  API, somit ist es leider nicht ohne Umwegen möglich ein Singelton aus dieser Klasse zu erstellen.
//
//  Die Klasse enthält ausschließlich Klassenmethoden und es ist nicht gedacht eine Instanz hiervon
//  zu erzeugen.
//

#ifndef MyOpenGLRenderer_hpp
#define MyOpenGLRenderer_hpp

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>


#include "Model.h"
#include "Camera.h"
#include "ResourceManager.hpp"

class MyOpenGLRenderer {

private:
    
    static MyOpenGLRenderer* m_Instance;
    static ResourceManager* m_ResManager;
    static Vector* m_LightPos;
    static Camera* m_Camera;
    static double m_WindowWidth;
    static double m_WindowHeight;
    static int m_MouseButton;
    static int m_MouseState;
    
    MyOpenGLRenderer();
    MyOpenGLRenderer(const MyOpenGLRenderer&);
    static void drawScene();
    static void mouseCallback(int p_Button, int p_State, int p_X, int p_Y);
    static void keyboardCallback(unsigned char p_Key, int p_X, int p_Y);
    static void specialKeyboardCallback(int key, int x, int y);
    static void specialKeyboardUpCallback(int key, int x, int y);
    static void mouseMoveCallback(int p_X, int p_Y);
    static void drawGroundGrid();
    static void setupDefaultOpenGLSettings();
    static void checkForErrors();
    
public:

    static void drawModel(Model* p_ModelToDraw);
    static void initialize(int argc, char* argv[]);
    static void startMainLoop();
    static void setResourceManager(ResourceManager* p_ResManager);
};

#endif /* MyOpenGLRenderer_hpp */
