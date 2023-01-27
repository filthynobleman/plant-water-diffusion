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
     * @brief       Reset the IDs of the nodes in this graph.
     * 
     * @details     This method resets the IDs of the nodes in this tree-graph.\n
     *              The IDs are recomputed so that the nodes are in the same order that
     *              would be obtained by a BFS visit.
     */
    void ResetIDs();

    
};

} // namespace pwd




