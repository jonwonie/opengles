#include "glutils.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#define _DEBUG 1
static void checkGLError(const char *cmd) {
    int error = glGetError();

    if (error != GL_NO_ERROR) {
        __android_log_print(ANDROID_LOG_ERROR, "checkGLError", "%s: %d", cmd, error);
    };
}

GLuint bindShaders(ShaderInfo *shaders) {
    if (shaders == nullptr) {
        return 0;
    }
    GLuint program = glCreateProgram();
    checkGLError("glCreateProgram");
    ShaderInfo *entry = shaders;
    while (entry->type != GL_NONE) {
        GLuint shader = glCreateShader(entry->type);
        checkGLError("glCreateShader");
        entry->shader = shader;
        if (entry->source == nullptr) {
            for (entry = shaders; entry->type != GL_NONE; ++entry) {
                glDeleteShader(entry->shader);
                entry->shader = 0;
            }
            return 0;
        }
        glShaderSource(shader, 1, &entry->source, nullptr);
        checkGLError("glShaderSource");
        glCompileShader(shader);
        checkGLError("glCompileShader");
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        checkGLError("glGetShaderiv");
        if (!compiled) {
#ifdef _DEBUG
            GLsizei len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
            auto log = new GLchar[len + 1];
            glGetShaderInfoLog(shader, len, &len, log);
            __android_log_print(ANDROID_LOG_ERROR, "bindShaders", "%s: %s",
                                "Shader compilation failed", log);
            delete[] log;
#endif /*_DEBUG*/
            return 0;
        }
        glAttachShader(program, shader);
        checkGLError("glAttachShader");
        ++entry;
    }
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
#ifdef _DEBUG
        GLsizei len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        auto log = new GLchar[len + 1];
        glGetProgramInfoLog(program, len, &len, log);

        __android_log_print(ANDROID_LOG_ERROR, "bindShaders", "%s: %s", "Shader linking failed",
                            log);
        delete[] log;
#endif /* DEBUG */
        for (entry = shaders; entry->type != GL_NONE; ++entry) {
            glDeleteShader(entry->shader);
            entry->shader = 0;
        }

        return 0;
    }
    return program;
}

#ifdef __cplusplus
}
#endif // __cplusplus