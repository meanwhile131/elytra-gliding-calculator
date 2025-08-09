#include <iostream>
#include <implementation.cpp>
#include <matplot/matplot.h>
#include <vector>
using namespace std;

int main()
{
    double bestDistance{};
    float bestPitch{};
    vector<double> pitches;
    vector<double> distances;
    ofstream log("log.txt");
    for (float pitch = -20; pitch < 20; pitch += 0.01)
    {
        Vec3d position(0, 150, 0);
        Vec3d velocity(0, 0, 0);
        while (position.y > 0)
        {
            velocity = calcGlidingVelocity(velocity, pitch);
            position = position.add(velocity.x, velocity.y, velocity.z);
        }
        double distance = position.z;
        if (distance > bestDistance)
        {
            bestDistance = distance;
            bestPitch = pitch;
        }
        pitches.push_back(pitch);
        distances.push_back(distance);
        log << "Pitch: " << pitch << " Distance: " << distance << "\n";
    }
    log << "Best pitch is " << bestPitch << " for " << bestDistance << "\n";
    log.close();
    {
        using namespace matplot;
        auto f = figure(true);
        auto ax = f->current_axes();
        auto p = ax->plot(pitches, distances);
        f->save("graph.png");
        f->show();
    }
    return 0;
}