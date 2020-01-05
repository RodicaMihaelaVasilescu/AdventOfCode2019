#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <map>
#include <numeric> 
#include <string>
#include <vector>

using namespace std;

#define ORE "ORE"
#define FUEL "FUEL"

#define ORE_CONSTANT_PART2 1000000000000

map<string, long long> outputChemicalName_coeficient;
map<string, long long> chemicalName_restQuantity;
map<string, vector<pair<long long, string>>> outputChemicalName_inputChemicals;

long long DFS(long long necessaryQuantity = 1, string chemicalName = FUEL)
{
    if (chemicalName == ORE)
    {
        return necessaryQuantity;
    }

    if (necessaryQuantity - chemicalName_restQuantity[chemicalName] >= 0)
    {
        necessaryQuantity -= chemicalName_restQuantity[chemicalName];
        chemicalName_restQuantity[chemicalName] = 0;
    }
    else
    {
        chemicalName_restQuantity[chemicalName] -= necessaryQuantity;
        necessaryQuantity = 0;
    }

    long long quantity = ceil(1.00 * necessaryQuantity / outputChemicalName_coeficient[chemicalName]);

    long long usedQuantity = outputChemicalName_coeficient[chemicalName] * quantity;
    chemicalName_restQuantity[chemicalName] += usedQuantity - necessaryQuantity;

    return  accumulate(outputChemicalName_inputChemicals[chemicalName].begin(), outputChemicalName_inputChemicals[chemicalName].end(), 0 * 1ll,
        [&](long long value, pair<long long, string> chemical) {
            return value + DFS(chemical.first * quantity, chemical.second);
        });
}

long long BinarySearch()
{
    long long left = 0;
    long long right = 10000000;
    long long middle = 0;

    while (left < right)
    {
        chemicalName_restQuantity.clear();

        middle = (left + right) / 2;
        auto ore = DFS(middle);

        if (ore < ORE_CONSTANT_PART2)
        {
            left = middle + 1;
        }
        else if (ore > ORE_CONSTANT_PART2)
        {
            right = middle - 1;
        }
        else
        {
            return middle;
        }
    }

    return middle;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    bool isNumber = true;
    long long number;
    string chemicalName;
    vector<pair<long long, string>> inputChemicals;

    string word;
    while (cin >> word)
    {
        if (word == "=>")
        {
            cin >> number >> chemicalName;
            outputChemicalName_coeficient[chemicalName] = number;
            outputChemicalName_inputChemicals[chemicalName] = inputChemicals;
            inputChemicals.clear();
        }
        else if (isNumber)
        {
            number = stoi(word);
            isNumber = false;
        }
        else if (!isNumber)
        {
            chemicalName = word;
            if (chemicalName.back() == ',')
            {
                chemicalName.pop_back();
            }
            inputChemicals.push_back({ number, chemicalName });
            isNumber = true;
        }
    }

    cout << "Part 1: " << DFS() << endl;
    cout << "Part 2: " << BinarySearch() << endl;

    return 0;
}