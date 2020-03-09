#type vertex
#version 330 core

uniform mat4 uViewProj;
uniform mat4 uTransform;

layout(location = 0) in vec3 aPos;
out vec3 vPos;

void main() {
    vPos = aPos;
    gl_Position = uViewProj * uTransform * vec4(aPos, 1.0);
}


#type fragment
#version 330 core

uniform vec3 uColor;

layout(location = 0) out vec4 color;
in vec3 vPos;

void main() {
    color = vec4(uColor, 1.0);
}