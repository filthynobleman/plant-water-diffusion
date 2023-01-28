/**
 * @file        graph.cpp
 * 
 * @brief       Implements pwd::Graph.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-28
 */
#include <pwd/graph/graph.hpp>
#include <pwd/common/common.hpp>
#include <pwd/utils/utils.hpp>


pwd::Graph::~Graph() { }


int pwd::Graph::NumNodes() const { return m_Nodes.size(); }

const pwd::Node* pwd::Graph::GetNode(int ID) const
{
    Assert(ID >= 0);
    Assert(ID < NumNodes());
    return m_Nodes[ID];
}
pwd::Node* pwd::Graph::GetNode(int ID)
{
    Assert(ID >= 0);
    Assert(ID < NumNodes());
    return m_Nodes[ID];
}

int pwd::Graph::GetNodeID(const pwd::Node* N) const
{
    CheckNull(N);
    Assert(std::find(m_Nodes.begin(), m_Nodes.end(), N) != m_Nodes.end());
    return m_IDs.at(N);
}

std::vector<const pwd::Node*> pwd::Graph::GetNodes() const
{
    std::vector<const pwd::Node*> Copy;
    Copy.insert(Copy.begin(), m_Nodes.begin(), m_Nodes.end());
    return Copy;
}
const std::vector<pwd::Node*>& pwd::Graph::GetNodes()
{
    return m_Nodes;
}

const pwd::Node* pwd::Graph::Root() const { return m_Root; }
pwd::Node* pwd::Graph::Root() { return m_Root; }




void pwd::Graph::AddNode(const Eigen::Vector3d& Head,
                         const Eigen::Vector3d& Tail,
                         double Radius,
                         bool IsOnLeaf)
{
    pwd::Node* NewNode = new pwd::Node(this, Head, Tail, Radius, IsOnLeaf);
    m_IDs.insert({ NewNode, m_Nodes.size() });
    m_Nodes.push_back(NewNode);
    if (NumNodes() == 1)
        m_Root = m_Nodes[0];
}



void pwd::Graph::AddConnection(int ID1, int ID2)
{
    Assert(ID1 >= 0);
    Assert(ID1 < NumNodes());
    Assert(ID2 >= 0);
    Assert(ID2 < NumNodes());
    Assert(ID1 != ID2);

    m_Nodes[ID1]->AddAdjacent(m_Nodes[ID2]);
    m_Nodes[ID2]->AddAdjacent(m_Nodes[ID1]);
}




void pwd::Graph::RecomputeHeadsAndTails(bool KeepTail)
{
    std::unordered_map<const pwd::Node*, bool> Visited;
    for (const pwd::Node* N : m_Nodes)
        Visited.insert({ N, false });

    pwd::Queue<pwd::Node*> Queue;
    Queue.Enqueue(m_Root);
    while(!Queue.IsEmpty())
    {
        pwd::Node* N = Queue.Dequeue();
        for (const pwd::Node* _Ch : N->m_Adj)
        {
            if (Visited.at(_Ch))
                continue;

            pwd::Node* Ch = GetNode(GetNodeID(_Ch));
            Eigen::Vector3d D = Ch->Direction();
            Ch->m_Head = N->m_Tail;
            if (!KeepTail)
                Ch->m_Tail = N->m_Tail + D;

            Queue.Enqueue(Ch);
        }
        Visited.at(N) = true;
    }
}








pwd::Graph::Graph(const std::string& Filename)
{
    m_Root = nullptr;

    std::ifstream Stream;
    Stream.open(Filename, std::ios::in);
    Assert(Stream.is_open());

    std::string Line;

    int NNodes;
    std::getline(Stream, Line);
    std::sscanf(Line.c_str(), "verts %d", &NNodes);
    int id;
    Eigen::Vector3d dir;
    double rad;
    int on_leaf;
    int RootID = -1;
    double OrigDist = std::numeric_limits<double>::max();
    for (int i = 0; i < NNodes; ++i)
    {
        std::getline(Stream, Line);
        int NumReads = std::sscanf(Line.c_str(), 
                                   "%d,%lf,%lf,%lf,%lf,%d", 
                                   &id,
                                   &(dir[0]), &(dir[1]), &(dir[2]),
                                   &rad,
                                   &on_leaf);
        Assert(NumReads == 6);

        AddNode(Eigen::Vector3d(0.0, 0.0, 0.0), 1e2 * dir, 1e2 * rad, on_leaf != 0);
        double NDir2 = dir.squaredNorm();
        if (NDir2 < OrigDist)
        {
            RootID = i;
            OrigDist = NDir2;
        }
    }
    m_Root = m_Nodes[RootID];


    int NEdges;
    std::getline(Stream, Line);
    std::sscanf(Line.c_str(), "edges %d", &NEdges);
    int id1, id2;
    for (int i = 0; i < NEdges; ++i)
    {
        std::getline(Stream, Line);
        int NumReads = std::sscanf(Line.c_str(), "%d,%d", &id1, &id2);
        Assert(NumReads == 2);

        AddConnection(id1, id2);
    }

    Stream.close();


    RecomputeHeadsAndTails();

}