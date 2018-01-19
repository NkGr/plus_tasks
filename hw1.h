#ifndef HW1_H   
#define HW1_H

class Sieve
{
public:
    Sieve(unsigned);
    ~Sieve();
    Sieve(const Sieve &) = delete;        	 // explicit ban of copy
    Sieve& operator=(const Sieve &) = delete;    // and assignment
    bool is_Prime(unsigned);
    unsigned get_nth_Prime(unsigned);
    unsigned get_size(void);
    unsigned get_max_num(void);
private:
    unsigned char *sieve_arr1_ = nullptr;            // for numbers of the form 6k - 1
    unsigned char *sieve_arr2_ = nullptr;            // for numbers of the form 6k + 1
    const unsigned ELEM_SIZE = 8;
    unsigned counter_ = 0;
    unsigned max_num_ = 0;
    unsigned asymptotics(unsigned);
    unsigned size_ = 0;
    inline unsigned char get_mask_size(unsigned);
    inline unsigned get_spot(unsigned);
}; 

void test_sieve(Sieve &);

#endif

