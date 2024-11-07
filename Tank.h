#pragma once

#include <vector>
#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object2D {

    // Funcție care creează baza tancului (două trapeze suprapuse)
    Mesh* CreateTankBase(const std::string& name, const glm::vec3& color);

    // Funcție care creează turela tancului (arc de cerc)
    Mesh* CreateTankTurret(const std::string& name, const glm::vec3& color);

    // Funcție care creează țeava tunului (dreptunghi)
    Mesh* CreateTankBarrel(const std::string& name, const glm::vec3& color);

    // Funcția principală pentru a crea un tanc complet (include baza, turela și țeava)
    void CreateTank(const std::string& name, const glm::vec3& baseColor, const glm::vec3& turretColor, std::vector<Mesh*>& tankMeshes);
}

