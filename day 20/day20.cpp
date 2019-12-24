#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stdio.h>
#include <string>
#include <map>
#include <ctype.h>

using namespace std;

#define IsAlpha(x) (x >= 'A' && x <= 'Z' ? true : false)

#define START "AA"
#define FINISH "ZZ"

#define LEFT 0
#define RIGHT 1
#define DOWN 2
#define UP 3

//             L  R  D  U  
int row[] = { 0, 0, 1, -1 };
int col[] = { -1, 1, 0, 0 };

//             R  L  U  D  
int oppositeRow[] = { 0, 0, -1, 1 };
int oppositeCol[] = { 1, -1, 0, 0 };

map <string, pair<int, int>> portalName_Coordinates;
map <pair<int, int>, pair<int, int>> teleport;

int minimumSteps = INT_MAX;

void BFS(pair<int, int > start, vector<string> maze, int step)
{
    if (step < minimumSteps && start == portalName_Coordinates[FINISH])
    {
        minimumSteps = step;
    }

    for (int direction = 0; direction < 4; direction++)
    {
        int x = start.first + row[direction];
        int y = start.second + col[direction];

        if (maze[x][y] == '.')
        {
            maze[x][y] = '*';
            if (teleport[{ x, y }] != make_pair(0, 0))
            {
                // go through portal
                BFS(teleport[{x, y}], maze, step + 2);
            }
            else
            {
                BFS({ x, y }, maze, step + 1);
            }
        }
    }
}

void setPortalNamesAndTeleports(vector<string>maze)
{
    int n = maze.size();
    int m = maze[0].size();
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            char current = maze[i][j];

            if (IsAlpha(current))
            {
                string name = "";
                pair<int, int> coordinates;

                for (int direction = 0; direction < 4; direction++)
                {
                    char neighbour = maze[i + row[direction]][j + col[direction]];
                    pair<int, int> oppositeNeighbour = { i + oppositeRow[direction],j + oppositeCol[direction] };
                    if (IsAlpha(neighbour) && maze[oppositeNeighbour.first][oppositeNeighbour.second] == '.')
                    {
                        name = row[direction] < 0 || col[direction] < 0 ?
                            string(1, neighbour) + current : string(1, current) + neighbour;

                        coordinates = oppositeNeighbour;
                    }
                }

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
    BFS(portalName_Coordinates[START], maze, 0);
    cout << "Part 1: " << minimumSteps << endl;
    return 0;
}