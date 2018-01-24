#ifndef HW1_H
#define HW1_H
// test
class Sieve
{
public:
    Sieve(unsigned);
    ~Sieve();
    Sieve(const Sieve&);
    Sieve& operator=(const Sieve&);
    Sieve(Sieve&&);
    Sieve& operator=(Sieve&&);
    bool is_Prime(unsigned);
    unsigned get_nth_Prime(unsigned);
    unsigned get_size(void) const {return size_;}
    unsigned get_max_num(void) const {return max_num_;}
private:
    unsigned char *sieve_arr1_ = nullptr;            // for numbers of the form 6k - 1
    unsigned char *sieve_arr2_ = nullptr;            // for numbers of the form 6k + 1
    const unsigned ELEM_SIZE = 8;
    unsigned counter_ = 0;
    unsigned max_num_ = 0;
    unsigned asymptotics(unsigned);
    unsigned size_ = 0;
    unsigned char get_mask_size(unsigned place) const {return ((ELEM_SIZE - 1) - (place / 6 - 1) % ELEM_SIZE);}
    unsigned get_spot(unsigned place) const {return (place / 6 - 1) / ELEM_SIZE;}
};

void test_sieve(Sieve&);

#endif

