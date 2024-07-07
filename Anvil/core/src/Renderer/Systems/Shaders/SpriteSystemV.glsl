#version 450

layout(binding = 0) uniform UBO {
    mat4 view;
    mat4 proj;
} ubo;

layout(push_constant) uniform Push {
    mat4 model;
    vec3 color;
} push;

layout(location = 0) in vec2 inPosition;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = ubo.proj * ubo.view * push.model * vec4(inPosition, 0.0, 1.0);
    fragColor = push.color;
}