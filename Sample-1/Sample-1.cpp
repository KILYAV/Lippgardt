#include <iostream>
#include <math.h>

using namespace std;

double GetDouble(const char* preview)
{
    double value;
    cout << preview;
    cin >> value;

    while (cin.fail())
    {
        cout << "The entered character is not a doubleing point number, repeat enter nuumber: ";
        cin.ignore().clear();
        cin >> value;
    }

    return value;
}
unsigned int GetInt(const char* preview)
{
    unsigned int value;
    cout << preview;
    cin >> value;

    while (cin.fail())
    {
        cout << "The entered character is not a integer point number, repeat enter nuumber: ";
        cin.clear();
        cin.ignore();
        cin >> value;
    }

    return value;
}

class CPoint
{
private:
    double x;
    double y;

public:
    CPoint(double X, double Y) { x = X, y = Y; };
    CPoint(const char* strY = { "Y:=" }, const char* strX = { "\nEnter position point\nX:=" }) : CPoint(GetDouble(strY), GetDouble(strX)) {};

    double Range(CPoint);
};
double CPoint::Range(CPoint point)
{
    point.x -= x;
    point.y -= y;
    return pow(point.x * point.x + point.y * point.y, 0.5);
}

class CManipulator : CPoint
{
private:
    double R;
    int number;

public:
    CManipulator(int numbeR, int r, CPoint point) : CPoint(point), R(r), number(numbeR) {};
    CManipulator() : CManipulator(GetInt("ID:="), GetDouble("R:="), CPoint("Y:=", "\nEnter position, range and ID manipulator\nX:=")) {};

    int Number() { return number; };
    double Range(CPoint);
};
double CManipulator::Range(CPoint point)
{
    double temp = CPoint::Range(point);
    if (R < temp)
        return  INFINITY;
    else
        temp;
}

CManipulator* ChangCManipulator(CManipulator* man0, CManipulator* man1, CPoint point)
{
    if (INFINITY == man0->Range(point) && INFINITY == man1->Range(point))
        return nullptr;
    else if (man0->Range(point) > man1->Range(point))
        return man0;
    else
        return man1;
};

int main()
{
    CManipulator man0 = {};
    CManipulator man1 = {};
    CPoint point = {};

    CManipulator* choice = ChangCManipulator(&man0, &man1, point);

    if (choice)
        cout << "\nCManipulator #" << (choice == &man0 ? man0 : man1).Number() << " can do this work.";
    else
        cout << "\nNo manipulator can do this work.";
}
