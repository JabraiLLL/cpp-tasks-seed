#include "util.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }

    std::vector<std::vector<double>> rows;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::vector<double> row;
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            if (cell.empty()) continue;
            row.push_back(std::stod(cell));
        }

        if (!row.empty())
        {
            rows.push_back(row);
        }
    }

    if (rows.empty())
    {
        throw std::runtime_error("Empty CSV");
    }

    size_t cols = rows[0].size();
    for (const auto &row : rows)
    {
        if (row.size() != cols)
        {
            throw std::runtime_error("Ragged CSV");
        }
    }

    GaussMatrix matrix(rows.size(), cols);
    for (size_t i = 0; i < rows.size(); ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix(i, j) = rows[i][j];
        }
    }

    return matrix;
}

void print_matrix_as_csv(std::ostream& out, const GaussMatrix &matrix, int prec)
{
    out << std::fixed << std::setprecision(prec);
    for (int i = 0; i < matrix.rows(); ++i)
    {
        for (int j = 0; j < matrix.cols(); ++j)
        {
            if (j > 0) out << ',';
            out << matrix(i, j);
        }
        out << '\n';
    }
}

void print_vector_as_csv(std::ostream& out, const GaussVector &vector, int prec)
{
    out << "x\n";
    out << std::fixed << std::setprecision(prec);
    for (int i = 0; i < vector.rows(); ++i)
    {
        out << vector(i) << '\n';
    }
}