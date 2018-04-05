#version 410 core
in mat4 vViewMatrix;
in vec4 vProjection;
in vec2 vScreenSize;
out vec4 outputColor;

float _MarchThreshold = 0.0001;
int _Steps = 500;
float _MarchRange = 1000.0;
float _Delta = 0.0001;
vec2 screenSize = vec2(1080, 1200);
float focalLength = 1.0;

float DE(vec3 pos){
	return length(pos - vec3(0, 0, 0)) - 1;
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
	vec3 curPos = vViewMatrix[3].xyz;

	float dist;
	vec2 vpPos = vec2((gl_FragCoord.x / screenSize.x + 1)/2, (gl_FragCoord.y / screenSize.y + 1)/2);
	vec3 rayDir = -(vViewMatrix * vec4(mix(-vProjection.x, vProjection.y, vpPos.x), mix(-vProjection.z, vProjection.w, vpPos.y), focalLength, 0)).xyz;
	for(int j = 0; j < _Steps; j++){
		dist = abs(DE(curPos.xyz));
		curPos += rayDir*dist;
		if(dist < _MarchThreshold || dist > _MarchRange) break;
	}

	float lumi = clamp(0, 1, dot(calculate_normal(curPos.xyz), vec3(-0.5, -0.5, -0.5)));
	if(dist < _MarchThreshold){
		outputColor = vec4(calculate_normal(curPos.xyz), 1);
		//outputColor = vec4(rayDir, 1);
	}else{
		outputColor = vec4(rayDir, 1);
	}
}