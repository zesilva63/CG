#include "sphere.h"
using std::vector;


vector<Vertex*> CreateSphere (double radious, int slicesV, int stacksH std::string file_name) {

    double angle = 0;

    double a;
    double b;

    vector<Vertex*> points;

    for(b = 0; b <= 90 - slicesV; b += slicesV) {

        for(a = 0; a <= 360 - slicesV; a += slicesV) {

            x1 = radious * sin((a) / 180 * PI) * sin((b) / 180 * PI);
            y1 = radious * cos((a) / 180 * PI) * sin((b) / 180 * PI);
            z1 = radious * cos((b) / 180 * PI);

            x2 = radious * sin((a) / 180 * PI) * sin((b + slicesV) / 180 * PI);
            y2 = radious * cos((a) / 180 * PI) * sin((b + slicesV) / 180 * PI);
            z2 = radious * cos((b + slicesV) / 180 * PI);

            x3 = radious * sin((a + slicesV) / 180 * PI) * sin((b) / 180 * PI);
            y3 = radious * cos((a + slicesV) / 180 * PI) * sin((b) / 180 * PI);
            z3 = radious * cos((b) / 180 * PI);

            x4 = radious * sin((a + slicesV) / 180 * PI) * sin((b + slicesV) / 180 * PI);
            y4 = radious * cos((a + slicesV) / 180 * PI) * sin((b + slicesV) / 180 * PI);
            z4 = radious * cos((b + slicesV) / 180 * PI);

            points.push_back(new Vertex(x1, y1, z1);
            points.push_back(new Vertex(x2, y2, z2);
            points.push_back(new Vertex(x3, y3, z3);
            points.push_back(new Vertex(x4, y4, z4);

        }
    }

    return points;
}
