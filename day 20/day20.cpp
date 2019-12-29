#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <queue>

using namespace std;

#define IsAlpha(x) (x >= 'A' && x <= 'Z' ? true : false)

#define START "AA"
#define FINISH "ZZ"

//            L  R  D  U                       R  L  U  D  
int row[] = { 0, 0, 1, -1 }, oppositeRow[] = { 0, 0, -1, 1 };
int col[] = { -1, 1, 0, 0 }, oppositeCol[] = { 1, -1, 0, 0 };

pair<int, int> startCoordinates, finishCoordinates;
map <pair<int, int>, pair<int, int>> teleport;
map<pair<int, int>, bool> isInnerPortal;

int BFS(vector<string> maze)
{
    queue<tuple<pair<int, int>, int>> coordinatesQueue; // queue of coordinates and step
    coordinatesQueue.push({ startCoordinates, 0 });

    while (!coordinatesQueue.empty())
    {
        auto coordinates = get<0>(coordinatesQueue.front());
        auto step = get<1>(coordinatesQueue.front());
        coordinatesQueue.pop();

        if (coordinates == finishCoordinates)
        {
            return step;
        }

        maze[coordinates.first][coordinates.second] = 'v'; // this location is visited
        for (int direction = 0; direction < 4; direction++)
        {
            pair<int, int> next = { coordinates.first + row[direction], coordinates.second + col[direction] };

            if (maze[next.first][next.second] == '.')
            {
                if (teleport[next] != make_pair(0, 0)) // if there is a portal
                {
                    // goes through portal
                    coordinatesQueue.push({ teleport[next], step + 2 });
                }
                else
                {
                    coordinatesQueue.push({ next, step + 1 });
                }
            }
        }
    }
}

int BFS2(vector<string> maze)
{
    // vector of mazes. the index of the vector reprezents the level
    vector<vector<string>>level_maze(30, maze); // I supposed there are maximum 30 levels

    auto initialMaze = maze;

    queue<tuple<pair<int, int>, int, int>> coordinatesQueue; // queue of coordinates, step, level
    coordinatesQueue.push({ startCoordinates, 0, 0 });

    while (!coordinatesQueue.empty())
    {
        auto coordinates = get<0>(coordinatesQueue.front());
        auto step = get<1>(coordinatesQueue.front());
        auto level = get<2>(coordinatesQueue.front());
        coordinatesQueue.pop();

        if (level < 0 || level > 29)
        {
            continue;
        }

        if (coordinates == finishCoordinates && level == 0)
        {
            return step;
        }

        level_maze[level][coordinates.first][coordinates.second] = 'v'; // this location is visited
        for (int direction = 0; direction < 4; direction++)
        {
            pair<int, int> next = { coordinates.first + row[direction], coordinates.second + col[direction] };

            if (level_maze[level][next.first][next.second] == '.')
            {
                if (teleport[next] != make_pair(0, 0)) // if there is a portal
                {
                    //goes through portal
                    coordinatesQueue.push({ teleport[next], step + 2, isInnerPortal[next] ? level + 1 : level - 1 });
                }
                else
                {
                    coordinatesQueue.push({ next ,step + 1, level });
                }
            }
        }
    }
}

void setPortalNamesAndTeleports(vector<string>input)
{
    map <string, pair<int, int>> portalName_Coordinates;
    int n = input.size();
    int m = input[0].size();

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            char current = input[i][j];
            if (IsAlpha(current))
            {
                string name = "";
                pair<int, int> coordinates;

                for (int direction = 0; direction < 4; direction++)
                {
                    char neighbour = input[i + row[direction]][j + col[direction]];
                    pair<int, int> oppositeNeighbour = { i + oppositeRow[direction],j + oppositeCol[direction] };
                    if (IsAlpha(neighbour) && input[oppositeNeighbour.first][oppositeNeighbour.second] == '.')
                    {
                        name = row[direction] < 0 || col[direction] < 0 ?
                            string(1, neighbour) + current : string(1, current) + neighbour;

                        coordinates = oppositeNeighbour;
                    }
                }

                isInnerPortal[coordinates] = coordinates.first != 2 && coordinates.first != n - 3 &&
                    coordinates.second != 2 && coordinates.second != m - 3;
                if (name == START)
                {
                    startCoordinates = coordinates;
                }
                if (name == FINISH)
                {
                    finishCoordinates = coordinates;
                }

                auto correspondingCoordinates = portalName_Coordinates[name];
                teleport[correspondingCoordinates] = coordinates;
                teleport[coordinates] = correspondingCoordinates;

                portalName_Coordinates[name] = coordinates;
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<string> maze;

    string s;
    while ((getline(cin, s)))
    {
        maze.push_back(s);
    }

    setPortalNamesAndTeleports(maze);
    cout << "Part 1: " << BFS(maze) << endl;
    cout << "Part 2: " << BFS2(maze) << endl;
    return 0;
}