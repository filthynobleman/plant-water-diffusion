/**
 * @file        nullexception.cpp
 * 
 * @brief       Implements pwd::AssertFailException.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#include <pwd/common/exceptions.hpp>



pwd::AssertFailException::AssertFailException(const std::string& Code,
                                              const std::string& File,
                                              int Line)
    : pwd::BaseException(Code, File, Line)
{
    std::stringstream ss;
    ss << "PWD_ERROR::ASSERTION_FAILED: Assertion failed at " << File << ':' << Line;
    ss << '.' << std::endl;
    ss << "The false statement is evaluated from the instruction: " << Code;
    ss << std::endl;

    m_ErrMsg = ss.str();
}


pwd::AssertFailException::~AssertFailException()
{ }