//
//  ShaderProgram.cpp
//  CGPrak6
//
//  Created by David Herzog on 08.06.16.
//  Copyright © 2016 HS Osnabrueck. All rights reserved.
//

#include "ShaderProgram.hpp"


ShaderProgram::ShaderProgram() {
    this->m_FragmentShader = 0;
    this->m_VertexShader = 0;
    this->m_ShaderProgram = 0;
}

ShaderProgram::~ShaderProgram() {
    
}

bool ShaderProgram::load(const char* vertexShader, const char* fragmentShader) {    
    if (this->loadVertexShader(vertexShader) && this->loadFragmentShader(fragmentShader)) {
        return true;
    }
    
    return false;
}

bool ShaderProgram::loadVertexShader(const char* vertexShader) {
    std::string* error;
    
    FILE* myFile = fopen(vertexShader, "r");
    
    if (myFile != NULL) {
        long fileSize;
        size_t result;
        
        
        fseek(myFile, 0.0, SEEK_END);
        fileSize = ftell(myFile);
        rewind(myFile);
        GLint fileSizeForShader = fileSize;
        
        char* myBuffer = new char[fileSize];
        if (myBuffer == NULL) {
            std::cout << "loadVertexShader: Der Speicher für den Buffer konnte nicht allokiert werden!" << std::endl;
            return false;
        }
        
        result = fread(myBuffer, 1, fileSize, myFile);
        if (result != fileSize) {
            std::cout << "loadVertexShader: Fehler beim Lesen des Vertex Shaders" << std::endl;
            return false;
        }
        
        
        
        this->m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        
        glShaderSource(this->m_VertexShader, 1, &myBuffer, &fileSizeForShader);
        
        
        fclose(myFile);
        delete[] myBuffer;
        return true;
    } else {
        std::cout << "loadVertexShader: Datei wurde nicht gefunden!" << std::endl;
        return false;
    }
    
    

}

bool ShaderProgram::loadFragmentShader(const char* fragmentShader) {
    std::string* error;

    FILE* myFile = fopen(fragmentShader, "r");
    
    if (myFile != NULL) {
        long fileSize;
        size_t result;
        
        fseek(myFile, 0.0, SEEK_END);
        fileSize = ftell(myFile);
        rewind(myFile);
        GLint fileSizeForShader = fileSize;
        
        
        char* myBuffer = new char[fileSize];
        if (myBuffer == NULL) {
            std::cout << "loadFragmentShader: Der Speicher für den Buffer konnte nicht allokiert werden!" << std::endl;
            return false;
        }
        
        result = fread(myBuffer, 1, fileSize, myFile);
        if (result != fileSize) {
            std::cout << "loadFragmentShader: Fehler beim Lesen des Fragment Shaders" << std::endl;
            return false;
        }
        
        this->m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        glShaderSource(this->m_FragmentShader, 1, &myBuffer, &fileSizeForShader);

        fclose(myFile);
        delete[] myBuffer;
        return true;
    } else {
        std::cout << "loadFragmentShader: Datei wurde nicht gefunden!" << std::endl;
        return false;
    }
}

bool ShaderProgram::compile(std::string* compileError) {
    
    std::cout << "Compiling Shaders..." << std::endl;
    GLint shaderCompiledCheck;
    
    this->m_ShaderProgram = glCreateProgram();
    
    if (this->m_VertexShader != 0) {
        glCompileShader(this->m_VertexShader);
        glGetShaderiv(this->m_VertexShader, GL_COMPILE_STATUS, &shaderCompiledCheck);
        if (shaderCompiledCheck == GL_FALSE) {
            std::cout << "VertexShader konnte nicht kompiliert werden!" << std::endl;
        }
        if (this->checkForCompileError(this->m_VertexShader)) return false;
        glAttachShader(this->m_ShaderProgram, this->m_VertexShader);
        if (this->checkForCompileError(this->m_VertexShader)) return false;
    }
    
    if (this->m_FragmentShader != 0) {
        glCompileShader(this->m_FragmentShader);
        glGetShaderiv(this->m_FragmentShader, GL_COMPILE_STATUS, &shaderCompiledCheck);
        if (shaderCompiledCheck == GL_FALSE) {
            std::cout << "FragmentShader konnte nicht kompiliert werden!" << std::endl;
        }
        if (this->checkForCompileError(this->m_FragmentShader)) return false;
        glAttachShader(this->m_ShaderProgram, this->m_FragmentShader);
        if (this->checkForCompileError(this->m_FragmentShader)) return false;
    }
    
    glLinkProgram(this->m_ShaderProgram);
    if (this->checkForLinkError(this->m_ShaderProgram)) {
        std::cout << "Fehler beim Linken..." << std::endl;
        return false;
    }
    
    
    glDeleteShader(this->m_VertexShader);
    glDeleteShader(this->m_FragmentShader);
    
    std::cout << "Shaders compiled succesfully" << std::endl;
    return true;
}

GLint ShaderProgram::getParameterId(const char* parameterName) const {
    return glGetUniformLocation(this->m_ShaderProgram, parameterName);
}

void ShaderProgram::setParameter(GLint id, float param) {
    glUniform1f(id, param);
}

void ShaderProgram::setParameter(GLint id, int param) {
    glUniform1i(id, param);
}

void ShaderProgram::setParameter(GLint id, const Vector& param) {
    glUniform3f(id, param.X, param.Y, param.Z);
}

void ShaderProgram::setParameter(GLint id, const Color& param) {
    glUniform3f(id, param.R, param.G, param.B);
}

void ShaderProgram::setParameter(GLint id, const Matrix& param) {
    glUniformMatrix4fv(id, 1, GL_FALSE, &param.m00);
}

void ShaderProgram::activate() {
    glUseProgram(this->m_ShaderProgram);
}

void ShaderProgram::deactivate() {
    glUseProgram(0);
}


//
//  Spezielle Fehlerbehandlung für Compile-Fehler (Quelle: https://www.opengl.org/wiki/Shader_Compilation )
//
bool ShaderProgram::checkForCompileError(GLuint shader) {
    
    GLint isCompiled = 0;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        
        for (int i = 0; i < errorLog.size(); i++) {
            std::cout << errorLog[i];
        }
        
        
        // Exit with failure.
        glDeleteShader(shader); // Don't leak the shader.
        return true;
    }
    
    return false;
}

//
//  Spezielle Fehlerbehandlung für Linker-Fehler (Quelle: https://www.opengl.org/wiki/Shader_Compilation )
//
bool ShaderProgram::checkForLinkError(GLuint program) {
    
    GLint isLinked = 0;
    
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(program, maxLength, &maxLength, &errorLog[0]);
        
        for (int i = 0; i < errorLog.size(); i++) {
            std::cout << errorLog[i];
        }
        
        
        // Exit with failure.
        glDeleteProgram(program); // Don't leak the shader.
        return true;
    }
    
    return false;
}
