```cpp
#include <iostream>
#include <cmath>
#define G 9.8
using namespace std;
class Parabola
{
public:
    Parabola(double x, double y, double vx, double vy)
        : x(x), y(y), vx(vx), vy(vy)
    {
    }
    bool isTimeValid(double t)
    {
        return (t <= getTime() && t >= 0);
    }
    double getX(double t)
    {
        if (!isTimeValid(t))
        {
            cout << "Input time error!" << endl;
            return -1;
        }
        return x + vx * t;
    }
    double getY(double t)
    {
        if (!isTimeValid(t))
        {
            cout << "Input time error!" << endl;
            return -1;
        }
        return y - 1.0 / 2 * G * t * t + vy * t;
    }
    double getSpeedX(double t)
    {
        return vx;
    }
    double getSpeedY(double t)
    {
        return vy - G * t;
    }
    double getTime()
    {
        return (2 * vy + sqrt(4 * vy * vy + 8 * G * y)) / (2 * G);
    }
    double getLandingPos()
    {
        return getX(getTime());
    }
    double getHighestX()
    {
        if (vy <= 0)
        {
            return x;
        }
        return getX(vy / G);
    }
    double getHighestY()
    {
        if (vy <= 0)
        {
            return y;
        }
        return getY(vy / G);
    }
    // Speed magnitude and direction
    double getSpeedMagnitude(double t)
    {
        return sqrt(getSpeedX(t) * getSpeedX(t) + getSpeedY(t) * getSpeedY(t));
    }
    double getSpeedTangentDirection(double t)
    {
        return getSpeedY(t) / getSpeedX(t);
    }
private:
    double x;
    double y;
    double vx;
    double vy;
};
int main()
{
    Parabola a = Parabola(4, 4, 3, 4);
    double t;
    cout << "Please input time" << endl;
    cin >> t;
    if (!a.isTimeValid(t))
    {
        cout << "Input time error!" << endl;
        cout << "Valid time is from " << 0 << " to " << a.getTime() << endl; 
        return 0;
    }
    cout << "x:" << a.getX(t) << "," << "y:" << a.getY(t) << endl;
    cout << "Speed Magnitude:" << a.getSpeedMagnitude(t) << endl;
    cout << "Speed Direction Tangent:" << a.getSpeedTangentDirection(t) << endl;
    cout << "Highest Position:x = " << a.getHighestX() << " y = " << a.getHighestY() << endl;
    cout << "Landing Postion:" << a.getLandingPos() << endl;
    cout << "Fly Time:" << a.getTime() << endl;
    return 0;
}
```