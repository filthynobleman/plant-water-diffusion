/**
 * @file        node.hpp
 * 
 * @brief       Declaration of a data structure represeting a graph nodes.
 * 
 * @details     This file contains the declaration of a data structure representing the
 *              nodes of a graph.
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
 * @brief       A class representing the node of a graph.
 * 
 * @details     This class represents a node inside a graph structure.\n 
 *              It offers an interface for accessing node's properties and its relations
 *              with the graph.\n 
 *              Nodes represents oriented cylinders in space, hence they have an head,
 *              a tail and a radius.
 */
class Node
{
private:
    /**
     * @brief       A pointer to the graph.
     * 
     * @details     This is a pointer to the graph containing the node.
     */
    const pwd::Graph* m_Graph;

    /**
     * @brief       The head of the node.
     * 
     * @details     This is where the head of the node is placed.
     */
    Eigen::Vector3d m_Head;

    /**
     * @brief       The tail of the node.
     * 
     * @details     This is where the tail of the node is placed.
     */
    Eigen::Vector3d m_Tail;

    /**
     * @brief       The node's radius.
     * 
     * @details     This is the radius of the cylinder represented by this node.
     */
    double m_Radius;

    /**
     * @brief       The nodes connected to this node.
     * 
     * @details     This vector contains pointers to the nodes connected to this node.
     */
    std::vector<const pwd::Node*> m_Adj;

public:
    /**
     * @brief       Create a new node inside the given graph.
     * 
     * @details     This constructor initializes a new node inside the given graph, 
     *              using the given informations.\n 
     *              Notice the node is initialized completely disconnected to any other
     *              node, and connections must be set from the graph structure.\n 
     *              If the given graph is null, the constructor will throw a
     *              pwd::NullPointerException.
     * 
     * @param Graph     The graph this node belongs to.
     * @param Head      The head of the node.
     * @param Tail      The tail of the node.
     * @param Radius    The radius of the node.
     */
    Node(pwd::Graph* Graph,
         const Eigen::Vector3d& Head,
         const Eigen::Vector3d& Tail,
         double Radius);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~Node();




    /**
     * @brief       Get the graph this node belongs to.
     * 
     * @details     This method returns a constant pointer to the graph the node
     *              belongs to.
     * 
     * @return const pwd::Graph* The graph this node belongs to.
     */
    const pwd::Graph* Graph() const;


    /**
     * @brief       Returns the node's head.
     * 
     * @details     This method returns a constant reference to the head of this node.
     * 
     * @return const Eigen::Vector3d& the head of this node.
     */
    const Eigen::Vector3d& Head() const;
    /**
     * @brief       Returns the node's head.
     * 
     * @details     This method returns a reference to the head of this node.
     * 
     * @return Eigen::Vector3d& the head of this node.
     */
    Eigen::Vector3d& Head();


    /**
     * @brief       Returns the node's tail.
     * 
     * @details     This method returns a constant reference to the tail of this node.
     * 
     * @return const Eigen::Vector3d& the tail of this node.
     */
    const Eigen::Vector3d& Tail() const;
    /**
     * @brief       Returns the node's tail.
     * 
     * @details     This method returns a reference to the tail of this node.
     * 
     * @return Eigen::Vector3d& the tail of this node.
     */
    Eigen::Vector3d& Tail();

    /**
     * @brief       Returns the direction of this node.
     * 
     * @details     This method returns the non-normalized direction vector of this node.
     * 
     * @return Eigen::Vector3d The non-normalized direction of this vector.
     */
    Eigen::Vector3d Direction() const;

    /**
     * @brief       Returns the rotation of this vector.
     * 
     * @details     This method returns the rotation that sends the vector (0, 1, 0) into
     *              the direction of this node.
     * 
     * @return Eigen::Quaterniond the rotation of this vector.
     */
    Eigen::Quaterniond Rotation() const;



    /**
     * @brief       The radius of this node.
     * 
     * @details     This method returns the radius of this node.
     * 
     * @return double the radius of this node.
     */
    double Radius() const;

    

    /**
     * @brief       Returns the length of this node.
     * 
     * @details     This method returns the length of the line connecting the head of
     *              this node to its tail. Namely
     *              \code {.cpp}
     *                  Direction().norm()
     *              \endcode
     * 
     * @return double the length of this node.
     */
    double Length() const;

    /**
     * @brief       The area section of this node.
     * 
     * @details     This method returns the area section of the cylinder represented by
     *              this node. Namely
     *              \code {.cpp}
     *                  Length() * Radius()
     *              \endcode
     * 
     * @return double the area of this node.
     */
    double Area() const;

    /**
     * @brief       The volume of this node.
     * 
     * @details     This method returns the volume of the cylinder represented by this
     *              node. Namely
     *              \code {.cpp}
     *                  pi * Radius() * Radius() * Length()
     *              \endcode
     * 
     * @return double the volume of this node.
     */
    double Volume() const;



    /**
     * @brief       Returns the degree of this node.
     * 
     * @details     This method returns the number of nodes adjacent to this node.
     * 
     * @return int the degree of this node.
     */
    int Degree() const;

    /**
     * @brief       Get the i-th adjacent node.
     * 
     * @details     This method returns the i-th node in the list of adjacency of 
     *              this node.\n 
     *              If this node has less than or equal to <code>i</code> nodes, this
     *              method throws a pwd::AssertFailException.
     * 
     * @param i     The index of the node in the adjacency list.
     * @return const pwd::Node* the i-th node in the list of adjacency.
     */
    const pwd::Node* GetAdjacent(int i) const;
};


} // namespace pwd
