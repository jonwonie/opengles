
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "render.h"

class TriangleRender : public Render {
private:

public:
    TriangleRender();

    ~TriangleRender();

    void onDrawFrame() override;

    void onSurfaceChanged(int width, int height) override;

    void onSurfaceCreated() override;
};

#endif
