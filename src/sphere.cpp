#include "sphere.h"

using std::vector;

#define PI  3.14159265358979323846

std::vector<Vertex*> sphere(double radius, int verticalLayers, int horizontalLayers) {

    std::vector<Vertex*> points;
    int i, j;
    float teta = 0, fi = 0;
	float saltoH = PI / horizontalLayers;
	float saltoV = (2 * PI) / verticalLayers;
	float x1, y1, z1, x2, y2, z2, x3, y3, z3;

    for (i = 0; i < horizontalLayers; i++) {
		teta = 0;

		for (j = 0; j < verticalLayers; j++) {

			x1 = radius*sin(fi)*sin(teta);
			y1 = radius*cos(fi);
			z1 = radius*cos(teta)*sin(fi);

			x2 = radius*sin(fi + saltoH)*sin(teta + saltoV);
			y2 = radius*cos(fi + saltoH);
			z2 = radius*cos(teta + saltoV)*sin(fi + saltoH);

			x3 = radius*sin(fi + saltoH)*sin(teta);
			y3 = radius*cos(fi + saltoH);
			z3 = radius*cos(teta)*sin(fi + saltoH);

            points.push_back(new Vertex(x1, y1, z1));
            points.push_back(new Vertex(x2, y2, z2));
            points.push_back(new Vertex(x3, y3, z3));

			printf("%f %f %f\n", x1, y1, z1);
			printf("%f %f %f\n", x2, y2, z2);
			printf("%f %f %f\n", x3, y3, z3);

            teta += saltoV;
		}
		fi += saltoH;
	}
    return points;
}

int main () {

    vector<Vertex*> v;
    v = sphere(1,20,15);
    return 0;
}
