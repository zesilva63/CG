#ifndef __SCALE__
#define __SCALE__

#include <tinyxml2.h>
#include "operation.h"

class Scale : public Operation {
    public:
        Scale();
        void parse(tinyxml2::XMLElement *sc);
        void apply();
        const char* type();
    private:
        double x;
        double y;
        double z;
};

#endif
