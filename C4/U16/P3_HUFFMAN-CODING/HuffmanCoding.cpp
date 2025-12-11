//
// Created by HaPpY on 2025/12/11.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip>

/**
 * 霍夫曼树节点结构
 */
struct HuffmanNode {
    char data;                     // 字符数据
    int frequency;                 // 字符频率
    HuffmanNode* left;             // 左子树
    HuffmanNode* right;            // 右子树
    
    // 构造函数
    HuffmanNode(char data, int frequency) 
        : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
    
    // 比较函数，用于优先队列（最小堆）
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
};

/**
 * 霍夫曼编码表项结构
 */
struct HuffmanCode {
    char character;                // 字符
    int frequency;                 // 频率
    std::string code;              // 对应的霍夫曼编码
    
    HuffmanCode(char ch, int freq, const std::string& c)
        : character(ch), frequency(freq), code(c) {}
};

/**
 * 比较函数，用于优先队列
 */
struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

/**
 * 递归构建霍夫曼编码表
 * 
 * @param root 霍夫曼树根节点
 * @param code 当前编码
 * @param huffmanCodeTable 霍夫曼编码表
 */
void buildHuffmanCodeTable(HuffmanNode* root, const std::string& code, 
                          std::unordered_map<char, std::string>& huffmanCodeTable) {
    if (!root) return;
    
    // 如果是叶子节点，保存字符对应的编码
    if (!root->left && !root->right) {
        huffmanCodeTable[root->data] = code;
    }
    
    // 递归构建左子树和右子树的编码
    buildHuffmanCodeTable(root->left, code + "0", huffmanCodeTable);
    buildHuffmanCodeTable(root->right, code + "1", huffmanCodeTable);
}

/**
 * 构建霍夫曼树
 * 
 * @param frequencies 字符频率表
 * @return 霍夫曼树根节点
 */
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& frequencies) {
    // 创建优先队列（最小堆）
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;
    
    // 为每个字符创建叶子节点并加入优先队列
    for (const auto& pair : frequencies) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // 当队列中节点数量大于1时，不断合并节点
    while (minHeap.size() > 1) {
        // 取出频率最小的两个节点
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();
        
        // 创建新的内部节点，频率为两个子节点频率之和
        int sum = left->frequency + right->frequency;
        HuffmanNode* newNode = new HuffmanNode('\0', sum);
        newNode->left = left;
        newNode->right = right;
        
        // 将新节点加入优先队列
        minHeap.push(newNode);
    }
    
    // 返回霍夫曼树根节点
    return minHeap.top();
}

/**
 * 生成霍夫曼编码表
 * 
 * @param root 霍夫曼树根节点
 * @return 霍夫曼编码表
 */
std::unordered_map<char, std::string> generateHuffmanCodes(HuffmanNode* root) {
    std::unordered_map<char, std::string> huffmanCodeTable;
    buildHuffmanCodeTable(root, "", huffmanCodeTable);
    return huffmanCodeTable;
}

/**
 * 使用霍夫曼编码压缩文本
 * 
 * @param text 原始文本
 * @param huffmanCodeTable 霍夫曼编码表
 * @return 压缩后的二进制字符串
 */
std::string encodeText(const std::string& text, 
                      const std::unordered_map<char, std::string>& huffmanCodeTable) {
    std::string encodedText = "";
    for (char ch : text) {
        encodedText += huffmanCodeTable.at(ch);
    }
    return encodedText;
}

/**
 * 使用霍夫曼编码解压缩文本
 * 
 * @param encodedText 压缩后的二进制字符串
 * @param root 霍夫曼树根节点
 * @return 解压后的原始文本
 */
std::string decodeText(const std::string& encodedText, HuffmanNode* root) {
    std::string decodedText = "";
    HuffmanNode* currentNode = root;
    
    for (char bit : encodedText) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
        
        // 如果到达叶子节点，添加对应字符到结果中
        if (!currentNode->left && !currentNode->right) {
            decodedText += currentNode->data;
            currentNode = root;  // 重新从根节点开始
        }
    }
    
    return decodedText;
}

/**
 * 计算字符频率
 * 
 * @param text 输入文本
 * @return 字符频率表
 */
std::unordered_map<char, int> calculateFrequency(const std::string& text) {
    std::unordered_map<char, int> frequencies;
    for (char ch : text) {
        frequencies[ch]++;
    }
    return frequencies;
}

/**
 * 打印字符频率表
 * 
 * @param frequencies 字符频率表
 */
void printFrequencyTable(const std::unordered_map<char, int>& frequencies) {
    std::cout << "字符频率表:" << std::endl;
    std::cout << "字符\t频率" << std::endl;
    std::cout << "--------------" << std::endl;
    for (const auto& pair : frequencies) {
        if (pair.first == ' ') {
            std::cout << "空格\t" << pair.second << std::endl;
        } else {
            std::cout << pair.first << "\t" << pair.second << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * 打印霍夫曼编码表
 * 
 * @param huffmanCodes 霍夫曼编码表
 */
void printHuffmanCodeTable(const std::unordered_map<char, std::string>& huffmanCodes) {
    std::cout << "霍夫曼编码表:" << std::endl;
    std::cout << "字符\t编码\t长度" << std::endl;
    std::cout << "------------------" << std::endl;
    for (const auto& pair : huffmanCodes) {
        if (pair.first == ' ') {
            std::cout << "空格\t" << pair.second << "\t" << pair.second.length() << std::endl;
        } else {
            std::cout << pair.first << "\t" << pair.second << "\t" << pair.second.length() << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * 打印霍夫曼树（中序遍历）
 * 
 * @param root 霍夫曼树根节点
 * @param indent 缩进字符
 */
void printHuffmanTree(HuffmanNode* root, const std::string& indent = "") {
    if (!root) return;
    
    if (!root->left && !root->right) {
        // 叶子节点
        if (root->data == ' ') {
            std::cout << indent << "叶子: 空格 (频率: " << root->frequency << ")" << std::endl;
        } else {
            std::cout << indent << "叶子: " << root->data << " (频率: " << root->frequency << ")" << std::endl;
        }
    } else {
        // 内部节点
        std::cout << indent << "内部节点 (频率: " << root->frequency << ")" << std::endl;
        if (root->left) {
            std::cout << indent << "├─ 0: ";
            printHuffmanTree(root->left, indent + "│  ");
        }
        if (root->right) {
            std::cout << indent << "└─ 1: ";
            printHuffmanTree(root->right, indent + "   ");
        }
    }
}

/**
 * 释放霍夫曼树内存
 * 
 * @param root 霍夫曼树根节点
 */
void deleteHuffmanTree(HuffmanNode* root) {
    if (!root) return;
    deleteHuffmanTree(root->left);
    deleteHuffmanTree(root->right);
    delete root;
}

/**
 * 主函数 - 演示霍夫曼编码算法
 */
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    std::cout << "==============================================" << std::endl;
    std::cout << "           霍夫曼编码算法演示程序" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "算法描述：" << std::endl;
    std::cout << "霍夫曼编码是一种用于无损数据压缩的贪心算法。" << std::endl;
    std::cout << "它根据字符出现频率构建最优二叉树，频率高的字符" << std::endl;
    std::cout << "使用较短的编码，频率低的字符使用较长的编码。" << std::endl;
    std::cout << "==============================================" << std::endl << std::endl;
    
    // 示例文本
    std::string text = "ABRACADABRA";
    
    std::cout << "原始文本: \"" << text << "\"" << std::endl << std::endl;
    
    // 计算字符频率
    std::unordered_map<char, int> frequencies = calculateFrequency(text);
    printFrequencyTable(frequencies);
    
    // 构建霍夫曼树
    std::cout << "构建霍夫曼树..." << std::endl;
    HuffmanNode* root = buildHuffmanTree(frequencies);
    
    // 打印霍夫曼树结构
    std::cout << "霍夫曼树结构:" << std::endl;
    printHuffmanTree(root);
    std::cout << std::endl;
    
    // 生成霍夫曼编码表
    std::unordered_map<char, std::string> huffmanCodes = generateHuffmanCodes(root);
    printHuffmanCodeTable(huffmanCodes);
    
    // 编码文本
    std::string encodedText = encodeText(text, huffmanCodes);
    std::cout << "编码后的文本: " << encodedText << std::endl;
    std::cout << "编码后长度: " << encodedText.length() << " 位" << std::endl << std::endl;
    
    // 解码文本
    std::string decodedText = decodeText(encodedText, root);
    std::cout << "解码后的文本: \"" << decodedText << "\"" << std::endl;
    
    // 验证编码解码正确性
    if (text == decodedText) {
        std::cout << "✅ 编码解码成功！原始文本与解码文本一致。" << std::endl;
    } else {
        std::cout << "❌ 编码解码失败！原始文本与解码文本不一致。" << std::endl;
    }
    
    // 计算压缩率
    int originalBits = text.length() * 8;  // 假设ASCII编码，每个字符8位
    int compressedBits = encodedText.length();
    double compressionRatio = (double)(originalBits - compressedBits) / originalBits * 100;
    
    std::cout << std::endl << "压缩效果分析:" << std::endl;
    std::cout << "原始文本大小: " << originalBits << " 位" << std::endl;
    std::cout << "压缩后大小: " << compressedBits << " 位" << std::endl;
    std::cout << "压缩率: " << std::fixed << std::setprecision(2) << compressionRatio << "%" << std::endl << std::endl;
    
    // 释放内存
    deleteHuffmanTree(root);
    
    std::cout << "==============================================" << std::endl;
    std::cout << "           算法执行完毕！" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    return 0;
}