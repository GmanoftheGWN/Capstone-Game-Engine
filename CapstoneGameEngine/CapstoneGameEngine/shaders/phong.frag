#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform LightingUBO {
	vec4 lightPos[3];
	vec4 diffColour[3];
} lightingUBO;

layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) out vec4 fragColor;

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 lightDir[3];
layout(location = 4) in vec3 eyeDir; 
layout(location = 5) in vec2 fragTexCoord; 

void main() { 
	vec4 ks[3];
	for (int i = 0; i < 3; ++i) {
		ks[i] = 0.075 * lightingUBO.diffColour[i];
	}
	vec4 kt = texture(texSampler, fragTexCoord);
	const vec4 ka = 0.1 * kt;
	
	float diff[3]; 
	vec3 reflection[3];
	float spec[3];
	for (int i = 0; i < 3; ++i) {
		reflection[i] = normalize(reflect(-lightDir[i], vertNormal));
		diff[i] = max(dot(vertNormal, -lightDir[i]), 0.0);
		spec[i] = 0.0f;
		if (diff[i] > 0) {
			spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
			spec[i] = pow(spec[i], 14.0);
		}
	}
	vec4 color = ka;
	for (int i = 0; i < 3; ++i) {
		color += (diff[i] * 0.1 * lightingUBO.diffColour[i]) + (spec[i] * ks[i]);
	}
	fragColor =  color;	
} 

