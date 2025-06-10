#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    void ProcessInput();
    void Update(float deltaTime);
    void Render();
};
