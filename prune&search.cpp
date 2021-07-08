#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <array>
using namespace std;

int main()
{
    int ranNum[100] = {}, num[20][5] = {{}}, s1[100] = {}, s3[100] = {};
    int p, totalNum = 100, answer, select;
    srand(time(NULL));
    for(int i = 0; i < totalNum; ++i)
    {
        ranNum[i] = rand() % 1000 + 1;
    }
    cout << "Please enter the Kth largest number you would like to search for : ";
    cin >> select;
    answer = select;
    while(1)
    {
        int subset = 0;
        for(int j = 0, k = 0; k < totalNum; ++j, ++k)
        {
            if(j == 5)
            {
                j = 0;
                ++subset;
            }
            num[subset][j] = ranNum[k];
        }
        if((totalNum % 5) != 0)
        {
            for(int j = totalNum % 5; j < 5; ++j)
            {
                num[subset][j] = 9999;
            }
        }
        for(int i = 0; i <= subset; ++i)
        {
            for(int j = 0; j < 5; ++j)
            {
                for(int k = 0; k < 4 - j; ++k)
                {
                    if(num[i][k] > num[i][k + 1])
                    {
                        swap(num[i][k], num[i][k + 1]);
                    }
                }
            }
        }
        for(int i = 0; i <= subset; ++i)
        {
            for(int j = 0; j < subset - i ; ++j)
            {
                if(num[j][2] > num[j + 1][2])
                {
                    swap(num[j], num[j + 1]);
                }
            }
        }
        int countSmaller = 0, countLarger = 0;
        if(subset == 0)
        {
            p = num[0][(totalNum - 1) % 5 / 2];
        }
        else if(subset > 0)
        {
            p = num[subset / 2][2];
        }
        cout << "p : " << p << endl;
        for(int i = 0; i <= subset; ++i)
        {
            if(i < (subset + 1) / 2)
            {
                if(num[i][0] != 9999)
                {
                    s3[countSmaller] = num[i][0];
                    ++countSmaller;
                }
                if(num[i][1] != 9999)
                {
                    s3[countSmaller] = num[i][1];
                    ++countSmaller;
                }
                for(int j = 2; j < 5; ++j)
                {
                    if(num[i][j] == 9999)
                        continue;
                    else if(num[i][j] < p)
                    {
                        s3[countSmaller] = num[i][j];
                        ++countSmaller;
                    }
                    else if(num[i][j] > p)
                    {
                        s1[countLarger] = num[i][j];
                        ++countLarger;
                    }
                }
            }
            else if(i >= (subset + 1) / 2)
            {
                if(num[i][3] != 9999)
                {
                    s1[countLarger] = num[i][3];
                    ++countLarger;
                }
                if(num[i][4] != 9999)
                {
                    s1[countLarger] = num[i][4];
                    ++countLarger;
                }
                for(int j = 0; j < 3; ++j)
                {
                    if(num[i][j] == 9999)
                        continue;
                    else if(num[i][j] > p)
                    {
                        s1[countLarger] = num[i][j];
                        ++countLarger;
                    }
                    else if(num[i][j] < p)
                    {
                        s3[countSmaller] = num[i][j];
                        ++countSmaller;
                    }
                }
            }
        }
        int countEqual = totalNum - countSmaller - countLarger;
        if(countLarger >= select)
        {
            fill_n(ranNum, 100, 0);
            for(int i = 0; i < countLarger; ++i)
            {
                ranNum[i] = s1[i];
            }
            cout << "Amount of numbers deleted : " << totalNum - countLarger << endl;
            totalNum = countLarger;
        }
        else if(countLarger + countEqual >= select)
        {
            cout << endl << answer << "th largest number found : " << p << endl;
            break;
        }
        else
        {
            select = select - countLarger - countEqual;
            for(int i = 0; i < countSmaller; ++i)
            {
                ranNum[i] = s3[i];
            }
            cout << "Amount of numbers deleted : " << totalNum - countSmaller << endl;
            totalNum = countSmaller;
        }
    }
    return 0;
}
