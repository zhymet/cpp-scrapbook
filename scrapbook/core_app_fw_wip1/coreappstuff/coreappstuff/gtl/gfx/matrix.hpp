#ifndef PPP_MATRIX_HPP
#define PPP_MATRIX_HPP

#include <array>
#include <algorithm>
#include <functional>

#include "../core/shortcuts.hpp"
#include "../core/requires.hpp"
namespace gtl::gfx {
    template<req::Arithmetic_ ArithT, std::size_t N_ROW, std::size_t N_COL>
    class matrix {
        using value_type = ArithT;
        using size_type = std::size_t;
        using data_rows_type = std::integral_constant<size_type, N_ROW>;
        using data_cols_type = std::integral_constant<size_type, N_COL>;
        using data_size_type = std::integral_constant<size_type, N_ROW* N_COL>;
    public:
        __CXSIN typename data_rows_type::type data_size = data_size_type::value;
        __CXSIN typename data_rows_type::type data_rows = data_rows_type::value;
        __CXSIN typename data_rows_type::type data_cols = data_cols_type::value;
    private:
        std::array<value_type, data_size> data_;
    public:

        // Return the size of the underlying array holding the values
        __CXSIN size_type size() {
            return data_size;
        }

        // Return the dimensions of the matrix as (rows, columns)
        __CXSIN std::pair<size_type, size_type> dim() {
            return std::make_pair(data_rows, data_cols);
        }

        // Return true if the amount of rows is equal to the amount of columns
        __CXSIN bool is_square() {
            return data_rows == data_cols;
        };

        // Returns a reference to a value in the matrix given a row and column ( Row-Major )
        __CXIN value_type& at(size_type row, size_type col) {
            return data_[row * data_rows + col];
        }

        // Returns a copy of a value in the matrix given a row and column ( Row-Major )
        __CXIN value_type get(size_type row, size_type col) const {
            return data_[row * data_rows + col];
        }

        /// <@operator> +
        /// <@requires> Matrices must be of equal dimensions.
        /// <@brief> Perform matrix addition
        /// <@out> Matrix of equal dimensions with all the values of rhs summed with their respective value in this.
        matrix<value_type, data_rows, data_cols> operator+(const matrix<value_type, data_rows, data_cols>& rhs) {
            matrix<value_type, data_rows, data_cols> ret_val = *this;
            std::transform(data_.begin(), data_.end(), rhs.data_.begin(), ret_val.data_.begin()
                , [](const value_type& l, const value_type& r) { return l + r; });
            return ret_val;
        }

        /// <@operator> +
        /// <@requires> Matrices must be of equal dimensions.
        /// <@brief> Perform matrix subtraction
        /// <@out> Matrix of equal dimensions with the differences between each value in this matrix and
        ///        their respective value in the rhs matrix.
        matrix<value_type, data_rows, data_cols> operator-(const matrix<value_type, data_rows, data_cols>& rhs) {
            matrix<value_type, data_rows, data_cols> ret_val = *this;
            std::transform(data_.begin(), data_.end(), rhs.data_.begin(), ret_val.data_.begin()
                , [](const value_type& l, const value_type& r) { return l - r; });
            return ret_val;
        }

        /// <@operator> *
        /// <@requires> The number of columns of the 1st matrix must equal the number of rows of the 2nd matrix.
        /// <@requires> Column size GREATER OR EQUAL to row_size
        /// <@out> The result will have the same number of rows as the 1st matrix,
        ///        and the same number of columns as the 2nd matrix.
        /// TODO: Optimize for unrolled loop case where DATA_SIZE < UNROLL_LIMIT
        /// TODO: Optimize for square matrix case where DATA_ROWS == rhs.DATA_COLS &&  DATA_COLS == rhs.DATA_ROWS
        template<typename data_rows_type::value_type RHS_ROWS, typename data_cols_type::value_type RHS_COLS>
        requires (data_cols == RHS_ROWS)
            constexpr auto operator*(const matrix<value_type, RHS_ROWS, RHS_COLS>& rhs) {
            matrix<value_type, data_rows, RHS_COLS> ret_val{};
            // https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
            // using the iterative matrix multiplication algorithm
            for (std::size_t i = 0u; i < data_rows; ++i) {
                for (std::size_t j = 0u; j < rhs.data_cols; ++j) {
                    auto& this_idx_dot = ret_val.data_[i * data_rows + j]; // ref to index where to sum the dot product
                    for (std::size_t k = 0u; k < data_cols; ++k) {
                        this_idx_dot += data_[i * data_cols + k] * rhs.data_[k * rhs.data_cols + j];
                    }
                }
            }
            return ret_val;
        }


    };

}
#endif //PPP_MATRIX_HPP
