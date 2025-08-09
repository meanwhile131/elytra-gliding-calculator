#include <iostream>
#include <implementation.cpp>
#include <vector>
#include <fstream>
#include <matplot/matplot.h>
#include <optional>
using namespace std;

const double starting_height = 50;
struct Trajectory
{
    float pitch;
    vector<Vec3d> positions;
    Vec3d velocity;
};

struct UpTrajectory : Trajectory
{
    float pitch_delta;
};

Trajectory bestDownTrajectory(Vec3d starting_position, Vec3d starting_velocity)
{
    Trajectory best_trajectory{0, {}, Vec3d(0, 0, -INFINITY)};
    for (float pitch = 0; pitch < 90; pitch++)
    {
        Vec3d position = starting_position;
        Vec3d velocity = starting_velocity;
        vector<Vec3d> positions{};
        while (position.y > 3)
        {
            velocity = calcGlidingVelocity(velocity, pitch);
            position += velocity;
            positions.push_back(position);
        }
        if (velocity.z > best_trajectory.velocity.z)
        {
            best_trajectory.pitch = pitch;
            best_trajectory.positions = positions;
            best_trajectory.velocity = velocity;
        }
    }
    return best_trajectory;
}

UpTrajectory bestUpTrajectory(Vec3d starting_position, Vec3d starting_velocity)
{
    UpTrajectory best_trajectory{0, {Vec3d(0, -INFINITY, 0)}, Vec3d(0, 0, 0), 0};
    for (float pitch_delta = 0; pitch_delta < 1; pitch_delta += 0.05)
    {
        for (float starting_pitch = -90; starting_pitch < 0; starting_pitch++)
        {
            float pitch = starting_pitch;
            Vec3d position = starting_position;
            Vec3d velocity = starting_velocity;
            vector<Vec3d> positions{};
            while ((velocity.y > 0 || position.y < 5) && position.y > 0)
            {
                velocity = calcGlidingVelocity(velocity, pitch);
                position += velocity;
                positions.push_back(position);
                pitch += pitch_delta;
            }
            if (position.y > best_trajectory.positions.back().y)
            {
                best_trajectory.pitch_delta = pitch_delta;
                best_trajectory.pitch = starting_pitch;
                best_trajectory.positions = positions;
                best_trajectory.velocity = velocity;
            }
        }
    }
    return best_trajectory;
}

int main()
{
    ofstream log("log.txt");

    Vec3d position(0, starting_height, 0);
    Vec3d velocity(0, 0, 0);
    vector<Vec3d> positions{position};
    while (position.y > 0 && position.z < 4000)
    {
        Trajectory down = bestDownTrajectory(position, velocity);
        log << "Down pitch: " << down.pitch << "\n";
        positions.insert(positions.end(), down.positions.begin(), down.positions.end());
        position = down.positions.back();
        velocity = down.velocity;
        log << position << " " << velocity << "\n";
        UpTrajectory up = bestUpTrajectory(position, velocity);
        log << "Up pitch: " << up.pitch << " with delta " << up.pitch_delta << " degrees/tick\n";
        positions.insert(positions.end(), up.positions.begin(), up.positions.end());
        position = up.positions.back();
        velocity = up.velocity;
        log << position << " " << velocity << "\n";
    }
    log.close();
    {
        using namespace matplot;
        figure_handle f = figure(true);
        axes_handle ax = f->current_axes();
        vector<double> z_positions;
        vector<double> y_positions;
        transform(positions.begin(), positions.end(),
                  back_inserter(z_positions),
                  [](const Vec3d &vec)
                  { return vec.z; });
        transform(positions.begin(), positions.end(),
                  back_inserter(y_positions),
                  [](const Vec3d &vec)
                  { return vec.y; });
        auto p = ax->plot(z_positions, y_positions);
        f->save("graph.png");
    }
    return 0;
}
