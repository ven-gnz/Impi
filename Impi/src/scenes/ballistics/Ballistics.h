#pragma once
#include "scenes/Scene.h"
#include "rendering/assets/Mesh.h"

class Ballistics : public Scene {
    
public:
    Ballistics(Camera& camera);
    SphereMesh sphere_mesh;
    PlaneMesh ground_mesh;
    void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    void onActivate() override;
    void update(real dt) override;
    void draw(Renderer& renderer, Camera& camera) override;
};