#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int part1 = 0;
    int part2 = 0;
    int n;
    while (cin >> n)
    {
        part1 += n / 3 - 2;
        while (n / 3 - 2 > 0)
        {
            n = n / 3 - 2;
            part2 += n;
        }
    }
    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
}
