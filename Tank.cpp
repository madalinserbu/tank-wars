#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include <vector>
#include <iostream>

using namespace std;

namespace object2D {

    // Creez baza tancului din doua trapeze suprapuse
    Mesh* CreateTankBase(const std::string& name, const glm::vec3& color) {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        // Trapez de jos
        vertices.emplace_back(glm::vec3(-20 * 0.75, -8 * 0.75, 0), color - 0.15f);  // Stânga jos - baza mica
        vertices.emplace_back(glm::vec3(20 * 0.75, -8 * 0.75, 0), color - 0.15f);   // Dreapta jos - baza mica
        vertices.emplace_back(glm::vec3(30 * 0.75, 0 * 0.75, 0), color - 0.15f);     // Dreapta sus - baza mare
        vertices.emplace_back(glm::vec3(-30 * 0.75, 0 * 0.75, 0), color - 0.15f);    // Stânga sus - baza mare

        // Trapez de sus
        vertices.emplace_back(glm::vec3(-45 * 0.75, 0 * 0.75, 0), color);    // Stânga jos - baza mare
        vertices.emplace_back(glm::vec3(45 * 0.75, 0 * 0.75, 0), color);     // Dreapta jos - baza mare
        vertices.emplace_back(glm::vec3(31 * 0.75, 17 * 0.75, 0), color);    // Dreapta sus - baza mica
        vertices.emplace_back(glm::vec3(-31 * 0.75, 17 * 0.75, 0), color);   // Stânga sus - baza mica

        // Indici pentru formarea trapezelor
        indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

        Mesh* tankBase = new Mesh(name);
        tankBase->InitFromData(vertices, indices);
        return tankBase;
    }

    // Creez turela tancului ca arc de cerc si il pozitionez deasupra trapezului superior
    Mesh* CreateTankTurret(const std::string& name, const glm::vec3& color) {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        int numSegments = 30;
        float radius = 10.0f;
        float angleStep = M_PI / numSegments; // Arc de cerc pe jumatate
        float offsetY = 12.50f;  // Offset vertical pentru a plasa turela deasupra trapezului superior

        // Adaug centrul arcului
        vertices.emplace_back(glm::vec3(0, offsetY, 0), color);

        // Adaug vertex-urile arcului de cerc
        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * angleStep;
            vertices.emplace_back(glm::vec3(radius * cos(angle), offsetY + radius * sin(angle), 0), color);
            if (i > 0) {
                indices.push_back(0);
                indices.push_back(i);
                indices.push_back(i + 1);
            }
        }

        Mesh* turret = new Mesh(name);
        turret->InitFromData(vertices, indices);
        return turret;
    }


    // Creez teava tunului tancului ca un dreptunghi alungit
    Mesh* CreateTankBarrel(const std::string& name, const glm::vec3& color) {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-1.5, 0, 0), color),
            VertexFormat(glm::vec3(1.5, 0, 0), color),
            VertexFormat(glm::vec3(1.5, 20, 0), color),
            VertexFormat(glm::vec3(-1.5,20, 0), color),
        };

        std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

        Mesh* barrel = new Mesh(name);
        barrel->InitFromData(vertices, indices);
        return barrel;
    }

	// Creez un tanc complet (baza, turela si teava)
    void CreateTank(const std::string& name, const glm::vec3& baseColor, const glm::vec3& turretColor, std::vector<Mesh*>& meshes) {
        // Baza tancului
        meshes.push_back(CreateTankBase(name + "_base", baseColor));

        // Turela tancului
        meshes.push_back(CreateTankTurret(name + "_turret", turretColor));

        // ?eava tunului
        meshes.push_back(CreateTankBarrel(name + "_barrel", glm::vec3(0.0f, 0.0f, 0.0f)));
    }

	// Creez un proiectil ca un cerc
    Mesh* CreateProjectile(const std::string& name, float radius, const glm::vec3& color) {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        int numSegments = 30;
        float angleStep = 2 * M_PI / numSegments;

        vertices.emplace_back(glm::vec3(0, 0, 0), color);  // Centrul

        // Coordonate pentru punctele de pe cerc
        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * angleStep;
            vertices.emplace_back(glm::vec3(radius * cos(angle), radius * sin(angle), 0), color);
            if (i > 0) {
                indices.push_back(0);
                indices.push_back(i);
                indices.push_back(i + 1);
            }
        }

        Mesh* projectile = new Mesh(name);
        projectile->InitFromData(vertices, indices);
        return projectile;
    }
}