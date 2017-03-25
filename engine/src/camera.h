#ifndef __CAMERA__
#define __CAMERA__

class Camera {
    public:
        float getXPos();
        float getYPos();
        float getZPos();
        float getXRot();
        float getYRot();
        void setXPos(float x);
        void setYPos(float y);
        void setZPos(float z);
        void setXRot(float x);
        void setYRot(float y);
        void camera_motion(unsigned char key, int x, int y);

    private:
        float xrot;
        float yrot;
        float xpos;
        float zpos;
};

#endif