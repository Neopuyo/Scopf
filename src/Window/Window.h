#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define WIN_WIDTH    1024
#define WIN_HEIGHT   768
class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    void setInputMode();
    int  getKey(int key) const;

    inline GLFWwindow* getWindow() const { return window; }
private:
    GLFWwindow* window;
};