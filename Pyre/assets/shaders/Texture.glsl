#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexID;
layout(location = 4) in float aTilingFactor;

uniform mat4 uViewProjection;

out vec4 vColor;
out vec2 vTexCoord;
out float vTexID;
out float vTilingFactor;

void main() {
    vColor = aColor;
    vTexID = aTexID;
    vTexCoord = aTexCoord;
    vTilingFactor = aTilingFactor;
    gl_Position = uViewProjection * vec4(aPosition, 1.0);
}


#type fragment
#version 330 core

const int MAX_TEXTURES = 16;

uniform sampler2D uTextures[MAX_TEXTURES];

in vec4 vColor;
in vec2 vTexCoord;
in float vTexID;
in float vTilingFactor;

void main() {
    // Directly accessing an array of sampler2Ds with a runtime variable produces artefacts
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (i == vTexID) {
            gl_FragColor = texture(uTextures[i], vTexCoord * vTilingFactor) * vColor;
        }
    }
    
    //gl_FragColor = vColor;
}