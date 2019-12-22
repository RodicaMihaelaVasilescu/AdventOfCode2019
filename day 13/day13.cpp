#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

#define EMPTY 0
#define WALL 1
#define BLOCK 2
#define HORIZONTAL_PADDLE 3
#define BALL 4

#define SCORE_COORDINATES make_pair(-1,0)

vector<long long > input, output;

bool runInstructions(vector<long long> initialInstructions)
{
    static vector<long long > instructions = initialInstructions;
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
    instructions[0] = 2;
    int score = 0;
    bool isGameFinished = false;
    vector<pair<int, int>> blocks, balls, horizontalPaddle;

    do
    {
        isGameFinished = runInstructions(instructions);

        for (int outputIndex = 0; outputIndex != output.size();)
        {
            int x = output[outputIndex++];
            int y = output[outputIndex++];
            int tile = output[outputIndex++];

            if (tile == BLOCK)
            {
                blocks.push_back({ x, y });
            }
            else if (tile == HORIZONTAL_PADDLE)
            {
                horizontalPaddle.push_back({ x,y });
            }
            else if (tile == BALL)
            {
                balls.push_back({ x,y });
            }

            if (make_pair(x, y) == SCORE_COORDINATES)
            {
                score = tile;
            }
        }
        input.push_back(horizontalPaddle.back().first < balls.back().first ? 1 : horizontalPaddle.back().first > balls.back().first ? -1 : 0);
        output.clear();

    } while (!isGameFinished);

    cout << "Part 1: " << blocks.size() << endl;
    cout << "Part 2: " << score << endl;
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

    return 0;
}