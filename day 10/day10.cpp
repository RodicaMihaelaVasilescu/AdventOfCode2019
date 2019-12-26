#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <map>
#include <math.h>
#include <algorithm>

using namespace std;

#define PI 3.14159265358979323846

int CountVisibileAsteroids(pair<int, int> currentAsteroid, vector<pair<int, int>> allAsteroids)
{
    int numberOfVisibleAsteroids = 0;
    map <double, bool> isAngleUsed;

    for_each(allAsteroids.begin(), allAsteroids.end(), [&](auto asteroid)
        {
            if (currentAsteroid != asteroid)
            {
                double angle = atan2(currentAsteroid.second - asteroid.second,
                    currentAsteroid.first - asteroid.first) * 180 / PI; // trigonomeric angle
                if (!isAngleUsed[angle])
                {
                    isAngleUsed[angle] = true;
                    numberOfVisibleAsteroids++;
                }
            }
        });

    return numberOfVisibleAsteroids;
}


int getThe200thIndex(pair<int, int> currentAsteroid, vector<pair<int, int>> allAsteroids)
{
    map<pair<int, int>, bool> removed;

    while (true)
    {
        map <double, bool> isAngleUsed;
        map <double, pair<int, int>> angleCoordinates;

        for_each(allAsteroids.begin(), allAsteroids.end(), [&](auto asteroid)
            {
                if (currentAsteroid != asteroid && !removed[asteroid])
                {
                    float angle = 360 - atan2(asteroid.second - currentAsteroid.second, asteroid.first -
                        currentAsteroid.first) * 180 / PI;  // clockwise angle

                    if (!isAngleUsed[angle])
                    {
                        isAngleUsed[angle] = true;
                        angleCoordinates[angle] = asteroid;
                    }
                    else
                    {
                        pair<int, int> point = angleCoordinates[angle];
                        if (abs(asteroid.first) + abs(asteroid.second) < abs(point.first) + abs(point.second))
                        {
                            angleCoordinates[angle] = asteroid;
                        }
                    }
                }
            });

        int index = 0;
        for (auto angle : angleCoordinates)
        {
            index++;
            removed[angle.second] = true;
            if (index == 200)
            {
                auto the200thIndex = angle.second;
                return the200thIndex.second * 100 + the200thIndex.first;
            }
        }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<pair<int, int>> allAsteroids;

    string inputLine;
    int lineIndex = 0;
    while (cin >> inputLine)
    {
        for (int column = 0; inputLine[column] != 0; column++)
        {
            if (inputLine[column] != '.')
            {
                allAsteroids.push_back({ lineIndex, column });
            }
        }
        lineIndex++;
    }

    int Max = INT_MIN;
    pair<int, int> monitoringStation;
    for_each(allAsteroids.begin(), allAsteroids.end(), [&](auto asteroid)
        {
            int numberOfVisibleAsteroids = CountVisibileAsteroids(asteroid, allAsteroids);
            if (numberOfVisibleAsteroids > Max)
            {
                Max = numberOfVisibleAsteroids;
                monitoringStation = asteroid;
            }
        });

    cout << "Part 1: " << Max << endl;
    cout << "Part 2: " << getThe200thIndex(monitoringStation, allAsteroids) << endl;

    return 0;
}