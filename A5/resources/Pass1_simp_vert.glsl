#version 120

uniform mat4 P;
uniform mat4 MV;
uniform mat4 MVit;

attribute vec4 aPos;
attribute vec3 aNor;
attribute vec3 aTex;	// not used?

varying vec3 vPos; // in camera space
varying vec3 vNor; // in camera space

void main()
{
	gl_Position = P * MV * aPos;

	vNor = vec3(MV * vec4(aNor, 0.0));
  vec4 vPos4 = MV * aPos;
	vPos = vec3(vPos4) / vPos4.w;
}
