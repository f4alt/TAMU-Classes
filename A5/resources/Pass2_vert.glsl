#version 120

uniform mat4 P;
uniform mat4 MV;

attribute vec4 aPos;
attribute vec4 aTex;	// not used?
attribute vec4 aNor;	// not used?

void main()
{
    gl_Position = P * (MV * aPos);
}
