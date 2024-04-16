#version 330 core

layout( location = 0) in vec3 aPos;
layout( location = 1) in vec2 aTexCoord;

out vec3 vPos;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proyection;

void main(){
	gl_Position = proyection*view*model*vec4(aPos,1.0);
	vPos = aPos;
	TexCoord = aTexCoord;
}