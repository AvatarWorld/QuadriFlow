#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_
#include "config.hpp"
#include "field-math.hpp"
#include "hierarchy.hpp"

class Optimizer {
   public:
    Optimizer();
    static void optimize_orientations(Hierarchy& mRes);
    static void optimize_scale(Hierarchy& mRes);
    static void optimize_positions(Hierarchy& mRes, int with_scale = 0);
    static void optimize_positions_fixed(Hierarchy& mRes, std::vector<DEdge>& edge_values,
                                         std::vector<Vector2i>& edge_diff, int with_scale = 0);
    static void optimize_integer_constraints(Hierarchy& mRes, std::map<int, int>& singularities);
    static void optimize_positions_dynamic(MatrixXi& F, MatrixXd& V, MatrixXd& N, MatrixXd& Q,
                                           std::vector<std::vector<int>>& Vset,
                                           std::vector<Vector3d>& O_compact,
                                           std::vector<Vector4i>& F_compact, VectorXi& V2E_compact,
                                           std::vector<int>& E2E_compact, double mScale);
#ifdef WITH_CUDA
    static void optimize_orientations_cuda(Hierarchy& mRes);
    static void optimize_positions_cuda(Hierarchy& mRes);
#endif
};

#ifdef WITH_CUDA
extern void UpdateOrientation(int* phase, int num_phases, glm::dvec3* N, glm::dvec3* Q, Link* adj,
                              int* adjOffset, int num_adj);
extern void PropagateOrientationUpper(glm::dvec3* srcField, int num_orientation,
                                      glm::ivec2* toUpper, glm::dvec3* N, glm::dvec3* destField);
extern void PropagateOrientationLower(glm::ivec2* toUpper, glm::dvec3* Q, glm::dvec3* N,
                                      glm::dvec3* Q_next, glm::dvec3* N_next, int num_toUpper);

extern void UpdatePosition(int* phase, int num_phases, glm::dvec3* N, glm::dvec3* Q, Link* adj,
                           int* adjOffset, int num_adj, glm::dvec3* V, glm::dvec3* O,
                           double scale);
extern void PropagatePositionUpper(glm::dvec3* srcField, int num_position, glm::ivec2* toUpper,
                                   glm::dvec3* N, glm::dvec3* V, glm::dvec3* destField);

#endif

#endif
