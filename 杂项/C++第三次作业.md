```cpp
#include <iostream>
#include <vector>
#include <conio.h>
#include <cmath>
using namespace std;
class Rectangle
{
public:
    Rectangle(int width, int length);
    Rectangle(const Rectangle &rec);
    int GetWidth();
    int GetLength();

private:
    int width;
    int length;
};
class Circle
{
public:
    Circle(int radius);
    Circle(const Circle &cir);
    int GetRadius();

private:
    int radius;
};
class Robot
{
public:
    Robot(int x, int y, const vector<Circle> &circles, const vector<Rectangle> &rectangles);
    Robot(const Robot &robot);
    int GetX();
    int GetY();
    void Increase_X(int delta);
    void Increase_Y(int delta);
    void OutputMyself();

private:
    int x;
    int y;
    vector<Circle> circles;
    vector<Rectangle> rectangles;
};
Rectangle::Rectangle(int width, int length)
{
    this->width = width;
    this->length = length;
}
Rectangle::Rectangle(const Rectangle &rec)
{
    this->length = rec.length;
    this->width = rec.width;
}
int Rectangle::GetWidth()
{
    return this->width;
}
int Rectangle::GetLength()
{
    return this->length;
}
Circle::Circle(int radius)
{
    this->radius = radius;
}
Circle::Circle(const Circle &cir)
{
    this->radius = cir.radius;
}
int Circle::GetRadius()
{
    return radius;
}
Robot::Robot(int x, int y, const vector<Circle> &circles, const vector<Rectangle> &rectangles)
{
    this->x = x;
    this->y = y;
    this->circles = circles;
    this->rectangles = rectangles;
}
Robot::Robot(const Robot &robot)
{
    this->x = robot.x;
    this->y = robot.y;
    this->circles = robot.circles;
    this->rectangles = robot.rectangles;
}
int Robot::GetX()
{
    return x;
}
int Robot::GetY()
{
    return y;
}
void Robot::Increase_X(int delta)
{
    x += delta;
}
void Robot::Increase_Y(int delta)
{
    y += delta;
}
void Robot::OutputMyself()
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
    vector<Rectangle> rectangles;
    rectangles.push_back(Rectangle(10, 20));
    rectangles.push_back(Rectangle(30, 40));
    vector<Circle> circles;
    circles.push_back(Circle(5));
    circles.push_back(Circle(8));
    Robot robot1(0, 0, circles, rectangles);
    Robot robot2(robot1);
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