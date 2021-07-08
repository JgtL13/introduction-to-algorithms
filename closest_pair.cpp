//A program that demonstrates the closest pair problem using divide and conquer technique

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;

void sortX(int coor[999][2], int number)
{
    for(int i = 0; i < number - 1; ++i)
    {
        for(int j = 0; j < number - 1 - i; ++j)
        {
            if(coor[j][0] > coor[j +1][0])
            {
                swap(coor[j][0], coor[j +1][0]);
                swap(coor[j][1], coor[j +1][1]);
            }
        }
    }
}

void sortY(int coor[999][2], int from, int to)
{
    for(int i = from; i <= to; ++i)
    {
        for(int j = from; j <= to - i; ++j)
        {
            if(coor[j][0] > coor[j +1][0])
            {
                swap(coor[j][0], coor[j +1][0]);
                swap(coor[j][1], coor[j +1][1]);
            }
        }
    }
}

float distance(int x1, int x2, int y1, int y2)
{
    float d;
    d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return d;
}

int main()
{
    int coordinate[999][2] = {{}};
    int x, y, n = 0;
    char comma;
    ifstream infile("node.txt");
    while(infile >> x >> comma >> y)
    {
        coordinate[n][0] = x;
        coordinate[n][1] = y;
        ++n;
    }
    sortX(coordinate, n);
    float minL = 9999, minR = 9999, d;
    int minX1L, minX2L, minY1L, minY2L, minX1R, minX2R, minY1R, minY2R;
    for(int i = 0; i < n / 2; ++i)
    {
        for(int j = 0; j < n / 2; ++j)
        {
            if(i == j)
            {
                continue;
            }
            else
            {
                d = distance(coordinate[i][0], coordinate[j][0], coordinate[i][1], coordinate[j][1]);
                if(d < minL)
                {
                    minL = d;
                    minX1L = coordinate[i][0];
                    minX2L = coordinate[j][0];
                    minY1L = coordinate[i][1];
                    minY2L = coordinate[j][1];
                }
            }
        }
    }
    for(int i = n / 2; i < n; ++i)
    {
        for(int j = n / 2; j < n; ++j)
        {
            if(i == j)
            {
                continue;
            }
            else
            {
                d = distance(coordinate[i][0], coordinate[j][0], coordinate[i][1], coordinate[j][1]);
                if(d < minR)
                {
                    minR = d;
                    minX1R = coordinate[i][0];
                    minX2R = coordinate[j][0];
                    minY1R = coordinate[i][1];
                    minY2R = coordinate[j][1];
                }
            }
        }
    }
    int minimumX1, minimumX2, minimumY1, minimumY2, rangeL = n / 2, rangeR = n / 2;
    float minimum;
    if(minL <= minR)
    {
        minimum = minL;
        minimumX1 = minX1L;
        minimumX2 = minX2L;
        minimumY1 = minY1L;
        minimumY2 = minY2L;
    }
    else
    {
        minimum = minR;
        minimumX1 = minX1R;
        minimumX2 = minX2R;
        minimumY1 = minY1R;
        minimumY2 = minY2R;
    }
    for(int i = n / 2 - 1; i >= 0; --i)
    {
        if(coordinate[n / 2 - 1][0] - coordinate[i][0] > minimum)
        {
            rangeL = i + 1;
        }
    }
    for(int i = n / 2; i < n; ++i)
    {
        if(coordinate[i][0] - coordinate[n / 2][0] > minimum)
        {
            rangeR = i - 1;
        }
    }
    int minX1M, minX2M, minY1M, minY2M;
    float minM = 9999, dM;
    if(rangeL != rangeR)
    {
        sortY(coordinate, rangeL, rangeR);
        for(int i = rangeL; i <= rangeR; ++i)
        {
            for(int j = rangeL; j <= rangeR; ++j)
            {
                if(i == j)
                {
                    continue;
                }
                else
                {
                    dM = distance(coordinate[i][0], coordinate[j][0], coordinate[i][1], coordinate[j][1]);
                    if(dM < minM)
                    {
                        minM = dM;
                        minX1M = coordinate[i][0];
                        minX2M = coordinate[j][0];
                        minY1M = coordinate[i][1];
                        minY2M = coordinate[j][1];
                    }
                }
            }
        }
        if(minimum > minM)
        {
            minimum = minM;
            minimumX1 = minX1M;
            minimumX2 = minX2M;
            minimumY1 = minY1M;
            minimumY2 = minY2M;
        }
    }
    cout <<  minimumX1 << "," << minimumY1 << endl;
    cout <<  minimumX2 << "," << minimumY2 << endl;
    cout << fixed << setprecision(1) << minimum << endl;
    return 0;
}
