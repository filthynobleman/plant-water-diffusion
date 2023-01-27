/**
 * @file        exceptions.hpp
 * 
 * @brief       Declaration of common exceptions.
 * 
 * @details     This file contains the declaration of common exceptions used all over the
 *              project.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#pragma once

#include <pwd/common/includes.hpp>


namespace pwd
{

/**
 * @brief       Base class for custom exceptions in this project
 * 
 * @details     This class extends the <code>std::exception</code> from the standard
 *              library.\n 
 *              It provides a base class for all the custom exceptions of this project,
 *              which are supposed to provide informations about the instruction that
 *              generated the exception.
 */
class BaseException : public std::exception
{
protected:
    /**
     * @brief       The code resulting in an exception.
     * 
     * @details     The code resulting in an exception.
     */
    std::string m_Code;

    /**
     * @brief       The file where the exception has been generated.
     * 
     * @details     The file where the exception has been generated.
     */
    std::string m_File;

    /**
     * @brief       The line where the exception has been generated.
     * 
     * @details     The line where the exception has been generated.
     */
    int m_Line;

    /**
     * @brief       The resulting error message.
     * 
     * @details     The resulting error message.
     */
    std::string m_ErrMsg;


public:
    /**
     * @brief       Initialize a BaseException.
     * 
     * @details     This constructor initializes a BaseException containing all
     *              the relevant informations about the code raising the exception.
     * 
     * @param Code  The code resulting in an exception.
     * @param File  The file where the exception has been generated.
     * @param Line  The line where the exception has been generated.
     */
    BaseException(const std::string& Code, const std::string& File, int Line);

    /**
     * @brief       Default destructor.
     * 
     * 
     * @details     Default destructor.
     */
    virtual ~BaseException();


    virtual const char* what() const noexcept override;
};







    

/**
 * @brief       Exception to be called when null pointers are found.
 * 
 * @details     This class extends the class pwd::BaseException, and implements an 
 *              exception to be thrown when null pointers are detected.
 */
class NullPointerException : public pwd::BaseException
{
public:
    /**
     * @brief       Initialize a NullPointerException.
     * 
     * @details     This constructor initializes a NullPointerException containing all
     *              the relevant informations about the code raising the exception.
     * 
     * @param Code  The code resulting in a null pointer.
     * @param File  The file where the null pointer has been generated.
     * @param Line  The line where the null pointer has been generated.
     */
    NullPointerException(const std::string& Code, const std::string& File, int Line);

    /**
     * @brief       Default destructor.
     * 
     * 
     * @details     Default destructor.
     */
    virtual ~NullPointerException();\
};










/**
 * @brief       Exception to be called when an assertion fails.
 * 
 * @details     This class extends the class pwd::BaseException , and implements an 
 *              exception to be thrown when an assertion fails.
 */
class AssertFailException : public pwd::BaseException
{
public:
    /**
     * @brief       Initialize an AssertFailException.
     * 
     * @details     This constructor initializes an AssertFailException containing all
     *              the relevant informations about the code raising the exception.
     * 
     * @param Code  The code resulting in a failed assertion.
     * @param File  The file where the assertion failed.
     * @param Line  The line where the assertion failed.
     */
    AssertFailException(const std::string& Code, const std::string& File, int Line);

    /**
     * @brief       Default destructor.
     * 
     * 
     * @details     Default destructor.
     */
    virtual ~AssertFailException();
};



} // namespace pwd
