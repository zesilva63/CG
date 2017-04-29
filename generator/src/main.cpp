#include "../../src/vertex.h"
#include "cube.h"
#include "plane.h"
#include "cone.h"
#include "sphere.h"
#include "patch.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using std::vector;
using std::ofstream;

void print_usage();
void generate_plane(char* size, char* file_path);
void generate_cube(char* x, char* y, char* z, char* n, char* file_path);
void generate_cone(char* radious, char* height, char* stacks, char* slices, char* file_path);
void generate_sphere(char* radious, char* verticalLayers, char* horizontalLayers, char* file_path);
void generate_patch(char* file_in, char* tesselate, char* file_out);
void write_file(vector<Vertex*> v, char* file_path);

int main (int argc, char** argv) {
    if (argc == 1)
        print_usage();
    else if (!strcmp(argv[1], "plane") && argc == 4)
        generate_plane(argv[2], argv[3]);
    else if (!strcmp(argv[1], "box") && argc == 7)
        generate_cube(argv[2], argv[3], argv[4], argv[5], argv[6]);
    else if(!strcmp(argv[1], "cone") && argc == 7)
        generate_cone(argv[2], argv[3], argv[4], argv[5], argv[6]);
    else if(!strcmp(argv[1], "sphere") && argc == 6)
        generate_sphere(argv[2], argv[3], argv[4], argv[5]);
    else if(!strcmp(argv[1], "patch") && argc == 5)
        generate_patch(argv[2], argv[3], argv[4]);
    else print_usage();

    return 0;
}

void generate_plane(char* size, char* file_path) {
    float f_size = atof(size);
    ofstream file;

    vector<Vertex*> shape = plane(f_size);
    write_file(shape, file_path);
}

void generate_cube(char* x, char* y, char* z, char* n, char* file_path){
    float f_x, f_y, f_z;
    int i_n;

    f_x = atof(x);
    f_y = atof(y);
    f_z = atof(z);
    i_n = atoi(n);

    vector<Vertex*> shape = cube(f_x, f_y, f_z, i_n);
    write_file(shape, file_path);
}

void generate_cone(char* radious, char* height, char* stacks, char* slices, char* file_path){
    float r,h;
    int st,sl;

    r = atof(radious);
    h = atof(height);
    st = atoi(stacks);
    sl = atoi(slices);

    vector<Vertex*> shape = cone(r,h,st,sl);
    write_file(shape, file_path);
}


void generate_sphere(char* radious, char* verticalLayers, char* horizontalLayers, char* file_path){
    float r;
    int vL,hL;

    r = atof(radious);
    vL = atoi(verticalLayers);
    hL = atoi(horizontalLayers);

    vector<Vertex*> shape = sphere(r,vL,hL);
    write_file(shape, file_path);
}

void generate_patch(char* file_in, char* tesselate, char* file_out){
    int n;

    n = atoi(tesselate);
    
    vector<Vertex*> shape = patch(file_in,n);
    write_file(shape, file_out);
}


void write_file(vector<Vertex*> shape, char* file_path){
    ofstream file;
    char buffer[1024];

    file.open(file_path);
    for (Vertex* v : shape) {
        sprintf(buffer, "%f %f %f\n", v->getX(), v->getY(), v->getZ());
        file << buffer;
    }
    file.close();
}

void print_usage() {
    std::cout << "Usage: generate <shape> [options] <file>" << std::endl;
    std::cout << "shapes and options:" << std::endl;
    std::cout << "\tplane <size>" << std::endl;
    std::cout << "\tbox <x> <y> <z> <divisions>" << std::endl;
    std::cout << "\tsphere <radius> <slices> <stacks>" << std::endl;
    std::cout << "\tcone <radius> <height> <slices> <stacks>" << std::endl;
    std::cout << "\tpatch <file> <tesselate>" << std::endl;
}
