#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using UINT = unsigned int;
using PCHAR = char*;

constexpr UINT XYZ = 3;

class CPoint
{
public:
	double x;
	double y;
	double z;

	CPoint(double X = 0, double Y = 0, double Z = 0) : x(X), y(Y), z(Z) {};
	void operator +=(CPoint point) { x += point.x, y += point.y, z += point.z; };
};

 bool GetDouble(double& value)
{
	char ch;
	while (cin.get(ch))
	{
		if ('/' < ch && ':' > ch || '-' == ch || '+' == ch)
		{
			cin.putback(ch);
			cin >> value;
			if (cin.fail())
				return false;
			else
				return true;
		}
		if (((ch | 0x20) - 'x' < XYZ) || '\n' == ch || '\t' == ch || ' ' == ch || ';' == ch)
			;
		else
			return false;
	}
	 return false;
}

int main()
{
	ifstream fin("GCODE.txt");
	cin.rdbuf(fin.rdbuf());

	CPoint point;
	double temp[] = { 0,0,0 };
	bool   stop = false;

	do {
		for (UINT index = 0; index < XYZ; index++)
			if (stop = !GetDouble(temp[index] = 0))
			{
				temp[0] = temp[1] = temp[2] = 0;
				break;
			}
		point += { temp[0], temp[1], temp[2] };
	} while (!cin.fail() && !stop);

	cout << point.x << " " << point.y << " " << point.z;
	if (!cin.fail())
		cout << "\nERROR SCRIPT";
}
