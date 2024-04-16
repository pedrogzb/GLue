#version 330 core

layout( location = 0) in vec3 aPos;
layout( location = 1) in vec3 aCol;
layout( location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec3 vPos;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proyection;

void main(){
	gl_Position = proyection*view*model*vec4(aPos,1.0);
	vPos = aPos;
	ourColor = aCol;
	TexCoord = aTexCoord;
}