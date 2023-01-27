/**
 * @file        queue.hpp
 * 
 * @brief       Definition of a basic queue data structure.
 * 
 * @details     This file contains the definition of a data structure implementing the
 *              basic functionalities of a queue.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#pragma once

#include <pwd/common/common.hpp>


namespace pwd
{
    

/**
 * @brief       A basic queue data structure.
 * 
 * @details     This class implements the basic functionalities of a queue.
 * 
 * @tparam T    Any type.
 */
template<typename T>
class Queue
{
private:
    /**
     * @brief       Backend of the queue.
     * 
     * @details     This vector provides the backend container for the queue.
     */
    std::vector<T> m_Data;

public:
    /**
     * @brief       Create an empty queue.
     * 
     * @details     This constructor creates an empty queue.
     */
    Queue() {}

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~Queue() {}


    /**
     * @brief       Returns the number of elements in the queue.
     * 
     * @details     This method returns the number of elements inside the queue.
     * 
     * @return size_t The number of elements in the queue.
     */
    size_t Size() const { return m_Data.size(); }

    /**
     * @brief       Checks if the queue is empty.
     * 
     * @details     This method tells if the queue is empty or has some elements inside.
     * 
     * @return true if this queue is empty.
     * @return false if this queue has some elements inside.
     */
    bool IsEmpty() const { return Size() == 0; }


    /**
     * @brief       Returns the next element to be extracted from the queue.
     * 
     * @details     This method returns a constant reference to the next element that
     *              will be extracted from the queue.\n 
     *              If the queue is empty, the method throws a pwd::AssertFailException.
     * 
     * @return const T& The next element to be extracted from the queue.
     * 
     * @throws pwd::AssertFailException if the queue is empty.
     */
    const T& Top() const 
    {
        Assert(!IsEmpty()); 
        return *(m_Data.begin()); 
    }

    /**
     * @brief       Enqueue an element in the queue.
     * 
     * @details     This method puts the given element at the end of the queue.
     * 
     * @param Element   An element to enqueue.
     */
    void Enqueue(T Element) { m_Data.push_back(Element); }


    /**
     * @brief       Dequeues an element from the queue.
     * 
     * @details     This method removes the first element from the queue and returns it.
     *              If the queue is empty, the method throws a pwd::AssertFailException.
     * 
     * @return T The element at the beginning of the queue.
     * 
     * @throws pwd::AssertFailException if the queue is empty.
     */
    T Dequeue()
    {
        Assert(!IsEmpty());
        T Next = *(m_Data.begin());
        m_Data.erase(m_Data.begin());
        return Next;
    }
};



} // namespace pwd
