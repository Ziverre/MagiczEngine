//TO DO: FIX FIX FIX

#version 330
layout (location=0) in vec2 aPos;

//TO DO: Make these vec2 (to be figured out)
uniform float startX;
uniform float startY;

uniform float endX;
uniform float endY;

uniform float startDiameter;
uniform float endDiameter;

void main(){
	vec2 screen = vec2(320.0, 240.0);
	
	float biggestDiameter = max(startDiameter, endDiameter);
	
	vec2 rectangle = vec2(abs(startX - endX) / 2.0 + biggestDiameter / 2.0, abs(startY - endY) / 2.0 + biggestDiameter / 2.0);
	
	vec2 center = vec2((startX + endX) / 2.0, (startY + endY) / 2.0);
	
	vec2 normalizedCoords = vec2(center.x + rectangle.x * aPos.x, center.y + rectangle.y * aPos.y);
	
	normalizedCoords.x = normalizedCoords.x / screen.x - 1.0;
	normalizedCoords.y = normalizedCoords.y / screen.y - 1.0;
	
    gl_Position = vec4(normalizedCoords.x, normalizedCoords.y, 0.0, 1.0); 
}