/**
 * @file        test_commons.cpp
 * 
 * @brief       Test the common utilities.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#include <pwd/pwd.hpp>


int main(int argc, char const *argv[])
{
    // Check null pointer exception
    int ElemToPoint = 1234;
    CheckNull(&ElemToPoint);
    try
    {
        CheckNull(nullptr);
    }
    catch(const std::exception& e)
    {
        std::cout << "The following exception is expected." << std::endl;
        std::cout << e.what() << '\n';
    }

    // Check assertion exception
    Assert(ElemToPoint == 1234);
    try
    {
        Assert(false);
    }
    catch(const std::exception& e)
    {
        std::cout << "The following exception is expected." << std::endl;
        std::cout << e.what() << '\n';
    }

    
    


    const size_t NumElems = 100;
    const size_t NumElemsHalf = NumElems / 2;
    // Try allocating memory and filling
    int* Array = pwd::Malloc<int>(NumElemsHalf);
    for (int i = 0; i < NumElemsHalf; ++i)
        Array[i] = i;
    // Try reallocating and filling the remaining
    Array = pwd::Realloc<int>(Array, NumElems);
    for (int i = NumElemsHalf; i < NumElems; ++i)
        Array[i] = i;
    // Check all the elements are correct
    for (int i = 0; i < NumElems; ++i)
        Assert(Array[i] == i);

    // Try allocating a copy
    int* ArrayCopy = pwd::AllocCopy<int>(Array, NumElems);
    // Check the copy is correct
    for (int i = 0; i < NumElems; ++i)
        Assert(ArrayCopy[i] == Array[i]);

    // Try setting memory to zero
    Array = pwd::Memset<int>(Array, 0, NumElems);
    // Check everything has been zeroed out
    for (int i = 0; i < NumElems; ++i)
        Assert(Array[i] == 0);

    // Try allocating a zero array
    int* ArrayZero = pwd::Calloc<int>(NumElems);
    // Check everything has been zeroed out
    for (int i = 0; i < NumElems; ++i)
        Assert(ArrayZero[i] == 0);


    // Free heap
    free(Array);
    free(ArrayCopy);
    free(ArrayZero);


    std::cout << "Everything has been evaluated without any errors." << std::endl;
    
    return 0;
}
