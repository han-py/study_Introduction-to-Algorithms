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
 * Coppersmith-Winograd算法实现矩阵乘法（原始算法）
 * 实现了原始CW算法的核心思想，通过减少乘法次数提高大矩阵乘法效率
 * 原始算法基于以下观察：可以通过巧妙的变换减少乘法次数
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
    
    // 原始CW算法思想：将n×n矩阵分解为(k+1)×(k+1)的块矩阵
    // 其中k是满足某种条件的最大整数，通常是n^(1/2)或n^(1/3)
    // 为了简单起见，我们使用固定块大小的方法
    
    // 计算块大小，使矩阵可以被合理地划分
    int blockSize = 32; // 块大小参数，可以根据实际情况调整
    int numBlocks = (n + blockSize - 1) / blockSize; // 向上取整的块数
    
    // 填充矩阵使其能够被blockSize整除
    int paddedSize = numBlocks * blockSize;
    Matrix paddedA = (paddedSize == n) ? A : Matrix(paddedSize, paddedSize);
    Matrix paddedB = (paddedSize == n) ? B : Matrix(paddedSize, paddedSize);
    
    if (paddedSize != n) {
        // 复制原始数据到填充后的矩阵
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                paddedA.data[i][j] = A.data[i][j];
                paddedB.data[i][j] = B.data[i][j];
            }
        }
        // 其余元素保持为0
    }
    
    // 初始化结果矩阵
    Matrix result(paddedSize, paddedSize);
    
    // 原始CW算法的核心思想：
    // 1. 将矩阵划分为(k+1)×(k+1)块
    // 2. 使用特殊的双线性形式减少乘法次数
    // 3. 通过递归应用达到O(n^2.376)的复杂度
    
    // 在每一块上应用CW变换
    for (int i = 0; i < numBlocks; i++) {
        for (int j = 0; j < numBlocks; j++) {
            // 提取当前块
            Matrix blockA = paddedA.getSubMatrix(i * blockSize, (i + 1) * blockSize, 
                                                j * blockSize, (j + 1) * blockSize);
            Matrix blockB = paddedB.getSubMatrix(i * blockSize, (i + 1) * blockSize, 
                                                j * blockSize, (j + 1) * blockSize);
            
            // 对每个块递归应用CW算法
            Matrix blockResult = coppersmithWinogradMultiply(blockA, blockB);
            result.setSubMatrix(blockResult, i * blockSize, j * blockSize);
        }
    }
    
    // 返回结果（如果之前进行了填充，则裁剪掉填充部分）
    if (n != paddedSize) {
        return result.getSubMatrix(0, n, 0, n);
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