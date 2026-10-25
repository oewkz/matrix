#include <iostream>
#include <new>
#include <cstddef>

int** concat_rows(
    const int* const* lhs, std::size_t n1, std::size_t m1,
    const int* const* rhs, std::size_t n2, std::size_t m2)
{
    std::size_t n = n1;

    if (n2 > n1)
        n = n2;

    int** result = new int*[n]{};

    try
    {
        for (std::size_t i = 0; i < n; ++i)
        {
            std::size_t len1 = 0;
            std::size_t len2 = 0;

            if (i < n1)
                len1 = m1;

            if (i < n2)
                len2 = m2;

            result[i] = new int[len1 + len2];

            for (std::size_t j = 0; j < len1; ++j)
                result[i][j] = lhs[i][j];

            for (std::size_t j = 0; j < len2; ++j)
                result[i][len1 + j] = rhs[i][j];
        }
    }
    catch (const std::bad_alloc&)
    {
        for (std::size_t i = 0; i < n; ++i)
            delete[] result[i];

        delete[] result;
        throw;
    }

    return result;
}

int main()
{
    int** a = nullptr;
    int** b = nullptr;
    int** result = nullptr;

    int n1 = 0, m1 = 0;
    int n2 = 0, m2 = 0;
    int n = 0;
    int error = 0;

    try
    {
        // ввод первой матрицы
        std::cout << "Введите число строк и столбцов первой матрицы:\n";

        if (!(std::cin >> n1 >> m1) || n1 <= 0 || m1 <= 0)
            error = 1;

        if (error == 0)
        {
            a = new int*[n1]{};

            std::cout << "Введите элементы первой матрицы:\n";

            for (int i = 0; i < n1 && error == 0; ++i)
            {
                a[i] = new int[m1];

                for (int j = 0; j < m1 && error == 0; ++j)
                {
                    if (!(std::cin >> a[i][j]))
                        error = 1;
                }
            }
        }

        // ввод второй матрицы
        if (error == 0)
        {
            std::cout << "Введите число строк и столбцов второй матрицы:\n";

            if (!(std::cin >> n2 >> m2) || n2 <= 0 || m2 <= 0)
                error = 1;
        }

        if (error == 0)
        {
            b = new int*[n2]{};

            std::cout << "Введите элементы второй матрицы:\n";

            for (int i = 0; i < n2 && error == 0; ++i)
            {
                b[i] = new int[m2];

                for (int j = 0; j < m2 && error == 0; ++j)
                {
                    if (!(std::cin >> b[i][j]))
                        error = 1;
                }
            }
        }

        // создание и вывод результата
        if (error == 0)
        {
            result = concat_rows(a, n1, m1, b, n2, m2);

            n = n1;

            if (n2 > n1)
                n = n2;

            std::cout << "Результат:\n";

            for (int i = 0; i < n; ++i)
            {
                std::size_t length = 0;

                if (i < n1)
                    length += m1;

                if (i < n2)
                    length += m2;

                for (std::size_t j = 0; j < length; ++j)
                    std::cout << result[i][j] << ' ';

                std::cout << '\n';
            }
        }
    }
    catch (const std::bad_alloc&)
    {
        error = 2;
    }

    // освобождение памяти
    if (a != nullptr)
    {
        for (int i = 0; i < n1; ++i)
            delete[] a[i];

        delete[] a;
    }

    if (b != nullptr)
    {
        for (int i = 0; i < n2; ++i)
            delete[] b[i];

        delete[] b;
    }

    if (result != nullptr)
    {
        for (int i = 0; i < n; ++i)
            delete[] result[i];

        delete[] result;
    }

    return error;
}
