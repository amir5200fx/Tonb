#include <iostream>
#include "random.hxx"

#define NUM_RND 10

int main()
{
    double rands[NUM_RND];
    for (int i = 0; i < NUM_RND; i++)
    {
        rands[i] = 1.0 + 0.5 * my_math::random_normal();
        std::cout << rands[i] << "\n";
    }
    return 0;
}