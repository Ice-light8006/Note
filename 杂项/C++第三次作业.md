```cpp
#include <iostream>
#include <vector>
#include <conio.h>
#include <cmath>
using namespace std;
class Rectangle_HYC
{
public:
    Rectangle_HYC(int width, int length);
    Rectangle_HYC(const Rectangle_HYC &rec);
    int GetWidth();
    int GetLength();

private:
    int width;
    int length;
};
class Circle_HYC
{
public:
    Circle_HYC(int radius);
    Circle_HYC(const Circle_HYC &cir);
    int GetRadius();

private:
    int radius;
};
class Robot_HYC
{
public:
    Robot_HYC(int x, int y, const vector<Circle_HYC> &circles, const vector<Rectangle_HYC> &rectangles);
    Robot_HYC(const Robot_HYC &robot);
    int GetX();
    int GetY();
    void Increase_X(int delta);
    void Increase_Y(int delta);
    void OutputMyself();

private:
    int x;
    int y;
    vector<Circle_HYC> circles;
    vector<Rectangle_HYC> rectangles;
};
Rectangle_HYC::Rectangle_HYC(int width, int length)
{
    this->width = width;
    this->length = length;
}
Rectangle_HYC::Rectangle_HYC(const Rectangle_HYC &rec)
{
    this->length = rec.length;
    this->width = rec.width;
}
int Rectangle_HYC::GetWidth()
{
    return this->width;
}
int Rectangle_HYC::GetLength()
{
    return this->length;
}
Circle_HYC::Circle_HYC(int radius)
{
    this->radius = radius;
}
Circle_HYC::Circle_HYC(const Circle_HYC &cir)
{
    this->radius = cir.radius;
}
int Circle_HYC::GetRadius()
{
    return radius;
}
Robot_HYC::Robot_HYC(int x, int y, const vector<Circle_HYC> &circles, const vector<Rectangle_HYC> &rectangles)
{
    this->x = x;
    this->y = y;
    this->circles = circles;
    this->rectangles = rectangles;
}
Robot_HYC::Robot_HYC(const Robot_HYC &robot)
{
    this->x = robot.x;
    this->y = robot.y;
    this->circles = robot.circles;
    this->rectangles = robot.rectangles;
}
int Robot_HYC::GetX()
{
    return x;
}
int Robot_HYC::GetY()
{
    return y;
}
void Robot_HYC::Increase_X(int delta)
{
    x += delta;
}
void Robot_HYC::Increase_Y(int delta)
{
    y += delta;
}
void Robot_HYC::OutputMyself()
{
    cout << "Position:x=" << x << ",y=" << y << endl;
    cout << "Rectangle count:" << rectangles.size() << endl;
    for (int i = 1; i <= rectangles.size(); i++)
    {
        cout << "Rectangle No." << i << ":Width=" << rectangles[i - 1].GetWidth() << ",Length=" << rectangles[i - 1].GetLength() << endl;
    }
    cout << "Circle count:" << circles.size() << endl;
    for (int i = 1; i <= circles.size(); i++)
    {
        cout << "Circle No." << i << ":Radius=" << circles[i - 1].GetRadius() << endl;
    }
}
int main()
{
    vector<Rectangle_HYC> rectangles;
    rectangles.push_back(Rectangle_HYC(10, 20));
    rectangles.push_back(Rectangle_HYC(30, 40));
    vector<Circle_HYC> circles;
    circles.push_back(Circle_HYC(5));
    circles.push_back(Circle_HYC(8));
    Robot_HYC robot1(0, 0, circles, rectangles);
    Robot_HYC robot2(robot1);
    cout << "Initial Robot1:" << endl;
    robot1.OutputMyself();
    cout << endl;
    cout << "Initial Robot2:" << endl;
    robot2.OutputMyself();
    cout << endl;
    cout << "Control:" << endl;
    cout << "Robot1: WASD" << endl;
    cout << "Robot2: Arrow Keys" << endl;
    cout << "Q quit" << endl;
    while (true)
    {
        char ch = _getch();

        if (ch == 'w')
        {
            cout << "W is pressed" << endl;
            robot1.Increase_Y(1);
        }
        else if (ch == 's')
        {
            cout << "S is pressed" << endl;
            robot1.Increase_Y(-1);
        }
        else if (ch == 'a')
        {
            cout << "A is pressed" << endl;
            robot1.Increase_X(-1);
        }
        else if (ch == 'd')
        {
            cout << "D is pressed" << endl;
            robot1.Increase_X(1);
        }
        else if (ch == -32 || ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
            case 72:
                cout << "UP is pressed" << endl;
                robot2.Increase_Y(1);
                break;

            case 80:
                cout << "DOWN is pressed" << endl;
                robot2.Increase_Y(-1);
                break;

            case 75:
                cout << "LEFT is pressed" << endl;
                robot2.Increase_X(-1);
                break;

            case 77:
                cout << "RIGHT is pressed" << endl;
                robot2.Increase_X(1);
                break;
            }
        }
        else if (ch == 'q')
        {
            cout << "Q is pressed" << endl;
            break;
        }
        cout << endl;
        cout << "Robot1:" << endl;
        robot1.OutputMyself();
        cout << endl;
        cout << "Robot2:" << endl;
        robot2.OutputMyself();
        int dx = robot1.GetX() - robot2.GetX();
        int dy = robot1.GetY() - robot2.GetY();
        double distance = sqrt(dx * dx + dy * dy);
        cout << "Distance between robots:"
             << distance << endl;
    }
    return 0;
}
```