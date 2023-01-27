/**
 * @file        stacck.hpp
 * 
 * @brief       Declaration of a basic stack data structure.
 * 
 * @details     This file contains the declaration of a data structure implementing the
 *              basic functionalities of a stack.
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
 * @brief       A basic stack data structure.
 * 
 * @details     This class implements the basic functionalities of a stack.
 * 
 * @tparam T    Any type.
 */
template<typename T>
class Stack
{
private:
    /**
     * @brief       Backend of the stack.
     * 
     * @details     This vector provides the backend container for the stack.
     */
    std::vector<T> m_Data;

public:
    /**
     * @brief       Create an empty stack.
     * 
     * @details     This constructor creates an empty stack.
     */
    Stack() {}

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~Stack() {}

    /**
     * @brief       Returns the number of elements in the stack.
     * 
     * @details     This method returns the number of elements inside the stack.
     * 
     * @return size_t The number of elements in the stack.
     */
    size_t Size() const { return m_Data.size(); }

    /**
     * @brief       Checks if the stack is empty.
     * 
     * @details     This method tells if the stack is empty or has some elements inside.
     * 
     * @return true if this stack is empty.
     * @return false if this stack has some elements inside.
     */
    bool IsEmpty() const { return Size() == 0; }

    /**
     * @brief       Returns the next element to be extracted from the stack.
     * 
     * @details     This method returns a constant reference to the next element that
     *              will be extracted from the stack.\n 
     *              If the stack is empty, the method throws a pwd::AssertFailException.
     * 
     * @return const T& The next element to be extracted from the stack.
     * 
     * @throws pwd::AssertFailException if the stack is empty.
     */
    const T& Top() const 
    { 
        Assert(!IsEmpty());
        return *(m_Data.end() - 1); 
    }

    /**
     * @brief       Push an element on top of the stack.
     * 
     * @details     This method pushes an element on top of this stack.
     * 
     * @param Element   The element to be pushed on top of the stack.
     */
    void Push(T Element)
    {
        m_Data.push_back(Element);
    }

    /**
     * @brief       Pops an element from the stack.
     * 
     * @details     This method pops an element from the top of the stack.\n 
     *              The method throws a pwd::AssertFailException if the stack is empty.
     * 
     * @return T The element on top of the stack.
     * 
     * @throws pwd::AssertFailException if the stack is empty.
     */
    T Pop()
    {
        Assert(!IsEmpty());
        T Next = *(m_Data.end() - 1);
        m_Data.pop_back();
        return Next;
    }
};


} // namespace pwd
