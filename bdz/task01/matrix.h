#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

#include <iostream>
#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T data[N][M];

  size_t RowsNumber() const {
    return N;
  }
  size_t ColumnsNumber() const {
    return M;
  }

  T& operator()(size_t i, size_t j) {
    return data[i][j];
  }
  const T& operator()(size_t i, size_t j) const {
    return data[i][j];
  }
  T& At(size_t i, size_t j) {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange{};
    }
    return data[i][j];
  }
  const T& At(size_t i, size_t j) const {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange{};
    }
    return data[i][j];
  }

  Matrix<T, N, M> operator-() const;
  Matrix<T, N, M>& operator+=(const Matrix<T, N, M>&);
  Matrix<T, N, M>& operator-=(const Matrix<T, N, M>&);
  Matrix<T, N, M>& operator*=(const Matrix<T, M, M>&);
  Matrix<T, N, M>& operator*=(int);
  Matrix<T, N, M>& operator/=(int);
};

template <class T, size_t N, size_t M>
inline Matrix<T, N, M> Matrix<T, N, M>::operator-() const {
  Matrix<T, N, M> result{};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = -(*this)(i, j);
    }
  }
  return result;
}

// Matrix binary operators
template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& left, const Matrix<T, N, M>& right) {
  Matrix<T, N, M> result{};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = left(i, j) + right(i, j);
    }
  }
  return result;
}
template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(const Matrix<T, N, M>& left, const Matrix<T, N, M>& right) {
  Matrix<T, N, M> result{};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = left(i, j) - right(i, j);
    }
  }
  return result;
}
template <class T, size_t N, size_t M, size_t K>
Matrix<T, N, K> operator*(const Matrix<T, N, M>& left, const Matrix<T, M, K>& right) {
  Matrix<T, N, K> result{};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      result(i, j) = {};
      for (size_t s = 0; s < M; ++s) {
        result(i, j) += left(i, s) * right(s, j);
      }
    }
  }
  return result;
}
template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(const Matrix<T, N, M>& matrix, int scalar) {
  Matrix<T, N, M> result{};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = scalar * matrix(i, j);
    }
  }
  return result;
}
template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(int scalar, const Matrix<T, N, M>& matrix) {
  return matrix * scalar;
}
template <class T, size_t N, size_t M>
Matrix<T, N, M> operator/(const Matrix<T, N, M>& matrix, int scalar) {
  Matrix<T, N, M> result{};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = matrix(i, j) / scalar;
    }
  }
  return result;
}

// Matrix assigment operators
template <class T, size_t N, size_t M>
inline Matrix<T, N, M>& Matrix<T, N, M>::operator+=(const Matrix<T, N, M>& right) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      (*this)(i, j) += right(i, j);
    }
  }
  return *this;
}
template <class T, size_t N, size_t M>
inline Matrix<T, N, M>& Matrix<T, N, M>::operator-=(const Matrix<T, N, M>& right) {
  *this += -right;
  return *this;
}
template <class T, size_t N, size_t M>
inline Matrix<T, N, M>& Matrix<T, N, M>::operator*=(const Matrix<T, M, M>& right) {
  *this = *this * right;
  return *this;
}
template <class T, size_t N, size_t M>
inline Matrix<T, N, M>& Matrix<T, N, M>::operator*=(int scalar) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      (*this)(i, j) *= scalar;
    }
  }
  return *this;
}
template <class T, size_t N, size_t M>
inline Matrix<T, N, M>& Matrix<T, N, M>::operator/=(int scalar) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      (*this)(i, j) /= scalar;
    }
  }
  return *this;
}

// Compare operators
template <class T, size_t N, size_t M>
bool operator==(const Matrix<T, N, M>& left, const Matrix<T, N, M>& right) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (left(i, j) != right(i, j)) {
        return false;
      }
    }
  }
  return true;
}
template <class T, size_t N, size_t M>
bool operator!=(const Matrix<T, N, M>& left, const Matrix<T, N, M>& right) {
  return !(left == right);
}

// IO
template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M - 1; ++j) {
      out << matrix(i, j) << ' ';
    }
    out << matrix(i, M - 1);
    out << '\n';
  }
  return out;
}
template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      in >> matrix(i, j);
    }
  }
  return in;
}

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& matrix) {
  Matrix<T, M, N> result{};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(j, i) = matrix(i, j);
    }
  }
  return result;
}

// Extra

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Transpose(Matrix<T, N, M>& matrix)
  requires(N == M)
{
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < i; ++j) {
      std::swap(matrix(i, j), matrix(j, i));
    }
  }
  return matrix;
}

template <class T, size_t N>
T Trace(const Matrix<T, N, N>& matrix) {
  T res{};
  for (size_t i = 0; i < N; ++i) {
    res += matrix(i, i);
  }
  return res;
}

template <class T, size_t N>
T Determinant(const Matrix<T, N, N>& matrix) {
  Matrix temp = matrix;
  T det{};

  for (size_t i = 0; i < N - 1; i++) {
    for (size_t j = i + 1; j < N; j++) {
      for (size_t k = i + 1; k < N; k++) {
        temp(j, k) = (temp(j, k) * temp(i, i) - temp(j, i) * temp(i, k));
        if (i) {
          temp(j, k) /= temp(i - 1, i - 1);
        }
      }
    }
  }

  return temp(N - 1, N - 1);
}

template <class T, size_t N>
Matrix<T, N - 1, N - 1> GetMinor(const Matrix<T, N, N>& matrix, size_t ii, size_t jj) {
  Matrix<T, N - 1, N - 1> minor{};
  for (size_t i = 0; i < N; ++i) {
    if (i == ii) {
      continue;
    }
    for (size_t j = 0; j < N; ++j) {
      if (j == jj) {
        continue;
      }
      minor(i - (i > ii), j - (j > jj)) = matrix(i, j);
    }
  }
  return minor;
}

template <class T>
Matrix<T, 1, 1> GetInversed(const Matrix<T, 1, 1>& matrix) {
  return {1 / matrix(0, 0)};
}

template <class T, size_t N>
Matrix<T, N, N> GetInversed(const Matrix<T, N, N>& matrix) {
  T det{Determinant(matrix)};
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }

  Matrix<T, N, N> adjoint{};
  if (N == 1) {
    adjoint(0, 0) = matrix(0, 0) / det;
  } else {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        adjoint(i, j) = (((i + j) % 2 == 0) ? 1 : -1) * Determinant(GetMinor(matrix, i, j)) / det;
      }
    }
  }

  Transpose(adjoint);
  return adjoint;
}

template <class T, size_t N>
Matrix<T, N, N>& Inverse(Matrix<T, N, N>& matrix) {
  matrix = GetInversed(matrix);
  return matrix;
}

#endif