#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <cmath>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


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
        // Aplica?i deplasarea vertical? pentru a ridica linia orizontului
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

    // Ajustare amplitudine, frecven?? ?i deplasare vertical? pentru un teren mai întins
    float amplitude1 = 20;      // Dealuri mai line
    float frequency1 = 0.02f;   // Frecven?? joas? pentru dealuri mai largi
    float amplitude2 = 10;      // Valoare mic? pentru varia?ii subtile
    float frequency2 = 0.05f;
    float verticalOffset = 150; // Ridic? terenul în sus pe ecran

    std::vector<float> heightMap = GenerateHeightMap(numPoints, amplitude1, frequency1, amplitude2, frequency2, xStart, xEnd, verticalOffset);

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < numPoints; ++i) {
        float x = xStart + i * ((xEnd - xStart) / (numPoints - 1));
        float y = heightMap[i];

        // Partea verde a terenului
        vertices.emplace_back(glm::vec3(x, y, 0), glm::vec3(0.3f, 0.6f, 0.2f));  // Verde închis pentru teren
        vertices.emplace_back(glm::vec3(x, 0, 0), glm::vec3(0.3f, 0.6f, 0.2f));  // Verde pentru partea de jos

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
}



void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds) {
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["terrain"], shaders["VertexColor"], modelMatrix);
}



void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


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