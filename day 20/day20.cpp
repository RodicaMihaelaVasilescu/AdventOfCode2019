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

map <pair<int, int>, string> portalCoordinates_Name;
map <string, pair<int, int>> portalName_Coordinates;
map <pair<int, int>, pair<int, int>> teleport;
map<pair<int, int>, bool> isInnerPortal;

int BFS(vector<string> maze)
{
    queue<tuple<pair<int, int>, int>> coordinates; // queue of coordinates and step
    coordinates.push({ portalName_Coordinates[START], 0 });

    while (!coordinates.empty())
    {
        auto current = get<0>(coordinates.front());
        auto step = get<1>(coordinates.front());
        coordinates.pop();

        if (current == portalName_Coordinates[FINISH])
        {
            return step;
        }

        maze[current.first][current.second] = 'v'; // this location is visited
        for (int direction = 0; direction < 4; direction++)
        {
            pair<int, int> next = { current.first + row[direction], current.second + col[direction] };

            if (maze[next.first][next.second] == '.')
            {
                if (teleport[next] != make_pair(0, 0)) // if there is a portal
                {
                    // goes through portal
                    coordinates.push({ teleport[next], step + 2 });
                }
                else
                {
                    coordinates.push({ next, step + 1 });
                }
            }
        }
    }
}

int BFS2(vector<string> maze)
{
    // vector of mazes. index of the vector reprezents the level
    vector<vector<string>>level_maze(30, maze); // I supposed there are maximum 30 levels

    auto initialMaze = maze;

    queue<tuple<pair<int, int>, int, int>> coordinates; // queue of coordinates, step, level
    coordinates.push({ portalName_Coordinates[START], 0, 0 });

    while (!coordinates.empty())
    {
        auto current = get<0>(coordinates.front());
        auto step = get<1>(coordinates.front());
        auto level = get<2>(coordinates.front());
        coordinates.pop();

        if (level < 0 || level > 29)
        {
            continue;
        }

        if (current == portalName_Coordinates[FINISH] && level == 0)
        {
            return step;
        }

        level_maze[level][current.first][current.second] = 'v'; // this location is visited
        for (int direction = 0; direction < 4; direction++)
        {
            pair<int, int> next = { current.first + row[direction], current.second + col[direction] };

            if (level_maze[level][next.first][next.second] == '.')
            {
                if (teleport[next] != make_pair(0, 0)) // if there is a portal
                {
                    //goes through portal
                    coordinates.push({ teleport[next], step + 2, isInnerPortal[next] ? level + 1 : level - 1 });
                }
                else
                {
                    coordinates.push({ next ,step + 1, level });
                }
            }
        }
    }
}

void setPortalNamesAndTeleports(vector<string>input)
{
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
                portalCoordinates_Name[coordinates] = name;
                isInnerPortal[coordinates] = coordinates.first != 2 && coordinates.first != n - 3 &&
                    coordinates.second != 2 && coordinates.second != m - 3;
                teleport[coordinates] = portalName_Coordinates[name];
                teleport[portalName_Coordinates[name]] = coordinates;
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