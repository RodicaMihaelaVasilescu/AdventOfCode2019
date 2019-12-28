#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define DECK_SIZE_PART1 10007
#define DECK_CONST_PART1 2019

#define CUT "cut"
#define NEW_STACK "new stack" 
#define INCREMENT "increment"

int SolvePart1()
{
    vector<int> deck;
    for (int i = 0; i < DECK_SIZE_PART1; i++)
    {
        deck.push_back(i);
    }
    auto initialDeck = deck;

    string inputLine;
    while ((getline(cin, inputLine)))
    {
        if (inputLine.find(NEW_STACK) != string::npos)
        {
            reverse(deck.begin(), deck.end());
        }
        else if (inputLine.find(CUT) != string::npos)
        {
            int number = stoi(inputLine.substr(3, inputLine.size() - 3));
            number += deck.size(); // for negative numbers
            number %= deck.size();
            rotate(deck.begin(), deck.begin() + number, deck.end());
        }
        else if (inputLine.find(INCREMENT) != string::npos)
        {
            int number = stoi(inputLine.substr(19, inputLine.size() - 19));
            auto incrementedDeck = initialDeck;
            for (int i = 0; i < deck.size(); i++)
            {
                incrementedDeck[i * number % deck.size()] = deck[i];
            }
            deck = incrementedDeck;
        }
    }

    return find(deck.begin(), deck.end(), DECK_CONST_PART1) - deck.begin();
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cout << "Part 1: " << SolvePart1() << endl;
}