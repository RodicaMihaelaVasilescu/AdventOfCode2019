// it takes about 4 minutes on my input... that's terrible! :'(
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define IsDoor(x) (x >= 'A' && x <= 'Z' ? true : false)
#define IsKey(x) (x >= 'a' && x <= 'z' ? true : false)

#define CLOSED_DOOR '0'
#define OPEN_DOOR '1'

//             L  R  D  U  
int row[] = { 0, 0, 1, -1 };
int col[] = { -1, 1, 0, 0 };

int numberOfAllKeys;
pair<int, int> entrance;

int SolutionPart1(vector<string> maze)
{
    // key:    pair< coordinates, doors configuration> 
    // value:  minimum number of steps
    // doors configuration: '0' = closed door, '1' = open door
    map<pair<pair<int, int>, string>, int> steps;

    queue<tuple<pair<int, int>, string>> coordinatesQueue; // coordinates, doors configuration
    coordinatesQueue.push({ entrance, string(numberOfAllKeys, CLOSED_DOOR) }); // all doors are closed

    int minSteps = INT_MAX;
    while (!coordinatesQueue.empty())
    {
        auto coordinates = get<0>(coordinatesQueue.front());
        auto doorsConfiguration = get<1>(coordinatesQueue.front());
        coordinatesQueue.pop();
        int step = steps[{coordinates, doorsConfiguration}] + 1;

        for (int direction = 0; direction < 4; direction++)
        {
            pair<int, int> nextCoordinates = { coordinates.first + row[direction], coordinates.second + col[direction] };
            char symbol = maze[nextCoordinates.first][nextCoordinates.second];

            if (symbol == '#')
            {
                continue;
            }

            if (IsDoor(symbol) && doorsConfiguration[symbol - 'A'] == CLOSED_DOOR)
            {
                //if the door is closed, continue
                continue; 
            }

            auto nextConfiguration = doorsConfiguration;

            if (IsKey(symbol))
            {
                // open the door of its corresponding key
                nextConfiguration[symbol - 'a'] = OPEN_DOOR; 
            }

            if (steps[{ nextCoordinates, nextConfiguration }] != 0)
            {
                // this configuration already has a minimum number of steps
                continue; 
            }

            steps[{ nextCoordinates, nextConfiguration }] = step;

            if (nextConfiguration == string(numberOfAllKeys, OPEN_DOOR)) // all the doors are open
            {
                minSteps = min(step, minSteps);
            }
            coordinatesQueue.push({ nextCoordinates, nextConfiguration });
        }
    }
    return minSteps;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<string> maze;
    string inputLine;

    int line = 0;
    while ((getline(cin, inputLine)))
    {
        for (int column = 0; inputLine[column] != 0; column++)
        {
            if (IsKey(inputLine[column]))
            {
                numberOfAllKeys++;
            }
            else if (inputLine[column] == '@')
            {
                entrance = { line, column };
                inputLine[column] = '.';
            }
        }
        maze.push_back(inputLine);
        line++;
    }

    cout << "Part 1: " << SolutionPart1(maze) << endl;

    return 0;
}