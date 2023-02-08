#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform CameraUBO {
    mat4 viewMatrix;
    mat4 projectionMatrix;
} cameraUBO;

layout(binding = 1) uniform LightingUBO {
	vec4 lightPos[3];
	vec4 diffColour[3];
} lightingUBO;

layout (push_constant) uniform PushConstMatrix {
	mat4 modelMatrix;
	mat4 normalMatrix;
} pushConstMatrix;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 lightDir[3];
layout(location = 4) out vec3 eyeDir; 
layout(location = 5) out vec2 fragTexCoord; 

void main() {
    fragTexCoord = inTexCoord;
	vertNormal = normalize(mat3(pushConstMatrix.normalMatrix) * inNormal); /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(cameraUBO.viewMatrix * pushConstMatrix.modelMatrix * vec4(inPosition, 1.0)); /// This is the position of the vertex from the origin
	vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;
	for (int i = 0; i < 3; ++i) {
		lightDir[i] = normalize(vec3(lightingUBO.lightPos[i]) - vertPos); /// Create the light direction. I do the math with in class 
	}
	gl_Position = cameraUBO.projectionMatrix * cameraUBO.viewMatrix * pushConstMatrix.modelMatrix * vec4(inPosition, 1.0);
}
