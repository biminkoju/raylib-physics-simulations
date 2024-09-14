#include <math.h>
#include <stdio.h>

#include <vector>

#include "raygui.h"
#include "raylib.h"

int main(void) {
  // Initialization
  InitWindow(800, 450, "simple harmonic motion");

  // Camera initialization
  Camera3D camera = {{0}};
  camera.position = (Vector3){10.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  // Hide cursor
  DisableCursor();

  // Variables for attractor
  const float omegaX = 1.0f;
  const float phiX = 90.0f;
  const float amplitudeX = 1.0f;
  const float omegaY = 20.0f;
  const float phiY = 45.0f;
  const float amplitudeY = 0.5f;
  const float omegaZ = 0.0f;
  const float phiZ = 0.0f;
  const float amplitudeZ = 0.0f;

  std::vector<Vector3> pointArray;
  const size_t maxPoints =
      200;  // Limit the number of points to keep the performance in check

  while (!WindowShouldClose()) {
    // Attractor calculations
    float currentTime = GetTime();  // Store the time to avoid redundant calls
    float x = amplitudeX * cosf(omegaX * currentTime + phiX);
    float y = amplitudeY * cosf(omegaY * currentTime + phiY);
    float z = amplitudeZ * cosf(omegaZ * currentTime + phiZ);

    // Store the point and manage size
    pointArray.push_back((Vector3){x, y, z});
    if (pointArray.size() > maxPoints) {
      pointArray.erase(
          pointArray
              .begin());  // Remove the oldest point to keep the size manageable
    }

    // Camera update
    UpdateCamera(&camera, CAMERA_FREE);

    // Drawing
    BeginDrawing();
    ClearBackground(BLACK);  // Clear the background

    BeginMode3D(camera);
    DrawSphere((Vector3){x, y, z}, 0.1f, RED);
    for (size_t i = 0; i < pointArray.size() - 1; ++i) {
      DrawLine3D(pointArray[i], pointArray[i + 1], BLUE);
    }
    EndMode3D();

    DrawFPS(10, 10);  // Display FPS in a less intrusive position
    EndDrawing();
  }

  // Deinitialization
  CloseWindow();
  return 0;
}
