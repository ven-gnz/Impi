#pragma once
#include "../Scene.h"

class Ballistics : public Scene {
public:
    Ballistics();

    void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;
};