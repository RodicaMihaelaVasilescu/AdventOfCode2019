#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define PART1_50X50 50
#define PART2_AREA 99

bool runInstructions(vector<long long> instructions, pair<int, int> start)
{
    long long i = 0;
    long long relativeBase = 0;
    long long inputIndex = 0;
	
	bool firstCoordinateInInput = false;
    bool secondCoordinateInInput = false;

    while (true)
    {
        long long opcode = instructions[i] % 100;

        long long firstParameterMode = instructions[i] / 100 % 10;
        long long secondParameterMode = instructions[i] / 1000 % 10;
        long long thirdParameterMode = instructions[i] / 10000;

        long long A = firstParameterMode == 1 ? i + 1 : firstParameterMode == 0 ? instructions[i + 1] : instructions[i + 1] + relativeBase;
        long long B = secondParameterMode == 1 ? i + 2 : secondParameterMode == 0 ? instructions[i + 2] : instructions[i + 2] + relativeBase;
        long long C = thirdParameterMode == 1 ? i + 3 : thirdParameterMode == 0 ? instructions[i + 3] : instructions[i + 3] + relativeBase;

        if (opcode == 1)
        {
            instructions[C] = instructions[A] + instructions[B];
            i += 4;
        }
        else if (opcode == 2)
        {
            instructions[C] = instructions[A] * instructions[B];
            i += 4;
        }
        else if (opcode == 3)
        {
            if (secondCoordinateInInput)
            {
                return false;
            }
            if (firstCoordinateInInput == false)
            {
                firstCoordinateInInput = true;
                instructions[A] = start.first;
            }
            else
            {
                secondCoordinateInInput = true;
                instructions[A] = start.second;
            }
            i += 2;
        }
        else if (opcode == 4)
        {
            return  instructions[A];
            i += 2;
        }
        else if (opcode == 5)
        {
            if (instructions[A] != 0)
            {
                i = instructions[B];
                continue;
            }
            i += 3;
        }
        else if (opcode == 6)
        {
            if (instructions[A] == 0)
            {
                i = instructions[B];
                continue;
            }
            i += 3;
        }
        else if (opcode == 7)
        {
            if (instructions[A] < instructions[B])
            {
                instructions[C] = 1;
            }
            else
            {
                instructions[C] = 0;
            }
            i += 4;
        }
        else if (opcode == 8)
        {
            if (instructions[A] == instructions[B])
            {
                instructions[C] = 1;
            }
            else
            {
                instructions[C] = 0;
            }
            i += 4;
        }
        else if (opcode == 9)
        {
            relativeBase += instructions[A];
            i += 2;
        }
        else if (opcode == 99)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void SolvePart1AndPart2(vector<long long> instructions)
{
    map<pair<int, int>, int> isBeamAtThisPosition;
    int numberOf50x50Beams = 0;

    queue<pair<int, int>> pointsOfBeam;
    /*
       "X=0, Y=0 is directly in front of the tractor beam emitter,
        so the drone control program will always report 1 at that location."
    */
    pointsOfBeam.push({ 0,0 });
    isBeamAtThisPosition[{0, 0}] = 1;

    while (true)
    {
        auto point = pointsOfBeam.front();
        pointsOfBeam.pop();

        if (point.first < PART1_50X50 && point.second < PART1_50X50)
        {
            numberOf50x50Beams++;
        }

        // search through 3x3 square of the points affected by tractor beam
        for (int i = -3; i <= 3; i++)
        {
            for (int j = 0; j <= 3; j++)
            {
                pair<int, int> neighbour = make_pair(point.first + i, point.second + j);

                if (isBeamAtThisPosition[neighbour] || point.first + i < 0 || point.second + j < 0)
                {
                    continue;
                }

                isBeamAtThisPosition[neighbour] = runInstructions(instructions, neighbour);
                if (isBeamAtThisPosition[neighbour])
                {
                    pointsOfBeam.push(neighbour);

                    // consider this neighbour to be the bottom-right corner of the 100x100 square
                    pair<int, int> bottomLeftCorner = { neighbour.first, neighbour.second - PART2_AREA };
                    pair<int, int> upperRightCorner = { neighbour.first - PART2_AREA, neighbour.second };
                    pair<int, int> upperLeftCorner = { neighbour.first - PART2_AREA, neighbour.second - PART2_AREA };
                    if (isBeamAtThisPosition[upperLeftCorner] && isBeamAtThisPosition[upperRightCorner] && isBeamAtThisPosition[bottomLeftCorner])
                    {
                        cout << "Part 1: " << numberOf50x50Beams << endl;
                        cout << "Part 2: " << (upperLeftCorner.first) * 10000 + (upperLeftCorner.second) << endl;
                        return;
                    }
                }
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<long long> instructions;
    long long number;
    char delimiter;

    while (cin >> number)
    {
        cin >> delimiter; // ',' character
        instructions.push_back(number);
    }
    instructions.resize(1000, 0);

    SolvePart1AndPart2(instructions);

    return 0;
}