#version 330

uniform float index;
uniform sampler2D palette;

out vec4 fragColor;

void main(){

    vec3 color = texture(palette, vec2(index / 256.0, 0.0)).rgb;
	
	fragColor = vec4(color, 1.0);
}