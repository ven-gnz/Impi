#pragma once
#include "scenes/Scene.h"
#include "rendering/assets/SphereMesh.h"

class Ballistics : public Scene {
    
public:
    Ballistics();
    SphereMesh sphere_mesh;
    PlaneMesh ground_mesh;
    void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;
};