```cpp
#include <iostream>
#include <limits>

using namespace std;

#define PI 3.14

class Rectangle_HYC
{
public:
    Rectangle_HYC(double length, double width, double x, double y);
    Rectangle_HYC(const Rectangle_HYC &rec);
    void Zoom(double k);
    void Output();
    void Move(double dx, double dy);

private:
    double length;
    double width;
    // Position is the lower-left corner; scaling keeps this point fixed.
    double x;
    double y;
};

class Circle_HYC
{
public:
    Circle_HYC(double r, double x, double y);
    Circle_HYC(const Circle_HYC &cir);
    void Zoom(double k);
    void Output();
    void Move(double dx, double dy);

private:
    double r;
    // Position is the center; scaling keeps this point fixed.
    double x;
    double y;
};

class Scene
{
public:
    Scene(Circle_HYC cir1, Circle_HYC cir2,
          Rectangle_HYC rec1, Rectangle_HYC rec2);
    Scene(const Scene &sce);
    // 1: circle 1, 2: circle 2, 3: rectangle 1, 4: rectangle 2.
    void Zoom(int index, double k);
    void Move(int index, double dx, double dy);
    void Output();

private:
    Circle_HYC cir1;
    Circle_HYC cir2;
    Rectangle_HYC rec1;
    Rectangle_HYC rec2;
};

Rectangle_HYC::Rectangle_HYC(double length, double width, double x, double y)
    : length(length), width(width), x(x), y(y)
{
}

Rectangle_HYC::Rectangle_HYC(const Rectangle_HYC &rec)
    : length(rec.length), width(rec.width), x(rec.x), y(rec.y)
{
}

void Rectangle_HYC::Zoom(double k)
{
    if (k <= 0)
    {
        cout << "Scale factor must be positive." << endl;
        return;
    }
    length *= k;
    width *= k;
}

void Rectangle_HYC::Output()
{
    cout << "Perimeter:" << 2 * length + 2 * width << endl;
    cout << "Area:" << length * width << endl;
    cout << "Position:" << endl;
    cout << "x:" << x << endl;
    cout << "y:" << y << endl;
}

void Rectangle_HYC::Move(double dx, double dy)
{
    x += dx;
    y += dy;
}

Circle_HYC::Circle_HYC(double r, double x, double y)
    : r(r), x(x), y(y)
{
}

Circle_HYC::Circle_HYC(const Circle_HYC &cir)
    : r(cir.r), x(cir.x), y(cir.y)
{
}

void Circle_HYC::Zoom(double k)
{
    if (k <= 0)
    {
        cout << "Scale factor must be positive." << endl;
        return;
    }
    r *= k;
}

void Circle_HYC::Output()
{
    cout << "Perimeter:" << 2 * PI * r << endl;
    cout << "Area:" << PI * r * r << endl;
    cout << "Position:" << endl;
    cout << "x:" << x << endl;
    cout << "y:" << y << endl;
}

void Circle_HYC::Move(double dx, double dy)
{
    x += dx;
    y += dy;
}

Scene::Scene(Circle_HYC cir1, Circle_HYC cir2,
             Rectangle_HYC rec1, Rectangle_HYC rec2)
    : cir1(cir1), cir2(cir2), rec1(rec1), rec2(rec2)
{
}

Scene::Scene(const Scene &sce)
    : cir1(sce.cir1), cir2(sce.cir2), rec1(sce.rec1), rec2(sce.rec2)
{
}

void Scene::Zoom(int index, double k)
{
    switch (index)
    {
    case 1:
        cir1.Zoom(k);
        break;
    case 2:
        cir2.Zoom(k);
        break;
    case 3:
        rec1.Zoom(k);
        break;
    case 4:
        rec2.Zoom(k);
        break;
    default:
        cout << "Invalid shape index. Use 1-4." << endl;
        break;
    }
}

void Scene::Move(int index, double dx, double dy)
{
    switch (index)
    {
    case 1:
        cir1.Move(dx, dy);
        break;
    case 2:
        cir2.Move(dx, dy);
        break;
    case 3:
        rec1.Move(dx, dy);
        break;
    case 4:
        rec2.Move(dx, dy);
        break;
    default:
        cout << "Invalid shape index. Use 1-4." << endl;
        break;
    }
}

void Scene::Output()
{
    cout << "\n[1] Circle 1" << endl;
    cir1.Output();
    cout << "\n[2] Circle 2" << endl;
    cir2.Output();
    cout << "\n[3] Rectangle 1" << endl;
    rec1.Output();
    cout << "\n[4] Rectangle 2" << endl;
    rec2.Output();
}

int main()
{
    Circle_HYC cir1(2, 0, 0);
    Circle_HYC cir2(3, 5, 5);
    Rectangle_HYC rec1(4, 2, 1, 1);
    Rectangle_HYC rec2(6, 3, -2, -2);
    Scene scene(cir1, cir2, rec1, rec2);

    cout << "Initial scene:" << endl;
    scene.Output();

    while (true)
    {
        cout << "\n0: Exit  1: Zoom  2: Move  3: Output\nChoice: ";
        int choice;
        if (!(cin >> choice))
        {
            if (cin.eof())
                break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number." << endl;
            continue;
        }
        if (choice == 0)
            break;

        int index;
        double k, dx, dy;
        switch (choice)
        {
        case 1:
            cout << "Enter shape index (1-4) and scale factor (>0): ";
            if (cin >> index >> k)
            {
                scene.Zoom(index, k);
                scene.Output();
            }
            break;
        case 2:
            cout << "Enter shape index (1-4), dx and dy: ";
            if (cin >> index >> dx >> dy)
            {
                scene.Move(index, dx, dy);
                scene.Output();
            }
            break;
        case 3:
            scene.Output();
            break;
        default:
            cout << "Invalid choice. Use 0-3." << endl;
            break;
        }

        if (cin.eof())
            break;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter numbers." << endl;
        }
    }
    return 0;
}
```