#version 120

uniform mat4 P;
uniform mat4 MV;
uniform mat4 MVit;

attribute vec4 aPos; // in object space
attribute vec3 aNor; // in object space

varying vec3 normal; // Pass to fragment shader

void main()
{
	gl_Position = P * (MV * aPos);

	normal = vec3(MVit * vec4(aNor, 0.0));
}
