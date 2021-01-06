#include "triangle.h"

const GLuint NumVertices = 3;

enum VAO_IDs {
    Triangles, NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer, NumBuffers
};
enum Attrib_IDs {
    vPosition = 0
};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

char vShaderStr[] =
        "#version 300 es                          \n"
        "layout(location = 0) in vec4 vPosition;  \n"
        "void main()                              \n"
        "{                                        \n"
        "   gl_Position = vPosition;              \n"
        "}                                        \n";

char fShaderStr[] =
        "#version 300 es                              \n"
        "precision mediump float;                     \n"
        "out vec4 fragColor;                          \n"
        "void main()                                  \n"
        "{                                            \n"
        "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
        "}                                            \n";


TriangleRender::TriangleRender() {
    static const GLfloat vertices[NumVertices][2] = {
            {0,    0.5},
            {-0.5, -0.5},
            {0.5,  -0.5},
    };
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   vShaderStr},
            {GL_FRAGMENT_SHADER, fShaderStr},
            {GL_NONE,            nullptr},
    };
    GLuint program = bindShaders(shaders);
    __android_log_print(ANDROID_LOG_INFO, "program", "%d", program);
    glUseProgram(program);

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

TriangleRender::~TriangleRender() {
    __android_log_print(ANDROID_LOG_INFO, "TriangleRender",
                        "TriangleRender::~TriangleRender is invoking!");
}

void TriangleRender::onSurfaceCreated() {
    glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
}

void TriangleRender::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
}


void TriangleRender::onDrawFrame() {
    const GLfloat black[] = {0.99, 0.99, 0.99, 1};
    glClearBufferfv(GL_COLOR, 0, black);
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

