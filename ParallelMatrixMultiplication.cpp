/*
	Concurrent Matrix Multiplication Example.
*/
#include <iostream>
#include <vector>
#include <thread>
#include <future>

using Matrix = std::vector<std::vector<int>>;

Matrix multiply(const Matrix& A, const Matrix& B) {
    int rows = A.size(), cols = B[0].size(), shared = B.size();
    Matrix result(rows, std::vector<int>(cols, 0));

    auto compute = [&](int start, int end) {
        for (int i = start; i < end; ++i)
            for (int j = 0; j < cols; ++j)
                for (int k = 0; k < shared; ++k)
                    result[i][j] += A[i][k] * B[k][j];
    };

    int mid = rows / 2;
    std::thread t1(compute, 0, mid);
    std::thread t2(compute, mid, rows);
    t1.join();
    t2.join();

    return result;
}

void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (int val : row)
            std::cout << val << " ";
        std::cout << "\n";
    }
}

int main() {
    Matrix A = {{1, 2, 3}, {4, 5, 6}};
    Matrix B = {{7, 8}, {9, 10}, {11, 12}};
    
    Matrix C = multiply(A, B);
    std::cout << "Matrix A x B = \n";
    printMatrix(C);

    return 0;
}
