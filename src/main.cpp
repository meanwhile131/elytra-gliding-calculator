#include <iostream>
#include <implementation.cpp>
#include <matplot/matplot.h>
#include <vector>
using namespace std;

int main()
{
    Vec3d intial_position = Vec3d(0, 150, 0);
    double bestDistance;
    float bestPitch;
    vector<double> pitches;
    vector<double> distances;
    ofstream log("out.txt");
    for (float pitch = -20; pitch < 20; pitch += 0.01)
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
        pitches.push_back(pitch);
        distances.push_back(distance);
        log << "Pitch: " << pitch << " Distance:" << distance << "\n";
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