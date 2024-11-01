#version 330

out vec4 fragColor;

uniform float diameter;
uniform float centerX;
uniform float centerY;
uniform float fuzz;
uniform sampler2D petTexture;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453) - 0.5;
}

float circle(vec2 center, vec2 coords, float radius){
	return pow(coords.x - center.x, 2.0) + pow(coords.y - center.y, 2.0) < pow(radius, 2.0) ? 1.0 : 0.0;
}

void main(){
	float radius = diameter / 2.0;
	
	vec2 coord = gl_FragCoord.xy;
	
	coord.x += random(vec2(coord.y - centerY + fuzz)) * fuzz;

	vec2 uv = fract((gl_FragCoord.xy - vec2(centerX + radius + 10.0, centerY + radius)) / vec2(radius * 2.0 + 10.0, radius * 2.0)); // what the fuck is this?
	//apparently not using floor() shits into the quality of displayed texture
	vec2 texUV = fract((gl_FragCoord.xy - floor(vec2(centerX + radius + 10.0, centerY + radius))) / vec2(128.0));
	//texUV.y = 1.0 - texUV.y;
	
	float circ = circle(vec2(centerX, centerY), coord, radius);
	vec4 color = vec4(texture(petTexture, texUV).rgb, circ);
    
	fragColor = color;
}