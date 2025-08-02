#include <iostream>
#include <implementation.cpp>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ofstream log("out.txt");

    double bestDistance = -INFINITY;
    float best_pitch_up{};
    float best_pitch_down{};
    for (float pitch_down = 0; pitch_down < 90; pitch_down++)
    {
        for (float pitch_up = -90; pitch_up < 0; pitch_up++)
        {
            Vec3d position(0, 100, 0);
            Vec3d velocity(0, 0, 0);
            float pitch = 0;
            while (position.y > 0)
            {
                if (velocity.y < 0)
                {
                    pitch = pitch_down;
                }
                if (position.y < 5)
                {
                    pitch = pitch_up;
                }
                velocity = calcGlidingVelocity(velocity, pitch);
                position += velocity;
            }
            log << "For " << pitch_down << "; " << pitch_up << ": " << position.z;
            if (position.z > bestDistance)
            {
                best_pitch_up = pitch_up;
                best_pitch_down = pitch_down;
                bestDistance = position.z;
                log << " (New best!)";
            }
            log << "\n";
        }
    }
    log << "\nThe best angles are " << best_pitch_down << "; " << best_pitch_up << " for " << bestDistance;
    log.close();
    return 0;
}