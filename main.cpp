#include <iostream>
#include <cstddef>

int* alloc_ints(const size_t size) {
  try {
    return new int[size];
  } catch (...) {
    return nullptr;
  }
}

int** alloc_ptrs(const size_t size) {
  try {
    return new int*[size];
  } catch (...) {
    return nullptr;
  }
}

void delete_matrix(int** matrix, const size_t n) {
  for (size_t i = 0; i < n; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** create_matrix(const size_t n, const size_t m) {
  int** matrix = alloc_ptrs(n);
  if (matrix == nullptr) {
    return nullptr;
  }
  for (size_t i = 0; i < n; ++i) {
    matrix[i] = alloc_ints(m);
    if (matrix[i] == nullptr) {
      delete_matrix(matrix, i);
      return nullptr;
    }
  }
  return matrix;
}

int main() {
  int n = 0;
  int m = 0;

  std::cout << "Введите количество строк и количество столбцов: " << std::endl;
  if (!(std::cin >> n >> m) || n <= 0 || m <= 0) {
    return 1;
  }

  int** matrix = create_matrix(n, m);
  if (matrix == nullptr) {
    return 2;
  }

  std::cout << "Введите элементы матрицы по строкам: " << std::endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!(std::cin >> matrix[i][j])) {
        delete_matrix(matrix, n);
        return 1;
      }
    }
  }

  std::cout << "Транспонированная матрица:" << std::endl;
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      if (i > 0) {
        std::cout << ' ';
      }
      std::cout << matrix[i][j];
    }
    std::cout << "\n";
  }

  delete_matrix(matrix, n);
  return 0;
}