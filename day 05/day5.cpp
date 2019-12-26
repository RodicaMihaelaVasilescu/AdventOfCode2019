#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int run(vector<int> instructions, int input)
{
    int output = 0;
	
    for (int i = 0; i + 1 < instructions.size(); )
    {
        int opcode = instructions[i] % 100;

        if (opcode == 1)
        {
            int firstParameterMode = instructions[i] / 100 % 10;
            int secondParameterMode = instructions[i] / 1000 % 10;
            // IMPORTANT: Parameters that an instruction writes to will never be in immediate mode.
            // int thirdParameterMode = instructions[i] / 10000 % 10; // WRONG
            int thirdParameterMode = 0; // 0 -> position mode; 1 -> immediate mode;

            int A = firstParameterMode ? i + 1 : instructions[i + 1];
            int B = secondParameterMode ? i + 2 : instructions[i + 2];
            int C = thirdParameterMode ? i + 3 : instructions[i + 3];

            instructions[C] = instructions[A] + instructions[B];

            i += 4;
        }
        else if (opcode == 2)
        {

            int firstParameterMode = instructions[i] / 100 % 10;
            int secondParameterMode = instructions[i] / 1000 % 10;
            // IMPORTANT: Parameters that an instruction writes to will never be in immediate mode.
            // int thirdParameterMode = instructions[i] / 10000 % 10; // WRONG
            int thirdParameterMode = 0; // 0 -> position mode; 1 -> immediate mode;

            int A = firstParameterMode ? i + 1 : instructions[i + 1];
            int B = secondParameterMode ? i + 2 : instructions[i + 2];
            int C = thirdParameterMode ? i + 3 : instructions[i + 3];

            instructions[C] = instructions[A] * instructions[B];

            i += 4;
        }
        else if (opcode == 3)
        {
            instructions[instructions[i + 1]] = input;
            i += 2;
        }
        else if (opcode == 4)
        {
            output = instructions[instructions[i + 1]];
            i += 2;
        }
        else if (opcode == 5)
        {
            int firstParameterMode = instructions[i] / 100 % 10;
            int secondParameterMode = instructions[i] / 1000 % 10;

            int A = firstParameterMode ? i + 1 : instructions[i + 1];
            int B = secondParameterMode ? i + 2 : instructions[i + 2];

            if (instructions[A] != 0)
            {
                i = instructions[B];
                continue;
            }

            i += 3;
        }
        else if (opcode == 6)
        {
            int firstParameterMode = instructions[i] / 100 % 10;
            int secondParameterMode = instructions[i] / 1000 % 10;

            int A = firstParameterMode ? i + 1 : instructions[i + 1];
            int B = secondParameterMode ? i + 2 : instructions[i + 2];

            if (instructions[A] == 0)
            {
                i = instructions[B];
                continue;
            }

            i += 3;
        }
        else if (opcode == 7)
        {
            int firstParameterMode = instructions[i] / 100 % 10;
            int secondParameterMode = instructions[i] / 1000 % 10;
            int thirdParameterMode = 0; // position mode;

            int A = firstParameterMode ? i + 1 : instructions[i + 1];
            int B = secondParameterMode ? i + 2 : instructions[i + 2];
            int C = thirdParameterMode ? i + 3 : instructions[i + 3];
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
            int firstParameterMode = instructions[i] / 100 % 10;
            int secondParameterMode = instructions[i] / 1000 % 10;
            int thirdParameterMode = 0; // position mode;

            int A = firstParameterMode ? i + 1 : instructions[i + 1];
            int B = secondParameterMode ? i + 2 : instructions[i + 2];
            int C = thirdParameterMode ? i + 3 : instructions[i + 3];

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

    vector<int> instructions;
    int number;
    char delimiter;

    while (cin >> number)
    {
        cin >> delimiter; // ',' character
        instructions.push_back(number);
    }

    cout << "Part 1: " << run(instructions, 1) << endl;
    cout << "Part 2: " << run(instructions, 5) << endl;

    return 0;
}
