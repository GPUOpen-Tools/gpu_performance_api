#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 fragColor;
void main() {
//    outColor = vec4(vec3(1,1,1) - fragColor, 1.0);
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
}
