/**
 * @file        readers.hpp
 * 
 * @brief       Declaration of functions for reading a mesh from file.
 * 
 * @details     This file contains the declaration of a set of functions for
 *              reading a Mesh data structure from a file.\n 
 *              Each function is responsible of handling a specific file format.\n 
 *              Currently supported formats are:
 *                  - OBJ
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-29
 */
#pragma once

#include <string>
#include <io/mesh.hpp>

namespace io
{

/**
 * @brief       Read a mesh from an OBJ file.
 * 
 * @details     This function parses a file in OBJ format and initializes the
 *              given Mesh data structure to represent the content of that file.
 * 
 * @param Filename  The OBJ file to read.
 * @param M         The Mesh data structure to initialize.
 */
void ReadOBJ(const std::string& Filename, Mesh& M);
    
} // namespace io
