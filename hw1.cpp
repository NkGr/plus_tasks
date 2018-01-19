#include "hw1.h"
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

Sieve::Sieve(unsigned num)
{
    assert(num > 2);
    unsigned size, place = 0;
    unsigned char mask = 0;
    size = asymptotics(num);
    size_ = size;
    size = size / 6;
    sieve_arr1_ = new unsigned char[(size / ELEM_SIZE + 1)]();    // 6k - 1
    sieve_arr2_ = new unsigned char[(size / ELEM_SIZE + 1)]();    // 6k + 1
    counter_ = 2;      // 2, 3 - prime
    max_num_ = 2;
    // k bit
    for (unsigned k = 1; k < size; k++)
    {
        mask = 1 << ((ELEM_SIZE - 1) - (k - 1) % ELEM_SIZE);
	if ((sieve_arr1_[((k + (ELEM_SIZE - 1)) / ELEM_SIZE) - 1] & mask) == 0)
        {
            counter_++;
            if (counter_ == num)
            {
                max_num_ = k * 6 - 1;
                break;
            }
            place = (k * 6 - 1) * 5;
            while(((place + 1) / 6) < size)
            {
                if (place % 2 == 0 || place % 3 == 0)
                {
                    place += k * 6 - 1;
                    continue;
                }
                if ((place - 1) % 6 == 0)
		{
		    mask = 1 << get_mask_size(place - 1);
		    sieve_arr2_[get_spot(place - 1)] = sieve_arr2_[get_spot(place - 1)] | mask;
		    place += k * 6 - 1;
		    continue;
		}
                mask = 1 << get_mask_size(place + 1);	
                sieve_arr1_[get_spot(place + 1)] = sieve_arr1_[get_spot(place + 1)] | mask;
                place += k * 6 - 1;
            }
        }
        
        mask = 1 << ((ELEM_SIZE - 1) - (k - 1) % ELEM_SIZE);
        if ((sieve_arr2_[((k + (ELEM_SIZE - 1)) / ELEM_SIZE) - 1] & mask) == 0)
        {
            counter_++;
            if (counter_ == num)
            {
                max_num_ = k * 6 + 1;
                break;
            }
            place = (k * 6 + 1) * 5;
            while(((place - 1) /  6) < size)
            {
                if (place % 2 == 0 || place % 3 == 0)
                {
                    place += k * 6 + 1;
                    continue;
                }
                if ((place + 1) % 6 == 0)
		{
		    mask = 1 << get_mask_size(place + 1);
		    sieve_arr1_[get_spot(place + 1)] = sieve_arr1_[get_spot(place + 1)] | mask;
		    place += k * 6 + 1;
		    continue;
		}
                mask = 1 << get_mask_size(place - 1);
                sieve_arr2_[get_spot(place - 1)] = sieve_arr2_[get_spot(place - 1)] | mask;
                place += k * 6 + 1;
            }
        }
    }
}

Sieve::~Sieve()
{
    delete[] sieve_arr1_;
    delete[] sieve_arr2_;
}

bool Sieve::is_Prime(unsigned num)
{
    assert(num <= max_num_ && num > 0);
    unsigned char mask = 0;
    if (num == 2 || num == 3)   { /*cout << "prime" << endl;*/ return true; }
    if (num == 1 || num % 2 == 0 || num % 3 == 0)   { /*cout << "not prime" << endl;*/ return false; }
    if ((num + 1) % 6 == 0)
    {
        mask = 1 << get_mask_size(num + 1);
        if ((sieve_arr1_[(((num + 1) / 6 + (ELEM_SIZE - 1)) / ELEM_SIZE) - 1] & mask) == 0)
        {
            //cout << "prime" << endl;
            return true;
        }
        else
        {
            //cout << "not prime" << endl;
            return false;
        }
    }
    else
    {
        mask = 1 << get_mask_size(num - 1);
        if ((sieve_arr2_[(((num - 1) / 6 + (ELEM_SIZE - 1)) / ELEM_SIZE) - 1] & mask) == 0)
        {
            //cout << "prime" << endl;
            return true;
        }
        else
        {
            //cout << "not prime" << endl;
            return false;
        }
    }
}

unsigned Sieve::get_nth_Prime(unsigned num)
{
    assert( num <= counter_ && num > 0);
    if ( num == 1 ) return 2;
    if ( num == 2 ) return 3;
    if ( num == counter_ )
    {
        return max_num_;
    }
    unsigned count = 2; // 2 and 3
    unsigned char mask = 0;
    for(unsigned i = 0; i < sizeof(sieve_arr1_) / ELEM_SIZE; i++)
    {
        for(unsigned j = 0; j < ELEM_SIZE; j++)
        {
            mask = 1 << ((ELEM_SIZE - 1) - j);
            if ((sieve_arr1_[i] & mask) == 0) count++;
            if (count == num)
            {
                return (i * ELEM_SIZE + j) * 6 - 1;
            }
            if ((sieve_arr2_[i] & mask) == 0) count++;
            if (count == num)
            {
                return (i * ELEM_SIZE + j) * 6 + 1;
            }
        }
    }
    return -1;
}

unsigned Sieve::asymptotics(unsigned n)
{
    assert(n > 0);
    if (n < 6) return 17;
    unsigned p = n * (log(n) + log(log(n)));
    return p;
}

unsigned char Sieve::get_mask_size(unsigned place)
{
    return ((ELEM_SIZE - 1) - (place / 6 - 1) % ELEM_SIZE);
}

unsigned Sieve::get_spot(unsigned place)
{
    return (place / 6 - 1) / ELEM_SIZE;
}

unsigned Sieve::get_size()
{
    return size_;
}

unsigned Sieve::get_max_num()
{
    return max_num_;
}

