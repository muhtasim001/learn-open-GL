#version 430

mat4 buildRotationZ(float rad) {
    mat4 zrot = mat4 (cos(rad), -sin(rad), 0.0, 0.0, 
                      sin(rad), cos(rad), 0.0, 0.0, 
                      0.0, 0.0, 1.0, 0.0, 
                      0.0 , 0.0, 0.0, 1.0);
    return zrot;
}

void main (void) {
    
    mat4 myrot = buildRotationZ(3.14159265359);

    if (gl_VertexID == 0)
        gl_Position = myrot * vec4 (0.25, -0.25, 0.0, 1.0);
    else if (gl_VertexID == 1)
        gl_Position = myrot * vec4 (-0.25, -0.25, 0.0, 1.0);
    else
        gl_Position = myrot * vec4 (0.00, 0.25, 0.0, 1.0);
}
