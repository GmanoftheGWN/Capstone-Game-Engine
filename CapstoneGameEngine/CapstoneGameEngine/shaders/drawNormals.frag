#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

layout(binding = 1) uniform LightingUBO {
	vec4 lightPos[3];
	vec4 diffColour[3];
} lightingUBO;

void main() {
    fragColor = lightingUBO.diffColour[0];
}