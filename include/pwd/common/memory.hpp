/**
 * @file        memory.hpp
 * 
 * @brief       Functions for fast memory handling.
 * 
 * @details     This file contains utility functions for fast memory handling.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#pragma once

#include <pwd/common/includes.hpp>
#include <pwd/common/checks.hpp>



namespace pwd
{
    

template<typename T>
T* Malloc(size_t numel, size_t elsize = sizeof(T))
{
    T* ptr = (T*)std::malloc(numel * elsize);
    CheckNull(ptr);
    return ptr;
}


template<typename T>
T* Calloc(size_t numel, size_t elsize = sizeof(T))
{
    T* ptr = (T*)std::calloc(numel, elsize);
    CheckNull(ptr);
    return ptr;
}


template<typename T>
T* Realloc(T* block, size_t numel, size_t elsize = sizeof(T))
{
    T* ptr = (T*)realloc(block, numel * elsize);
    CheckNull(ptr);
    return ptr;
}


template<typename T>
T* Memset(T* block, int val, size_t numel, size_t elsize = sizeof(T))
{
    T* ptr = (T*)std::memset(block, val, numel * elsize);
    CheckNull(ptr);
    return ptr;
}


template<typename T>
T* Memcpy(T* dst, const T* const src, size_t numel, size_t elsize = sizeof(T))
{
    T* ptr = (T*)std::memcpy(dst, src, numel * elsize);
    CheckNull(ptr);
    return ptr;
}


template<typename T>
T* AllocCopy(const T* const src, size_t numel, size_t elsize = sizeof(T))
{
    T* ptr = pwd::Malloc<T>(numel, elsize);
    return pwd::Memcpy<T>(ptr, src, numel, elsize);
}



} // namespace pwd
