#version 330 core

in vec3 ourColor;
in vec3 vPos;
out vec4 FragColor;


void main() {
	FragColor = vec4(vPos,1.0);
}