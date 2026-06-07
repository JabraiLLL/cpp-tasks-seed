#ifndef GAUSS_UTIL_H
#define GAUSS_UTIL_H

#include <iostream>
#include <iomanip>
#include <Eigen/Dense>

using GaussVector = Eigen::VectorXd;
using GaussMatrix = Eigen::Matrix<double, -1, -1, Eigen::RowMajor>;

GaussMatrix load_csv_to_matrix(const char *filename);
void print_matrix_as_csv(std::ostream& out, const GaussMatrix &matrix, int prec = 6);
void print_vector_as_csv(std::ostream& out, const GaussVector &vector, int prec = 6);

#endif