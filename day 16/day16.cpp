// credits to Mircea D. Brasoveanu for the second part :)

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string solvePart1(string input)
{
    int nr = 100;
    while (nr--)
    {
        vector<int> pattern{ 0, 1, 0, -1 };
        string previous = input;
        input = "";
        for (int it = 1; it <= previous.size(); it++)
        {
            int index = 0;
            int sum = 0;
            for (char ch : previous)
            {
                ++index %= it * 4;
                sum += ((ch - '0') * pattern[index]) % 10;
            }
            for (int i = 0; i < pattern.size(); i += it + 1)
            {
                pattern.insert(pattern.begin() + i, pattern[i]);
            }
            input += char(abs(sum % 10) + '0');
        }
    }
    return input.substr(0, 8);
}

string solvePart2(string input)
{
    // original solution: https://github.com/denmircea/AdventOfCode2k19/blob/master/day16-2.cpp
    string initial = input;
    int offset = stoi(input.substr(0, 7));

    for (int i = 1; i < 10000; i++)
    {
        input += initial;
    }

    int middle = input.size() / 2;
    for (int phase = 1; phase <= 100; phase++)
    {
        int sum = 0;
        for_each(input.rbegin(), input.rend() - middle, [&](char& ch)
            {
                sum += ch - '0';
                ch = sum % 10 + '0';
            });
    }

    return input.substr(offset, 8);
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    string input;
    cin >> input;

    cout << "Part 1: " << solvePart1(input) << endl;
    cout << "Part 2: " << solvePart2(input) << endl;
}