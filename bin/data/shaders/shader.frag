#version 150
precision mediump float;

uniform sampler2DRect tex0;

in vec4 gsColor;
in vec2 gsTexCoord;

out vec4 outputColor;

void main(){
    vec4 smpColor = texture(tex0, gsTexCoord);
    outputColor = gsColor * smpColor;
}
