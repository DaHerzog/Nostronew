uniform vec3 LightPos;
uniform vec3 EyePos;

varying vec3 Normal;
varying vec3 Position;
varying vec2 Texcoord;

varying vec3 CamRoomLightPos;



void main() {
    
    CamRoomLightPos = (gl_ModelViewMatrix * vec4(LightPos, 1)).xyz;
    Position = (gl_ModelViewMatrix * gl_Vertex).xyz;
    Normal = gl_NormalMatrix * gl_Normal;
    Texcoord = gl_MultiTexCoord0.xy;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
}

