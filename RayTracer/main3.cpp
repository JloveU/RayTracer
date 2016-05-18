#include <iostream>
#include <time.h>
#include <math.h>


class A
{

public:
    A()
    :num(100000000)
    ,haha(1)
    {

    }

    void a()
    {
// #pragma omp parallel for
        for (int i = 0; i < num; i++)
        {
            float b = pow((float)i + 0.1, 10);
        }
    }

private:
    unsigned num;
    int haha;
};


int main()
{
    A a;

    clock_t processStartTime = clock();
    a.a();
// #pragma omp parallel for
//     for (int i = 0; i < 100000000; i++)
//     {
//         float b = pow((float)i + 0.1, 10);
//     }
    clock_t processEndTime = clock();
    std::cout << "ÓÃÊ± " << processEndTime - processStartTime << " ms¡£" << std::endl;

    std::cin.get();

    return 0;
}
