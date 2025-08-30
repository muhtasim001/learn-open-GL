#version 430

layout (location = 0) in vec3 position;

uniform mat4 v_matrix;
uniform mat4 p_matrix;

uniform float tf;

out vec4 varyingColor;

mat4 buildRotationX (float rad);
mat4 buildRotationY (float rad);
mat4 buildRotationZ (float rad);
mat4 buildTranslate (float x, float y, float z);

void main (void) {
    
    float i = gl_InstanceID + tf;

    float a = sin (2.35 * i) * 8.0;
    float b = cos (3.52 * i) * 8.0;
    float c = sin (4.70 * i) * 8.0;

    mat4 localRotX = buildRotationX(100.75 * i);
    mat4 localRotY = buildRotationX(100.75 * i);
    mat4 localRotZ = buildRotationX(100.75 * i);
    mat4 localTran = buildTranslate(a, b , c);

    mat4 r_matrix = localRotY * localRotX * localRotZ;
    mat4 m_matrix = localTran * r_matrix;
    mat4 mv_matrix = v_matrix * m_matrix;

    gl_Position = p_matrix * mv_matrix * vec4 (position, 1.0);
    varyingColor = vec4(position, 1.0) * 0.5 + vec4 (0.5, 0.5, 0.5, 0.5);

}

mat4 buildTranslate(float x , float y, float z) {
    
    mat4 trans = mat4 (0.1, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                         x,   y,   z, 1.0);

    return trans;

}

mat4 buildRotationX(float rad) {

    mat4 xrot = mat4 (1.0,      0.0,       0.0, 0.0,
                      0.0, cos(rad), -sin(rad), 0.0,
                      0.0, sin(rad),  cos(rad), 0.0,
                      0.0,      0.0,       0.0, 1.0);

    return xrot;

}

mat4 buildRotationY(float rad) {

    mat4 yrot = mat4 (cos(rad), 0.0, sin(rad), 0.0,
                           0.0, 1.0,      0.0, 0.0,
                      sin(rad), 0.0, cos(rad), 0.0,
                      0.0,      0.0,      0.0, 1.0);

    return yrot;
}

mat4 buildRotationZ(float rad) {
    
    mat4 zrot = mat4 (cos(rad), -sin(rad), 0.0, 0.0, 
                      sin(rad),  cos(rad), 0.0, 0.0, 
                      0.0,            0.0, 1.0, 0.0, 
                      0.0,            0.0, 0.0, 1.0);
    return zrot;

}
