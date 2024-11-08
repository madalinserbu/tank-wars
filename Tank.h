#pragma once

#include <vector>
#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object2D {

    // Func?ie care creeaz? baza tancului (dou? trapeze suprapuse)
    Mesh* CreateTankBase(const std::string& name, const glm::vec3& color);

    // Func?ie care creeaz? turela tancului (arc de cerc)
    Mesh* CreateTankTurret(const std::string& name, const glm::vec3& color);

    // Func?ie care creeaz? ?eava tunului (dreptunghi)
    Mesh* CreateTankBarrel(const std::string& name, const glm::vec3& color);

    // Func?ia principal? pentru a crea un tanc complet (include baza, turela ?i ?eava)
    void CreateTank(const std::string& name, const glm::vec3& baseColor, const glm::vec3& turretColor, std::vector<Mesh*>& tankMeshes);
}

