#include <iostream>
#include <implementation.cpp>
#include <vector>
#include <fstream>
#include <optional>
using namespace std;

int main()
{
    double bestDistance;
    float bestPitch;
    vector<double> pitches;
    vector<double> distances;
    ofstream log("log.txt");

    Vec3d position(0, 100, 0);
    Vec3d velocity(0, 0, 0);
    while (position.z < 2000 && position.y > 0)
    {
        Vec3d best_velocity(0, 0, 0);
        float best_pitch;
        for (float pitch = -90; pitch < 90; pitch += 0.01)
        {
            Vec3d new_velocity = calcGlidingVelocity(velocity, pitch);
            if (new_velocity.z > best_velocity.z)
            {
                best_velocity = new_velocity;
                best_pitch = pitch;
            }
        }
        velocity = best_velocity;
        position = position.add(best_velocity.x, best_velocity.y, best_velocity.z);
        log << position << " " << velocity << " " << best_pitch << "\n";
        cout << position << " " << velocity << " " << best_pitch << "\n";
        ;
    }
    log.close();
    return 0;
}