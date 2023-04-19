/**
 * @file        watermodel.hpp
 * 
 * @brief       Declaration of the water diffusion model.
 * 
 * @details     This file contains the declaration of a class that implements the
 *              water diffusion model inside a plant represented with a pwd::Graph.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-28
 */
#include <pwd/common/common.hpp>
#include <pwd/utils/utils.hpp>
#include <pwd/graph/graph.hpp>




namespace pwd
{
    
/**
 * @brief       This class implements the water diffusion model.
 * 
 * @details     The class pwd::WaterModel implements the water diffusion model inside a
 *              plant.\n 
 *              The class also offers an interface for regulating the input parameters
 *              to the model.
 */
class WaterModel
{
private:
    /**
     * @brief       A constant pointer to the graph.
     * 
     * @details     This is a reference to the graph on which this water model is
     *              implemented.\n 
     *              The water model cannot modify the graph structure at any moment.
     */
    const pwd::Graph* m_Graph;

    /**
     * @brief       The initial amount of water of each node.
     * 
     * @details     This column vector contains the initial amount of water inside
     *              each node of the graph.
     */
    Eigen::VectorXd m_Water0;

    /**
     * @brief       The amount of water in each node.
     * 
     * @details     This vector contains the amount of water inside each node of the
     *              graph at the last evaluated time point.
     */
    Eigen::VectorXd m_Water;

    /**
     * @brief       Inverse of eigenvectors times the water.
     * 
     * @details     This vector contains the inverse of the eigenvector matrix,
     *              multiplied by the initial water amount.\n 
     *              Used to speed up the computation.
     */
    Eigen::VectorXcd m_Xi;

    /**
     * @brief       Support vector.
     * 
     * @details     This is a support vector for intermediate operations.
     */
    Eigen::VectorXcd m_Xi2;

    /**
     * @brief       System matrix.
     * 
     * @details     The system matrix of this model.
     */
    Eigen::MatrixXd m_S;

    /**
     * @brief       The eigenvectors of the system matrix.
     * 
     * @details     The eigenvectors of the system matrix.
     */
    Eigen::MatrixXcd m_Evecs;

    /**
     * @brief       The inverse of the eigenvectors of the system matrix.
     * 
     * @details     The inverse of the eigenvectors of the system matrix.
     */
    Eigen::MatrixXcd m_InvEvecs;

    /**
     * @brief       The eigenvalues of the system matrix.
     * 
     * @details     The eigenvalues of the system matrix.
     */
    Eigen::VectorXcd m_Evals;

    /**
     * @brief       Last evaluated time point.
     * 
     * @details     This is the last time point at which the system has been evaluated.
     */
    double m_LastTime;

    

public:
    /**
     * @brief       Initializes a water model from a graph.
     * 
     * @details     This constructor initializes a water model from an input pwd::Graph.\n 
     *              If the input graph is null, the constructor throws a
     *              pwd::NullPointerException.
     * 
     * @param Graph         The graph of which constructing the system.
     * @param LossRate      The loss rate of the leaf nodes.
     * @param InitialWater  The total amount of initial water.
     * 
     * @throws pwd::NullPointerException if <code>Graph</code> is nullptr.
     */
    WaterModel(const pwd::Graph* Graph, 
               double LossRate, 
               double InitialWater);

    /**
     * @brief       Initializes a water model with dead edges from a graph.
     * 
     * @details     This constructor initializes a water model with dead edges from an 
     *              input pwd::Graph.\n 
     *              The dead edges are edges that are not able to let water flow.\n 
     *              If the input graph is null, the constructor throws a
     *              pwd::NullPointerException.
     * 
     * @param Graph         The graph of which constructing the system.
     * @param LossRate      The loss rate of the leaf nodes.
     * @param InitialWater  The total amount of initial water.
     * @param DeadEdges     The list of dead edges.
     * 
     * @throws pwd::NullPointerException if <code>Graph</code> is nullptr.
     */
    WaterModel(const pwd::Graph* Graph, 
               double LossRate,
               double InitialWater,
               const std::vector<std::pair<int, int>>& DeadEdges);

    /**
     * @brief       Initializes a water model with dead edges from a graph.
     * 
     * @details     This constructor initializes a water model with dead edges from an 
     *              input pwd::Graph.\n 
     *              The dead edges are edges that are not able to let water flow.\n 
     *              If the input graph is null, the constructor throws a
     *              pwd::NullPointerException.
     * 
     * @param Graph         The graph of which constructing the system.
     * @param LossRates     The vector of loss rates.
     * @param InitialWater  The total amount of initial water.
     * @param DeadEdges     The list of dead edges.
     * 
     * @throws pwd::NullPointerException if <code>Graph</code> is nullptr.
     */
    WaterModel(const pwd::Graph* Graph, 
               const Eigen::VectorXd& LossRates, 
               double InitialWater,
               const std::vector<std::pair<int, int>>& DeadEdges);

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes a new pwd::WaterModel as an exact copy
     *              of the given one.
     * 
     * @param Model The pwd::WaterModel to copy.
     */
    WaterModel(const pwd::WaterModel& Model);

    /**
     * @brief       Overload of the assignment operator.
     * 
     * @details     This constructor sets this pwd::WaterModel to be an exact copy of
     *              the given one.
     * 
     * @param Model The pwd::WaterModel to copy.
     * @return pwd::WaterModel& this model after the assignment.
     */
    pwd::WaterModel& operator=(const pwd::WaterModel& Model);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~WaterModel();


    /**
     * @brief       Returns the graph.
     * 
     * @details     This method returns a pointer to the graph simulated by this model.
     * 
     * @return const pwd::Graph* the graph simulated by this model.
     */
    const pwd::Graph* GetGraph() const;


    /**
     * @brief       Get the vector of initial water.
     * 
     * @details     This method returns the vector of the initial amount of water.
     * 
     * @return const Eigen::VectorXd& the initial water.
     */
    const Eigen::VectorXd& Water0() const;

    /**
     * @brief       Get the initial water at a node.
     * 
     * @details     This method returns the initial amount of water at the i-th node.
     * 
     * @param i     The ID of a node.
     * @return double the initial amount of water at node <code>i</code>.
     */
    double Water0(int i) const;

    /**
     * @brief       Get the last evaluated water.
     * 
     * @details     This method returns the vector of water at the last evaluated 
     *              time point.
     * 
     * @return const Eigen::VectorXd& the last evaluated water.
     */
    const Eigen::VectorXd& Water() const;

    /**
     * @brief       Get the last evaluated water at a node.
     * 
     * @details     This method returns the amount of water at the last evaluated
     *              time point at the i-th node.
     * 
     * @param i     The ID of a node.
     * @return double the last evaluated water at node <code>i</code>.
     */
    double Water(int i) const;

    /**
     * @brief       Evaluates the model at given time.
     * 
     * @details     This method evaluates the water diffusion model at the given
     *              time point and updates the last evaluation time.\n 
     *              If the given time point is less than zero, the method throws a
     *              pwd::AssertFailException.
     * 
     * @param Time  The evaluation time.
     * 
     * @throws pwd::AssertFailException if <code>Time < 0.0</code>.
     */
    void Evaluate(double Time);

    /**
     * @brief       Returns the last evaluation time.
     * 
     * @details     This method returns the last time point at which the model has
     *              been evaluated.
     * 
     * @return double the last evaluation time.
     */
    double LastEvaluationTime() const;


    /**
     * @brief       Initialize a model.
     * 
     * @details     This method initializes a water diffusion model setting the given
     *              loss rate on the leaves.
     * 
     * @param LossRate      The loss rate at the leaves.
     * @param InitialWater  The total amount of initial water.
     */
    void Initialize(double LossRate,
                    double InitialWater);

    /**
     * @brief       Initialize a model with dead edges.
     * 
     * @details     This method initializes a water diffusion model with dead edges,
     *              setting the given loss rate on the leaves.\n 
     *              The dead edges are edges that are not able to let water flow.
     * 
     * @param LossRate      The loss rate at the leaves.
     * @param DeadEdges     The list of dead edges.
     * @param InitialWater  The total amount of initial water.
     */
    void Initialize(double LossRate,
                    double InitialWater, 
                    const std::vector<std::pair<int, int>>& DeadEdges);

    /**
     * @brief       Initialize a model with dead edges and custom loss rates.
     * 
     * @details     This method initializes a water diffusion model with dead edges and
     *              a node-level specified water loss rate.\n 
     *              The dead edges are edges that are not able to let water flow.
     * 
     * @param LossRates     The vector of loss rates.
     * @param DeadEdges     The list of dead edges.
     * @param InitialWater  The total amount of initial water.
     */
    void Initialize(const Eigen::VectorXd& LossRates,
                    double InitialWater, 
                    const std::vector<std::pair<int, int>>& DeadEdges);

    
    /**
     * @brief       Build the water model.
     * 
     * @details     This method builds the system matrix of the water model.
     */
    void Build();
};

} // namespace pwd
