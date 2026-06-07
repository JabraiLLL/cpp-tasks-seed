#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    const int n = static_cast<int>(ab.rows());
    if (n == 0 || ab.cols() != n + 1)
    {
        throw std::invalid_argument("invalid augmented matrix size");
    }

    constexpr double eps = 1e-12;

    for (int col = 0; col < n; ++col)
    {
        int pivot_row = col;
        double pivot_abs = std::abs(ab(col, col));
        for (int row = col + 1; row < n; ++row)
        {
            const double value_abs = std::abs(ab(row, col));
            if (value_abs > pivot_abs)
            {
                pivot_abs = value_abs;
                pivot_row = row;
            }
        }

        if (pivot_abs < eps)
        {
            throw std::runtime_error("singular matrix");
        }

        if (pivot_row != col)
        {
            ab.row(col).swap(ab.row(pivot_row));
        }

        for (int row = col + 1; row < n; ++row)
        {
            const double factor = ab(row, col) / ab(col, col);
            ab.row(row) -= factor * ab.row(col);
            ab(row, col) = 0.0;
        }
    }

    GaussVector x(n);
    for (int row = n - 1; row >= 0; --row)
    {
        double rhs = ab(row, n);
        if (row + 1 < n)
        {
            rhs -= ab.row(row).segment(row + 1, n - row - 1).dot(x.segment(row + 1, n - row - 1));
        }
        x(row) = rhs / ab(row, row);
    }

    return x;
}