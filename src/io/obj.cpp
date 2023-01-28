/**
 * @file        obj.cpp
 * 
 * @brief       Implements the routines relative to OBJ file format.
 * 
 * @details     This file contains the definition of the routines relative to
 *              I/O operations on files in OBJ format.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-29
 */
#include <io/readers.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

void io::ReadOBJ(const std::string& Filename, io::Mesh& M)
{
    std::ifstream Stream;
    Stream.open(Filename, std::ios::in);
    if (!Stream.is_open())
    {
        std::stringstream ss;
        ss << "Cannot open file " << Filename << " for reading.";
        throw std::runtime_error(ss.str());
    }


    // Read line by line
    std::string Line;
    while (true)
    {
        std::getline(Stream, Line);
        if (Line.empty())
            break;

        
        // Vertex or face information?
        if (Line[0] == 'v')
        {
            Eigen::Vector3d V;
            // Try to read the different kind of informations
            if (std::sscanf(Line.c_str(), "v %lf %lf %lf", &(V[0]), &(V[1]), &(V[2])) == 3)
                M.Verts3D.push_back(V);
            else if (std::sscanf(Line.c_str(), "vn %lf %lf %lf", &(V[0]), &(V[1]), &(V[2])) == 3)
                M.Normals.push_back(V);
            else if (std::sscanf(Line.c_str(), "vt %lf %lf", &(V[0]), &(V[1])) == 2)
                M.VertsUV.push_back(Eigen::Vector2d(V[0], V[1]));
        }
        else if (Line[0] == 'f')
        {
            // Try to read the face. A UV parametrization is mandatory
            Eigen::Vector3i T3D, T2D, TN;
            if (std::sscanf(Line.c_str(), "f %d %d %d", &(T3D[0]), &(T3D[1]), &(T3D[2])) == 3)
            {
                std::stringstream ss;
                ss << "A UV parametrization is required for this application." << std::endl
                   << "Please, provide a mesh with a texture parametrization.";
                Stream.close();
                throw std::runtime_error(ss.str());
            }
            else if (std::sscanf(Line.c_str(), "f %d//%d %d//%d %d//%d", 
                                 &(T3D[0]), &(TN[0]), 
                                 &(T3D[1]), &(TN[1]),
                                 &(T3D[2]), &(TN[2])) == 6)
            {
                std::stringstream ss;
                ss << "A UV parametrization is required for this application." << std::endl
                   << "Please, provide a mesh with a texture parametrization.";
                Stream.close();
                throw std::runtime_error(ss.str());
            }
            else if (std::sscanf(Line.c_str(), "f %d/%d %d/%d %d/%d", 
                                 &(T3D[0]), &(T2D[0]), 
                                 &(T3D[1]), &(T2D[1]),
                                 &(T3D[2]), &(T2D[2])) == 6)
            {
                M.Verts3DTri.push_back(T3D - Eigen::Vector3i(1, 1, 1));
                M.VertsUVTri.push_back(T2D - Eigen::Vector3i(1, 1, 1));
            }
            else if (std::sscanf(Line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", 
                                 &(T3D[0]), &(T2D[0]), &(TN[0]), 
                                 &(T3D[1]), &(T2D[1]), &(TN[1]),
                                 &(T3D[2]), &(T2D[2]), &(TN[2])) == 9)
            {
                M.Verts3DTri.push_back(T3D - Eigen::Vector3i(1, 1, 1));
                M.VertsUVTri.push_back(T2D - Eigen::Vector3i(1, 1, 1));
                M.NormalsTri.push_back(TN - Eigen::Vector3i(1, 1, 1));
            }
            else
            {
                std::stringstream ss;
                ss << "Reader cannot recognize this syntax for a face:" << std::endl
                   << Line << std::endl
                   << "Please, provide a OBJ file with only triangular faces and "
                   << "containing a complete texture parametrization.";
                Stream.close();
                throw std::runtime_error(ss.str());
            }
        }
    }


    // Ensure that triangulations are consistent with the number of vertices
    // 3D vertices
    int MinIdx = INT32_MAX;
    int MaxIdx = INT32_MIN;
    std::vector<Eigen::Vector3i>::const_iterator it;
    for (it = M.Verts3DTri.begin(); it != M.Verts3DTri.end(); it++)
    {
        for (int j = 0; j < 3; ++j)
        {
            MinIdx = std::min(MinIdx, (*it)[j]);
            MaxIdx = std::max(MaxIdx, (*it)[j]);
        }
    }
    assert(MinIdx == 0);
    assert(MaxIdx == M.NVerts3D() - 1);

    // 2D vertices
    MinIdx = INT32_MAX;
    MaxIdx = INT32_MIN;
    for (it = M.VertsUVTri.begin(); it != M.VertsUVTri.end(); it++)
    {
        for (int j = 0; j < 3; ++j)
        {
            MinIdx = std::min(MinIdx, (*it)[j]);
            MaxIdx = std::max(MaxIdx, (*it)[j]);
        }
    }
    assert(MinIdx == 0);
    assert(MaxIdx == M.NVertsUV() - 1);

    // Normals
    MinIdx = INT32_MAX;
    MaxIdx = INT32_MIN;
    for (it = M.NormalsTri.begin(); it != M.NormalsTri.end(); it++)
    {
        for (int j = 0; j < 3; ++j)
        {
            MinIdx = std::min(MinIdx, (*it)[j]);
            MaxIdx = std::max(MaxIdx, (*it)[j]);
        }
    }
    assert(MinIdx == 0);
    assert(MaxIdx == M.NNormals() - 1);


    // Also, must have the same amount of 3D and UV triangles
    assert(M.Verts3DTri.size() == M.VertsUVTri.size());

    // Triangulation of surface normals is either empty or must have the
    // same number of triangles of the others
    assert((M.NormalsTri.size() == 0) || (M.NormalsTri.size() == M.Verts3DTri.size()));



    Stream.close();
}