#version 330

//TO DO: Make these vec2 (to be figured out)
uniform float startX;
uniform float startY;

uniform float endX;
uniform float endY;

uniform float startDiameter;
uniform float endDiameter;

uniform sampler2D petTexture;

out vec4 fragColor;

//With love and without shame, copied from https://thebookofshaders.com/
mat2 rotate2d(float _angle){
    return mat2(cos(_angle), -sin(_angle), sin(_angle), cos(_angle));
}

void main(){
	vec2 uv = gl_FragCoord.xy / vec2(640.0, 480.0);
	vec2 translate = gl_FragCoord.xy - vec2(startX, startY);
	
	//texture
	
	vec2 texUV = fract(translate / vec2(128.0));
	
	//
	
	translate *= rotate2d(atan(startY - endY, endX - startX));
	
	float alpha = 1.0;
	
	float distance = sqrt(pow(startX - endX, 2.0) +  pow(startY - endY, 2.0));
	
	float slope = (endDiameter/2.0 - startDiameter/2.0) / distance;
	//if someone has a better name for this, please let me know :)
	float girth = translate.x * slope;
	
	//
	alpha = step(0., translate.x) * step(translate.x, distance);
	alpha *= step(-startDiameter/2.0 - girth, translate.y) * step(translate.y, startDiameter/2.0 + girth);
	
    fragColor = vec4(texture(petTexture, texUV).rgb, alpha);
}