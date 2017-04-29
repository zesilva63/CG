#include "cone.h"
#include <math.h>

using std::vector;


vector<Vertex*> torus(float inner_radious, float outter_radius, int slices, int stacks){
	vector<Vertex*> r;
    float angle_iterator = 0;
    float stack_iterator = 0;
    float slice_iterator = 0;
    float stack_height = ( outter_radius - inner_radious ) / stacks;
    float slices_height = ( outter_radius - inner_radious ) / slices;
    float angle = 2 * M_PI / slices;
    int i,j;


	//making firts cicle
	for(i=0; i!=slices;i++){
        r.push_back(new Vertex(inner_radious * cos(angle_iterator) , stack_height, radious * sin(angle_iterator)));
        r.push_back(new Vertex(inner_radious * cos(angle_iterator) , 0, radious * sin(angle_iterator)));
        angle_iterator += angle;
        r.push_back(new Vertex( inner_radious * cos(angle_iterator) , 0, radious * sin(angle_iterator) ));
    }





    return r;
}
