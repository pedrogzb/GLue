#version 330 core

in vec3 ourColor;
in vec3 vPos;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_val;

void main() {
	vec4 col1 = texture(texture1,TexCoord);
	vec4 col2 = texture(texture2,TexCoord);
	FragColor = mix(col1,col2,mix_val);
}