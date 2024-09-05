#include "Ball.h"

Shader Ball::s_shader;

Ball::Ball()
{
    s_shader.Init("shaders/ball.vs", "shaders/ball.fs");

    _x = 320; _y = 240; _z = 0;

    vao = Global.GetDefaultVAO();

    SetUniformAddr();
}


//
void Ball::SetCoords(int x, int y, int z){
    _x = static_cast<float>(x);
    _y = static_cast<float>(y);
    _z = static_cast<float>(z);
}

void Ball::SetCoords(float x, float y, float z){
    _x = x;
    _y = y;
    _z = z;
}

void Ball::SetDiameter(int s){
    _diameter = static_cast<float>(s) / 2.0f;
}


void Ball::GetCoords(float* x, float* y){
    *x = _x;
    *y = _y;
}

float Ball::GetDiameter(){
    return _diameter;
}

void Ball::SetUniformAddr(){
    if (!s_shader.IsInitialized())
        return;

    _uniform.diameter = s_shader.GetUniform("diameter");
    _uniform.fuzz = s_shader.GetUniform("fuzz");
    _uniform.x = s_shader.GetUniform("centerX");
    _uniform.y = s_shader.GetUniform("centerY");

}

//

void Ball::Update(){ //TO DO: Re-think what this function gonna do

}

void Ball::Draw(){

    if (!s_shader.IsInitialized())
        return;

    s_shader.Use();
    glUniform1f(_uniform.diameter, _diameter);
    glUniform1f(_uniform.x, _x);
    glUniform1f(_uniform.y, _y);
    glUniform1f(_uniform.fuzz, 0.0f);


    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

float Ball::GetZ(){
    return _z;
}

//
Ball::~Ball()
{
    //dtor
}
