#include "sphere.h"
using std::vector;

#define PI 3.14159265358979323846

vector<Vertex*> sphere(double radious, int slices, int stacks) {

    double camadas = PI / slices;
	double rotacoes = 2 * PI / stacks;
    vector<Vertex*> points;

	for (int i = 0; i <= slices; i++) {
		double angYX = camadas * i; // 0 to 180º in vertical

		for (int j = 0; j <= stacks; j++) {

			double angZX = rotacoes * j; // 0 to 360º in horizontal

			double x1 = radious * sin(angYX) * sin(angZX);
			double y1 = radious * cos(angYX);
			double z1 = radious * sin(angYX) * cos(angZX);

			points.push_back(new Vertex(x1/radious, y1/radious, z1/radious));
		}
	}

    return points;
}
