#pragma once

#include <vector>
#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object2D {

    // Functie care creeaza baza tancului (doua trapeze suprapuse)
    Mesh* CreateTankBase(const std::string& name, const glm::vec3& color);

    // Functie care creeaza turela tancului (arc de cerc)
    Mesh* CreateTankTurret(const std::string& name, const glm::vec3& color);

    // Functie care creeaza teava tunului (dreptunghi)
    Mesh* CreateTankBarrel(const std::string& name, const glm::vec3& color);

    // Functia principala pentru a crea un tanc complet (include baza, turela si teava)
    void CreateTank(const std::string& name, const glm::vec3& baseColor, const glm::vec3& turretColor, std::vector<Mesh*>& tankMeshes);
    Mesh* CreateProjectile(const std::string& name, float radius, const glm::vec3& color);
    Mesh* CreateCircle(std::string name, float radius);
    Mesh* CreateLine(std::string name, float length);
}
