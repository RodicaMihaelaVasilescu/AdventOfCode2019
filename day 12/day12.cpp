#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string> 
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

int getIndexAfter1000Steps(vector<tuple<int, int, int>> moons)
{
    vector<tuple<int, int, int>> velocity(moons.size(), make_tuple(0, 0, 0));

    for (int stepIndex = 1; ; stepIndex++)
    {
        int kineticEnergy = 0, potentialEnergy = 0, energy = 0;

        int moonIndex = -1;
        auto moonsCopy = moons;
        for_each(moons.begin(), moons.end(), [&](auto moon)
            {
                ++moonIndex;
                for_each(moons.begin(), moons.end(), [&](auto another)
                    {
                        if (moon != another)
                        {
                            int x = get<0>(moon) < get<0>(another) ? 1 : get<0>(moon) > get<0>(another) ? -1 : 0;
                            int y = get<1>(moon) < get<1>(another) ? 1 : get<1>(moon) > get<1>(another) ? -1 : 0;
                            int z = get<2>(moon) < get<2>(another) ? 1 : get<2>(moon) > get<2>(another) ? -1 : 0;

                            get<0>(velocity[moonIndex]) += x;
                            get<1>(velocity[moonIndex]) += y;
                            get<2>(velocity[moonIndex]) += z;

                        }
                    });
                get<0>(moonsCopy[moonIndex]) += get<0>(velocity[moonIndex]);
                get<1>(moonsCopy[moonIndex]) += get<1>(velocity[moonIndex]);
                get<2>(moonsCopy[moonIndex]) += get<2>(velocity[moonIndex]);

                potentialEnergy = abs(get<0>(moons[moonIndex])) + abs(get<1>(moons[moonIndex])) + abs(get<2>(moons[moonIndex]));
                kineticEnergy = abs(get<0>(velocity[moonIndex])) + abs(get<1>(velocity[moonIndex])) + abs(get<2>(velocity[moonIndex]));
                energy += kineticEnergy * potentialEnergy;
            });
        moons = moonsCopy;

        if (stepIndex == 1000)
        {
            return energy;
        }

    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<tuple<int, int, int>> moons;
    long long number;
    char delimiter;

    string xString, yString, zString;
    while (cin >> xString >> yString >> zString)
    {
        xString = xString.substr(3, xString.size() - 4);
        yString = yString.substr(2, yString.size() - 3);
        zString = zString.substr(2, zString.size() - 3);

        moons.push_back(make_tuple(stoi(xString), stoi(yString), stoi(zString)));
    }

    cout << "Part 1: " <<getIndexAfter1000Steps(moons) <<endl;


    return 0;
}