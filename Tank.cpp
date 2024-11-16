#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include <vector>
#include <iostream>

// Use the standard namespace for simplicity
using namespace std;

namespace object2D {

    /**
     * @brief Creates the base of a tank using two overlapping trapezoids.
     *
     * @param name Name of the mesh.
     * @param color Base color for the mesh.
     * @return Mesh* Pointer to the created tank base mesh.
     */
    Mesh* CreateTankBase(const std::string& name, const glm::vec3& color) {
        // Container for vertices and indices
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        // Define vertices for the bottom trapezoid
        vertices.emplace_back(glm::vec3(-15, -6, 0), color - 0.15f);  // Bottom-left (smaller base)
        vertices.emplace_back(glm::vec3(15, -6, 0), color - 0.15f);   // Bottom-right (smaller base)
        vertices.emplace_back(glm::vec3(22.5, 0, 0), color - 0.15f);  // Top-right (larger base)
        vertices.emplace_back(glm::vec3(-22.5, 0, 0), color - 0.15f); // Top-left (larger base)

        // Define vertices for the top trapezoid
        vertices.emplace_back(glm::vec3(-33.75, 0, 0), color);       // Bottom-left (larger base)
        vertices.emplace_back(glm::vec3(33.75, 0, 0), color);        // Bottom-right (larger base)
        vertices.emplace_back(glm::vec3(23.25, 12.75, 0), color);    // Top-right (smaller base)
        vertices.emplace_back(glm::vec3(-23.25, 12.75, 0), color);   // Top-left (smaller base)

        // Define indices to connect vertices and form the trapezoids
        indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

        // Create the mesh
        Mesh* tankBase = new Mesh(name);
        tankBase->InitFromData(vertices, indices);

        return tankBase;
    }

    /**
     * @brief Creates the turret of a tank as a semicircular arc positioned above the tank base.
     *
     * @param name Name of the mesh.
     * @param color Base color for the turret.
     * @return Mesh* Pointer to the created turret mesh.
     */
    Mesh* CreateTankTurret(const std::string& name, const glm::vec3& color) {
        // Container for vertices and indices
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        // Parameters for the circular arc
        int numSegments = 30;            // Number of segments for the arc
        float radius = 10.0f;            // Radius of the arc
        float angleStep = M_PI / numSegments; // Angular step for the arc
        float offsetY = 12.5f;           // Vertical offset to position the turret above the base

        // Add the center of the arc
        vertices.emplace_back(glm::vec3(0, offsetY, 0), color);

        // Generate vertices for the arc
        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * angleStep;
            vertices.emplace_back(glm::vec3(radius * cos(angle), offsetY + radius * sin(angle), 0), color);

            // Add indices to form triangles for the arc
            if (i > 0) {
                indices.push_back(0);
                indices.push_back(i);
                indices.push_back(i + 1);
            }
        }

        // Create the mesh
        Mesh* turret = new Mesh(name);
        turret->InitFromData(vertices, indices);

        return turret;
    }

    /**
     * @brief Creates the tank barrel as a long rectangular prism.
     *
     * @param name Name of the mesh.
     * @param color Base color for the barrel.
     * @return Mesh* Pointer to the created barrel mesh.
     */
    Mesh* CreateTankBarrel(const std::string& name, const glm::vec3& color) {
        // Define vertices for the rectangle
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-1.5f, 0, 0), color),   // Bottom-left
            VertexFormat(glm::vec3(1.5f, 0, 0), color),    // Bottom-right
            VertexFormat(glm::vec3(1.5f, 20.0f, 0), color),// Top-right
            VertexFormat(glm::vec3(-1.5f, 20.0f, 0), color)// Top-left
        };

        // Define indices to form the rectangle
        std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

        // Create the mesh
        Mesh* barrel = new Mesh(name);
        barrel->InitFromData(vertices, indices);

        return barrel;
    }

    /**
     * @brief Assembles a complete tank by combining the base, turret, and barrel.
     *
     * @param name Base name for the tank components.
     * @param baseColor Color for the tank base.
     * @param turretColor Color for the turret.
     * @param meshes Output container for the tank components.
     */
    void CreateTank(const std::string& name, const glm::vec3& baseColor, const glm::vec3& turretColor, std::vector<Mesh*>& meshes) {
        // Create and add the tank base
        meshes.push_back(CreateTankBase(name + "_base", baseColor));

        // Create and add the turret
        meshes.push_back(CreateTankTurret(name + "_turret", turretColor));

        // Create and add the barrel (default color: black)
        meshes.push_back(CreateTankBarrel(name + "_barrel", glm::vec3(0.0f, 0.0f, 0.0f)));
    }

    /**
     * @brief Creates a projectile as a circular mesh.
     *
     * @param name Name of the mesh.
     * @param radius Radius of the projectile.
     * @param color Color of the projectile.
     * @return Mesh* Pointer to the created projectile mesh.
     */
    Mesh* CreateProjectile(const std::string& name, float radius, const glm::vec3& color) {
        // Container for vertices and indices
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        // Parameters for the circle
        int numSegments = 30;             // Number of segments for the circle
        float angleStep = 2 * M_PI / numSegments;

        // Add the center of the circle
        vertices.emplace_back(glm::vec3(0, 0, 0), color);

        // Generate vertices for the circle
        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * angleStep;
            vertices.emplace_back(glm::vec3(radius * cos(angle), radius * sin(angle), 0), color);

            // Add indices to form triangles
            if (i > 0) {
                indices.push_back(0);
                indices.push_back(i);
                indices.push_back(i + 1);
            }
        }

        // Create the mesh
        Mesh* projectile = new Mesh(name);
        projectile->InitFromData(vertices, indices);

        return projectile;
    }
}
