#version 120

uniform mat4 P;
uniform mat4 MV;
uniform mat4 MVit;

attribute vec4 aPos; // in object space
attribute vec3 aNor; // in object space

varying vec3 normal; // in camera space
varying vec3 vPos; // in camera space

void main()
{
	gl_Position = P * (MV * aPos);

	normal = vec3(MVit * vec4(aNor, 0.0));
	vec4 vPos4 = MV * aPos;
	vPos = vec3(vPos4) / vPos4.w;
}
