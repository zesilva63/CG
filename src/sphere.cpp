#include "sphere.h"

using std::vector;

std::vector<Vertex*> sphere(double radious, int camadasV, int camadasH, std::string file_name) {

    const double PI = 3.14159265358979323846;

    double a;
    double b;
    float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
    float saltoH = 90 / camadasH;
    float saltoV = 360 / camadasV;
    std::vector<Vertex*> points;

    for(b = 0; b <= 90 - saltoH; b += saltoH) {

        for(a = 0; a <= 360 - saltoV; a += saltoV) {

            x1 = radious * sin((a) / 180 * PI) * sin((b) / 180 * PI);
            y1 = radious * cos((a) / 180 * PI) * sin((b) / 180 * PI);
            z1 = radious * cos((b) / 180 * PI);

            x2 = radious * sin((a) / 180 * PI) * sin((b + camadasV) / 180 * PI);
            y2 = radious * cos((a) / 180 * PI) * sin((b + camadasV) / 180 * PI);
            z2 = radious * cos((b + camadasH) / 180 * PI);

            x3 = radious * sin((a + camadasH) / 180 * PI) * sin((b) / 180 * PI);
            y3 = radious * cos((a + camadasH) / 180 * PI) * sin((b) / 180 * PI);
            z3 = radious * cos((b) / 180 * PI);

            x4 = radious * sin((a + camadasH) / 180 * PI) * sin((b + camadasV) / 180 * PI);
            y4 = radious * cos((a + camadasH) / 180 * PI) * sin((b + camadasV) / 180 * PI);
            z4 = radious * cos((b + camadasH) / 180 * PI);

            points.push_back(new Vertex(x1, y1, z1));
            points.push_back(new Vertex(x2, y2, z2));
            points.push_back(new Vertex(x3, y3, z3));
            points.push_back(new Vertex(x4, y4, z4));

        }
    }

    return points;
}
