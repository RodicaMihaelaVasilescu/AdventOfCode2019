#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define LEFT 0
#define RIGHT 1
#define DOWN 2
#define UP 3

vector<long long> input, output;

bool runInstructions(vector<long long> initialInstructions)
{
    static auto instructions = initialInstructions;
    static long long i = 0;
    static long long relativeBase = 0;
    static long long inputIndex = 0;

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
            if (inputIndex != input.size())
            {
                instructions[A] = input[inputIndex++];
            }
            else
            {
                return false;
            }
            i += 2;
        }
        else if (opcode == 4)
        {
            output.push_back(instructions[A]);
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
    //            L  R  D  U  
    int row[] = { 0, 1, 0, -1 };
    int col[] = { -1, 0, 1, 0 };

    map <pair<int, int>, bool> panelColors; // 0 -> black; 1 -> white
    int x = 0, y = 0, currentDirection = UP;
    int xMin = INT_MAX, yMin = INT_MAX, xMax = INT_MIN, yMax = INT_MIN;

    long long outputIndex = 0;

    panelColors[{x, y}] = true;
    input.push_back(panelColors[{x, y}]);

    while (!runInstructions(instructions))
    {
        int color = output[outputIndex++];
        int direction = output[outputIndex++];

        panelColors[{x, y}] = color;

        if (direction == LEFT) {
            currentDirection -= 3;
        }
        else if (direction == RIGHT)
        {
            currentDirection -= 1;
        }
        currentDirection += 4;
        currentDirection %= 4;

        x += row[currentDirection];
        y += col[currentDirection];

        xMin = min(x, xMin);
        yMin = min(y, yMin);
        xMax = max(x, xMax);
        yMax = max(y, yMax);

        input.push_back(panelColors[{ x, y }]);
    }
    cout << "Part 1: " << panelColors.size() << endl;

    cout << "Part 2: \n";
    for (int i = xMin; i <= xMax; i++)
    {
        for (int j = yMin; j <= yMax; j++)
        {
            printf("%c", panelColors[{i, j}] ? '#' : ' ');
        }
        printf("\n");
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

    instructions.resize(10000, 0);

    SolvePart1AndPart2(instructions);
}