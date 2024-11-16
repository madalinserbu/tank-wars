#pragma once

#include "components/simple_scene.h"
#include <vector>

namespace m1 {
    class Tema1 : public gfxc::SimpleScene {
    public:
        Tema1();
        ~Tema1();

        // **Initialization and Update Functions**
        void Init() override;
        void UpdateTankPosition();

        // **Projectile Structure**
        struct Projectile {
            glm::vec2 position;
            glm::vec2 velocity;
            float lifetime;
        };

    private:
        // **Core Game Loop Functions**
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        // **Tank Properties**
        float xPosTank1 = 100.0f;            // Tank 1's X position
        float xPosTank2 = 400.0f;            // Tank 2's X position
        float barrelAngleTank1 = 5.0f;       // Tank 1's barrel angle
        float barrelAngleTank2 = -5.0f;      // Tank 2's barrel angle
        const float barrelRotationSpeed = 1.5f;  // Speed of barrel rotation

        // Movement Flags for Tanks
        float xStart, xEnd;
        bool moveTank1Right = false;
        bool moveTank1Left = false;
        bool moveTank2Right = false;
        bool moveTank2Left = false;

        // **Projectile Properties**
        std::vector<Projectile> tank1Projectiles;
        std::vector<Projectile> tank2Projectiles;
        const float projectileSpeed = 300.0f;     // Initial speed of projectiles
        const float projectileLifetime = 3.0f;   // Lifespan of a projectile (in seconds)
        const float gravity = -500.0f;           // Gravity effect on projectiles

        // **Terrain and Health**
        std::vector<float> heightMap;            // Stores terrain height data
        float tank1Health = 100;                 // Health of Tank 1
        float tank2Health = 100;                 // Health of Tank 2
        const float damageValue = 20;            // Damage per hit

        // **Input Handling Functions**
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // **Utility Functions**
        void DrawTrajectory(float xStart, float yStart, float angle, float initialSpeed);

    protected:
        // **Transformation Variables**
        glm::mat3 modelMatrix;    // Transformation matrix
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // Placeholder for any additional variables
        // TODO(student): Define other class variables as needed
    };
} // namespace m1
