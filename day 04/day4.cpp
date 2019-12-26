#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int first, last;
    cin >> first >> last;

    int solutionPart1 = 0;
    int solutionPart2 = 0;

    for (int number = first; number <= last; number++)
    {
        string numberToString = to_string(number) + char(CHAR_MAX);

        bool isIncreasing = true;
        bool atLeastTwoDuplicates = false;
        bool exactlyTwoDuplicates = false;

        char previous = char(CHAR_MIN);
        int lengthOfDuplicates = 1;

        for (char current : numberToString)
        {
            if (previous > current)
            {
                isIncreasing = false;
                break;
            }

            if (previous == current)
            {
                lengthOfDuplicates++;
                atLeastTwoDuplicates = true;
            }
            else
            {
                if (lengthOfDuplicates == 2)
                {
                    exactlyTwoDuplicates = true;
                }
                lengthOfDuplicates = 1;
            }
            previous = current;
        }

        if (isIncreasing)
        {
            if (atLeastTwoDuplicates)
            {
                solutionPart1++;
            }
            if (exactlyTwoDuplicates)
            {
                solutionPart2++;
            }
        }
    }

    cout << "Part 1: " << solutionPart1 << endl;
    cout << "Part 2: " << solutionPart2 << endl;
}
