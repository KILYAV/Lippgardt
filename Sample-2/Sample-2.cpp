#include <iostream>

using namespace std;
using UINT = unsigned int;

double GetDouble(const char* preview)
{
    double value;
    cout << preview;
    cin >> value;

    while (cin.fail())
    {
        cout << "The entered character is not a doubleing point number, repeat enter nuumber: ";
        cin.clear();
        cin.ignore();
        cin >> value;
    }

    return value;
}
UINT GetInt(const char* preview)
{
    UINT value;
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

class CManipulator;
class CPoint
{
private:
    double x;
    double y;

public:
    CPoint(double Y, double X) { x = X, y = Y; };
    CPoint(const char* strY = { "Y:=" }, const char* strX = { "\nEnter position point\nX:=" }) : CPoint(GetDouble(strY), GetDouble(strX)) {};

    double Range(CPoint);

    friend class CManipulator;
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
    UINT ID;

public:
    CManipulator(int id, int r, CPoint point) : CPoint(point), R(r), ID(id) {};
    CManipulator() : CManipulator(GetInt("ID:="), GetDouble("R:="), CPoint("Y:=", "\nEnter position, range and ID manipulator, or press enter for a random choice\nX:=")) {};

    UINT GetID() { return ID; };

    void Move(CPoint point) { x = point.x, y = point.y; };
    void Print();

    double Range(CPoint);
};
void CManipulator::Print()
{
    cout << "\nPosition of the manipulator #" << ID << ": X:=" << x << " Y:=" << y;
}
double CManipulator::Range(CPoint point)
{
    double temp = CPoint::Range(point);
    if (R < temp)
        return  INFINITY;
    else
        temp;
}

CManipulator& ChangCManipulator(CManipulator& manipulator0, CManipulator& manipulator1, CPoint point)
{
    UINT range[2] = { manipulator0.Range(point), manipulator1.Range(point) };
    if (range[0] > range[1])
        return manipulator0;
    else
        return manipulator1;
};


constexpr UINT maxPoint = 5;

int main()
{
    CManipulator manipulator[2] = {};
    CPoint point[maxPoint] = {};

    for (UINT index = 0; index < maxPoint; index++)
    {
        ChangCManipulator(manipulator[0], manipulator[1], point[index]).Move(point[index]);
        manipulator[0].Print();
        manipulator[1].Print();
    }
}
