#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int run(vector<int> instructions, int noun, int verb)
{
    instructions[1] = noun;
    instructions[2] = verb;

    bool ok = true;
    for (int i = 0; i + 1 < instructions.size() && ok; i += 4)
    {
        if (instructions[i] == 1)
        {
            instructions[instructions[i + 3]] = instructions[instructions[i + 1]] + instructions[instructions[i + 2]];
        }
        else if (instructions[i] == 2)
        {
            instructions[instructions[i + 3]] = instructions[instructions[i + 1]] * instructions[instructions[i + 2]];
        }
        else if (instructions[i] == 99)
        {
            return instructions[0];
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<int> instructions;
    int x;
    char ch;

    while (cin >> x >> ch)
    {
        instructions.push_back(x);
    }

    cout << "Part 1: " << run(instructions, 12, 2) << endl;

    for (int i = 0; i <= 99; i++)
    {
        for (int j = 0; j <= 99; j++)
        {
            if (run(instructions, i, j) == 19690720)
            {
                cout << "Part 2: " << i * 100 + j << endl;
                return 0;
            }
        }
    }

    return 0;
}
