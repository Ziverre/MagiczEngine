#include "Line.h"

Shader Line::s_shader;

Line::Line() : _startBall(nullptr), _endBall(nullptr)
{
    if (!s_shader.isInitialized()){
        s_shader.Init("shaders/line.vs", "shaders/line.fs");
    }

    //TO DO: Move these into a single static variable

    float vertices[] = {
         1.0f,  1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,

         1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f,  1.0f,
    };

    vao = 0; vbo = 0; ebo = 0;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    SetUniformAddr();
}


void Line::SetStartAndEndBalls(Ball* startBall, Ball* endBall){
    _startBall = startBall;
    _endBall = endBall;
}


//
void Line::SetUniformAddr(){
    if (!s_shader.isInitialized())
        return;

    _start_x_addr = glGetUniformLocation(s_shader.GetID(), "startX");
    _start_y_addr = glGetUniformLocation(s_shader.GetID(), "startY");
    _end_x_addr = glGetUniformLocation(s_shader.GetID(), "endX");
    _end_y_addr = glGetUniformLocation(s_shader.GetID(), "endY");
    _start_diameter_addr = glGetUniformLocation(s_shader.GetID(), "startDiameter");
    _end_diameter_addr = glGetUniformLocation(s_shader.GetID(), "endDiameter");

}

void Line::Update(){ // ...

}

void Line::Draw(){
    if (!s_shader.isInitialized())
        return;

    if (!_startBall || !_endBall) //if either is nullptr, do not render
        return;

    float startX = 0.f, startY = 0.f, endX = 0.f, endY = 0.f;

    _startBall->GetCoords(&startX, &startY);
    _endBall->GetCoords(&endX, &endY);

    float startDiameter = _startBall->GetDiameter();
    float endDiameter = _endBall->GetDiameter();

    s_shader.Use();

    glUniform1f(_start_x_addr, startX);
    glUniform1f(_start_y_addr, startY);
    glUniform1f(_end_x_addr, endX);
    glUniform1f(_end_y_addr, endY);

    glUniform1f(_start_diameter_addr, startDiameter);
    glUniform1f(_end_diameter_addr, endDiameter);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

float Line::GetZ(){
    return 0.0f;
}


//
Line::~Line()
{
}
