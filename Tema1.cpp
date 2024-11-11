#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/Tank.h"

#include <vector>
#include <iostream>
#include <cmath>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "../../../build/Tank.h"

using namespace std;
using namespace m1;

Tema1::Tema1() : xPosTank1(100), xPosTank2(400),
moveTank1Right(false), moveTank1Left(false),
moveTank2Right(false), moveTank2Left(false) {
    // Initialize positions and movement states
}

Tema1::~Tema1() {
}

std::vector<float> GenerateHeightMap(int numPoints, float amplitude1, float frequency1, float amplitude2, float frequency2, float xStart, float xEnd, float verticalOffset) {
    std::vector<float> heightMap(numPoints);
    float step = (xEnd - xStart) / (numPoints - 1);

    for (int i = 0; i < numPoints; ++i) {
        float x = xStart + i * step;
        heightMap[i] = verticalOffset + amplitude1 * sin(frequency1 * x) + amplitude2 * sin(frequency2 * x);
    }

    return heightMap;
}

void Tema1::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();

    int numPoints = 900;
    xStart = 0; // Pozi?ia de început pe axa X
    xEnd = (float)resolution.x; // Pozi?ia final? pe axa X

    float amplitude1 = 20;
    float frequency1 = 0.02f;
    float amplitude2 = 10;
    float frequency2 = 0.05f;
    float verticalOffset = 150;

    heightMap = GenerateHeightMap(numPoints, amplitude1, frequency1, amplitude2, frequency2, xStart, xEnd, verticalOffset);

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < numPoints; ++i) {
        float x = xStart + i * ((xEnd - xStart) / (numPoints - 1));
        float y = heightMap[i];

        vertices.emplace_back(glm::vec3(x, y, 0), glm::vec3(0.3f, 0.6f, 0.2f));
        vertices.emplace_back(glm::vec3(x, 0, 0), glm::vec3(0.3f, 0.6f, 0.2f));

        if (i > 0) {
            indices.push_back(2 * i - 2);
            indices.push_back(2 * i - 1);
            indices.push_back(2 * i);
            indices.push_back(2 * i + 1);
        }
    }

    Mesh* terrainMesh = new Mesh("terrain");
    terrainMesh->InitFromData(vertices, indices);
    terrainMesh->SetDrawMode(GL_TRIANGLE_STRIP);
    AddMeshToList(terrainMesh);

    // Ini?ializare tancuri
    std::vector<Mesh*> tank1Meshes;
    std::vector<Mesh*> tank2Meshes;

    glm::vec3 camoBeigeDark = glm::vec3(0.76f, 0.69f, 0.50f);
    glm::vec3 camoGreenDark = glm::vec3(0.33f, 0.42f, 0.18f);

    // Creeaz? primul tanc
    object2D::CreateTank("tank1", camoBeigeDark, camoBeigeDark, tank1Meshes);
    for (auto& mesh : tank1Meshes) {
        AddMeshToList(mesh);
    }

    // Creeaz? al doilea tanc
    object2D::CreateTank("tank2", camoGreenDark, camoGreenDark, tank2Meshes);
    for (auto& mesh : tank2Meshes) {
        AddMeshToList(mesh);
    }
}

void Tema1::FrameStart() {
    glClearColor(0, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
    // Definim un offset vertical pentru a ridica tancurile deasupra terenului
    const float tankYOffset = 4.8f;  // Valoare ajustabil? pentru a ridica tancurile (în pixeli)

    // Reset?m modelMatrix pentru a începe o nou? randare
    modelMatrix = glm::mat3(1);

    // Red?m terenul
    RenderMesh2D(meshes["terrain"], shaders["VertexColor"], modelMatrix);

    // Actualizare pozi?ie ?i rota?ie tanc 1
    glm::mat3 tank1ModelMatrix = glm::mat3(1);
    int indexTank1 = std::min(static_cast<int>((xPosTank1 - xStart) / (xEnd - xStart) * (heightMap.size() - 1)), static_cast<int>(heightMap.size() - 1));
    float yPosTank1 = heightMap[indexTank1] + tankYOffset;  // Pozi?ia corect? pe teren pentru tanc 1, cu offset

    tank1ModelMatrix *= transform2D::Translate(xPosTank1, yPosTank1);

    // Calcul?m panta terenului pentru a determina rota?ia corect?
    float dx = 5.0f;  // Distan?? mai mare pentru o estimare mai bun? a pantei
    int indexNextTank1 = std::min(indexTank1 + static_cast<int>(dx), static_cast<int>(heightMap.size() - 1));
    float yNextPosTank1 = heightMap[indexNextTank1] + tankYOffset;  // În?l?imea la punctul urm?tor pentru panta

    float angle = atan2(yNextPosTank1 - yPosTank1, dx);  // Calculul unghiului

    tank1ModelMatrix *= transform2D::Rotate(angle);  // Rote?te tancul pe baza pantei terenului

    // Red?m tancul 1
    RenderMesh2D(meshes["tank1_base"], shaders["VertexColor"], tank1ModelMatrix);
    RenderMesh2D(meshes["tank1_turret"], shaders["VertexColor"], tank1ModelMatrix);

    // Actualizare pozi?ie ?i rota?ie tanc 2 (similar cu tanc 1)
    glm::mat3 tank2ModelMatrix = glm::mat3(1);
    int indexTank2 = std::min(static_cast<int>((xPosTank2 - xStart) / (xEnd - xStart) * (heightMap.size() - 1)), static_cast<int>(heightMap.size() - 1));
    float yPosTank2 = heightMap[indexTank2] + tankYOffset;  // Pozi?ia corect? pe teren pentru tanc 2, cu offset

    tank2ModelMatrix *= transform2D::Translate(xPosTank2, yPosTank2);

    int indexNextTank2 = std::min(indexTank2 + static_cast<int>(dx), static_cast<int>(heightMap.size() - 1));
    float yNextPosTank2 = heightMap[indexNextTank2] + tankYOffset;

    float angle2 = atan2(yNextPosTank2 - yPosTank2, dx);  // Calculul unghiului pentru tancul 2

    tank2ModelMatrix *= transform2D::Rotate(angle2);  // Rote?te tancul pe baza pantei terenului

    // Red?m tancul 2
    RenderMesh2D(meshes["tank2_base"], shaders["VertexColor"], tank2ModelMatrix);
    RenderMesh2D(meshes["tank2_turret"], shaders["VertexColor"], tank2ModelMatrix);
    // Render tank 1's barrel with rotation
    RenderMesh2D(
        meshes["tank1_barrel"],
        shaders["VertexColor"],
        tank1ModelMatrix * transform2D::Translate(0, 20) * transform2D::Rotate(barrelAngleTank1)
    );

    // Render tank 2's barrel with rotation
    RenderMesh2D(
        meshes["tank2_barrel"],
        shaders["VertexColor"],
        tank2ModelMatrix * transform2D::Translate(0, 20) * transform2D::Rotate(barrelAngleTank2)
    );

}

void Tema1::FrameEnd() {
}

void Tema1::UpdateTankPosition() {
    // Update the tank's x position based on input or movement logic
    if (moveTank1Right) {
        xPosTank1 += 10.0f;  // Move tank1 right
    }
    if (moveTank1Left) {
        xPosTank1 -= 10.0f;  // Move tank1 left
    }

    // Ensure tank1 stays within bounds
    if (xPosTank1 < 0) {
        xPosTank1 = 0;
    }
    if (xPosTank1 > window->GetResolution().x) {
        xPosTank1 = window->GetResolution().x;
    }

    if (moveTank2Right) {
        xPosTank2 += 1.0f;  // Move tank2 right
    }
    if (moveTank2Left) {
        xPosTank2 -= 1.0f;  // Move tank2 left
    }

    // Ensure tank2 stays within bounds
    if (xPosTank2 < 0) {
        xPosTank2 = 0;
    }
    if (xPosTank2 > window->GetResolution().x) {
        xPosTank2 = window->GetResolution().x;
    }
}

void Tema1::OnKeyPress(int key, int mods) {
    const float moveSpeed = 2.0f;  // Viteza de deplasare (po?i ajusta aceast? valoare pentru a controla viteza)

    if (key == GLFW_KEY_RIGHT) {
        // Mi?c? tancul 1 spre dreapta
        xPosTank1 += moveSpeed;  // Viteza mai mic? pentru deplasare
    }
    if (key == GLFW_KEY_LEFT) {
        // Mi?c? tancul 1 spre stânga
        xPosTank1 -= moveSpeed;  // Viteza mai mic? pentru deplasare
    }

    // Asigur?-te c? tancul 1 nu dep??e?te limitele feronavei
    if (xPosTank1 < 0) xPosTank1 = 0;
    else if (xPosTank1 > window->GetResolution().x) xPosTank1 = window->GetResolution().x;

    if (key == GLFW_KEY_D) {
        // Mi?c? tancul 2 spre dreapta
        xPosTank2 += moveSpeed;
    }
    if (key == GLFW_KEY_A) {
        // Mi?c? tancul 2 spre stânga
        xPosTank2 -= moveSpeed;
    }

    // Asigur?-te c? tancul 2 nu dep??e?te limitele feronavei
    if (xPosTank2 < 0) xPosTank2 = 0;
    else if (xPosTank2 > window->GetResolution().x) xPosTank2 = window->GetResolution().x;

    if (key == GLFW_KEY_W) {
        // Rotate barrel of tank 1 upwards
        barrelAngleTank1 += barrelRotationSpeed;
    }
    if (key == GLFW_KEY_S) {
        // Rotate barrel of tank 1 downwards
        barrelAngleTank1 -= barrelRotationSpeed;
    }
    if (key == GLFW_KEY_UP) {
        // Rotate barrel of tank 2 upwards
        barrelAngleTank2 += barrelRotationSpeed;
    }
    if (key == GLFW_KEY_DOWN) {
        // Rotate barrel of tank 2 downwards
        barrelAngleTank2 -= barrelRotationSpeed;
    }

}


void Tema1::OnKeyRelease(int key, int mods) {
    // Check for key release events
    if (key == GLFW_KEY_RIGHT) {
        moveTank1Right = false;
    }
    if (key == GLFW_KEY_LEFT) {
        moveTank1Left = false;
    }

    // Same for tank2
    if (key == GLFW_KEY_D) {
        moveTank2Right = false;
    }
    if (key == GLFW_KEY_A) {
        moveTank2Left = false;
    }
}

void Tema1::OnInputUpdate(float deltaTime, int mods) {
    const float moveSpeed = 110.0f;  // Viteza de deplasare pe secund? (mai mic? pentru mi?care mai lent?)

    // Mi?c? tancul 1 spre dreapta sau spre stânga în func?ie de input
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        xPosTank1 += moveSpeed * deltaTime;  // Mi?care lent? în func?ie de timpul trecut
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        xPosTank1 -= moveSpeed * deltaTime;  // Mi?care lent? în func?ie de timpul trecut
    }

    // Mi?care pentru tancul 2
    if (window->KeyHold(GLFW_KEY_D)) {
        xPosTank2 += moveSpeed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        xPosTank2 -= moveSpeed * deltaTime;
    }

    // Asigur?-te c? tancurile nu ies din limitele feronavei
    if (xPosTank1 < 0) xPosTank1 = 0;
    if (xPosTank1 > window->GetResolution().x) xPosTank1 = window->GetResolution().x;

    if (xPosTank2 < 0) xPosTank2 = 0;
    if (xPosTank2 > window->GetResolution().x) xPosTank2 = window->GetResolution().x;

    if (window->KeyHold(GLFW_KEY_W)) {
        barrelAngleTank1 += barrelRotationSpeed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        barrelAngleTank1 -= barrelRotationSpeed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_UP)) {
        barrelAngleTank2 += barrelRotationSpeed * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        barrelAngleTank2 -= barrelRotationSpeed * deltaTime;
    }

}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // Add mouse move event logic here if necessary
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event logic here if necessary
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event logic here if necessary
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
    // Add mouse scroll event logic here if necessary
}

void Tema1::OnWindowResize(int width, int height) {
    // Handle window resize if necessary
}