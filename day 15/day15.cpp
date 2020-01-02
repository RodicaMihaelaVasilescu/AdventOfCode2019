#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

//             N   S  W   E
int row[4] = { -1, 1, 0 , 0 };
int col[4] = { 0, 0, -1 , 1 };

vector<int> input, output;
int outputIndex = 0, inputIndex = 0;

bool runInstructions(vector<long long>& instructions)
{
    long long i = 0;
    long long relativeBase = 0;

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

map<pair<int, int>, int> getOxygenSystemMap(vector<long long> instructions, pair<int, int>& start)
{
    map<pair<int, int>, int> oxygenSystemMap;

    // Queue of coordinates, instructions, step
    queue<tuple< pair<int, int>, vector<long long>, int>>coordinatesQueue;
    coordinatesQueue.push({ {0, 0}, instructions, 0 });

    while (!coordinatesQueue.empty())
    {
        auto currentCoordinates = get<0>(coordinatesQueue.front());
        auto currentInstructions = get<1>(coordinatesQueue.front());
        auto step = get<2>(coordinatesQueue.front()) + 1;
        coordinatesQueue.pop();

        // Only four movement commands are understood: north (1), south (2), west (3), and east (4)
        for (int movementCommand = 0; movementCommand < 4; movementCommand++)
        {
            pair<int, int> next = { currentCoordinates.first + row[movementCommand],
                currentCoordinates.second + col[movementCommand] };

            if (oxygenSystemMap[next] != 0)
            {
                continue;
            }

            auto nextInstructions = currentInstructions;

            input.push_back(movementCommand + 1);
            runInstructions(nextInstructions);

            int status = output[outputIndex++];

            if (status == 1)
            {
                oxygenSystemMap[next] = 1; // '.'
                coordinatesQueue.push({ next, nextInstructions, step });
            }
            else if (status == 0)
            {
                oxygenSystemMap[next] = -1; // '#'
            }
            else if (status == 2)
            {
                cout << "Part 1: " << step << endl;
                start = next;
            }
        }
    }

    return oxygenSystemMap;
}

int getMinutesToFillWithOxygen(map<pair<int, int>, int> oxygenSystemMap, pair<int, int> start)
{
    queue<pair<int, int>>coordinatesQueue;
    coordinatesQueue.push(start);

    int minutesToFillWithOxygen = 0;

    while (!coordinatesQueue.empty())
    {
        auto current = coordinatesQueue.front();
        coordinatesQueue.pop();

        minutesToFillWithOxygen = max(minutesToFillWithOxygen, oxygenSystemMap[current]);

        for (int direction = 0; direction < 4; direction++)
        {
            pair<int, int> next = { current.first + row[direction],
                current.second + col[direction] };

            if (oxygenSystemMap[next] == 1)
            {
                oxygenSystemMap[next] = oxygenSystemMap[current] + 1; // visited
                coordinatesQueue.push(next);
            }
        }
    }

    return minutesToFillWithOxygen;
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

    pair<int, int> start;

    auto oxygenSystemMap = getOxygenSystemMap(instructions, start);
    cout << "Part 2: " << getMinutesToFillWithOxygen(oxygenSystemMap, start) << endl;

    return 0;
}