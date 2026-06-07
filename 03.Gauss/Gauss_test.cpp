#include <gtest/gtest.h>
#include <cmath>
#include <random>
#include <stdexcept>
#include "Gauss_solve.h"

namespace
{
void expect_vector_near(const GaussVector &actual, const GaussVector &expected)
{
    ASSERT_EQ(actual.rows(), expected.rows());
    for (int i = 0; i < actual.rows(); ++i)
    {
        EXPECT_NEAR(actual(i), expected(i), 1e-8);
    }
}
} // namespace

TEST(GaussSolve, SolvesSmallSystem)
{
    GaussMatrix ab(2, 3);
    ab << 2.0, 1.0, 5.0,
          1.0, -1.0, 1.0;
    GaussVector expected(2);
    expected << 2.0, 1.0;
    expect_vector_near(Gauss_solve(ab), expected);
}

TEST(GaussSolve, UsesRowPivot)
{
    GaussMatrix ab(2, 3);
    ab << 0.0, 2.0, 4.0,
          1.0, 1.0, 3.0;
    GaussVector expected(2);
    expected << 1.0, 2.0;
    expect_vector_near(Gauss_solve(ab), expected);
}

TEST(GaussSolve, ThrowsForSingularMatrix)
{
    GaussMatrix ab(2, 3);
    ab << 1.0, 2.0, 3.0,
          2.0, 4.0, 6.0;
    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, SolvesGeneratedSystem)
{
    constexpr int n = 40;
    std::mt19937 gen(20250604U);
    std::uniform_real_distribution<double> dist(-5.0, 5.0);

    GaussMatrix a(n, n);
    for (int i = 0; i < n; ++i)
    {
        double row_sum = 0.0;
        for (int j = 0; j < n; ++j)
        {
            a(i, j) = dist(gen);
            row_sum += std::abs(a(i, j));
        }
        a(i, i) += row_sum + 1.0;
    }

    GaussVector expected(n);
    for (int i = 0; i < n; ++i)
    {
        expected(i) = dist(gen);
    }

    GaussMatrix ab(n, n + 1);
    ab.leftCols(n) = a;
    ab.col(n) = a * expected;

    expect_vector_near(Gauss_solve(ab), expected);
}