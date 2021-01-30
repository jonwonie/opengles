
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "render.h"

class TriangleRender : public Render {
private:

public:
    TriangleRender();

    ~TriangleRender();

    void onDrawFrame() override;

};

#endif
