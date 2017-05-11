#ifndef __CAMERA__
#define __CAMERA__

class Camera {
    public:
        Camera();
        void key_down(unsigned int key);
        void key_up(unsigned int key);
        void mouse_button(int button, int state, int x, int y);
        void mouse_move(int x, int y);
        void view();

    private:
        bool keys[256];
        float lx, ly, lz;
        float px, py, pz;
        float dx, dy, dz;
        float up[3];
        float norma, alpha, deltaX, deltaY, angle;
        int xOrigin, yOrigin;;

        void apply();
        void update(float *d, int s);
        void update_aux(float *d, float *r);
        void update_direction();
        void move_to_camera(bool backwards);
};

#endif
