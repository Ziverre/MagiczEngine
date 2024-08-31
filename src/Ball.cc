#include "Ball.h"

Shader Ball::s_shader;

Ball::Ball()
{
    if (!s_shader.isInitialized()){
        s_shader.Init("shaders/ball.vs", "shaders/ball.fs");
    }

    //TO DO: Move these into a single static variable

    _x = 320; _y = 240; _z = 0;

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
    return _diameter; //what _z in Drawable?
}


//
void Ball::SetUniformAddr(){
    //TO DO: ... (Is getting uniform address outside render loop even necessary?)
    if (!s_shader.isInitialized())
        return;

    _x_addr = glGetUniformLocation(s_shader.GetID(), "centerX");
    _y_addr = glGetUniformLocation(s_shader.GetID(), "centerY");
    _diameter_addr = glGetUniformLocation(s_shader.GetID(), "diameter");
    _fuzz_addr = glGetUniformLocation(s_shader.GetID(), "fuzz");

}


void Ball::Update(){ //TO DO: Re-think what this function gonna do

}

void Ball::Draw(){

    if (!s_shader.isInitialized())
        return;

    s_shader.Use();
    glUniform1f(_diameter_addr, _diameter);
    glUniform1f(_x_addr, _x);
    glUniform1f(_y_addr, _y);
    glUniform1f(_fuzz_addr, 0.0f);


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
