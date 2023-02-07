/**
 * @file        watermodel.cpp
 * 
 * @brief       Implements pwd::WaterModel.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-28
 */
#include <pwd/watermodel.hpp>


// #define GAS_CONST               8.31446261815324
// #define GRAMS2MOL(grams)        ((grams) * 0.05550929780738273660838190396891)
// #define PRESSURE(w, v)          (GAS_CONST * GRAMS2MOL(w) * 25.0) / (v)
#define PRESS_CONST             11.538249539485484318623369414376


namespace std {
template <> struct hash<std::pair<int, int>> {
    inline size_t operator()(const std::pair<int, int> &v) const {
        std::hash<int> int_hasher;
        return int_hasher(v.first) ^ int_hasher(v.second);
    }
};
}


pwd::WaterModel::WaterModel(const pwd::Graph* Graph, 
                            double LossRate,
                            double InitialWater)
    : m_Graph(Graph), m_LastTime(0.0)
{
    Initialize(LossRate, InitialWater);
}

pwd::WaterModel::WaterModel(const pwd::Graph* Graph, 
                            double LossRate,
                            double InitialWater, 
                            const std::vector<std::pair<int, int>>& DeadEdges)
    : m_Graph(Graph), m_LastTime(0.0)
{
    Initialize(LossRate, InitialWater, DeadEdges);
}

pwd::WaterModel::WaterModel(const pwd::Graph* Graph, 
                            const Eigen::VectorXd& LossRates,
                            double InitialWater, 
                            const std::vector<std::pair<int, int>>& DeadEdges)
    : m_Graph(Graph), m_LastTime(0.0)
{
    Initialize(LossRates, InitialWater, DeadEdges);
}

pwd::WaterModel::WaterModel(const pwd::WaterModel& Model)
{
    m_Graph = Model.m_Graph;
    m_LastTime = Model.m_LastTime;
    m_Water0 = Model.m_Water0;
    m_Water = Model.m_Water;
    m_Evecs = Model.m_Evecs;
    m_Evals = Model.m_Evals;
    m_InvEvecs = Model.m_InvEvecs;
}

pwd::WaterModel& pwd::WaterModel::operator=(const pwd::WaterModel& Model)
{
    m_Graph = Model.m_Graph;
    m_LastTime = Model.m_LastTime;
    m_Water0 = Model.m_Water0;
    m_Water = Model.m_Water;
    m_Evecs = Model.m_Evecs;
    m_Evals = Model.m_Evals;
    m_InvEvecs = Model.m_InvEvecs;

    return *this;
}

pwd::WaterModel::~WaterModel() { }

const pwd::Graph* pwd::WaterModel::GetGraph() const { return m_Graph; }

const Eigen::VectorXd& pwd::WaterModel::Water0() const { return m_Water0; }
double pwd::WaterModel::Water0(int i) const { return m_Water0[i]; }

const Eigen::VectorXd& pwd::WaterModel::Water() const { return m_Water; }
double pwd::WaterModel::Water(int i) const { return m_Water[i]; }

void pwd::WaterModel::Evaluate(double Time)
{
    Assert(Time >= 0.0);

    m_LastTime = Time;
    Eigen::VectorXcd Xi = m_InvEvecs * m_Water0;
    for (int i = 0; i < Xi.size(); ++i)
        Xi[i] *= std::exp(m_Evals[i] * m_LastTime);
    m_Water = (m_Evecs * Xi).real();
}

double pwd::WaterModel::LastEvaluationTime() const { return m_LastTime; }

void pwd::WaterModel::Initialize(double LossRate,
                                 double InitialWater)
{
    Eigen::VectorXd LossRates;
    LossRates.resize(m_Graph->NumNodes());
    for (int i = 0; i < m_Graph->NumNodes(); ++i)
        LossRates[i] = m_Graph->GetNode(i)->IsOnLeaf() ? LossRate : 0.0;
    Initialize(LossRates, InitialWater, { });
}

void pwd::WaterModel::Initialize(double LossRate,
                                 double InitialWater,
                                 const std::vector<std::pair<int, int>>& DeadEdges)
{
    Eigen::VectorXd LossRates;
    LossRates.resize(m_Graph->NumNodes());
    for (int i = 0; i < m_Graph->NumNodes(); ++i)
        LossRates[i] = m_Graph->GetNode(i)->IsOnLeaf() ? LossRate : 0.0;
    Initialize(LossRates, InitialWater, DeadEdges);
}

void pwd::WaterModel::Initialize(const Eigen::VectorXd& LossRates,
                                 double InitialWater,
                                 const std::vector<std::pair<int, int>>& DeadEdges)
{
    // Compute an hash set of dead edges for fast computation
    std::unordered_set<std::pair<int, int>> DEMap;
    for (auto Edge : DeadEdges)
    {
        // Dead edges are symmetrically dead, of course
        if (DEMap.find(Edge) == DEMap.end())
            DEMap.insert(Edge);
        std::pair<int, int> InvEdge = { Edge.second, Edge.first };
        if (DEMap.find(InvEdge) == DEMap.end())
            DEMap.insert(InvEdge);
    }

    // Compute nodes properties
    Eigen::VectorXd Areas;      // node area
    Eigen::VectorXd Volumes;    // node volume
    Eigen::VectorXd FlowRes;    // node water flow resistance
    Areas.resize(m_Graph->NumNodes());
    Volumes.resize(m_Graph->NumNodes());
    FlowRes.resize(m_Graph->NumNodes());
    m_Water0.resize(m_Graph->NumNodes());
    for (int i = 0; i < m_Graph->NumNodes(); ++i)
    {
        const pwd::Node* N = m_Graph->GetNode(i);
        Areas[i] = N->Area();
        Volumes[i] = N->Volume();
        m_Water0[i] = Volumes[i];

        // Water flow resistence
        // Dynamic viscosity at room temperature is about 0.9
        double DynVisc = 0.9;
        double L = N->Length();
        double r4 = N->Radius() * N->Radius() * N->Radius() * N->Radius();
        // (mPa * s * cm) / cm^4
        // (mPa * s) / cm^3
        // (1e-6 * kPa * s) / cm^3
        // 1e-6 * (kPa * s) / cm^3
        // multiply by 1e6 to get (kPa * s) / cm^3
        FlowRes[i] = 1e6 * (M_PI * r4) / (8 * DynVisc * L);
    }
    // Rescale water
    m_Water0 *= InitialWater / m_Water0.sum();
    m_Water = m_Water0;


    // Create the adjacency matrix with inverse of water flows
    Eigen::MatrixXd Adj;
    Adj.resize(m_Graph->NumNodes(), m_Graph->NumNodes());
    Adj.setZero();
    for (int i = 0; i < m_Graph->NumNodes(); ++i)
    {
        const pwd::Node* N = m_Graph->GetNode(i);
        double FRes = 0.0;
        for (int ch = 0; ch < N->Degree(); ++ch)
        {
            int j = m_Graph->GetNodeID(N->GetAdjacent(ch));
            // If the connection is dead, ignore it
            if (DEMap.find({ i, j }) != DEMap.end())
                continue;
            // Otherwise, compute the average flow resistance and add it to the matrix
            double FResLoc = 0.5 * (FlowRes[i] + FlowRes[j]);
            FResLoc = 1.0 / FResLoc;
            Adj(i, j) = FResLoc;
            FRes += FResLoc;
        }
        if (FRes > 0.0)
            Adj(i, i) = -FRes;
    }

    // Compute the system matrix
    Eigen::MatrixXd S = Adj * (PRESS_CONST * Volumes).cwiseInverse().asDiagonal();
    S -= Eigen::SparseMatrix<double>(LossRates.cwiseProduct(Areas).asDiagonal());

    // Compute the eigendecomposition
    std::cout << "Generated ODE system has " << S.cols() << " variables." << std::endl;
    std::cout << "Solving the eigendecomposition..." << std::endl;
    std::chrono::system_clock::time_point Start, End;
    Start = std::chrono::system_clock::now();
    Eigen::EigenSolver<Eigen::MatrixXd> EigSolver;
    EigSolver.compute(S);
    m_Evals = EigSolver.eigenvalues();
    m_Evecs = EigSolver.eigenvectors();
    m_InvEvecs = m_Evecs.inverse();
    Eigen::MatrixXcd Diff = S - (m_Evecs * m_Evals.asDiagonal() * m_InvEvecs);
    End = std::chrono::system_clock::now();
    std::chrono::system_clock::duration ElapsTimeChrono = End - Start;
    unsigned long long ElapsTime;
    ElapsTime = std::chrono::duration_cast<std::chrono::microseconds>(ElapsTimeChrono).count();
    std::cout << "Elapsed time:        " << (ElapsTime / 1.0e6) << " seconds" << std::endl;
    std::cout << "Decomposition error: " << Diff.cwiseAbs2().sum() << std::endl;
}