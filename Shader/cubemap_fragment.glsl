uniform samplerCube cubeMap;

varying vec3 Texcoords;


void main() {
    
    gl_FragColor = textureCube(cubeMap, Texcoords);
    
}

