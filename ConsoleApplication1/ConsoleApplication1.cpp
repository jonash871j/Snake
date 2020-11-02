#include <iostream>

void Func(int* x)
{
    x += 1;
}

int main()
{
    int x = 32;
    Func(&x);


    std::cout << x;
}
