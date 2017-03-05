#include "sphere.h"

using std::vector;


vector<Vertex*> sphere(double radious, int slicesV, int stacksH, std::string file_name) {

    const double PI = 3.14159265358979323846;

    double distVertical = (2 * PI) / slicesV;
    double distHorizontal = PI / stacksH;

    vector<Vertex*> points;

	for (int i = 0; i <= slicesV; i++) {

        double angYX = distHorizontal * i;

		for (int j = 0; j <= stacksH; j++) {

			double angZX = distVertical * j;

			double x1 = radious * sin(angYX) * sin(angZX);
			double y1 = radious * cos(angYX);
			double z1 = radious * sin(angYX) * cos(angZX);
            printf("%f %f %f\n",x1/radious,y1/radious,z1/radious);
			points.push_back(new Vertex(x1/radious, y1/radious, z1/radious));
		}
	}

    return points;
}
/*
int main () {

    vector<Vertex*> v;
    v = sphere(2,10,10,"sphere.3d");
    return 0;
}
*/
