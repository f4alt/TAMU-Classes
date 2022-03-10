#version 120

varying vec2 vTex;

void main()
{
	gl_FragColor.rgb = vec3(vTex, 0.0);
}
