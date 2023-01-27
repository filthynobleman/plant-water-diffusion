/**
 * @file        test_utils.cpp
 * 
 * @brief       Sample application for testing the utils classes.
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
    int NumElems = 10;
    if (argc > 1)
        NumElems = std::atoi(argv[1]);

    // Creating a vector of values
    std::vector<int> Vec;
    std::vector<int>::const_iterator it;
    for (int i = 0; i < NumElems; ++i)
        Vec.push_back(i);

    // Putting the elements in the queue means they will be dequeued in ascending order
    pwd::Queue<int> Queue;
    for (it = Vec.begin(); it != Vec.end(); ++it)
        Queue.Enqueue(*it);
    Assert(Queue.Size() == NumElems);
    Assert(Queue.Top() == 0);
    for (int i = 0; i < NumElems; ++i)
    {
        Assert(!Queue.IsEmpty());
        Assert(Queue.Dequeue() == i);
    }
    Assert(Queue.IsEmpty());


    // Putting the elements in the stack means they will be popped in descending order
    pwd::Stack<int> Stack;
    for (it = Vec.begin(); it != Vec.end(); ++it)
        Stack.Push(*it);
    Assert(Stack.Size() == NumElems);
    Assert(Stack.Top() == NumElems - 1);
    for (int i = NumElems - 1; i >= 0; --i)
    {
        Assert(!Stack.IsEmpty());
        Assert(Stack.Pop() == i);
    }
    Assert(Stack.IsEmpty());



    std::cout << "Everything has been evaluated without any errors." << std::endl;


    return 0;
}
