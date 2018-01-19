#include "hw1.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    clock_t time;
    time = clock();
    Sieve s(1000000);
    time = clock() - time;
    cout << "" << s.get_nth_Prime(1000000) << endl;
    cout << "Execution time: " << (double)time/CLOCKS_PER_SEC << endl;
    
    test_sieve(s);
    
    return 0;
}