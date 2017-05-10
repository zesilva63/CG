#ifndef __CAMERA__
#define __CAMERA__

class Camera {
    public:
        Camera();
        void key_down(unsigned int key);
        void key_up(unsigned int key);
        void view();

    private:
        float xpos;
        float ypos;
        float zpos;
        float look_at_x;
        float look_at_y;
        float look_at_z;
        bool keys[256];

        void apply();
};

#endif
