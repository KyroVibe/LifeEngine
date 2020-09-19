#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform vec4 cameraPosition;
uniform float aspectRatio;
uniform float cameraScale;

uniform float rotation = 30;

mat2 rotate2d(float _angle) {
    return mat2(cos(_angle), sin(_angle),
        -sin(_angle), cos(_angle));
}

vec4 rotate2dCoord(vec4 _coord, float _angle) {
    vec2 a = vec2(_coord.x, _coord.y) * rotate2d(_angle);
    return vec4(a.x, a.y, _coord.z, _coord.w);
}

void main() {
    float xScale = cameraScale * (1 / aspectRatio);
    float yScale = cameraScale;
    vec4 newPos = vec4((position.x - cameraPosition.x), (position.y - cameraPosition.y), position.z, position.w);
    vec4 rotatedPos = rotate2dCoord(newPos, rotation);
    gl_Position = vec4(xScale* rotatedPos.x, yScale* rotatedPos.y, newPos.z, newPos.w);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
    color = u_Color;
};