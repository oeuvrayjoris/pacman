#version 330 core

// Entrées du fragment shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

// Sortie du fragment shader
out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
    vec3 newColor;
    float wi_dot_N = dot(normalize(uLightDir_vs), normalize(vNormal_vs));
    vec3 halfVector = (normalize(uLightDir_vs) + normalize(-vPosition_vs)) / 2.0;
    float halfVector_dot_N = dot(normalize(halfVector), normalize(vNormal_vs));
    newColor = uLightIntensity * (uKd * (wi_dot_N) + (uKs * pow(halfVector_dot_N, uShininess)));
    return newColor;
}

void main() {
	fFragColor = blinnPhong();	
  //fFragColor = normalize(vNormal_vs);
}