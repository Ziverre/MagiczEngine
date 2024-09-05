#include "Global.h"

_Global Global;

void _Global::Configure(){
    //Call this before using any of MagiczEngine objects :)
    //MUST BE CALLED AFTER CREATION OF OPENGL CONTEXT, OTHERWISE IT IS UNDEFINED BEHAVIOR
    SetDefaultVAO();
}

unsigned int _Global::GetDefaultVAO(){
    return _default_vao;
}

void _Global::SetDefaultVAO(){
    float vertices[] = {
         1.0f,  1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,

         1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f,  1.0f,
    };

    unsigned int vbo;
    _default_vao = 0;

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &_default_vao);

    glBindVertexArray(_default_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}