/**
 * @file        checks.hpp
 * 
 * @brief       Macros providing fast checks.
 * 
 * @details     This file contains useful macros providing fast safety checks.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#pragma once

#include <pwd/common/exceptions.hpp>



/**
 * @brief       Not to use. Refer to the macro CODE_STRING(), instead.
 * 
 * @details     This macro results in the string representing the code instruction.\n 
 *              Notice this is an unsafe instruction which is only used internally.\n 
 *              Please, refer to the macro CODE_STRING().
 * 
 * @param x     Any instruction.
 * 
 * @warning     For internal use only. Refer to CODE_STRING() for an actaully usable
 *              macro.
 */
#define __CODE_STRING(x) #x


/**
 * @brief       Results in the string representing the instruction.
 * 
 * @details     This macro results in the restrin that represents the instruction in the
 *              code.
 * 
 * @param x     Any instruction.
 */
#define CODE_STRING(x) __CODE_STRING(x)




/**
 * @brief       Check if pointer is null and throws an exception.
 * 
 * @details     This macros checks if the given instruction evaluates to a null pointer,
 *              and in that case it throws a pwd::NullPointerException.
 * 
 * @param ptr   Any instruction that evaluates to a pointer.
 * 
 * @throws pwd::NullPointerException if <code>ptr</code> evaluates to <code>nullptr</code>.
 */
#define CheckNull(ptr)  do {                                                            \
                            if ((ptr) == nullptr)                                       \
                                throw pwd::NullPointerException(CODE_STRING(ptr),       \
                                                                __FILE__,               \
                                                                __LINE__);              \
                        } while(0)


/**
 * @brief       Check if expression is false and throws an exception.
 * 
 * @details     This macros checks if the given instruction evaluates to a false value,
 *              and in that case it throws a pwd::AssertFailException.
 * 
 * @param ptr   Any instruction that evaluates to a boolean.
 * 
 * @throws pwd::AssertFailException if <code>expr</code> evaluates to <code>false</code>.
 */
#define Assert(expr)    do {                                                            \
                            if (!(expr))                                                \
                                throw pwd::AssertFailException(CODE_STRING(expr),       \
                                                               __FILE__,                \
                                                               __LINE__);               \
                        } while(0)



