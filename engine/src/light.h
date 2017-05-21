#ifndef __LIGHT__
#define __LIGHT__

#include <tinyxml2.h>

class Light {
    public:
    	void turnOn();
        void parse(tinyxml2::XMLElement *model);

    private:
        float pos[4];
};

#endif
