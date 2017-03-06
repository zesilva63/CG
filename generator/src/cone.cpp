#include "cone.h"
#include <math.h>

using std::vector;

vector<Vertex*> cone(float base, float height, int slices, int stacks) {
    vector<Vertex*> r;
    float radious = base/2;
    float angle = 2 * M_PI / slices;
    float angle_iterator = 0;
    float angle_upper;
    float step = height/stacks;
    float top_step = 0;
    float bot_step = - step;
    float inner = radious/stacks;
    float outer_radious = radious +inner;
    int i,j;
    
    // making the base of the cone
    for(i=0; i!=slices;i++){
        r.push_back(new Vertex(0,0,0));
        r.push_back(new Vertex(radious * cos(angle_iterator) , 0, radious * sin(angle_iterator)));
        angle_iterator += angle;
        r.push_back(new Vertex( radious * cos(angle_iterator) , 0, radious * sin(angle_iterator) ));
    }
    
    //making all the stacks
    for(j=0;j!=stacks;j++){
        radious -= inner; outer_radious -= inner;
        top_step += step; bot_step += step;
        angle_iterator=0;  angle_upper = angle;
        
        //making a stack
        for(i=0; i!=slices;i++){
            //making down triangle of a slice of a stack
            r.push_back(new Vertex( outer_radious * cos(angle_iterator), bot_step, outer_radious * sin(angle_iterator)));
            r.push_back(new Vertex( radious * cos(angle_upper)  , top_step, radious * sin(angle_upper)));
            r.push_back(new Vertex( outer_radious * cos(angle_upper) , bot_step, outer_radious * sin(angle_upper)));
            
            //making upper triangle of a slice of a stack
            r.push_back(new Vertex( outer_radious * cos(angle_iterator), bot_step, outer_radious * sin(angle_iterator)));
            r.push_back(new Vertex( radious * cos(angle_iterator), top_step, radious * sin(angle_iterator)));
            r.push_back(new Vertex( radious * cos(angle_upper), top_step, radious * sin(angle_upper)));   
            angle_iterator += angle;
            angle_upper += angle;
        }
    }
    return r;
}
