#version 450
#extension GL_ARB_separate_shader_objects : enable

out gl_PerVertex {
    vec4 gl_Position;
};

// A triangle-strip of vertex locations which define a cube.
vec3 cubePositions[36] = vec3[](
    vec3(-1.0f,-1.0f,-1.0f),  // -X side
    vec3(-1.0f,-1.0f, 1.0f),
    vec3(-1.0f, 1.0f, 1.0f),
    vec3(-1.0f, 1.0f, 1.0f),
    vec3(-1.0f, 1.0f,-1.0f),
    vec3(-1.0f,-1.0f,-1.0f),

    vec3(-1.0f,-1.0f,-1.0f),  // -Z side
    vec3( 1.0f, 1.0f,-1.0f),
    vec3( 1.0f,-1.0f,-1.0f),
    vec3(-1.0f,-1.0f,-1.0f),
    vec3(-1.0f, 1.0f,-1.0f),
    vec3( 1.0f, 1.0f,-1.0f),

    vec3(-1.0f,-1.0f,-1.0f),  // -Y side
    vec3( 1.0f,-1.0f,-1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3(-1.0f,-1.0f,-1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3(-1.0f,-1.0f, 1.0f),

    vec3(-1.0f, 1.0f,-1.0f),  // +Y side
    vec3(-1.0f, 1.0f, 1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3(-1.0f, 1.0f,-1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3( 1.0f, 1.0f,-1.0f),

    vec3( 1.0f, 1.0f,-1.0f),  // +X side
    vec3( 1.0f, 1.0f, 1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3( 1.0f,-1.0f,-1.0f),
    vec3( 1.0f, 1.0f,-1.0f),

    vec3(-1.0f, 1.0f, 1.0f),  // +Z side
    vec3(-1.0f,-1.0f, 1.0f),
    vec3( 1.0f, 1.0f, 1.0f),
    vec3(-1.0f,-1.0f, 1.0f),
    vec3( 1.0f,-1.0f, 1.0f),
    vec3( 1.0f, 1.0f, 1.0f)
);

// The width of the cube (used to shrink it down so it is entirely visible in the viewport).
float cubeWidth = 3.0f;

// Rotation angle to tilt the front of the cube downwards so the top is visible.
float tiltRotationRadian = radians(-30.0f);

layout(location = 0) out vec3 fragColor;

void main() {
    // Perform a color correction on the cube to bring all vertex locations
    // (which are being remapped as a color) in the [0-1] range.
    vec3 cubeColor = (cubePositions[gl_VertexIndex] * 1/cubeWidth) + 0.5f;
    fragColor = cubeColor;

    mat3 tiltMatrix;
    tiltMatrix[0] = vec3(1.0f, 0.0f, 0.0f);
    tiltMatrix[1] = vec3(0.0f, cos(tiltRotationRadian), -sin(tiltRotationRadian));
    tiltMatrix[2] = vec3(0.0f, sin(tiltRotationRadian), cos(tiltRotationRadian));

    // Divide the cube position by its width as a simple way to make sure the whole cube is visible.
    vec3 vertPosition = cubePositions[gl_VertexIndex]/cubeWidth;
    vertPosition *= tiltMatrix;

    // Move cube forward so the back isn't being cut off by the depth.
    vertPosition.z += 0.5f;

    gl_Position = vec4(vertPosition, 1.0);

}
