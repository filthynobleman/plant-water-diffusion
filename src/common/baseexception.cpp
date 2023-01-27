/**
 * @file        baseexception.cpp
 * 
 * @brief       Implements pwd::BaseException.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#include <pwd/common/exceptions.hpp>


pwd::BaseException::BaseException(const std::string& Code,
                                  const std::string& File,
                                  int Line)
    : m_Code(Code), m_File(File), m_Line(Line)
{ }


pwd::BaseException::~BaseException() 
{ }



const char* pwd::BaseException::what() const noexcept
{
    return m_ErrMsg.c_str();
}
