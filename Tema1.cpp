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

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
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

    int numPoints = 100;
    float xStart = 0;
    float xEnd = (float)resolution.x;

    float amplitude1 = 20;
    float frequency1 = 0.02f;
    float amplitude2 = 10;
    float frequency2 = 0.05f;
    float verticalOffset = 150;

    std::vector<float> heightMap = GenerateHeightMap(numPoints, amplitude1, frequency1, amplitude2, frequency2, xStart, xEnd, verticalOffset);

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

    // Ini?ializarea tancurilor
    std::vector<Mesh*> tank1Meshes;
    std::vector<Mesh*> tank2Meshes;


    glm::vec3 camoBeigeDark = glm::vec3(0.76f, 0.69f, 0.50f);  // A shade of beige
    glm::vec3 camoGreenDark = glm::vec3(0.33f, 0.42f, 0.18f);  // A shade of green

    // Creeaz? primul tanc (albastru)
    object2D::CreateTank("tank1",  camoBeigeDark, camoBeigeDark, tank1Meshes);
    for (auto& mesh : tank1Meshes) {
        AddMeshToList(mesh);
    }

    // Creeaz? al doilea tanc (ro?u)
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
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["terrain"], shaders["VertexColor"], modelMatrix);

    // Pozi?ionare ?i redare pentru primul tanc
    glm::mat3 tank1ModelMatrix = glm::mat3(1);
    tank1ModelMatrix *= transform2D::Translate(100, 200);
    RenderMesh2D(meshes["tank1_base"], shaders["VertexColor"], tank1ModelMatrix);
    RenderMesh2D(meshes["tank1_turret"], shaders["VertexColor"], tank1ModelMatrix);
    RenderMesh2D(meshes["tank1_barrel"], shaders["VertexColor"], tank1ModelMatrix * transform2D::Translate(0, 20));

    // Pozi?ionare ?i redare pentru al doilea tanc
    glm::mat3 tank2ModelMatrix = glm::mat3(1);
    tank2ModelMatrix *= transform2D::Translate(400, 200);
    RenderMesh2D(meshes["tank2_base"], shaders["VertexColor"], tank2ModelMatrix);
    RenderMesh2D(meshes["tank2_turret"], shaders["VertexColor"], tank2ModelMatrix);
    RenderMesh2D(meshes["tank2_barrel"], shaders["VertexColor"], tank2ModelMatrix * transform2D::Translate(0, 20));
}

void Tema1::FrameEnd() {
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
