#include <stdio.h>

// Structure to represent a point in 2D space
typedef struct {
    double x;
    double y;
} t_vec2f;

t_vec2f vec2f(double x, double y)
{
	return ((t_vec2f){.x =x, .y = y});
}
// Function to convert screen coordinates to world coordinates
t_vec2f screenToWorld(t_vec2f vec, t_vec2f screen, t_vec2f x_dem, t_vec2f y_dem) {
    t_vec2f worldPoint;

    // Calculate the scale factors
    double scaleX = (x_dem.x - x_dem.y) / screen.x;
    double scaleY = (y_dem.x - y_dem.y) / screen.y;

    // // Convert screen coordinates to world coordinates
    worldPoint.x = vec.x * scaleX + x_dem.x;
    worldPoint.y = vec.y * scaleY + y_dem.y;

    return worldPoint;
}

int main() {
    // Example screen coordinates
    float screenX = 1.0f;
    float screenY = 0.0f;

    // Example screen dimensions
    float screenWidth = 64.0f;
    float screenHeight = 64.0f;

    // Example world coordinates boundaries
    float worldXMin = -32.0f;
    float worldYMin = -32.0f;
    float worldXMax = 32.0f;
    float worldYMax = 32.0f;

    // Convert screen coordinates to world coordinates
    t_vec2f worldPoint = screenToWorld(vec2f(screenX, screenY), vec2f(screenWidth, screenHeight), vec2f(worldXMin, worldYMin), vec2f(worldXMax, worldYMax));

    // Print the result
    printf("Screen coordinates: (%.2f, %.2f)\n", screenX, screenY);
    printf("World coordinates: (%.2f, %.2f)\n", worldPoint.x, worldPoint.y);

    return 0;
}
