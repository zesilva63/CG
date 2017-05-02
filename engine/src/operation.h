#ifndef __OPERATION__
#define __OPERATION__

#include <tinyxml2.h>

class Operation {
    public:
        virtual void apply() = 0;
        virtual void parse(tinyxml2::XMLElement *op) = 0;
        virtual const char* type() = 0;
};

#endif
