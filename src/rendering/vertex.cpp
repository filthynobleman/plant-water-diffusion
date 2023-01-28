/**
 * @file        vertex.cpp
 * 
 * @brief       Implements the vertex part of model.hpp.
 * 
 * @author      Filippo Maggioli\n 
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n 
 *              Sapienza, University of Rome - Department of Computer Science
 * @date        2022-10-31
 */
#include <rendering/model.hpp>


render::Vertex::Vertex(const glm::vec3& Position, const glm::vec2& UV, const glm::vec3& Normal)
    : Position(Position), UV(UV), Normal(Normal)
{ }

render::Vertex::Vertex(const render::Vertex& V)
    : Position(V.Position), UV(V.UV), Normal(V.Normal)
{ }

render::Vertex& render::Vertex::operator=(const render::Vertex& V)
{
    Position = V.Position;
    UV = V.UV;
    Normal = V.Normal;

    return *this;
}

render::Vertex::~Vertex() { }


float render::Vertex::operator[](int i) const
{
    assert(i >= 0);
    assert(i < 3);
    return Position[i];
}
float& render::Vertex::operator[](int i)
{
    assert(i >= 0);
    assert(i < 3);
    return Position[i];
}

float render::Vertex::operator()(int i) const
{
    assert(i >= 0);
    assert(i < 2);
    return UV[i];
}
float& render::Vertex::operator()(int i)
{
    assert(i >= 0);
    assert(i < 2);
    return UV[i];
}