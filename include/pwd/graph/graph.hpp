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
    

public:
    /**
     * @brief       Create an empty graph.
     * 
     * @details     This method creates an empty tree-graph.
     */
    Graph();

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
     * @brief       Returns the vector of nodes.
     * 
     * @details     This method returns a constant reference to the vector of nodes
     *              contained in this tree-graph.
     * 
     * @return const std::vector<const pwd::Node*>& the vector of nodes.
     */
    const std::vector<const pwd::Node*>& GetNodes() const;
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
     * @param Mass      The mass of the node.
     * @param IsOnLeaf  If this node is on a leaf area or not.
     */
    void AddNode(const Eigen::Vector3d& Head,
                 const Eigen::Vector3d& Tail,
                 double Radius,
                 double Mass,
                 bool IsOnLeaf);

    /**
     * @brief       Creates a connection between two nodes.
     * 
     * @details     This method creates a connection in the tree-graph between the node
     *              with ID <code>ID1</code> and the node with ID <code>ID2</code>.\n 
     *              If one of the IDs does not belong to the tree-graph, the method
     *              throws a pwd::AssertFailException.
     * 
     * @param ID1   The ID of the first node.
     * @param ID2   The ID of the second node.
     * 
     * @throws pwd::AssertFailException if ID1 or ID2 are not valid node IDs.
     */
    void AddConnection(int ID1,int ID2);

    /**
     * @brief       Remove a node from the tree-graph.
     * 
     * @details     This method removes a node from the tree and recompute the 
     *              connections.\n 
     *              Removing a node forces the recomputation of heads and tails.\n 
     *              If the node does not belong to the tree, the method throws a
     *              pwd::AssertFailException.
     * 
     * @param ID    The ID of the node to remove.
     * 
     * @throws pwd::AssertFailException if ID is not a valid node ID.
     */
    void RemoveNode(int ID);

    /**
     * @brief       Removes a connection from the tree-graph.
     * 
     * @details     This method removes from the tree-graph the connection between the
     *              nodes with IDs <code>ID1</code> and <code>ID2</code>.\n
     *              Removing a connection <b>does not</b> force the recomputation of
     *              heads and tails.\n 
     *              If one between the two nodes does not belong to the tree, the
     *              method throws a pwd::AssertFailException.
     * 
     * @param ID1   The ID of the first node.
     * @param ID2   The ID of the second node.
     * 
     * @throws pwd::AssertFailException if ID1 or ID2 are not valid node IDs.
     */
    void RemoveConnection(int ID1, int ID2);

    


    /**
     * @brief       Reset the IDs of the nodes in this graph.
     * 
     * @details     This method resets the IDs of the nodes in this tree-graph.\n
     *              The IDs are recomputed so that the nodes are in the same order that
     *              would be obtained by a BFS visit.
     */
    void ResetIDs();


    /**
     * @brief       Recompute head and tails of each node.
     * 
     * @details     This method recomputes head and tail of each node in the tree-graph.\n 
     *              The head and tail recomputation occurs under the assumption that each
     *              node segment is connected to its neighbour.
     */
    void RecomputeHeadsAndTails();


};

} // namespace pwd




