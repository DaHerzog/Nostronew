varying vec3 Texcoords;


void main() {
    
    Texcoords = gl_Vertex.xyz;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
}
