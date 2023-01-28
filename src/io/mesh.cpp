/**
 * @file        mesh.cpp
 * 
 * @brief       Implements mesh.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-29
 */
#include <io/mesh.hpp>
#include <io/readers.hpp>

std::string AllowedFormats[] = {
    ".obj"
};

void (*AllowedReaders[])(const std::string&, io::Mesh&) = {
    io::ReadOBJ
};

int NumAllowedFormats = 1;

io::Mesh::Mesh(const std::string& Filename)
{
    int i;
    for (i = 0; i < NumAllowedFormats; ++i)
    {
        std::string Format = AllowedFormats[i];
        if (Filename.rfind(Format) == Filename.length() - Format.length())
        {
            AllowedReaders[i](Filename, *this);
            break;
        }
    }
    if (i == NumAllowedFormats)
    {
        std::stringstream ss;
        ss << "File " << Filename << " is not in a supported format." << std::endl;
        ss << "Supported formats are the following:" << std::endl;
        for (int j = 0; j < NumAllowedFormats; ++j)
            ss << "    - " << AllowedFormats[j] << std::endl;
        throw std::runtime_error(ss.str());
    }
}





int io::Mesh::NVerts3D() const { return Verts3D.size(); }
int io::Mesh::NVertsUV() const { return VertsUV.size(); }
int io::Mesh::NNormals() const { return Normals.size(); }
int io::Mesh::NTris() const { return Verts3DTri.size(); }