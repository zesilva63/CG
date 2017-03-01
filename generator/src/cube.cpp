#include "cube.h"
#include <algorithm>
using std::vector;

vector<Vertex*> draw_xy(float x, float y, float z, int n);
vector<Vertex*> draw_xy(float x, float jx, float y, float jy, float z);
vector<Vertex*> draw_yz(float x, float y, float z, int n);
vector<Vertex*> draw_yz(float x, float y, float jy, float z, float jz);
vector<Vertex*> draw_xz(float x, float y, float z, int n);
vector<Vertex*> draw_xz(float x, float jx, float y, float z, float jz);

vector<Vertex*> cube(float x, float y, float z, int n) {
    vector<Vertex*> r, tmp;

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
    r.insert(r.end(), tmp.begin(), tmp.end());

    //Draws B face
    tmp = draw_xy(x, y, -z/2, n);
    std::reverse(tmp.begin(), tmp.end());
    r.insert(r.end(), tmp.begin(), tmp.end());

    //Draws C face
    tmp = draw_yz(x/2, y, z, n);
    r.insert(r.end(), tmp.begin(), tmp.end());

    //Draws D face
    tmp = draw_yz(-x/2, y, z, n);
    std::reverse(tmp.begin(), tmp.end());
    r.insert(r.end(), tmp.begin(), tmp.end());

    //Draws E face
    tmp = draw_xz(x, y, z, n);
    r.insert(r.end(), tmp.begin(), tmp.end());

    //Draws F face
    tmp = draw_xz(x, 0, z, n);
    std::reverse(tmp.begin(), tmp.end());
    r.insert(r.end(), tmp.begin(), tmp.end());

    return r;
}

vector<Vertex*> draw_xy(float x, float y, float z, int n) {
    vector<Vertex*> r, tmp;
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
            r.insert(r.end(), tmp.begin(), tmp.end());
        }


    return r;
}

vector<Vertex*> draw_yz(float x, float y, float z, int n) {
    vector<Vertex*> r, tmp;
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
            r.insert(r.end(), tmp.begin(), tmp.end());
        }

    return r;
}

vector<Vertex*> draw_xz(float x, float y, float z, int n) {
    vector<Vertex*> r, tmp;
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
            r.insert(r.end(), tmp.begin(), tmp.end());
        }

    return r;
}

vector<Vertex*> draw_xy(float x, float jx, float y, float jy, float z) {
    vector<Vertex*> r;

    r.push_back(new Vertex(x, y, z));
    r.push_back(new Vertex(x+jx, y, z));
    r.push_back(new Vertex(x+jx, y+jy, z));

    r.push_back(new Vertex(x, y, z));
    r.push_back(new Vertex(x+jx, y+jy, z));
    r.push_back(new Vertex(x, y+jy, z));


    return r;
}

vector<Vertex*> draw_yz(float x, float y, float jy, float z, float jz){
    vector<Vertex*> r;

    r.push_back(new Vertex(x, y, z+jz));
    r.push_back(new Vertex(x, y, z));
    r.push_back(new Vertex(x, y+jy, z+jz));

    r.push_back(new Vertex(x, y+jy, z+jz));
    r.push_back(new Vertex(x, y, z));
    r.push_back(new Vertex(x, y+jy, z));

    return r;
}

vector<Vertex*> draw_xz(float x, float jx, float y, float z, float jz){
    vector<Vertex*> r;

    r.push_back(new Vertex(x, y, z));
    r.push_back(new Vertex(x, y, z+jz));
    r.push_back(new Vertex(x+jx, y, z+jz));

    r.push_back(new Vertex(x, y, z));
    r.push_back(new Vertex(x+jx, y, z+jz));
    r.push_back(new Vertex(x+jx, y, z));

    return r;
}
