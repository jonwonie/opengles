
#ifndef __RENDER_H__
#define __RENDER_H__

#include <android/log.h>
#include "glutils.h"

class Render {

public:
    virtual ~Render() {};

    void onSurfaceCreated() {
        glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
    };

    void onSurfaceChanged(int width, int height) {
        glViewport(0, 0, width, height);
    };

    virtual void onDrawFrame() = 0;
};

#endif