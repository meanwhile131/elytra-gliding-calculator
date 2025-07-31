#include <iostream>
#include <math.h>

class Vec3d
{
public:
    double x, y, z;
    Vec3d(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    double horizontalLength()
    {
        return sqrt(x * x + z * z);
    }
    Vec3d add(double x, double y, double z)
    {
        return Vec3d(this->x + x, this->y + y, this->z + z);
    }
    Vec3d multiply(double x, double y, double z)
    {
        return Vec3d(this->x * x, this->y * y, this->z * z);
    }
};

std::ostream &operator<<(std::ostream &stream, Vec3d &vector)
{
    return stream << "(" << vector.x << " " << vector.y << " " << vector.z << ")";
}

Vec3d getRotationVector(float pitch, float yaw)
{
    float f = pitch * (float)(M_PI / 180.0);
    float g = -yaw * (float)(M_PI / 180.0);
    float h = cos(g);
    float i = sin(g);
    float j = cos(f);
    float k = sin(f);
    return Vec3d(i * j, -k, h * j);
}

Vec3d simulateFlight(Vec3d position, float pitch)
{
    float yaw{};
    Vec3d oldVelocity(0, 0, 0);
    while (position.y > 0)
    {
        Vec3d vec3d = getRotationVector(pitch, yaw);
        float f = pitch * (float)(M_PI / 180.0);
        double d = sqrt(vec3d.x * vec3d.x + vec3d.z * vec3d.z);
        double e = oldVelocity.horizontalLength();
        double g = 0.08; // Minecraft's gravity constant
        double h = pow(cos(f), 2);
        oldVelocity = oldVelocity.add(0.0, g * (-1.0 + h * 0.75), 0.0);
        if (oldVelocity.y < 0.0 && d > 0.0)
        {
            double i = oldVelocity.y * -0.1 * h;
            oldVelocity = oldVelocity.add(vec3d.x * i / d, i, vec3d.z * i / d);
        }

        if (f < 0.0F && d > 0.0)
        {
            double i = e * -sin(f) * 0.04;
            oldVelocity = oldVelocity.add(-vec3d.x * i / d, i * 3.2, -vec3d.z * i / d);
        }

        if (d > 0.0)
        {
            oldVelocity = oldVelocity.add((vec3d.x / d * e - oldVelocity.x) * 0.1, 0.0, (vec3d.z / d * e - oldVelocity.z) * 0.1);
        }

        oldVelocity = oldVelocity.multiply(0.99F, 0.98F, 0.99F);
        position = position.add(oldVelocity.x, oldVelocity.y, oldVelocity.z);
    }
    return position;
}

int main()
{
    double bestDistance;
    float bestPitch;
    for (float pitch = -90; pitch < 90; pitch += 0.01)
    {
        double distance = simulateFlight(Vec3d(0, 50, 0), pitch).z;
        if (distance > bestDistance) {
            bestDistance = distance;
            bestPitch = pitch;
        }
        std::cout << distance << " for " << pitch << "\n";
    }
    std::cout << "Best: " << bestDistance << " for " << bestPitch << "\n";
    return 0;
}