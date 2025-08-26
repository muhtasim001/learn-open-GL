#version 430

mat4 buildTranslation(float x , float y, float z) {
    
    mat4 trans = mat4 (0.1, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0
                       0.0, 0.0, 1.0, 0.0
                       x, y, z, 1.0);

    return trans;

}

mat4 buildRotationX(float rad) {

    mat4 xrot = mat4 (1.0, 0.0, 0.0, 0.0
                      0.0, cos(rad), -sin(rad), 0.0
                      0.0, sin(rad), cos(rad), 0.0,
                      0.0, 0.0, 0.0, 1.0);

    return xrot;

}

mat4 buildRotationY(float rad) {

    mat4 yrot = mat4 (cos(rad), 0.0, sin(rad), 0.0,
                      0.0, 1.0, 0.0, 1.0
                      sin(rad), 0.0, cos(rad), 0.0
                      0.0, 0.0, 0.0, 1.0);

    return yrot;
}

mat4 buildRotationZ (float rad) {
    
    mat4 zrot = mat4 (cos(rad), -sin(rad), 0.0, 0.0, 
                      sin(rad), cos(rad), 0.0, 0.0, 
                      0.0, 0.0, 1.0, 0.0, 
                      0.0 , 0.0, 0.0, 1.0);
    return zrot;

}
