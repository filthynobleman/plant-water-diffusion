/**
 * @file        node.cpp
 * 
 * @brief       Implements the class pwd::Node.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#include <pwd/graph/node.hpp>
#include <pwd/utils/utils.hpp>


pwd::Node::Node(const pwd::Graph* Graph,
                const Eigen::Vector3d& Head,
                const Eigen::Vector3d& Tail,
                double Radius,
                bool IsOnLeaf)
    : m_Graph(Graph), m_Head(Head), m_Tail(Tail),
      m_Radius(Radius), m_IsOnLeaf(IsOnLeaf)
{
    CheckNull(Graph);
    Assert((Tail - Head).norm() > 1e-16);
    Assert(Radius > 0);
}


pwd::Node::~Node() { }

const pwd::Graph *pwd::Node::Graph() const { return m_Graph; }

const Eigen::Vector3d& pwd::Node::Head() const { return m_Head; }
Eigen::Vector3d& pwd::Node::Head() { return m_Head; }

const Eigen::Vector3d& pwd::Node::Tail() const { return m_Tail; }
Eigen::Vector3d& pwd::Node::Tail() { return m_Tail; }

Eigen::Vector3d pwd::Node::Direction() const 
{ 
    return m_Tail - m_Head; 
}

Eigen::Quaterniond pwd::Node::Rotation() const
{
    return Eigen::Quaterniond::FromTwoVectors(Eigen::Vector3d(0, 1, 0), Direction());
}

double pwd::Node::Radius() const { return m_Radius; }
bool pwd::Node::IsOnLeaf() const { return m_IsOnLeaf; }

double pwd::Node::Length() const { return Direction().norm(); }
double pwd::Node::Area() const { return Length() * Radius(); }
double pwd::Node::Volume() const { return M_PI * Radius() * Radius() * Length(); }

int pwd::Node::Degree() const { return m_Adj.size(); }
const pwd::Node* pwd::Node::GetAdjacent(int i) const
{
    Assert(i >= 0);
    Assert(i < Degree());
    return m_Adj[i];
}
void pwd::Node::AddAdjacent(const pwd::Node* N)
{
    CheckNull(N);
    Assert(N->Graph() == m_Graph);
    if (std::find(m_Adj.begin(), m_Adj.end(), N) == m_Adj.end())
        m_Adj.push_back(N);
}
void pwd::Node::RemoveAdjacent(const pwd::Node* N)
{
    CheckNull(N);
    auto NPos = std::find(m_Adj.begin(), m_Adj.end(), N);
    Assert(NPos != m_Adj.end());
    m_Adj.erase(NPos);
}