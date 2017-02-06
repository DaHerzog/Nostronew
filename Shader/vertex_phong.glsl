uniform vec3 LightPos;

varying vec3 Normal;
varying vec3 Position;
varying vec2 Texcoord;
varying vec3 LightPosCamRoom;

void main() {
    
    vec4 tmpLightPos = vec4(LightPos.x, LightPos.y, LightPos.z, 1);
    LightPosCamRoom = (gl_ModelViewMatrix * tmpLightPos).xyz;
    Position = (gl_ModelViewMatrix * gl_Vertex).xyz;
    Normal = gl_NormalMatrix * gl_Normal;
    Texcoord = gl_MultiTexCoord0.xy;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
}

