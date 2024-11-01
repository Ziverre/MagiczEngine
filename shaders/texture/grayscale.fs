#version 330

out vec4 fragColor;

//uniform float _texture_width;
//uniform float _texture_height;

uniform sampler2D inputTexture;

void main(){
	
	vec2 uv = gl_FragCoord.xy / vec2(128.0);
	
	//the naming is so stupid, I feel ashamed
	vec3 providedTexture = texture(inputTexture, uv);
    vec3 color = vec3((providedTexture.r + providedTexture.g + providedTexture.b) / 3.0);
	
	fragColor = vec4(color, 1.0);
}