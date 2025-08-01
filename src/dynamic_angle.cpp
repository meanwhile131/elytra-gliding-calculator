#include <iostream>
#include <implementation.cpp>
#include <vector>
#include <fstream>
#include <optional>
using namespace std;

struct FlightConfiguration {
    Vec3d position;
    Vec3d velocity;
    float pitch;
};

int main()
{
    double bestDistance;
    float bestPitch;
    vector<double> pitches;
    vector<double> distances;
    ofstream log("out.txt");
    
    Vec3d position(0, 100, 0);
    Vec3d velocity(0, 0, 0);
    while (position.z < 2000 && position.y > 0) {
        FlightConfiguration best{position, velocity, 0};
        double bestSpeed;
        for (float pitch = -90; pitch < 90; pitch += 0.01)
        {
            Vec3d new_position = position;
            Vec3d new_velocity = velocity;
            simulateTick(new_position, new_velocity, pitch);
            if (new_velocity.z > best.velocity.z)
            {
                best = FlightConfiguration {new_position, new_velocity, pitch};
            }
        }
        log << best.position << " " << best.velocity << " " << best.pitch << "\n";
        cout << best.position << " " << best.velocity << " " << best.pitch << "\n";
        position = best.position;
        velocity = best.velocity;
    }
    log.close();
    return 0;
}