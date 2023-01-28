/**
 * @file        graph.hpp
 * 
 * @brief       Declaration of a graph data structure.
 * 
 * @details     This file contains the declaration of a class representing a graph
 *              structure.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-27
 */
#pragma once

#include <pwd/common/common.hpp>
#include <pwd/graph/node.hpp>



namespace pwd
{
    
/**
 * @brief       A class representing a graph structure.
 * 
 * @details     This class represents a graph structure and exposes a set of methods for
 *              accessing the graph's properties and modifiyng it.\n 
 *              Notice that even if the structure is general, this graph actually
 *              represents a tree. Connections are undirected, the structure contains 
 *              no cycles and has a root.
 */
class Graph
{
private:
    /**
     * @brief       Vector of nodes in the graph.
     * 
     * @details     This vector contains the nodes of this graph, ordered by their ID.
     */
    std::vector<pwd::Node*> m_Nodes;

    /**
     * @brief       Map of the nodes' IDs.
     * 
     * @details     This is a map from each node pointer to its ID.\n 
     *              Basically a reverse mapping of <code>m_Nodes</code>. Formally
     *              \code {.cpp}
     *                  m_Nodes[m_IDs[N]] == N
     *                  m_IDs[m_Nodes[i]] == i
     *              \endcode
     *              for each valid node index <code>i</code> and valid node pointer
     *              <code>N</code>.
     */
    std::unordered_map<const pwd::Node*, int> m_IDs;

    /**
     * @brief       The root of the tree-graph.
     * 
     * @details     This is a pointer to the root node of this tree-graph.
     */
    pwd::Node* m_Root;




    /**
     * @brief       Add a node to this tree-graph.
     * 
     * @details     This method adds a node to this tree-graph.\n 
     *              If the tree-graph contains no node, the newly added node will be the
     *              root.\n 
     *              The newly added node is completely disconnected from the rest of the
     *              graph.
     * 
     * @param Head      The head of the node.
     * @param Tail      The tail of the node.
     * @param Radius    The radius of the node.
     * @param IsOnLeaf  If this node is on a leaf area or not.
     */
    void AddNode(const Eigen::Vector3d& Head,
                 const Eigen::Vector3d& Tail,
                 double Radius,
                 bool IsOnLeaf);

    /**
     * @brief       Creates a connection between two nodes.
     * 
     * @details     This method creates a connection in the tree-graph between the node
     *              with ID <code>ID1</code> and the node with ID <code>ID2</code>.\n 
     *              If one of the IDs does not belong to the tree-graph, the method
     *              throws a pwd::AssertFailException.\n 
     *              If ID1 == ID2 the method throws a pwd::AssertFailException.\n 
     *              If the connection already exists, the method does nothing.
     * 
     * @param ID1   The ID of the first node.
     * @param ID2   The ID of the second node.
     * 
     * @throws pwd::AssertFailException if ID1 or ID2 are not valid node IDs or ID1 = ID2.
     */
    void AddConnection(int ID1,int ID2);
    


public:
    /**
     * @brief       Load a graph from a file.
     * 
     * @details     This constructor initializes a tree-graph loading informations from
     *              a file. The file specifies the graph structure like this:
     *              \code
     *              verts num_verts
     *              id,dir_x,dir_y,dir_z,radius,is_on_leaf
     *              ...
     *              edges num_edges
     *              id_1, id_2
     *              ...
     *              \endcode
     * 
     * @param Filename  The file containing the graph structure.
     */
    Graph(const std::string& Filename);

    /**
     * @brief       Destroy the graph and deletes all the nodes from memory.
     * 
     * @details     This destructor deletes this tree-graph and all the nodes it contains
     *              from memory.
     */
    ~Graph();



    /**
     * @brief       Returns the number of nodes in the tree-graph.
     * 
     * @details     This method returns the number of nodes in this tree-graph.
     * 
     * @return int the number of nodes in the tree-graph.
     */
    int NumNodes() const;

    /**
     * @brief       Get the node with the given ID.
     * 
     * @details     This method returns the node in this tree-graph with the given ID.\n 
     *              If no node in this graph has the given ID, the method throws a
     *              pwd::AssertFailException.
     * 
     * @param ID    The ID of a node.
     * @return const pwd::Node* the node with the given ID.
     * 
     * @throws pwd::AssertFailException if no node in the graph has the given ID.
     */
    const pwd::Node* GetNode(int ID) const;
    /**
     * @brief       Get the node with the given ID.
     * 
     * @details     This method returns the node in this tree-graph with the given ID.\n 
     *              If no node in this graph has the given ID, the method throws a
     *              pwd::AssertFailException.
     * 
     * @param ID    The ID of a node.
     * @return pwd::Node* the node with the given ID.
     * 
     * @throws pwd::AssertFailException if no node in the graph has the given ID.
     */
    pwd::Node* GetNode(int ID);

    /**
     * @brief       Returns the ID of the given node.
     * 
     * @details     This method returns the ID of a given node.\n 
     *              If the node is null, the method throws a pwd::NullPointerException.\n 
     *              If the node does not belong to the tree-graph, the method throws a
     *              pwd::AssertFailException.
     * 
     * @param N     A node in the tree.
     * @return int the ID of the node.
     * 
     * @throws pwd::NullPointerException if <code>N</code> is nullptr.
     * @throws pwd::AssertFailException if <code>N</code> does not belong to the tree.
     */
    int GetNodeID(const pwd::Node* N) const;

    /**
     * @brief       Returns the vector of nodes.
     * 
     * @details     This method returns a copy of the vector of nodes
     *              contained in this tree-graph.
     * 
     * @return std::vector<const pwd::Node*> the vector of nodes.
     */
    std::vector<const pwd::Node*> GetNodes() const;
    /**
     * @brief       Returns the vector of nodes.
     * 
     * @details     This method returns a constant reference to the vector of nodes
     *              contained in this tree-graph.
     * 
     * @return const std::vector<pwd::Node*>& the vector of nodes.
     */
    const std::vector<pwd::Node*>& GetNodes();



    /**
     * @brief       Returns the root of this tree-graph.
     * 
     * @details     This method returns the root node in this tree-graph.\n 
     *              If this tree-graph contains no node, the method returns a nullptr.
     * 
     * @return const pwd::Node* the root of this tree-graph.
     */
    const pwd::Node* Root() const;
    /**
     * @brief       Returns the root of this tree-graph.
     * 
     * @details     This method returns the root node in this tree-graph.\n 
     *              If this tree-graph contains no node, the method returns a nullptr.
     * 
     * @return pwd::Node* the root of this tree-graph.
     */
    pwd::Node* Root();



    
    /**
     * 
     * @brief       Recompute head and tails of each node.
     * 
     * @details     This method recomputes head and tail of each node in the tree-graph.\n 
     *              The head and tail recomputation occurs under the assumption that each
     *              node segment is connected to its neighbour.\n 
     *              If the parameter <code>KeepTail</code> is set to true, the tail is
     *              not recomputed.
     * 
     * @param KeepTail  Decide wheter or not to recompute the tail.
     */
    void RecomputeHeadsAndTails(bool KeepTail = true);
};

} // namespace pwd




