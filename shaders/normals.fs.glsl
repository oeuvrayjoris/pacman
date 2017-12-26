#version 330 core

in vec2 vFragTexCoords;
in vec3 vFragPosition;
in vec3 vFragNormal;

out vec3 fFragColor;

void main(){
   fFragColor = normalize(vFragNormal);
}