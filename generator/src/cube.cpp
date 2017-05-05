#include "cube.h"
#include <algorithm>
#include <cmath>
#include "../../src/vertex.h"
using std::vector;

Shape* draw_xy(float x, float y, float z, int n);
Shape* draw_xy(float x, float jx, float y, float jy, float z);
Shape* draw_yz(float x, float y, float z, int n);
Shape* draw_yz(float x, float y, float jy, float z, float jz);
Shape* draw_xz(float x, float y, float z, int n);
Shape* draw_xz(float x, float jx, float y, float z, float jz);
void convert_xyz_to_cube_uv(float x, float y, float z, float *u, float *v);

Shape* cube(float x, float y, float z, int n) {
    Shape *r, *tmp;

/*
    "<-" points to hidden faces

        o--------o
       /   E    /|<- B
      /        / |
     o--------o  |
  D->|        | C|
     |    A   |  o
     |        | /
     |        |/<- F
     o--------o
*/
    //Draws A face
    tmp = draw_xy(x, y, z/2, n);
    r->push_shape(tmp);

    //Draws B face
    tmp = draw_xy(x, y, -z/2, n);
    tmp->reverse();
    r->push_shape(tmp);

    //Draws C face
    tmp = draw_yz(x/2, y, z, n);
    r->push_shape(tmp);

    //Draws D face
    tmp = draw_yz(-x/2, y, z, n);
    tmp->reverse();
    r->push_shape(tmp);

    //Draws E face
    tmp = draw_xz(x, y, z, n);
    r->push_shape(tmp);

    //Draws F face
    tmp = draw_xz(x, 0, z, n);
    tmp->reverse();
    r->push_shape(tmp);

    return r;
}

Shape* draw_xy(float x, float y, float z, int n) {
    Shape *r, *tmp;
    float ix, fx, jx; //initial x, final x, jump x
    float iy, fy, jy;

    ix = -x/2;
    jx = x/n;
    fx = x/2;

    iy = 0;
    jy = y/n;
    fy = y;


    for (; iy < fy; iy += jy)
        for(ix = -x/2; ix < fx; ix += jx) {
            tmp = draw_xy(ix, jx, iy, jy, z);
            r->push_shape(tmp);
        }


    return r;
}

Shape* draw_yz(float x, float y, float z, int n) {
    Shape *r, *tmp;
    float iz, fz, jz; //initial z, final z, jump z
    float iy, fy, jy;

    iy = 0;
    jy = y/n;
    fy = y;

    iz = -z/2;
    jz = z/n;
    fz = z/2;

    for (; iy < fy; iy += jy)
        for(iz = -z/2; iz < fz; iz += jz) {
            tmp = draw_yz(x, iy, jy, iz, jz);
            r->push_shape(tmp);
        }

    return r;
}

Shape* draw_xz(float x, float y, float z, int n) {
    Shape *r, *tmp;
    float ix, fx, jx; //initial x, final x, jump x
    float iz, fz, jz;

    ix = -x/2;
    jx = x/n;
    fx = x/2;

    iz = -z/2;
    jz = z/n;
    fz = z/2;

    for (; ix < fx; ix += jx)
        for(iz = -z/2; iz < fz; iz += jz) {
            tmp = draw_xz(ix, jx, y, iz, jz);
            r->push_shape(tmp);
        }

    return r;
}

Shape* draw_xy(float x, float jx, float y, float jy, float z) {
    Shape* r;
    int p = z > 0 ? 1 : -1;
    float u, v;

    r->push_vertex(new Vertex(x, y, z));
    r->push_normal(new Vertex(0, 0, p));
    convert_xyz_to_cube_uv(x, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x+jx, y, z));
    r->push_normal(new Vertex(0, 0, p));
    convert_xyz_to_cube_uv(x+jx, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x+jx, y+jy, z));
    r->push_normal(new Vertex(0, 0, p));
    convert_xyz_to_cube_uv(x+jx, y+jy, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));



    r->push_vertex(new Vertex(x, y, z));
    r->push_normal(new Vertex(0, 0, p));
    convert_xyz_to_cube_uv(x, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x+jx, y+jy, z));
    r->push_normal(new Vertex(0, 0, p));
    convert_xyz_to_cube_uv(x+jx, y+jy, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x, y+jy, z));
    r->push_normal(new Vertex(0, 0, p));
    convert_xyz_to_cube_uv(x, y+jy, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    return r;
}

Shape* draw_yz(float x, float y, float jy, float z, float jz){
    Shape* r;
    int p = x > 0 ? 1 : -1;
    float u, v;

    r->push_vertex(new Vertex(x, y, z+jz));
    r->push_normal(new Vertex(p, 0, 0));
    convert_xyz_to_cube_uv(x, y, z+jz, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x, y, z));
    r->push_normal(new Vertex(p, 0, 0));
    convert_xyz_to_cube_uv(x, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x, y+jy, z+jz));
    r->push_normal(new Vertex(p, 0, 0));
    convert_xyz_to_cube_uv(x, y+jy, z+jz, &u, &v);
    r->push_texture(new Vertex(u, v, 0));



    r->push_vertex(new Vertex(x, y+jy, z+jz));
    r->push_normal(new Vertex(p, 0, 0));
    convert_xyz_to_cube_uv(x, y+jy, z+jz, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x, y, z));
    r->push_normal(new Vertex(p, 0, 0));
    convert_xyz_to_cube_uv(x, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x, y+jy, z));
    r->push_normal(new Vertex(p, 0, 0));
    convert_xyz_to_cube_uv(x, y+jy, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    return r;
}

Shape* draw_xz(float x, float jx, float y, float z, float jz){
    Shape* r;
    int p = y > 0 ? 1 : -1;
    float u, v;

    r->push_vertex(new Vertex(x, y, z));
    r->push_normal(new Vertex(0, p, 0));
    convert_xyz_to_cube_uv(x, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x, y, z+jz));
    r->push_normal(new Vertex(0, p, 0));
    convert_xyz_to_cube_uv(x, y, z+jz, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x+jx, y, z+jz));
    r->push_normal(new Vertex(0, p, 0));
    convert_xyz_to_cube_uv(x+jx, y, z+jz, &u, &v);
    r->push_texture(new Vertex(u, v, 0));


    r->push_vertex(new Vertex(x, y, z));
    r->push_normal(new Vertex(0, p, 0));
    convert_xyz_to_cube_uv(x, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x+jx, y, z+jz));
    r->push_normal(new Vertex(0, p, 0));
    convert_xyz_to_cube_uv(x+jx, y, z+jz, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    r->push_vertex(new Vertex(x+jx, y, z));
    r->push_normal(new Vertex(0, p, 0));
    convert_xyz_to_cube_uv(x+jx, y, z, &u, &v);
    r->push_texture(new Vertex(u, v, 0));

    return r;
}

void convert_xyz_to_cube_uv(float x, float y, float z, float *u, float *v) {
  float absX = fabs(x);
  float absY = fabs(y);
  float absZ = fabs(z);

  int isXPositive = x > 0 ? 1 : 0;
  int isYPositive = y > 0 ? 1 : 0;
  int isZPositive = z > 0 ? 1 : 0;

  float maxAxis, uc, vc;

  // POSITIVE X
  if (isXPositive && absX >= absY && absX >= absZ) {
    // u (0 to 1) goes from +z to -z
    // v (0 to 1) goes from -y to +y
    maxAxis = absX;
    uc = -z;
    vc = y;
  }
  // NEGATIVE X
  if (!isXPositive && absX >= absY && absX >= absZ) {
    // u (0 to 1) goes from -z to +z
    // v (0 to 1) goes from -y to +y
    maxAxis = absX;
    uc = z;
    vc = y;
  }
  // POSITIVE Y
  if (isYPositive && absY >= absX && absY >= absZ) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from +z to -z
    maxAxis = absY;
    uc = x;
    vc = -z;
  }
  // NEGATIVE Y
  if (!isYPositive && absY >= absX && absY >= absZ) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from -z to +z
    maxAxis = absY;
    uc = x;
    vc = z;
  }
  // POSITIVE Z
  if (isZPositive && absZ >= absX && absZ >= absY) {
    // u (0 to 1) goes from -x to +x
    // v (0 to 1) goes from -y to +y
    maxAxis = absZ;
    uc = x;
    vc = y;
  }
  // NEGATIVE Z
  if (!isZPositive && absZ >= absX && absZ >= absY) {
    // u (0 to 1) goes from +x to -x
    // v (0 to 1) goes from -y to +y
    maxAxis = absZ;
    uc = -x;
    vc = y;
  }

  // Convert range from -1 to 1 to 0 to 1
  *u = 0.5f * (uc / maxAxis + 1.0f);
  *v = 0.5f * (vc / maxAxis + 1.0f);
}
