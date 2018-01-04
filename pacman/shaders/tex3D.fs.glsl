#version 330 core

// Entrées du fragment shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

// Sortie du fragment shader
out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
	fFragColor = vec3(texture(uTexture, vTexCoords));
}
