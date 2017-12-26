#version 330 core

layout(location = 1) in vec3 aVertexPosition;
layout(location = 2) in vec3 aVertexNormal;
layout(location = 3) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vFragPosition;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

void main(){
    vFragPosition = (uMVMatrix * vec4 (aVertexPosition, 1)).xyz;
    vFragNormal = (uNormalMatrix * vec4 (aVertexNormal, 1)).xyz;

    gl_Position =  (uMVPMatrix * vec4 (aVertexPosition, 1));
}