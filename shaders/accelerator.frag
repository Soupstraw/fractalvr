#version 410 core

precision highp float;

uniform sampler2D mainTex;

in mat4 vViewMatrix;
in mat4 vProjectionMatrix;
in vec3 vRayDir;
in vec2 vScreenSize;
in vec2 vScreenPos;
in vec2 vPosition;

out vec4 outputColor;

float _MarchThreshold = 0.0001;
int _Steps = 500;
float _MarchRange = 1000.0;
float _Delta = 0.0001;
int Iterations = 4;
float Bailout = 2;
float Power = 8;
float focalLength = 1.0;
float accelRange = 0.01f;

float DE(vec3 pos) {
	pos -= vec3(0, 1, 0);
	vec3 z = pos;
	float dr = 1.0;
	float r = 0.0;
	for (int i = 0; i < Iterations ; i++) {
		r = length(z);
		if (r>Bailout) break;

		// convert to polar coordinates
		float theta = acos(z.z/r);
		float phi = atan(z.y,z.x);
		dr =  pow( r, Power-1.0)*Power*dr + 1.0;

		// scale and rotate the point
		float zr = pow( r,Power);
		theta = theta*Power;
		phi = phi*Power;

		// convert back to cartesian coordinates
		z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
		z+=pos;
	}
	return 0.5*log(r)*r/dr;
}

vec3 calculate_normal(vec3 pos) {
	return -normalize(vec3(
		DE(pos-vec3(_Delta,0,0)) - DE(pos+vec3(_Delta,0,0)),
		DE(pos-vec3(0,_Delta,0)) - DE(pos+vec3(0,_Delta,0)),
		DE(pos-vec3(0,0,_Delta)) - DE(pos+vec3(0,0,_Delta))
	));
}

void main()
{
	if(mod(vScreenPos, vec2(3, 3)) == vec2(0)){
        outputColor = texture2D(mainTex, vPosition);
	}else{
	    outputColor = vec4(0, 0, 1, 1);
	    //outputColor = texture2D(mainTex, vPosition);
	}
	//outputColor = texture2D(mainTex, vec2(0, 0));
}