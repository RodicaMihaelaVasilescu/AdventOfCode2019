#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define COM "COM"
#define YOU "YOU"
#define SANTA "SAN"

bool areYouVisted, isSantaVisited;
string  lastOrbitThatVisitedYou, lastOrbitThatVisitedSanta, lastOrbitThatVisitedBoth;
unordered_map<string, int> checksum;
unordered_map<string, set<string>>orbits;
unordered_map <string, string> PreviousOrbit_Orbit;

void DFS(string orbit)
{
    if (orbit == YOU)
    {
        areYouVisted = true;
        lastOrbitThatVisitedYou = PreviousOrbit_Orbit[orbit];
    }

    if (orbit == SANTA)
    {
        isSantaVisited = true;
        lastOrbitThatVisitedSanta = PreviousOrbit_Orbit[orbit];
    }

    int yourInitialState = areYouVisted, santasInitialState = isSantaVisited;

    for (auto currentOrbit : orbits[orbit])
    {
        checksum[currentOrbit]++; // add current direct orbit
        checksum[currentOrbit] += checksum[orbit]; // add indirect orbits
        DFS(currentOrbit);
    }

    if (isSantaVisited && areYouVisted && !santasInitialState && !yourInitialState && lastOrbitThatVisitedBoth.empty())
    {
        lastOrbitThatVisitedBoth = orbit;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    vector<string> input;

    string s;
    while ((getline(cin, s)))
    {
        int i = s.find(')');
        string a = s.substr(0, i);
        string b = s.substr(i + 1, s.length() - i + 1);

        orbits[a].insert(b);
        PreviousOrbit_Orbit[b] = a;
    }

    DFS(COM);

    cout << "Part 1: " << accumulate(checksum.begin(), checksum.end(), 0,
        [](int value, unordered_map<string, int>::value_type x)
        {
            return value + x.second;
        }) << endl;

    cout << "Part 2: "
        << checksum[lastOrbitThatVisitedSanta] + checksum[lastOrbitThatVisitedYou] -
        2 * checksum[lastOrbitThatVisitedBoth] << endl;

    return 0;
}
