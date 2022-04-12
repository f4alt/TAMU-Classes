#version 120

uniform mat4 P;
uniform mat4 MV;
uniform mat4 MVit;
uniform float t;
attribute vec4 aPos; // In object space
attribute vec3 aNor; // In object space
attribute vec2 aTex;

varying vec3 normal; // In camera space
varying vec3 vPos; // in camera space
varying vec2 vTex;

void main()
{
	// calculate position (x is in pos.x, theta is in pos.y)
	float x = aPos.x;
	float theta = aPos.y;
	float cosx = cos(x+t);
	float sinx = sin(x+t);
	float cost = cos(theta);
	float sint = sin(theta);

	float f = cosx + 2.0;
	float y = f * cost;
	float z = f * sint;
	vec4 newPos = vec4(x, y, z, 1.0);

	gl_Position = P * (MV * newPos);

	// calculate normals using derivative
	vec3 dp_dx = vec3(1, -sinx * cost, -sinx * sint);
	vec3 dp_dtheta = vec3(0, -(cosx + 2) * sint, (cosx + 2) * cost);
	vec3 nor = cross(dp_dx, dp_dtheta);
	vec3 n_hat = normalize(nor);

	normal = vec3(MV * vec4(n_hat, 0.0)); // Assuming MV contains only translations and rotations
	vTex = aTex;

  vPos = vec3(1.0);
}
