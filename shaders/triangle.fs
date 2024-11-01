#version 330
out vec4 fragColor;
void main(){
	vec2 uv = gl_FragCoord.xy / vec2(640.0, 480.0);
    fragColor = vec4(uv.y, uv.x, 1.0, 1.0);
}