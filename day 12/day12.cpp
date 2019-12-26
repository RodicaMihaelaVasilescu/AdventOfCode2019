#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string> 
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <math.h>

using namespace std;

long long lcm(long long a, long long b)
{
    long long A = a, B = b;
    long long r;
    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return 1ll * A * B / a;
}

void SolvePart1And2(vector<tuple<long long, long long, long long>> moons)
{
    int stepIndex = 0;

    vector<tuple<long long, long long, long long>> velocity(moons.size(), make_tuple(0, 0, 0));
    map<int, long long> frequency; // fr[0] - number of steps until x column repeats, etc..  

    auto moonsInitialStates = moons;
    auto initialVelocities = velocity;

    while (frequency[0] == 0 || frequency[1] == 0 || frequency[2] == 0)
    {
        stepIndex++;
        long long kineticEnergy = 0, potentialEnergy = 0, energy = 0;

        long long moonIndex = -1;
        auto moonsCopy = moons;
        for_each(moons.begin(), moons.end(), [&](auto moon)
            {
                ++moonIndex;
                for_each(moons.begin(), moons.end(), [&](auto another)
                    {
                        if (moon != another)
                        {
                            long long x = get<0>(moon) < get<0>(another) ? 1 : get<0>(moon) > get<0>(another) ? -1 : 0;
                            long long y = get<1>(moon) < get<1>(another) ? 1 : get<1>(moon) > get<1>(another) ? -1 : 0;
                            long long z = get<2>(moon) < get<2>(another) ? 1 : get<2>(moon) > get<2>(another) ? -1 : 0;

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
            cout << "Part 1: " << energy << endl;;
        }

        map<int, bool> doesCoordinateDiffer;
        for (int i = 0; i < moons.size(); i++)
        {
            if (get<0>(moons[i]) != get<0>(moonsInitialStates[i]) || get<0>(velocity[i]) != get<0>(initialVelocities[i]))
            {
                doesCoordinateDiffer[0] = true;
            }
            if (get<1>(moons[i]) != get<1>(moonsInitialStates[i]) || get<1>(velocity[i]) != get<1>(initialVelocities[i]))
            {
                doesCoordinateDiffer[1] = true;
            }
            if (get<2>(moons[i]) != get<2>(moonsInitialStates[i]) || get<2>(velocity[i]) != get<2>(initialVelocities[i]))
            {
                doesCoordinateDiffer[2] = true;
            }
        }

        for (int i = 0; i < 3; i++) // for x, y, z columns
        {
            if (!doesCoordinateDiffer[i] && frequency[i] == 0)
            {
                frequency[i] = stepIndex;
            }
        }
    }

    cout << "Part 2: " << lcm(frequency[0], lcm(frequency[1], frequency[2])) << endl;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<tuple<long long, long long, long long>> moons;
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

    SolvePart1And2(moons);

    return 0;
}