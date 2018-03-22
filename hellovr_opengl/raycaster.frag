#version 410 core

in mat4 vMatrix;
out vec4 outputColor;

float DE(vec3 pos)
{
	return sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) - 1;
}

float3 calculate_normal(float3 pos) 
{
	return -normalize(float3(
		DE(pos-float3(_Delta,0,0)) - DE(pos+float3(_Delta,0,0)),
		DE(pos-float3(0,_Delta,0)) - DE(pos+float3(0,_Delta,0)),
		DE(pos-float3(0,0,_Delta)) - DE(pos+float3(0,0,_Delta))
	));
}

void main()
{
   if(floor(i.vertex.x + i.vertex.y) % 2 < 0.5){
		float3 curPos = i.camPos;

		float dist;
		for(int j = 0; j < _Steps; j++){
			dist = abs(DE(curPos));
			curPos += i.viewDir * DE(curPos);
			if(dist < 0.01 || dist > 500) break;
		}


		float lumi = clamp(0, 1, dot(calculate_normal(curPos), _LightDir));
		if(dist < _MarchThreshold){
			return fixed4(lumi*_Color);
		}
	}
	outputColor = vec4(0,0,0,1);
}