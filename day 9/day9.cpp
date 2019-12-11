#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

long long run(vector<long long> instructions, long long input)
{
    long long output = 0;
    long long relativeBase = 0;

    for (long long i = 0; i + 1 < instructions.size();)
    {
        long long opcode = instructions[i] % 100;

        long long firstParameterMode = instructions[i] / 100 % 10;
        long long secondParameterMode = instructions[i] / 1000 % 10;
        long long thirdParameterMode = instructions[i] / 10000;

        long long A = firstParameterMode ? i + 1 : instructions[i + 1];
        long long B = secondParameterMode ? i + 2 : instructions[i + 2];
        long long C = thirdParameterMode ? i + 3 : instructions[i + 3];

        if (firstParameterMode == 2)
        {
            A = instructions[i + 1] + relativeBase;
        }
        if (secondParameterMode == 2)
        {
            B = instructions[i + 2] + relativeBase;
        }
        if (thirdParameterMode == 2)
        {
            C = instructions[i + 3] + relativeBase;
        }

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
            instructions[A] = input;
            i += 2;
        }
        else if (opcode == 4)
        {
            output = instructions[A];
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
            return output;
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

    instructions.resize(10000, 0);

    cout << "Part 1: " << run(instructions, 1) << endl;
    cout << "Part 2: " << run(instructions, 2) << endl;

    return 0;
}
