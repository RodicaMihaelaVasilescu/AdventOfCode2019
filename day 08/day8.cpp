#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define TALL 6
#define WIDE 25

void solvePart1(string s)
{
    vector<int> frequency(3, 0);
    vector<int> minFrequency(3, 0);

    minFrequency[0] = INT_MAX;

    for (int i = 0; s[i] != 0; i++)
    {
        if (i % (WIDE * TALL) == 0 && i != 0)
        {
            if (frequency[0] < minFrequency[0])
            {
                minFrequency = frequency;
            }

            fill(frequency.begin(), frequency.end(), 0);
        }

        frequency[s[i] - '0']++;
    }

    cout << "Part 1: " << minFrequency[1] * minFrequency[2] << endl;
}

void solvePart2(string s)
{
    char a[100][100]{};

    for (int i = 0; s[i] != 0; i++)
    {
        int row = i / WIDE % TALL;
        int column = i % WIDE;
        if (a[row][column] != '0' && a[row][column] != '1')
        {
            a[row][column] = s[i];
        }
    }

    cout << "Part 2: \n";
    for (int i = 0; i < TALL; i++)
    {
        for (int j = 0; j < WIDE; j++)
        {
            printf("%c", a[i][j] == '1' ? '#' : ' ');
        }
        cout << endl;
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    string s;
    cin >> s;

    solvePart1(s);
    solvePart2(s);
}
