#version 410 core
in mat4 vMatrix;
out vec4 outputColor;

float _MarchThreshold = 0.01;

void main()
{
   if(floor(i.vertex.x + i.vertex.y) % 2 < 0.5){
		vec3 curPos = i.camPos;

		float dist;
		for(int j = 0; j < _Steps; j++){
			dist = abs(DE(curPos));
			curPos += i.viewDir * DE(curPos);
			if(dist < _MarchThreshold || dist > _MarchRange) break;
		}


		float lumi = clamp(0, 1, dot(calculate_normal(curPos), vec3(-0.5, -0.5, -0.5)));
		if(dist < _MarchThreshold){
			outputColor = lumi*vec4(0.5, 0.5, 1, 1);
		}
	}
	outputColor = vec4(0,0,0,1);
}