#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Cube.h"

class Engine {
public:
    Engine(int width, int height, const std::string& title);
    ~Engine();

    bool Init();
    void Run();
    void Cleanup();

private:
    int width, height;
    std::string title;
    GLFWwindow* window;

    Camera* camera;
    Cube* cube;

    double lastX, lastY;
    bool firstMouse;

    void ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Render();
};
