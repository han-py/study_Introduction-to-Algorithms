//
// Created by HaPpY on 2025/11/30.
//

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>

/**
 * 矩阵类，用于表示和操作矩阵
 */
class Matrix {
public:
    std::vector<std::vector<int>> data;
    int size;

    /**
     * 构造函数，创建一个n×n的零矩阵
     * @param n 矩阵的大小
     */
    Matrix(int n) : size(n) {
        data.resize(n, std::vector<int>(n, 0));
    }

    /**
     * 构造函数，从二维向量创建矩阵
     * @param input 输入的二维向量
     */
    Matrix(const std::vector<std::vector<int>>& input) {
        size = input.size();
        data = input;
    }

    /**
     * 获取子矩阵
     * @param rowStart 行起始索引
     * @param rowEnd 行结束索引
     * @param colStart 列起始索引
     * @param colEnd 列结束索引
     * @return 子矩阵
     */
    Matrix getSubMatrix(int rowStart, int rowEnd, int colStart, int colEnd) const {
        Matrix result(rowEnd - rowStart);
        for (int i = rowStart; i < rowEnd; i++) {
            for (int j = colStart; j < colEnd; j++) {
                result.data[i - rowStart][j - colStart] = data[i][j];
            }
        }
        return result;
    }

    /**
     * 设置子矩阵
     * @param sub 子矩阵
     * @param rowStart 行起始索引
     * @param colStart 列起始索引
     */
    void setSubMatrix(const Matrix& sub, int rowStart, int colStart) {
        for (int i = 0; i < sub.size; i++) {
            for (int j = 0; j < sub.size; j++) {
                data[i + rowStart][j + colStart] = sub.data[i][j];
            }
        }
    }

    /**
     * 矩阵加法运算符重载
     * @param other 另一个矩阵
     * @return 两个矩阵相加的结果
     */
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    /**
     * 矩阵减法运算符重载
     * @param other 另一个矩阵
     * @return 两个矩阵相减的结果
     */
    Matrix operator-(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    /**
     * 标准矩阵乘法（用于小矩阵）
     * @param other 另一个矩阵
     * @return 两个矩阵相乘的结果
     */
    Matrix standardMultiply(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    /**
     * 打印矩阵
     */
    void print() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << std::setw(6) << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

/**
 * Strassen算法实现矩阵乘法
 * @param A 第一个矩阵
 * @param B 第二个矩阵
 * @return 两个矩阵相乘的结果
 */
Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size;
    
    // 基本情况：1x1矩阵直接相乘
    if (n == 1) {
        Matrix result(1);
        result.data[0][0] = A.data[0][0] * B.data[0][0];
        return result;
    }
    
    // 对于小矩阵，使用标准算法以避免递归开销
    if (n <= 64) {
        return A.standardMultiply(B);
    }
    
    // 将矩阵划分为四个子矩阵
    int half = n / 2;
    Matrix A11 = A.getSubMatrix(0, half, 0, half);
    Matrix A12 = A.getSubMatrix(0, half, half, n);
    Matrix A21 = A.getSubMatrix(half, n, 0, half);
    Matrix A22 = A.getSubMatrix(half, n, half, n);
    
    Matrix B11 = B.getSubMatrix(0, half, 0, half);
    Matrix B12 = B.getSubMatrix(0, half, half, n);
    Matrix B21 = B.getSubMatrix(half, n, 0, half);
    Matrix B22 = B.getSubMatrix(half, n, half, n);
    
    // 计算Strassen算法所需的10个中间矩阵（加减法）
    Matrix S1 = B12 - B22;
    Matrix S2 = A11 + A12;
    Matrix S3 = A21 + A22;
    Matrix S4 = B21 - B11;
    Matrix S5 = A11 + A22;
    Matrix S6 = B11 + B22;
    Matrix S7 = A12 - A22;
    Matrix S8 = B21 + B22;
    Matrix S9 = A11 - A21;
    Matrix S10 = B11 + B12;
    
    // 递归计算Strassen算法所需的7个乘积
    Matrix P1 = strassenMultiply(A11, S1);
    Matrix P2 = strassenMultiply(S2, B22);
    Matrix P3 = strassenMultiply(S3, B11);
    Matrix P4 = strassenMultiply(A22, S4);
    Matrix P5 = strassenMultiply(S5, S6);
    Matrix P6 = strassenMultiply(S7, S8);
    Matrix P7 = strassenMultiply(S9, S10);
    
    // 通过7个乘积计算结果矩阵的四个子块
    Matrix C11 = P5 + P4 - P2 + P6;
    Matrix C12 = P1 + P2;
    Matrix C21 = P3 + P4;
    Matrix C22 = P5 + P1 - P3 - P7;
    
    // 合并四个子矩阵得到最终结果
    Matrix result(n);
    result.setSubMatrix(C11, 0, 0);
    result.setSubMatrix(C12, 0, half);
    result.setSubMatrix(C21, half, 0);
    result.setSubMatrix(C22, half, half);
    
    return result;
}

/**
 * 标准矩阵乘法（用于对比验证）
 * @param A 第一个矩阵
 * @param B 第二个矩阵
 * @return 两个矩阵相乘的结果
 */
Matrix standardMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size;
    Matrix result(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
    return result;
}

/**
 * 创建一个单位矩阵
 * @param n 矩阵大小
 * @return n×n的单位矩阵
 */
Matrix createIdentityMatrix(int n) {
    Matrix result(n);
    for (int i = 0; i < n; i++) {
        result.data[i][i] = 1;
    }
    return result;
}

/**
 * 主函数，用于测试Strassen算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    // 创建测试矩阵
    std::vector<std::vector<int>> a_data = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    std::vector<std::vector<int>> b_data = {
        {1, 0, 2, 0},
        {0, 1, 0, 3},
        {2, 0, 1, 0},
        {0, 3, 0, 1}
    };
    
    Matrix A(a_data);
    Matrix B(b_data);
    
    std::cout << "矩阵 A:" << std::endl;
    A.print();
    
    std::cout << "\n矩阵 B:" << std::endl;
    B.print();
    
    // 使用标准算法计算矩阵乘法（用于验证）
    Matrix standardResult = standardMultiply(A, B);
    std::cout << "\n标准算法结果 C = A * B:" << std::endl;
    standardResult.print();
    
    // 使用Strassen算法计算矩阵乘法
    Matrix strassenResult = strassenMultiply(A, B);
    std::cout << "\nStrassen算法结果 C = A * B:" << std::endl;
    strassenResult.print();
    
    // 验证两种算法结果是否相同
    bool isCorrect = true;
    for (int i = 0; i < A.size; i++) {
        for (int j = 0; j < A.size; j++) {
            if (standardResult.data[i][j] != strassenResult.data[i][j]) {
                isCorrect = false;
                break;
            }
        }
        if (!isCorrect) break;
    }
    
    std::cout << "\n算法验证: " << (isCorrect ? "通过" : "失败") << std::endl;
    
    // 测试更大的矩阵
    std::cout << "\n\n=== 大矩阵测试 ===" << std::endl;
    Matrix identity = createIdentityMatrix(8);
    Matrix testMatrix(8);
    
    // 填充测试矩阵
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            testMatrix.data[i][j] = i * 8 + j + 1;
        }
    }
    
    std::cout << "测试矩阵:" << std::endl;
    testMatrix.print();
    
    std::cout << "\n单位矩阵:" << std::endl;
    identity.print();
    
    Matrix largeResult = strassenMultiply(testMatrix, identity);
    std::cout << "\nStrassen算法结果 (矩阵 × 单位矩阵):" << std::endl;
    largeResult.print();
    
    return 0;
}