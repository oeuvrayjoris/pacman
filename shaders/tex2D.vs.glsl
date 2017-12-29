#version 330 core

layout(location = 1) in vec2 aVertexPosition;
layout(location = 2) in vec2 aVertexTexture;

out vec2 vFragPosition;
out vec2 vFragTexture;

uniform float uTime = 22.5f;

mat3 rotate(float a){
    float rad = radians(a);

    mat3 M = mat3 (cos(rad)  ,sin(rad),  0,
                   -sin(rad) ,cos(rad),  0,
                            0,       0,  1);
    return M;
}

void main(){
    mat3 uRotMatrix = rotate(45.0);

    vFragPosition = (vec3 (aVertexPosition, 1) * uRotMatrix).xy;
    vFragTexture = aVertexTexture;
}