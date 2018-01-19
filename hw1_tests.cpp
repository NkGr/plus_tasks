#include "hw1.h"
#include <fstream>
#include <iostream>

using namespace std;

/*
 * In prime_sample.txt there are 
 * 669 prime numbers in range of 0-4999 
 * and
 * 319 prime numbers in range of 15485000-15489999 
 *
 */

void test_sieve(Sieve &sieve)
{
    unsigned buff = 0, counter = 0, border = 1;
    ifstream fin;
    fin.open("prime_samples.txt");
    if (!fin.is_open())
	cout << "File doesn't exist" << endl;
    else 
    {
	if (sieve.get_size() == 0) 
	{
	    cout << "Sieve is empty" << endl;
	    return;
	}
	while(!fin.eof())
	{	
	    fin >> buff;
	    if (buff > sieve.get_max_num())
		break;
	    
	    if (buff <= 4999 || buff > 15485039) 
	    {
		for(unsigned i = border; i < buff; i++)
		{
		    if (sieve.is_Prime(i)) 
		    {
			cout << "Test failed. Number " << i << " is not prime" << endl;
			counter++;
		    }
		}
	    }
	    if (buff < 4999 || buff >= 15485039) 
	    {
		border = buff + 1;
	    }
	    
	    if (!sieve.is_Prime(buff))
	    {
		cout << "Test failed. Number " << buff << " is prime" << endl; 
		counter++;
	    }
	}
	
	fin.close();
    }
    
    if (counter == 0)
	cout << endl << "All tests ran successfully" << endl;
    else
	cout << endl << "Totally " << counter << "tests have failed"  << endl;
    
    return;
}
