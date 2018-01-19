#include "hw1.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        clock_t time;
        time = clock();
        Sieve s(atoi(argv[1]));
        Sieve s1(s);
        Sieve s2(s1);
        s2 = s1;
        time = clock() - time;
        cout << "" << s2.get_nth_Prime(atoi(argv[2])) << endl;
        cout << "Execution time: " << (double)time/CLOCKS_PER_SEC << endl;
        test_sieve(s);
    }
    else
    {
        cout << "Incorrect arguments" << endl;
        return 0;
    }

    return 0;
}
