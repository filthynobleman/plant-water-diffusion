/**
 * @file        nullexception.cpp
 * 
 * @brief       Implements pwd::NullPointerException.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#include <pwd/common/exceptions.hpp>



pwd::NullPointerException::NullPointerException(const std::string& Code,
                                                const std::string& File,
                                                int Line)
    : pwd::BaseException(Code, File, Line)
{
    std::stringstream ss;
    ss << "PWD_ERROR::NULL_POINTER: Null pointer detected at " << File << ':' << Line;
    ss << '.' << std::endl;
    ss << "The null pointer is evaluated from the instruction: " << Code;
    ss << std::endl;

    m_ErrMsg = ss.str();
}


pwd::NullPointerException::~NullPointerException()
{ }