#include "exrender.h"
#include "render.h"
#include "triangle.h"

Render *render;

Render *createRender(int type) {
    switch (type) {
        case 0:
            return new TriangleRender();
    }
    return nullptr;
}

JNIEXPORT void JNICALL init(JNIEnv *env, jobject obj, jint type) {
    render = createRender(type);
}

JNIEXPORT void JNICALL release(JNIEnv *env, jobject obj) {
    delete render;
}

JNIEXPORT void JNICALL onSurfaceCreated(JNIEnv *env, jobject obj) {
    if (render != nullptr) {
        render->onSurfaceCreated();
    }
}

JNIEXPORT void JNICALL onSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height) {
    if (render != nullptr) {
        render->onSurfaceChanged(width, height);
    }
}

JNIEXPORT void JNICALL onDrawFrame(JNIEnv *env, jobject obj) {
    if (render != nullptr) {
        render->onDrawFrame();
    }
}