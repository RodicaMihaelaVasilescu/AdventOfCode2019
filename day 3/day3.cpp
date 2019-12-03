#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

//            R  L  U  D
int row[] = { 1,-1, 0, 0 };
int col[] = { 0, 0, 1,-1 };

int part1 = INT_MAX;
int part2 = INT_MAX;

void move(map<pair<int, int>, int>& matrix, int& x, int& y, int direction,
    int numberOfSteps, int pathID, int& currentStep)
{
    while (numberOfSteps--)
    {
        currentStep++;
        x += row[direction];
        y += col[direction];
        if (matrix[{x, y}] == 0 && pathID == 1)
        {
            matrix[{x, y}] = currentStep;
        }
        else if (matrix[{x, y}] != 0 && pathID == 2)
        {
            part1 = min(abs(x) + abs(y), part1);
            part2 = min(matrix[{x, y}] + currentStep, part2);
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    map<pair<int, int>, int> matrix;
    int pathID = 0;
    string path;

    while (getline(cin, path))
    {
        path += ',';
        pathID++;

        int x = 0, y = 0;
        int steps = 0;
        int direction = 0;
        int currentStep = 0;

        for (char character : path)
        {
            switch (character)
            {
            case 'R':
                direction = 0;
                break;
            case 'L':
                direction = 1;
                break;
            case 'U':
                direction = 2;
                break;
            case 'D':
                direction = 3;
                break;
            case ',':
                move(matrix, x, y, direction, steps, pathID, currentStep);
                steps = 0;
                break;
            default:
                steps = steps * 10 + character - '0';
                break;
            }
        }
    }

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2;
}
