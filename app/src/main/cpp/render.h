
#ifndef __RENDER_H__
#define __RENDER_H__

#include <android/log.h>
#include "glutils.h"

class Render {

public:
    virtual void onSurfaceCreated() = 0;

    virtual void onSurfaceChanged(int width, int height) = 0;

    virtual void onDrawFrame() = 0;
};

#endif