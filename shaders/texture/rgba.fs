#version 330

out vec4 fragColor;

void main(){

    vec3 color = vec3(0.75, 0.0, 0.75);
	
	fragColor = vec4(color, 1.0);
}