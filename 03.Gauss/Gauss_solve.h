#ifndef GAUSS_SOLVE_H
#define GAUSS_SOLVE_H

#include <Eigen/Dense>
#include <stdexcept>
#include <cmath>

using GaussMatrix = Eigen::MatrixXd;
using GaussVector = Eigen::VectorXd;

GaussVector Gauss_solve(GaussMatrix& ab);

#endif
