#ifndef __OPERATION__
#define __OPERATION__

#include <tinyxml2.h>

class Operation {
    public:
        virtual void parse(tinyxml2::XMLElement *op) = 0;
        virtual void apply() = 0;
        virtual const char* type() = 0;
};

class Translation : public Operation {
    public:
        Translation();
        void parse(tinyxml2::XMLElement *tr);
        void apply();
        const char* type();
    private:
        double x;
        double y;
        double z;
};

class Rotation : public Operation {
    public:
        Rotation();
        void parse(tinyxml2::XMLElement *rt);
        void apply();
        const char* type();
    private:
        double angle;
        double axisX;
        double axisY;
        double axisZ;
};

class Scaling : public Operation {
    public:
        Scaling();
        void parse(tinyxml2::XMLElement *sc);
        void apply();
        const char* type();
    private:
        double x;
        double y;
        double z;
};

class Coloring : public Operation{
    public:
        Coloring();
        void parse(tinyxml2::XMLElement *sc);
        void apply();
    private:
        double r;
        double g;
        double b;
};

#endif
