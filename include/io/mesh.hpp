/**
 * @file        mesh.hpp
 * 
 * @brief       Declaration of the data structure Mesh.
 * 
 * @details     This foile contains the declaration of the data structure Mesh,
 *              which represents a triangular mesh.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-29
 */
#pragma once

#include <vector>
#include <string>
#include <Eigen/Dense>


namespace io
{

/**
 * @brief       A data structure representing a triangular mesh.
 * 
 * @details     This data structure represents a triangular mesh and contains
 *              informations about extrinsic embedding, triangulation, normals
 *              and UV parametrization.
 */
struct Mesh
{
    /**
     * @brief       Vertices of the mesh.
     * 
     * @details     This vector contains the list of vertices of the triangular mesh.\n 
     *              Each vertex is represented as a 3-dimensional vector of double
     *              precision floating point coordinates.
     */
    std::vector<Eigen::Vector3d> Verts3D;

    /**
     * @brief       Vertices of the mesh in parametric space.
     * 
     * @details     This vector contains the list of vertices of the triangular mesh
     *              in the space of UV parametrization.\n 
     *              Each vertex is represented as a 2-dimensional vector of double
     *              precision floating point coordinates.
     */
    std::vector<Eigen::Vector2d> VertsUV;

    /**
     * @brief       Normals of the mesh.
     * 
     * @details     This vector contains the list of surface normal vectors of the
     *              triangular mesh. The normals here are not necessarily associated
     *              to the vertices or the triangles. Instead, their placement is
     *              determined by the definition of the triangles.\n 
     *              Each normal is represented as a 3-dimensional vector of double
     *              precision floating point coordinates.
     */
    std::vector<Eigen::Vector3d> Normals;




    /**
     * @brief       Triangulation of 3D vertices.
     * 
     * @details     This vector contains a list of triplets of indices which 
     *              determine the triangulation of the vertices in 3D space.\n 
     *              The i-th triplet of indices indicates which vertices in 3D
     *              space forms the i-th triangle of the mesh.\n 
     *              Notice that the numbering of triangles is consistent through
     *              all the types of triangulations.
     */
    std::vector<Eigen::Vector3i> Verts3DTri;

    /**
     * @brief       Triangulation of UV vertices.
     * 
     * @details     This vector contains a list of triplets of indices which 
     *              determine the triangulation of the vertices in parametric
     *              space.\n 
     *              The i-th triplet of indices indicates which vertices in UV
     *              space forms the i-th triangle of the mesh.\n 
     *              Notice that the numbering of triangles is consistent through
     *              all the types of triangulations.
     */
    std::vector<Eigen::Vector3i> VertsUVTri;

    /**
     * @brief       Triangulation of normals.
     * 
     * @details     This vector contains a list of triplets of indices which
     *              determine the triangulation of surface normal vectors.\n 
     *              The i-th triplet of indices indicates which normal vectors
     *              must be placed at the vertices of the i-th triangle of the 
     *              mesh.\n 
     *              Notice that the numbering of triangles is consistent through
     *              all the types of triangulations.
     */
    std::vector<Eigen::Vector3i> NormalsTri;


    /**
     * @brief       Get the number of 3D vertices.
     * 
     * @details     This method returns the number of vertices in 3D space 
     *              composing this mesh.
     * 
     * @return int  Number of 3D vertices.
     */
    int NVerts3D() const;

    /**
     * @brief       Get the number of UV vertices.
     * 
     * @details     This method returns the number of vertices in parametric
     *              space composing this mesh.
     * 
     * @return int  Number of UV vertices.
     */
    int NVertsUV() const;

    /**
     * @brief       Get the number of normals.
     * 
     * @details     This method returns the number of surface normals for
     *              this mesh.
     * 
     * @return int  Number of normals.
     */
    int NNormals() const;

    /**
     * @brief       Get the number of triangles.
     * 
     * @details     This method returns the number of triangles determining
     *              the connectivity of this mesh.
     * 
     * @return int  Number of triangles.
     */
    int NTris() const;


    /**
     * @brief       Build a new Mesh object from file.
     * 
     * @details     This constructor creates a new Mesh from the given file.\n 
     *              Currently supported file formats are:
     *                  - OBJ
     * 
     * @param Filename  The path to the file containing the mesh.
     */
    Mesh(const std::string& Filename);
};

} // namespace io
