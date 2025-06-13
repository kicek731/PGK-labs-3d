#include "Engine.h"
#include <iostream>

Engine::Engine(int width, int height, const std::string& title)
    : width(width), height(height), title(title), window(nullptr),
    camera(nullptr), cube(nullptr), lastX(width / 2.0), lastY(height / 2.0),
    firstMouse(true), lightingEnabled(true), shadingEnabled(true) {
}

Engine::~Engine() {
    Cleanup();
}

bool Engine::Init() {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Window creation failed!\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!\n";
        return false;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f, 45.0f, (float)width / height);
    cube = new Cube();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return true;
}

void Engine::Run() {
    float lastTime = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(window)) {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        ProcessInput(deltaTime);
        Update(deltaTime);
        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::ProcessInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    camera->ProcessKeyboard(deltaTime, forward, backward, left, right);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float offsetX = static_cast<float>(xpos - lastX);
    float offsetY = static_cast<float>(lastY - ypos);

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouse(offsetX, offsetY);

    // Lighting toggle (L)
    static bool lPressedLastFrame = false;
    bool lPressedNow = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
    if (lPressedNow && !lPressedLastFrame) {
        lightingEnabled = !lightingEnabled;
        std::cout << "Lighting " << (lightingEnabled ? "enabled" : "disabled") << std::endl;
    }
    lPressedLastFrame = lPressedNow;

    // Shading toggle (K)
    static bool kPressedLastFrame = false;
    bool kPressedNow = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
    if (kPressedNow && !kPressedLastFrame) {
        shadingEnabled = !shadingEnabled;
        std::cout << "Shading " << (shadingEnabled ? "smooth" : "flat") << std::endl;
    }
    kPressedLastFrame = kPressedNow;
}

void Engine::Update(float deltaTime) {
    // opcjonalna logika gry
}

void Engine::Render() {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();

    cube->Draw(view, projection, camera->GetPosition(), lightingEnabled, shadingEnabled);
}

void Engine::Cleanup() {
    delete camera;
    delete cube;
    glfwDestroyWindow(window);
    glfwTerminate();
}
