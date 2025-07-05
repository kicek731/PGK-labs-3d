#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Cube.h"
#include "stb_easy_font.h"



class Engine {
public:
    Engine(int width, int height, const std::string& title);
    ~Engine();

    bool Init();
    void Run();
    void Cleanup();

    void DrawText(float x, float y, const char* text, float r, float g, float b);

private:
    int width, height;
    std::string title;
    GLFWwindow* window;

    Camera* camera;
    Cube* cube;

    double lastX, lastY;
    bool firstMouse;
    bool rightMousePressed = false;

    float modelYaw = 0.0f;
    float modelPitch = 0.0f;

    bool lightingEnabled;
    bool shadingEnabled;


    glm::vec3 cubeScale = glm::vec3(1.0f);


    bool drawIrregular = false;  
    bool drawConcaveDisk = false;

    void ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Render();



    GLuint textVAO = 0;
    GLuint textVBO = 0;
    GLuint textShaderProgram = 0;



};
