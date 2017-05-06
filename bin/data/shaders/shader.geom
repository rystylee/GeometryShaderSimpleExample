#version 150
precision mediump float;

layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;
uniform int scale;
uniform int NormalMode;

in vec3 vNormal[];
in vec4 vColor[];
in vec2 vTexCoord[];
in vec3 vPosition[];

out vec4 gsColor;
out vec2 gsTexCoord;

void main(){
    vec3 faceEdgeA = vPosition[1] - vPosition[0];
    vec3 faceEdgeB = vPosition[2] - vPosition[0];
    vec3 faceNormal = normalize(cross(faceEdgeA, faceEdgeB));
    vec3 offset;
    if(NormalMode == 0){
        offset = faceNormal * -scale;
    }
    
    for(int i=0; i<gl_in.length(); i++){
        gl_Position = mvp * vec4(vPosition[i], 1.0);
        gsColor = vColor[i];
        gsTexCoord = vTexCoord[i];
        EmitVertex();
    }
    EndPrimitive();

    for(int i=0; i<gl_in.length(); i++){
        if(NormalMode == 1){
            offset = vNormal[i] * scale * i;
        }
        gl_Position = mvp * vec4(vPosition[i] + (offset.xyz), 1.0);
        gsColor = vColor[i];
        gsTexCoord = vTexCoord[i];
        EmitVertex();
    }
    EndPrimitive();
}
