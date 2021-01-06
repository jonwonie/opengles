#ifndef __GLUTILS_H__
#define __GLUTILS_H__

#include <android/log.h>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else

#include <GLES3/gl3.h>
//#include <GLES3/gl3ext.h>
#endif

#define BUFFER_OFFSET(a) ((void*)(a))

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct {
    GLenum type;
    const GLchar *source;
    GLuint shader;
} ShaderInfo;

GLuint bindShaders(ShaderInfo *shaders);

#ifdef __cplusplus
}
#endif

#endif

