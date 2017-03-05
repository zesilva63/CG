#include "sphere.h"

using std::vector;

std::vector<Vertex*> sphere(double raio, int camadasV, int camadasH) {

    std::vector<Vertex*> points;

    int i, j;
    float teta = 0;
    float fi = 0;
	float saltoH = M_PI / camadasH;
	float saltoV = 2 * (M_PI) / camadasV;
	float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	for (i = 0; i < camadasH; i++) {
		teta = 0;

		for (j = 0; j < camadasV; j++) {

			x1 = raio*sin(fi)*sin(teta);
			y1 = raio*cos(fi);
			z1 = raio*cos(teta)*sin(fi);

			x2 = raio*sin(fi + saltoH)*sin(teta + saltoV);
			y2 = raio*cos(fi + saltoH);
			z2 = raio*cos(teta + saltoV)*sin(fi + saltoH);

			x3 = raio*sin(fi + saltoH)*sin(teta);
			y3 = raio*cos(fi + saltoH);
			z3 = raio*cos(teta)*sin(fi + saltoH);

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
/*
int main () {

    vector<Vertex*> v;
    v = sphere(1,20,20);
    return 0;
}
*/
