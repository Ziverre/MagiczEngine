#version 330
layout (location=0) in vec2 aPos;

uniform float radius;
uniform float centerX;
uniform float centerY;

void main(){
	vec2 screen = vec2(320.0, 240.0);
	
	//vec2 coord = vec2(320.0, 240.0);
	
	vec2 normCoord  = vec2( (centerX / screen.x - 1), (centerY / screen.y - 1));
	vec2 normRadius = vec2( (radius + 10)/ screen.x, radius / screen.y); // extra 10 so the fuzz does not get clipped
	
    gl_Position = vec4(normCoord.x + normRadius.x * aPos.x, normCoord.y + normRadius.y * aPos.y, 0.0, 1.0);
}