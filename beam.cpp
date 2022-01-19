#include <math.h>
#include "beam.h"
#include <iostream>

using namespace std;

double Beam::CanBeamAnal(int loadType, double L, double a, double B, double f, double f2, double x, double ei, int output)
{
    if (output == 2) return 0.0;

    a = a / L;
    x = x / L;
    B = 1 - B / L;

    if (loadType == 2 || loadType == 3)
        f = (f + f2) * L * (1 - a - B) / 2;

    if (loadType == 4)
        f = f * L * (1 - a - B);

    double b1 = -f * pow(L, 3) / ei;
    double b2 = (x - a) / (1 - a - B);
    double b3 = (1 + a - B);
    double b4;
    double Vx = 0, Mx = 0, Dx = 0;

    switch (loadType)
    {
    case 1:
        if (x < a)
        {
            Vx = f;
            Mx = -f * L * (a - x);
            Dx = -b1 * pow(x, 2) * (3 * a - x) / 6;
        }
        else
        {
            Vx = 0; Mx = 0;
            Dx = -b1 * pow(x, 2) * (3 * x - a) / 6;
        }
        break;

    case 2:   //Triangle (decrease from Left)
        b4 = (1 + 2 * a - B);
        if (x < a)
        {
            Vx = f;
            Mx = -f * L * (b4 - 3 * x) / 3;
            Dx = -b1 * pow(x, 2) / 6 * (b4 - x);
        }
        else if (x < (1 - B))
        {
            Vx = f * (1 - b2 * (2 - b2));
            Mx = -f * L * ((b4 - 3 * x) + b2 * (x - a) * (3 - b2)) / 3;
            Dx = -b1 * (10 * pow(x, 2) * (b4 - x) + b2 * pow((x - a), 4) * (5 - b2)) / 60;
        }
        else
        {
            Vx = 0; Mx = 0;
            Dx = -b1 * (a * (pow((1 - B), 2) + 10 * x * a - 3 * pow(a, 2)) - pow(b3, 2) * (b3 - 5 * x)) / 60;
        }
        break;

    case 3:   //Triangle (decrease from Right)
        b4 = (2 + a - 2 * B);
        if (x < a)
        {
            Vx = f;
            Mx = -f * L * (b4 - 3 * x) / 3;
            Dx = -b1 * pow(x, 2) * (b4 - x) / 6;
        }
        else if (x < (1 - B))
        {
            Vx = f * (1 - pow(b2, 2));
            Mx = -f * L * ((b4 - 3 * x) + pow(b2, 2) * (x - a)) / 3;
            Dx = -b1 * (10 * pow(x, 2) * (b4 - x) + (pow(b2, 2) * pow((x - a), 3))) / 60;
        }
        else
        {
            Vx = 0; Mx = 0;
            Dx = -b1 * ((1 - B) * (pow(a, 2) + 10 * x * (1 - B) - 3 * pow((1 - B), 2)) - pow(b3, 2) * (b3 - 5 * x)) / 60;
        }
        break;

    case 4:  //Uniform
        if (x < a)
        {
            Vx = f;
            Mx = -f * L * (b3 / 2 - x);
            Dx = -b1 * pow(x, 2) * (3 * b3 - 2 * x) / 12;
        }
        else if (x < (1 - B))
        {
            Vx = f * (1 - b2);
            Mx = -f * L * (b3 - 2 * x + b2 * (x - a)) / 2;
            Dx = -b1 * (6 * pow(x, 2) * (b3 - 2 * x / 3) + b2 * pow((x - a), 3)) / 24;
        }
        else
        {
            Vx = 0; Mx = 0;
            Dx = -b1 * (2 * a * (1 - B) * (b3 - 2 * x) - pow(b3, 2) * (b3 - 4 * x)) / 24;
        }
        break;
    default:
        break;
    }
    if (output == 1) return f;
    if (output == 3) return Vx;
    if (output == 4) return Mx;
    if (output == 5) return Dx;
    return 0.0;
}
