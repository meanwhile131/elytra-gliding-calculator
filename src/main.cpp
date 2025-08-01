#include <iostream>
#include <implementation.cpp>

int main()
{
    double bestDistance;
    float bestPitch;
    Vec3d intial_position = Vec3d(0, 150, 0);
    for (float pitch = -90; pitch < 90; pitch += 0.01)
    {
        GlidingPlayer player(pitch, intial_position);
        while (!player.simulateTick())
        {
        }
        double distance = player.getPos().z;
        if (distance > bestDistance)
        {
            bestDistance = distance;
            bestPitch = pitch;
        }
        std::cout << distance << " for " << pitch << "\n";
    }
    std::cout << "Best: " << bestDistance << " for " << bestPitch << "\n";
    return 0;
}