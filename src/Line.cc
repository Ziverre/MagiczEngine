#include "Line.h"

Shader Line::s_shader;

Line::Line() : _startBall(nullptr), _endBall(nullptr)
{
    s_shader.Init("shaders/line.vs", "shaders/line.fs");

    //TO DO: Move these into a single static variable

    vao = Global.GetDefaultVAO();

    SetUniformAddr();
}


void Line::SetStartAndEndBalls(Ball* startBall, Ball* endBall){
    _startBall = startBall;
    _endBall = endBall;
}


//
void Line::SetUniformAddr(){
    if (!s_shader.IsInitialized())
        return;

    _uniform.start_x = s_shader.GetUniform("startX");
    _uniform.start_y = s_shader.GetUniform("startY");
    _uniform.end_x = s_shader.GetUniform("endX");
    _uniform.end_y = s_shader.GetUniform("endY");
    _uniform.start_diameter = s_shader.GetUniform("startDiameter");
    _uniform.end_diameter = s_shader.GetUniform("endDiameter");

}

void Line::Update(){ // ...

}

void Line::Draw(){
    if (!s_shader.IsInitialized())
        return;

    if (!_startBall || !_endBall) //if either is nullptr, do not render
        return;

    float startX = 0.f, startY = 0.f, endX = 0.f, endY = 0.f;

    _startBall->GetCoords(&startX, &startY);
    _endBall->GetCoords(&endX, &endY);

    float startDiameter = _startBall->GetDiameter();
    float endDiameter = _endBall->GetDiameter();

    s_shader.Use();

    glUniform1f(_uniform.start_x, startX);
    glUniform1f(_uniform.start_y, startY);
    glUniform1f(_uniform.end_x, endX);
    glUniform1f(_uniform.end_y, endY);

    glUniform1f(_uniform.start_diameter, startDiameter);
    glUniform1f(_uniform.end_diameter, endDiameter);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

float Line::GetZ(){
    if (!_startBall || !_endBall)
        return 0.0f;

    //In Original Petz games, each line is rendered behind both the ballz which are connected to it;
    //bigger Z value means "further" from the screen, therefore the maximum Z is chosen
    float zindex = std::max(_startBall->GetZ(), _endBall->GetZ()) + 0.5;

    return zindex;
}


//
Line::~Line()
{
}
