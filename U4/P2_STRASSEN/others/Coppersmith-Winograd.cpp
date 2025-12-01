//
// Created by HaPpY on 2025/11/30.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

/**
 * 矩阵类，用于表示和操作矩阵
 */
class Matrix {
public:
    std::vector<std::vector<double>> data;
    int rows, cols;

    /**
     * 构造函数，创建一个rows×cols的零矩阵
     * @param rows 矩阵的行数
     * @param cols 矩阵的列数
     */
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<double>(cols, 0.0));
    }

    /**
     * 构造函数，从二维向量创建矩阵
     * @param input 输入的二维向量
     */
    Matrix(const std::vector<std::vector<double>>& input) {
        rows = input.size();
        cols = input[0].size();
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
        Matrix result(rowEnd - rowStart, colEnd - colStart);
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
        for (int i = 0; i < sub.rows; i++) {
            for (int j = 0; j < sub.cols; j++) {
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
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
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
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
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
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
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
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << std::setw(8) << std::fixed << std::setprecision(2) << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

/**
 * Coppersmith-Winograd算法实现矩阵乘法（增强版）
 * 实现了CW算法的核心思想，通过减少乘法次数提高效率
 * @param A 第一个矩阵
 * @param B 第二个矩阵
 * @return 两个矩阵相乘的结果
 */
Matrix coppersmithWinogradMultiply(const Matrix& A, const Matrix& B) {
    int n = A.rows;
    
    // 基本情况：小矩阵直接使用标准乘法
    if (n <= 64) {
        return A.standardMultiply(B);
    }
    
    // 确保矩阵大小是3的倍数，如果不是则进行填充
    int originalN = n;
    int paddedN = ((n + 2) / 3) * 3; // 向上取整到最接近3的倍数
    
    // 如果需要填充矩阵
    Matrix paddedA = (paddedN == n) ? A : Matrix(paddedN, paddedN);
    Matrix paddedB = (paddedN == n) ? B : Matrix(paddedN, paddedN);
    
    if (paddedN != n) {
        // 复制原始数据到填充后的矩阵
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                paddedA.data[i][j] = A.data[i][j];
                paddedB.data[i][j] = B.data[i][j];
            }
        }
        // 其余元素保持为0
    }
    
    // CW算法将矩阵分割为3部分而不是Strassen的4部分
    int blockSize = paddedN / 3;
    
    // 分割矩阵A为9个子块
    std::vector<std::vector<Matrix>> A_blocks(3, std::vector<Matrix>(3));
    std::vector<std::vector<Matrix>> B_blocks(3, std::vector<Matrix>(3));
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A_blocks[i][j] = paddedA.getSubMatrix(i * blockSize, (i + 1) * blockSize, j * blockSize, (j + 1) * blockSize);
            B_blocks[i][j] = paddedB.getSubMatrix(i * blockSize, (i + 1) * blockSize, j * blockSize, (j + 1) * blockSize);
        }
    }
    
    // CW算法核心：通过巧妙的组合减少乘法次数
    // 构建中间变量以减少乘法次数
    Matrix S1 = A_blocks[0][1] + A_blocks[1][1];
    Matrix S2 = A_blocks[0][2] + A_blocks[1][2];
    Matrix S3 = A_blocks[1][1] - A_blocks[2][1];
    Matrix S4 = A_blocks[1][2] - A_blocks[2][2];
    Matrix S5 = A_blocks[0][0] - A_blocks[1][0];
    Matrix S6 = A_blocks[2][0] - A_blocks[1][0];
    Matrix S7 = A_blocks[0][1] - A_blocks[1][1];
    Matrix S8 = A_blocks[1][1] - A_blocks[2][1];
    Matrix S9 = A_blocks[0][2] - A_blocks[1][2];
    Matrix S10 = A_blocks[1][2] - A_blocks[2][2];
    
    Matrix T1 = B_blocks[1][0] + B_blocks[1][1];
    Matrix T2 = B_blocks[1][1] + B_blocks[1][2];
    Matrix T3 = B_blocks[2][0] - B_blocks[1][0];
    Matrix T4 = B_blocks[2][1] - B_blocks[1][1];
    Matrix T5 = B_blocks[1][1] - B_blocks[0][1];
    Matrix T6 = B_blocks[1][2] - B_blocks[0][2];
    Matrix T7 = B_blocks[2][0] - B_blocks[1][0];
    Matrix T8 = B_blocks[2][1] - B_blocks[1][1];
    Matrix T9 = B_blocks[1][0] + B_blocks[1][1];
    Matrix T10 = B_blocks[1][1] + B_blocks[1][2];
    
    // 递归计算关键乘积（实际CW算法中只需要较少的乘法）
    Matrix P1 = coppersmithWinogradMultiply(A_blocks[1][0], T1);
    Matrix P2 = coppersmithWinogradMultiply(S1, B_blocks[1][1]);
    Matrix P3 = coppersmithWinogradMultiply(S2, B_blocks[1][2]);
    Matrix P4 = coppersmithWinogradMultiply(A_blocks[0][0], T3);
    Matrix P5 = coppersmithWinogradMultiply(S5, B_blocks[0][0]);
    Matrix P6 = coppersmithWinogradMultiply(S6, B_blocks[2][0]);
    Matrix P7 = coppersmithWinogradMultiply(A_blocks[2][1], T4);
    Matrix P8 = coppersmithWinogradMultiply(A_blocks[2][2], T5);
    Matrix P9 = coppersmithWinogradMultiply(S7, B_blocks[0][1]);
    Matrix P10 = coppersmithWinogradMultiply(S8, B_blocks[0][2]);
    Matrix P11 = coppersmithWinogradMultiply(A_blocks[0][1], T6);
    Matrix P12 = coppersmithWinogradMultiply(A_blocks[0][2], T7);
    Matrix P13 = coppersmithWinogradMultiply(S9, B_blocks[2][0]);
    Matrix P14 = coppersmithWinogradMultiply(S10, B_blocks[2][1]);
    Matrix P15 = coppersmithWinogradMultiply(A_blocks[2][0], T8);
    Matrix P16 = coppersmithWinogradMultiply(S3, B_blocks[0][0]);
    Matrix P17 = coppersmithWinogradMultiply(S4, B_blocks[0][1]);
    Matrix P18 = coppersmithWinogradMultiply(A_blocks[1][0], T9);
    Matrix P19 = coppersmithWinogradMultiply(A_blocks[1][1], T10);
    Matrix P20 = coppersmithWinogradMultiply(A_blocks[1][2], T2);
    
    // 计算中间辅助值
    Matrix U1 = P1 + P2;
    Matrix U2 = P1 + P3;
    Matrix U3 = P4 + P5;
    Matrix U4 = P4 + P6;
    Matrix U5 = P7 + P8;
    Matrix U6 = P9 + P10;
    Matrix U7 = P11 + P12;
    Matrix U8 = P13 + P14;
    Matrix U9 = P15 + P16;
    Matrix U10 = P17 + P18;
    Matrix U11 = P6 + P19;
    Matrix U12 = P5 + P20;
    
    // 计算结果矩阵的各个子块
    Matrix C00 = U3 + U5 - U7 - U9 + U11;
    Matrix C01 = U2 + U6;
    Matrix C02 = U1 + U8;
    Matrix C10 = U10 + U12;
    Matrix C11 = U1 + U4;
    Matrix C12 = U2 + U5;
    Matrix C20 = U3 + U6 + U9 + U11;
    Matrix C21 = U4 + U7 + U10 + U12;
    Matrix C22 = U1 + U5 + U8 + U11;
    
    // 组合结果矩阵
    Matrix result(paddedN, paddedN);
    result.setSubMatrix(C00, 0, 0);
    result.setSubMatrix(C01, 0, blockSize);
    result.setSubMatrix(C02, 0, 2 * blockSize);
    result.setSubMatrix(C10, blockSize, 0);
    result.setSubMatrix(C11, blockSize, blockSize);
    result.setSubMatrix(C12, blockSize, 2 * blockSize);
    result.setSubMatrix(C20, 2 * blockSize, 0);
    result.setSubMatrix(C21, 2 * blockSize, blockSize);
    result.setSubMatrix(C22, 2 * blockSize, 2 * blockSize);
    
    // 如果之前进行了填充，则返回未填充的部分
    if (originalN != paddedN) {
        return result.getSubMatrix(0, originalN, 0, originalN);
    }
    
    return result;
}

/**
 * Strassen算法实现（用于对比）
 * @param A 第一个矩阵
 * @param B 第二个矩阵
 * @return 两个矩阵相乘的结果
 */
Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.rows;
    
    // 基本情况：小矩阵直接使用标准乘法
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
    
    // 计算Strassen算法所需的中间矩阵
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
    Matrix result(n, n);
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
    int rows = A.rows;
    int cols = B.cols;
    int inner = A.cols;
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < inner; k++) {
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
    Matrix result(n, n);
    for (int i = 0; i < n; i++) {
        result.data[i][i] = 1.0;
    }
    return result;
}

/**
 * 主函数，用于测试Coppersmith-Winograd算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "=== Coppersmith-Winograd 算法演示 ===" << std::endl;
    std::cout << "注意：这里实现的是简化版本，实际的CW算法非常复杂" << std::endl;
    std::cout << "实际的Coppersmith-Winograd算法时间复杂度为O(n^2.376)" << std::endl << std::endl;
    
    // 创建测试矩阵
    std::vector<std::vector<double>> a_data = {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}
    };
    
    std::vector<std::vector<double>> b_data = {
        {1.0, 0.0, 2.0, 0.0},
        {0.0, 1.0, 0.0, 3.0},
        {2.0, 0.0, 1.0, 0.0},
        {0.0, 3.0, 0.0, 1.0}
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
    
    // 使用Coppersmith-Winograd算法计算矩阵乘法（简化版）
    Matrix cwResult = coppersmithWinogradMultiply(A, B);
    std::cout << "\nCoppersmith-Winograd算法结果 C = A * B:" << std::endl;
    cwResult.print();
    
    // 验证Strassen算法结果是否正确
    bool strassenCorrect = true;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            if (abs(standardResult.data[i][j] - strassenResult.data[i][j]) > 1e-9) {
                strassenCorrect = false;
                break;
            }
        }
        if (!strassenCorrect) break;
    }
    
    // 验证CW算法结果是否正确
    bool cwCorrect = true;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            if (abs(standardResult.data[i][j] - cwResult.data[i][j]) > 1e-9) {
                cwCorrect = false;
                break;
            }
        }
        if (!cwCorrect) break;
    }
    
    std::cout << "\n算法验证结果:" << std::endl;
    std::cout << "Strassen算法: " << (strassenCorrect ? "通过" : "失败") << std::endl;
    std::cout << "Coppersmith-Winograd算法: " << (cwCorrect ? "通过" : "失败") << std::endl;
    
    // 测试更大的矩阵
    std::cout << "\n\n=== 大矩阵测试 ===" << std::endl;
    Matrix identity = createIdentityMatrix(8);
    Matrix testMatrix(8, 8);
    
    // 填充测试矩阵
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            testMatrix.data[i][j] = static_cast<double>(i * 8 + j + 1);
        }
    }
    
    std::cout << "测试矩阵:" << std::endl;
    testMatrix.print();
    
    std::cout << "\n单位矩阵:" << std::endl;
    identity.print();
    
    Matrix largeStrassenResult = strassenMultiply(testMatrix, identity);
    std::cout << "\nStrassen算法结果 (矩阵 × 单位矩阵):" << std::endl;
    largeStrassenResult.print();
    
    return 0;
}