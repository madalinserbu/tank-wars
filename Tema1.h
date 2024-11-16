#pragma once

#include "components/simple_scene.h"
#include <vector>

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        // Initialization and update functions
        void Init() override;
        void UpdateTankPosition();
        struct Projectile {
            glm::vec2 position;
            glm::vec2 velocity;
            float lifetime;
        };


    private:
        float yPosTank1, yNextPosTank1, dx, yNextPosTank2, yPosTank2;
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        // Tank positions and movement flags
        float xPosTank1 = 100.0f;
        float xPosTank2 = 400.0f;
        float xStart, xEnd;
        bool moveTank1Right = false;
        bool moveTank1Left = false;
        bool moveTank2Right = false;
        bool moveTank2Left = false;
        float barrelAngleTank1 = 5.0f;
        float barrelAngleTank2 = -5.0f;
        const float barrelRotationSpeed = 1.5f;

        std::vector<Projectile> tank1Projectiles;
        std::vector<Projectile> tank2Projectiles;
        const float projectileSpeed = 300.0f;
        const float gravity = -500.0f;
        const float projectileLifetime = 3.0f; // Seconds
        const float tankYOffset = 4.8f;


        // Height map data for terrain
        std::vector<float> heightMap;

        float tank1Health = 100;
        float tank2Health = 100;
        const float damageValue = 20;

        // Input handling functions
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        // Transformation variables
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
    };
}   // namespace m1
